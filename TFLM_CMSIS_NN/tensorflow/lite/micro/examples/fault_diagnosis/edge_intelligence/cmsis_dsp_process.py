# The idea is to follow as closely as possible the C CMSIS-DSP API to ease the migration to the final implementation on a board.
import numpy as np
import pandas as pd
import cmsisdsp as dsp
import matplotlib.pyplot as plt
import tensorflow as tf

from joblib import dump, load
#from numpy.polynomial import Polynomial

# Obtain frequency sequence
def fftfreq(N, sampling_rate):
    frequencies = []
    for k in range(N):
        if k < N // 2:
            frequencies.append(k * (sampling_rate / N))
        else:
            frequencies.append((k - N) * (sampling_rate / N))
    return np.array(frequencies)

# Array of complex numbers as an array of real numbers
def imToReal1D(a):
    ar=np.zeros(np.array(a.shape) * 2)
    ar[0::2]=a.real
    ar[1::2]=a.imag
    return(ar)

def data_preprocess(signal):
    #remove trend
    signal = signal - dsp.arm_mean_f32(signal)
    
    ## IIR butterworth high-pass 4-order filter
    biquadf32 = dsp.arm_biquad_casd_df1_inst_f32()
    numStages = 2 
    state = np.zeros(numStages*4)
    # By MATLAB
    scale_values = 0.995174909795582540716907260502921417356 * 0.988484701982508928708170969912316650152
    # The high-pass filter coefficient is obtained from the C language header file using MATLAB FADTOOL, and remember a1 and a2 are inverse
    coefs = [1.0, -2.0, 1.0, 1.990271241661728529592778613732662051916, -0.990428397520601744297152890794677659869,
             1.0, -2.0, 1.0, 1.976891354287120039501246537838596850634, -0.977047453642915675331437341810669749975]
    dsp.arm_biquad_cascade_df1_init_f32(biquadf32, numStages, coefs, state)
    pre_signal = dsp.arm_biquad_cascade_df1_f32(biquadf32, signal)
    pre_signal *= scale_values;
    return pre_signal

# Extract vibration signals features based time domain 
def extract_time_domain_features(signal):
    p1 = dsp.arm_absmax_f32(signal)[0] #max absolute value
    p2 = dsp.arm_absmin_f32(signal)[0] #min absolute value
    p3 = dsp.arm_mean_f32(dsp.arm_abs_f32(signal)) #absolute mean value/average amplitude
    p4 = p1 - p2 #peak to peak value
    p5 = dsp.arm_mean_f32(signal) #mean value
    p6 = dsp.arm_rms_f32(signal) #root mean square
    p7 = (dsp.arm_mean_f32([index1[1] for index1 in [dsp.arm_sqrt_f32(index) for index in dsp.arm_abs_f32(signal)]])) * (
        dsp.arm_mean_f32([index1[1] for index1 in [dsp.arm_sqrt_f32(index) for index in dsp.arm_abs_f32(signal)]])) #square root amplitude
    p8 = dsp.arm_std_f32(signal) #standard deviation
    p9 = dsp.arm_mean_f32(dsp.arm_mult_f32(dsp.arm_mult_f32(signal,signal), signal)) #skewness
    p10 = dsp.arm_mean_f32(dsp.arm_mult_f32(dsp.arm_mult_f32(dsp.arm_mult_f32(signal,signal), signal), signal)) #kurtosis
    p11 = dsp.arm_var_f32(signal) #variance
    p12 = p1 / p7 #margin/clearance factor
    p13 = p8 / p3 #Waveform Factor
    p14 = p6 / p3 #wave/shape factor
    p15 = p1 / p6 #crest/peak factor
    p16 = p1 / p3 #impulse factor
    p17 = p9 / ((dsp.arm_mult_f32(dsp.arm_mult_f32(dsp.arm_sqrt_f32(p11), dsp.arm_sqrt_f32(p11)), dsp.arm_sqrt_f32(p11)))[1]) #skewness coefficient
    p18 = p10 / ((dsp.arm_mult_f32(dsp.arm_sqrt_f32(p11), dsp.arm_sqrt_f32(p11)))[1]) #kurtosis coefficient
    p19 = dsp.arm_entropy_f32(dsp.arm_abs_f32(signal)) #entropy
    
    feature_matrix = np.zeros((1, 19))  
    feature_matrix[0, 0] = p1
    feature_matrix[0, 1] = p2
    feature_matrix[0, 2] = p3
    feature_matrix[0, 3] = p4
    feature_matrix[0, 4] = p5
    feature_matrix[0, 5] = p6
    feature_matrix[0, 6] = p7
    feature_matrix[0, 7] = p8
    feature_matrix[0, 8] = p9
    feature_matrix[0, 9] = p10
    feature_matrix[0, 10] = p11
    feature_matrix[0, 11] = p12
    feature_matrix[0, 12] = p13
    feature_matrix[0, 13] = p14
    feature_matrix[0, 14] = p15
    feature_matrix[0, 15] = p16
    feature_matrix[0, 16] = p17
    feature_matrix[0, 17] = p18
    feature_matrix[0, 18] = p19

    return feature_matrix
    
