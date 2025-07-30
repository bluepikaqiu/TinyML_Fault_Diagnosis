import pandas as pd
import matplotlib.pyplot as plt
import sklearn
import tensorflow as tf

from scipy.io import loadmat
from joblib import dump, load

##CWRU DATASETS
#convert it to .csv file
def convert_csv():
    #import driven end data
    data_columns = ['X097_DE_time', 'X105_DE_time', 'X118_DE_time', 'X130_DE_time', 'X169_DE_time', 
                    'X185_DE_time', 'X197_DE_time', 'X209_DE_time', 'X222_DE_time', 'X234_DE_time']

    columns_name = ['DE_normal', 'DE_7_inner', 'DE_7_ball', 'DE_7_outer', 'DE_14_inner',
                    'DE_14_ball', 'DE_14_outer', 'DE_21_inner', 'DE_21_ball', 'DE_21_outer']

    file_name = ['97.mat', '105.mat', '118.mat', '130.mat', '169.mat',
                '185.mat', '197.mat', '209.mat', '222.mat', '234.mat']

    data_CWRU_12K_1797_10c = pd.DataFrame()
    for index in range(10):
        #read mat files
        data = loadmat(f'C:\\Users\\Yanfeng\\Downloads\\Bearing_Data\\CWRU_0_1797\\{file_name[index]}')
        data_list = data[data_columns[index]].reshape(-1)
        data_CWRU_12K_1797_10c[columns_name[index]] = data_list[:119808] #1024 * 117
    print(data_CWRU_12K_1797_10c)

    data_CWRU_12K_1797_10c.set_index(data_CWRU_12K_1797_10c.index, inplace=True)
    data_CWRU_12K_1797_10c.to_csv(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\data_CWRU_12K_1797_10c.csv')

    #import CWRU dataset
    data = pd.read_csv(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\data_CWRU_12K_1797_10c.csv', usecols=
                    ['DE_normal', 'DE_7_inner', 'DE_7_ball', 'DE_7_outer', 'DE_14_inner', 'DE_14_ball', 'DE_14_outer', 'DE_21_inner', 'DE_21_ball', 'DE_21_outer'])
    fig, axs = plt.subplots(2, 5, sharex=True)

    #visualization
    data_1 = data[:1000]
    for i in range(2):
        for j in range(5):
            index = i * 5 + j
            if index < len(data_1.columns):
                axs[i, j].plot(data_1[data_1.columns[index]])
                axs[i, j].set_title(data_1.columns[index])
                axs[i, j].set_xlabel('Time')
                axs[i, j].set_ylabel('Vibration Signal')
    plt.show()


""" data_train = data[:1000]
data_train.plot()
plt.show() """


#resample, and add the label
#切割划分方法: 参考论文 《时频图结合深度神经网络的轴承智能故障诊断研究》
#time steps:1024 overlap ratio：0.5
#split the dataset
def split_data_with_overlap(data, time_steps, label, overlap_ratio=0.5):
    '''
        data:要切分的时间序列数据,可以是一个一维数组或列表。
        time_steps:切分的时间步长,表示每个样本包含的连续时间步数。
        label: 切分数据所对应的分类标签
        overlap_ratio:前后帧切分时的重叠率,取值范围为 0 到 1,表示重叠的比例。
    '''
    stride = int(time_steps * (1 - overlap_ratio))  # 计算步幅
    samples = (len(data) - time_steps) // stride + 1  # 计算样本数
    Classify_dataFrame = pd.DataFrame(columns=[index for index in range(time_steps + 1)])
    
    split_data = []
    for i in range(samples):
        start_idx = i * stride
        end_idx = start_idx + time_steps
        temp_data = data[start_idx:end_idx].tolist()
        temp_data.append(label) # 添加标签
        split_data.append(temp_data)
    Classify_dataFrame = pd.DataFrame(split_data, columns=Classify_dataFrame.columns)
    return Classify_dataFrame

#data normalization
def normalize(data):
    ''' (0,1)归一化
        参数:一维时间序列数据
    '''
    s = (data-min(data)) / (max(data)-min(data))
    return  s

#make datasets
def make_datasets(data_file_csv, label_list=[],split_rate = [0.7,0.2,0.1]):
    '''
        参数:
        data_file_csv: 故障分类的数据集,csv格式,数据形状: 119808行  10列
        label_list: 故障分类标签
        split_rate: 训练集、验证集、测试集划分比例

        返回:
        train_set: 训练集数据
        val_set: 验证集数据
        test_set: 测试集数据
    '''
    # 1.读取数据
    origin_data = pd.read_csv(data_file_csv, 
                              usecols=['DE_normal', 'DE_7_inner', 'DE_7_ball', 'DE_7_outer', 'DE_14_inner', 'DE_14_ball', 'DE_14_outer', 'DE_21_inner', 'DE_21_ball', 'DE_21_outer'])
    # 数据集的分类标签
    #classify_labels = label_list
    #classify_labels = origin_data.columns # 标签默认为列名
    
    # 2.分割样本点
    time_steps = 1024  # 时间步长
    overlap_ratio = 0.5  # 重叠率
    samples_data = pd.DataFrame(columns=[index for index in range(time_steps + 1)])  # 10个样本集合
    label = 0 # 记录分类标签
    
    # 使用iteritems()方法遍历每一列
    for column_name, column_data in origin_data.items():
        # 对数据集的每一维进行归一化
        # column_data = normalize(column_data)
        # 划分样本点  time_steps: 1024
        split_data = split_data_with_overlap(column_data, time_steps, label, overlap_ratio)
        label += 1 # 分类标签递增
        samples_data = pd.concat([samples_data, split_data])
        # 随机打乱样本点顺序 
        samples_data = sklearn.utils.shuffle(samples_data) # 可以选择设置随机种子 保证每次实验数据一致

    # 3.分割训练集-、验证集、测试集
    sample_len = len(samples_data) # 每一类样本数量
    train_len = int(sample_len * split_rate[0])  # 向下取整
    val_len = int(sample_len * split_rate[1]) 
    train_set = samples_data.iloc[0:train_len, :]   
    val_set = samples_data.iloc[train_len:train_len + val_len, :]   
    test_set = samples_data.iloc[train_len + val_len:sample_len, :]   
    return  train_set, val_set, test_set

#make dataset and labels
#these conversions are to convert data and labels from Pandas data structures to tensors
#that tensorflow can handle for training and prediction in neural networks.
def make_dataset_labels(dataFrame):
    '''
        参数 dataframe: 数据框
        返回 x_data: 数据集     tf tensor
             y_label: 对应标签值  tf tensor
    '''
    # 信号值
    x_data = dataFrame.iloc[:, 0:-1]
    # 标签值
    y_label = dataFrame.iloc[:, -1]
    x_data = tf.convert_to_tensor(x_data.values, dtype=tf.float32)
    y_label = tf.convert_to_tensor(y_label.values, dtype=tf.int8)
    return x_data, y_label

#split trainning set、validation set、test set [0.7,0.2,0.1]
convert_csv()
train_set, val_set, test_set = make_datasets(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\data_CWRU_12K_1797_10c.csv')

#save the data
dump(train_set, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_train_set') 
dump(val_set, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_val_set') 
dump(test_set, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_test_set') 

""" for column_name, split_data in train_set.items():
    for index in range(len(split_data)):
        print(split_data[index]) """

#loading data
train_set = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_train_set')
val_set = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_val_set')
test_set = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_test_set')

#making labels
train_data, train_label = make_dataset_labels(train_set)
val_data, val_label = make_dataset_labels(val_set)
test_data, test_label = make_dataset_labels(test_set)

#save data
dump(train_data, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_train_data')
dump(train_label, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_train_label')
dump(test_data, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_test_data')
dump(test_label, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_test_label')
dump(val_data, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_val_data')
dump(val_label, r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_val_label')

print('Data Shape: ')
print(tf.shape(train_data))
print(tf.shape(train_label))
print(tf.shape(test_data))
print(tf.shape(test_label))
print(tf.shape(val_data))
print(tf.shape(val_label))