# Extract vibration acceleration signals features based frequency domain features 
def extract_frequency_domain_features(signal):    
    N = len(signal) #length of the signal
    Fs = 12000 #sampling frequency
    rfftf32=dsp.arm_rfft_fast_instance_f32()
    dsp.arm_rfft_fast_init_f32(rfftf32,N)
    rfft_result = dsp.arm_rfft_fast_f32(rfftf32,signal,0) #RFFT transform
    rfft_mag = dsp.arm_cmplx_mag_f32(rfft_result / (N/2)) #amplitude and normalized FFT
    rfft_mag[0] = 0 #eliminate DC component bias
    rfft_mag[1: -1] *= 2
    N_ps = len(rfft_mag) #length of power spectrum
    rfft_ps = (dsp.arm_mult_f32(rfft_mag, rfft_mag)) / N_ps
    freqs = fftfreq(N_ps * 2, Fs)[:N_ps] #only positive frequency component    
    p20 = dsp.arm_mean_f32(rfft_ps) #mean of power spectrum
    p21 = dsp.arm_std_f32(rfft_ps) #standard deviation of power spectrum
    p22 = (dsp.arm_accumulate_f32(dsp.arm_mult_f32(dsp.arm_mult_f32((rfft_ps - p20), (rfft_ps - p20)), (rfft_ps - p20)))) / (N_ps * p21 ** 3) #skewness of power spectrum
    p23 = (dsp.arm_accumulate_f32(dsp.arm_mult_f32(dsp.arm_mult_f32(dsp.arm_mult_f32((rfft_ps - p20), (rfft_ps - p20)), (rfft_ps - p20)), (rfft_ps - p20)))) / (
        N_ps * p21 ** 4) #kurtosis of power spectrum
    p24 = (dsp.arm_accumulate_f32(dsp.arm_mult_f32(freqs, rfft_ps))) / (dsp.arm_accumulate_f32(rfft_ps)) #frequency center
    p25 = (dsp.arm_accumulate_f32(dsp.arm_mult_f32(dsp.arm_mult_f32(freqs - p24, freqs - p24), rfft_ps))) / (dsp.arm_accumulate_f32(rfft_ps)) #frequency deviation
    p26 = (dsp.arm_sqrt_f32((dsp.arm_accumulate_f32(dsp.arm_mult_f32(dsp.arm_mult_f32(freqs - p24, freqs - p24), rfft_ps))) / (dsp.arm_accumulate_f32(rfft_ps))))[1] #frequency standard deviation
    p27 = (dsp.arm_sqrt_f32((dsp.arm_accumulate_f32(dsp.arm_mult_f32(dsp.arm_mult_f32(freqs, freqs), rfft_ps))) / (dsp.arm_accumulate_f32(rfft_ps))))[1] #frequency root mean square
    
    feature_matrix = np.zeros((1, 8))
    feature_matrix[0, 0] = p20
    feature_matrix[0, 1] = p21
    feature_matrix[0, 2] = p22
    feature_matrix[0, 3] = p23
    feature_matrix[0, 4] = p24
    feature_matrix[0, 5] = p25
    feature_matrix[0, 6] = p26
    feature_matrix[0, 7] = p27
    
    return feature_matrix

# Acceleration signal integration
def time_and_frequency_integration(signal):
    #c = 9.8
    N = len(signal) #length of signal
    Fs = 12000 #sampling frequency
    Ts = 1/Fs #sampling period
    T = np.arange(0, N/Fs, 1/Fs)
    F = np.arange(0, Fs/2, Fs/N)
    rfftf32=dsp.arm_rfft_fast_instance_f32()
    dsp.arm_rfft_fast_init_f32(rfftf32, N)
    
    #remove trend: polynomial fit 
    """ coefficients = np.polyfit(T, signal, 0)
    poly_values = np.polyval(coefficients, T)
    signal = signal - poly_values  """
    
    #perform FFT operations on the original signal
    original_acc_RFFT = dsp.arm_rfft_fast_f32(rfftf32,signal * dsp.arm_hanning_f32(N),0)   
    original_acc_RFFT_mag = dsp.arm_cmplx_mag_f32(original_acc_RFFT / (N/2))
    original_acc_RFFT_mag[0] = 0 #eliminate DC component bias
    original_acc_RFFT_mag[1: -1] *= 2 
    
    ## IIR butterworth high-pass 4-order filter
    biquadf32 = dsp.arm_biquad_casd_df1_inst_f32()
    numStages = 2 
    state = np.zeros(numStages*4)
    # By MATLAB
    scale_values = 0.995174909795582540716907260502921417356 * 0.988484701982508928708170969912316650152
    # The high-pass filter coefficient is obtained from the C language header file using MATLAB FADTOOL, and remember a1 and a2 are inverse
    coefs = [1.0, -2.0, 1.0, 1.990271241661728529592778613732662051916, -0.990428397520601744297152890794677659869,
             1.0, -2.0, 1.0, 1.976891354287120039501246537838596850634, -0.977047453642915675331437341810669749975]
    dsp.arm_biquad_cascade_df1_init_f32(biquadf32, numStages, coefs, state)
    hp_signal = dsp.arm_biquad_cascade_df1_f32(biquadf32, signal)
    hp_signal *= scale_values;
    
    #remove trend    
    signal_pre = hp_signal - dsp.arm_mean_f32(hp_signal)
    
    ## Time domain integration
    time_domain_output = np.zeros(N)

    #computed ladder integral
    for i in range(1, N):
        time_domain_output[i] = time_domain_output[i - 1] + (Ts / 2.0) * (signal_pre[i - 1] + signal_pre[i])
    
    #remove trend    
    time_domain_output = (time_domain_output - dsp.arm_mean_f32(time_domain_output)) * 1000 # remove trend and convert m/s to mm/s
    """ 
    time_domain_RFFT = dsp.arm_rfft_fast_f32(rfftf32,time_domain_output * dsp.arm_hanning_f32(N),0)   
    time_domain_RFFT_mag = dsp.arm_cmplx_mag_f32(time_domain_RFFT / (N/2))
    time_domain_RFFT_mag[0] = 0 #eliminate DC component bias
    time_domain_RFFT_mag[1: -1] *= 2 
    """
    
    ## Frequency domain integration
    signal_RFFT = dsp.arm_rfft_fast_f32(rfftf32,hp_signal,0) #RFFT Transform
    
    #calculated frequency interval
    df = Fs / N
    #calculate the circle frequency interval
    dw = 2 * np.pi * df
    #establish a positive discrete circular frequency vector
    w1 = np.arange(0, 2 * np.pi * 0.5 * Fs, dw)
    #establish a negative discrete circular frequency vector
    #w2 = np.arange(2 * np.pi * (0.5 * Fs - df), 0, -dw)
    #combine the positive and negative circular frequency vectors into one vector
    #w = np.concatenate((w1, -w2))
    it = 1  #integrating times
    w = w1 ** it

    #return zero matrix
    signal_RFFT_process = np.zeros(N)
    signal_RFFT_process[2:N-2] = signal_RFFT[2:N-2] / np.repeat(w1, 2)[2:N-2]
    
    #1/jw transform
    for i in range(N // 2):
        temp1 = -signal_RFFT_process[2*i] 
        temp2 = signal_RFFT_process[2*i+1] 
        signal_RFFT_process[2*i] = temp2
        signal_RFFT_process[2*i+1] = temp1

    #inverse FFT transformation
    frequency_domain_output = dsp.arm_rfft_fast_f32(rfftf32,signal_RFFT_process,1)
    
    #remove trend    
    frequency_domain_output = (frequency_domain_output) * 1000 # remove trend and convert m/s to mm/s
    """ 
    frequency_domain_RFFT = dsp.arm_rfft_fast_f32(rfftf32,frequency_domain_output * dsp.arm_hanning_f32(N),0)
    frequency_domain_RFFT_mag = dsp.arm_cmplx_mag_f32(frequency_domain_RFFT / (N/2))
    frequency_domain_RFFT_mag[0] = 0 #eliminate DC component bias
    frequency_domain_RFFT_mag[1: -1] *= 2 
    """
     
    """ 
    plt.clf()
    plt.plot(T, time_domain_output, label='Time-domain Integrating')
    plt.plot(T, frequency_domain_output, label='Frequency-domain Integrating')
    plt.legend(loc='upper right')
    plt.xlabel('Time(s)')
    plt.ylabel('Velocity(mm/s)')
    plt.title('Integrating Signal')
    plt.show() 
    """
    return time_domain_output

# Perform Hilbert transform on the acc signal to obtain envelope signal and the amplitude spectrum of the envelope signal
def Hilbert_and_envelope_signal(signal):
    N = len(signal) #length of signal
    Fs = 12000 #sampling frequency
    Ts = 1/Fs #sampling period
    T = np.arange(0, N/Fs, Ts)
    F = np.arange(0, Fs, Fs/N)
    cfftf32=dsp.arm_cfft_instance_f32()
    dsp.arm_cfft_init_f32(cfftf32,N)
    rfftf32=dsp.arm_rfft_fast_instance_f32()
    dsp.arm_rfft_fast_init_f32(rfftf32, N)

    pre_signal = data_preprocess(signal) #data preprocessing
    hp_signal = imToReal1D(pre_signal)
    hp_signal_cfft = dsp.arm_cfft_f32(cfftf32,hp_signal,0,1) #CFFT transform (By High-Pass)

    #generate the frequency-domain representation of the Hilbert transform
    H = np.zeros(2*N)
    H[0] = 0  #DC component
    H[:N] = 2  #positive frequency
    H[N:] = 0 #negative frequency
    
    #obtain analytic signal to get envelope signal
    hp_analytic_signal_f = hp_signal_cfft * H
    hp_analytic_signal = dsp.arm_cfft_f32(cfftf32,hp_analytic_signal_f,1,1) #ICFFT transform
    hp_signal_envelop = dsp.arm_cmplx_mag_f32(hp_analytic_signal)

    #obtain the amplitude spectrum of the envelope signal
    """ 
    hp_envelope_cfft = dsp.arm_rfft_fast_f32(rfftf32,hp_signal_envelop * dsp.arm_hanning_f32(N),0) #CFFT transform
    hp_envelope_cfft_mag = dsp.arm_cmplx_mag_f32(hp_envelope_cfft / (N/2)) #amplitude
    hp_envelope_cfft_mag[0] = 0 #eliminate DC component bias
    hp_envelope_cfft_mag[1: -1] *= 2
    """
    return hp_signal_envelop

# Make datasets after MSFE layer
def make_datasets_after_MSFE_layer(data, features_columns):
    feature_matrix = pd.DataFrame()
    for index in range(len(data)):
        #obtain velocity and envelope signal from acceleration signal
        pre_signal = data_preprocess(data.numpy()[index,])
        velocity_signal = time_and_frequency_integration(data.numpy()[index,])
        envelope_signal = Hilbert_and_envelope_signal(pre_signal)
        
        #extract time-domain and frequency-domain features from acceleration, velocity and envelope signal
        acc_time_domain_feature = extract_time_domain_features(pre_signal)
        vel_time_domain_feature = extract_time_domain_features(velocity_signal)
        env_time_domain_feature = extract_time_domain_features(envelope_signal)
        acc_frequency_domain_feature = extract_frequency_domain_features(pre_signal)
        vel_frequency_domain_feature = extract_frequency_domain_features(velocity_signal)
        env_frequency_domain_feature = extract_frequency_domain_features(envelope_signal)
        
        #generate feature matrix
        acc_features = np.append(acc_time_domain_feature, acc_frequency_domain_feature)
        vel_features = np.append(vel_time_domain_feature, vel_frequency_domain_feature)
        env_features = np.append(env_time_domain_feature, env_frequency_domain_feature)
        
        features = np.concatenate((acc_features, vel_features, env_features))
        features = pd.DataFrame(features.reshape(1, -1))
        features.index = [f'{index}']
        feature_matrix = pd.concat([feature_matrix, features])
    feature_matrix.columns = features_columns
    
    return feature_matrix

# Training set
r""" file_path_097 = r'C:\Users\Yanfeng\Downloads\acc2vel_validation_data-v20241205\data\1\1.txt'
file_path_118= r'C:\Users\Yanfeng\Downloads\acc2vel_validation_data-v20241205\data\2\2.txt'
acc_source_097 = np.loadtxt(file_path_097)
acc_source_118 = np.loadtxt(file_path_118)
acc_source_097_4096_frame = [acc_source_097[i:i + 4096] for i in range(0, len(acc_source_097), 4096)]
acc_source_118_4096_frame = [acc_source_118[i:i + 4096] for i in range(0, len(acc_source_118), 4096)]

for idx_097, sample_097 in enumerate(acc_source_097_4096_frame):
    # print(f"Sample {idx} (length {len(sample)}): {sample}")
    time_and_frequency_integration(sample_097)
    Hilbert_and_envelope_signal(sample_097)

for idx_118, sample_118 in enumerate(acc_source_118_4096_frame):
    # print(f"Sample {idx} (length {len(sample)}): {sample}")
    time_and_frequency_integration(sample_118)
    Hilbert_and_envelope_signal(sample_118) 
""" 
    
features_columns = ['A_Max', 'A_Min', 'A_Absolute Mean', 'A_Peak to Peak', 'A_Mean', 'A_Root Mean Square', 'A_Square Root Amplitude', 'A_Standard Deviation', 
                    'A_Skewness', 'A_Kurtosis', 'A_Variance', 'A_Margin/Clearance Factor', 'A_Wave Form', 'A_Shape Factor', 'A_Crest/Peak Factor', 'A_Skewness Coefficient', 
                    'A_Kurtosis Coefficient', 'A_Impulse Factor', 'A_Mean of Power Spectrum', 'A_STD of Power Spectrum', 'A_Skewness of Power Spectrum', 'A_Kurtosis of Power Spectrum', 
                    'A_Frequency Center', 'A_Frequency Deviation', 'A_Frequency STD', 'A_Frequency RMS', 'A_Entropy',
                    'V_Max', 'V_Min', 'V_Absolute Mean', 'V_Peak to Peak', 'V_Mean', 'V_Root Mean Square', 'V_Square Root Amplitude', 'V_Standard Deviation', 
                    'V_Skewness', 'V_Kurtosis', 'V_Variance', 'V_Margin/Clearance Factor', 'V_Wave Form', 'V_Shape Factor', 'V_Crest/Peak Factor', 'V_Skewness Coefficient', 
                    'V_Kurtosis Coefficient', 'V_Impulse Factor', 'V_Mean of Power Spectrum', 'V_STD of Power Spectrum', 'V_Skewness of Power Spectrum', 'V_Kurtosis of Power Spectrum', 
                    'V_Frequency Center', 'V_Frequency Deviation', 'V_Frequency STD', 'V_Frequency RMS', 'V_Entropy',
                    'E_Max', 'E_Min', 'E_Absolute Mean', 'E_Peak to Peak', 'E_Mean', 'E_Root Mean Square', 'E_Square Root Amplitude', 'E_Standard Deviation', 
                    'E_Skewness', 'E_Kurtosis', 'E_Variance', 'E_Margin/Clearance Factor', 'E_Wave Form', 'E_Shape Factor', 'E_Crest/Peak Factor', 'E_Skewness Coefficient', 
                    'E_Kurtosis Coefficient', 'E_Impulse Factor', 'E_Mean of Power Spectrum', 'E_STD of Power Spectrum', 'E_Skewness of Power Spectrum', 'E_Kurtosis of Power Spectrum', 
                    'E_Frequency Center', 'E_Frequency Deviation', 'E_Frequency STD', 'E_Frequency RMS', 'E_Entropy']
train_data = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_train_data')
val_data = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_val_data')
test_data = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_test_data')

train_feature_matrix = make_datasets_after_MSFE_layer(train_data, features_columns)
val_feature_matrix = make_datasets_after_MSFE_layer(val_data, features_columns)
test_feature_matrix = make_datasets_after_MSFE_layer(test_data, features_columns)

train_feature_matrix.to_csv(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_12K_1797_10c_MSFE_train.csv')
val_feature_matrix.to_csv(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_12K_1797_10c_MSFE_val.csv')
test_feature_matrix.to_csv(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_12K_1797_10c_MSFE_test.csv')

#convert ... to tf tensor
train_feature_matrix = tf.convert_to_tensor(train_feature_matrix.values, dtype=tf.float32)
val_feature_matrix = tf.convert_to_tensor(val_feature_matrix.values, dtype=tf.float32)
test_feature_matrix = tf.convert_to_tensor(test_feature_matrix.values, dtype=tf.float32)

print('Training Data Shape: ', tf.shape(train_feature_matrix))
print('Validation Data Shape: ', tf.shape(val_feature_matrix))
print('Testing Data Shape: ', tf.shape(test_feature_matrix))

#save training data after MSFE layer
dump(train_feature_matrix, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_12K_1797_10c_MSFE_train')
dump(val_feature_matrix, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_12K_1797_10c_MSFE_val')
dump(test_feature_matrix, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_12K_1797_10c_MSFE_test')
