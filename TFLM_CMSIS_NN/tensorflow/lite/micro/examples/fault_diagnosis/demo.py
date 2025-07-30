import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import math
import os

path = os.path.abspath(os.curdir)
print(path)

SAMPLES = 1000
SEED = 1234
np.random.seed(SEED)
tf.random.set_seed(SEED)
x_values = np.random.uniform(low = 0, high = 2*math.pi, size = SAMPLES)
np.random.shuffle(x_values) #shuffle the values to guarantee they're nuot in order
y_values = np.sin(x_values) #calculate the corresponding sine values
plt.plot(x_values, y_values, 'b.') #plot data
plt.show()

#Add a small random number to each y value
y_values += 0.1*np.random.randn(*y_values.shape)
plt.plot(x_values, y_values, 'b.')
plt.show()

#use 60% of our data  for training and 20% for testing. The remaining 20% will be used for validation.
TRAIN_SPLIT = int(0.6*SAMPLES)
TEST_SPLIT = int(0.2*SAMPLES + TRAIN_SPLIT)

#use np.split to chop our data into three parts
x_train, x_validate, x_test = np.split(x_values, [TRAIN_SPLIT, TEST_SPLIT])
y_train, y_validate, y_test = np.split(y_values, [TRAIN_SPLIT, TEST_SPLIT])

#double check thar our splits add up correctly
assert(x_train.size + x_validate.size + x_test.size) == SAMPLES

#plot the data
plt.plot(x_train, y_train, 'b.', label = "Train")
plt.plot(x_validate, y_validate, 'y.', label = "Validate")
plt.plot(x_test, y_test, 'r.', label = "TEST")
plt.show()

#regression problem(predict)
#use Keras to create a simple model architecture
import keras.models
from keras import layers
from keras import callbacks
from keras.utils import model_to_dot

model_1 = keras.models.Sequential()

#first layer takes a scalar input and feeds it through 16 "neurons"
#the neurons decide whether to activate based on the 'relu' activation function
#'activation' (mean activation function) is designed by keras and tf
#activation = activation_function((input*weight) + bias)
model_1.add(layers.Dense(16, activation='relu', input_shape=(1,)))

#the new second layer may help the network learn more complex representation
model_1.add(layers.Dense(16, activation='relu'))

#final layer is a single neuron, since we want to output a single value
#heren 'input' and 'weights' are both numpy arrays with 16 elements each
#output = sum((input * weights)) + bias
model_1.add(layers.Dense(1))

#compile the model using as standard optimizer and loss function for regression
model_1.compile(optimizer='rmsprop', loss='mse', metrics=['mae'])

#Print as summary of the model's architecture
model_1.summary()
#trainning
history_1 = model_1.fit(x_train, y_train, epochs=600, batch_size=16, validation_data=(x_validate, y_validate))

loss = history_1.history['loss']
val_loss = history_1.history['val_loss']
epochs = range(1, len(loss) + 1)

plt.plot(epochs, loss, 'g.', label='Training loss')
plt.plot(epochs, val_loss, 'b', label = 'Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()

#Exclude the first few epochs so the graph is easier to read
SKIP = 100
plt.plot(epochs[SKIP:], loss[SKIP:], 'g.', label='Training loss')
plt.plot(epochs[SKIP:], val_loss[SKIP:], 'b.', label='Validation loss')
plt.title('Training and validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()

#Draw a graph of mean obsolute error, which is another way of measuring the amount of error in the prediction
mae = history_1.history['mae']
val_mae = history_1.history['val_mae']
plt.plot(epochs[SKIP:], mae[SKIP:], 'g.', label='Training MAE')
plt.plot(epochs[SKIP:], val_mae[SKIP:], 'b.', label='Validation MAE')
plt.title('Training and validation mean absolute error')
plt.xlabel('Epochs')
plt.ylabel('MAE')
plt.legend()
plt.show()

#use the model to make prediction from our validation data
predictions = model_1.predict(x_train)
#plot the predications along with the test data
plt.clf()
plt.title('Training data predicted vs actual values')
plt.plot(x_train, y_train, 'b.', label='Actual')
plt.plot(x_train, predictions, 'r.', label='Predicted')
plt.legend()
plt.show()

#Calculate and print the loss on our test dataset
loss = model_1.evaluate(x_test, y_test)
#make predications based on our test dataset
predictions = model_1.predict(x_test)
#graph the predictions against the actual values
plt.clf()
plt.title('Training data predicted vs actual values')
plt.plot(x_test, y_test, 'b.', label='Actual')
plt.plot(x_test, predictions, 'r.', label='Predicted')
plt.legend()
plt.show()

#convert the model to the tensorflow lite format without quantization
converter = tf.lite.TFLiteConverter.from_keras_model(model_1)
tflite_model = converter.convert()
#save the model to disk
f = open("tensorflow/lite/micro/examples/fault_diagnosis/sine_model.tflite", "wb")
f.write(tflite_model)
f.close()

#convert the model to the tensorflow lite format with quantization
converter = tf.lite.TFLiteConverter.from_keras_model(model_1)
#indicate that we want to perform the default optimizations
#which include quantization
converter.optimizations = [tf.lite.Optimize.DEFAULT]
#Define a generator function that provides our test data's x values
#as a representative dataset, and tell the converter to use it
def representative_dataset_generator():
    for value in x_test:
        #Each scalar value must be inside of a 2D array that is wrapped in a list
        yield [np.array(value, dtype=np.float32, ndmin=2)]

converter.representative_dataset = representative_dataset_generator
#convert the model
tflite_model = converter.convert()

#save the model the disk
f = open("tensorflow/lite/micro/examples/fault_diagnosis/sine_model_quantized.tflite", "wb")
f.write(tflite_model)
f.close()

#Instantiate an interpreter for each model
sine_model = tf.lite.Interpreter('tensorflow/lite/micro/examples/fault_diagnosis/sine_model.tflite')
sine_model_quantized = tf.lite.Interpreter('tensorflow/lite/micro/examples/fault_diagnosis/sine_model_quantized.tflite')

#Allocate memory for each model
sine_model.allocate_tensors()
sine_model_quantized.allocate_tensors()

#Get indexes of the input and output tensors
sine_model_input_index = sine_model.get_input_details()[0]["index"]
sine_model_output_index = sine_model.get_output_details()[0]["index"]
sine_model_quantized_input_index = sine_model_quantized.get_input_details()[0]["index"]
sine_model_quantized_output_index = sine_model_quantized.get_output_details()[0]["index"]

#Create arrays to store the results
sine_model_predictions = []
sine_model_quantized_predictions = []

#Run each model's interpreter for each value and store the results in arrays for x_value in x_test:
for x_value in x_test:
    #Create a 2D tensor wrapping the current x value
    x_value_tensor = tf.convert_to_tensor([[x_value]], dtype=np.float32)
    #Write the value to the input tensor
    sine_model.set_tensor(sine_model_input_index, x_value_tensor)
    #Run inference
    sine_model.invoke()
    #Read the prediction from the output tensor
    sine_model_predictions.append(
        sine_model.get_tensor(sine_model_output_index)[0]
    )
    print("sine_model.get_tensor(sine_model_output_index): ", sine_model.get_tensor(sine_model_output_index))
    #Do the same for the quantized model
    sine_model_quantized.set_tensor(sine_model_quantized_input_index, x_value_tensor)
    sine_model_quantized.invoke()
    sine_model_quantized_predictions.append(
        sine_model_quantized.get_tensor(sine_model_quantized_output_index)[0]
    )

#See how they line up with the data
plt.clf()
plt.title('Comparison of various models against actual values')
plt.plot(x_test, y_test, 'bo', label='Actual')
plt.plot(x_test, predictions, 'ro', label='Original predictions')
plt.plot(x_test, sine_model_predictions, 'bx', label='Lite predictions')
plt.plot(x_test, sine_model_quantized_predictions, 'gx', label='Lite quantized predictions')
plt.legend()
plt.show()

import os
basic_model_size = os.path.getsize("tensorflow/lite/micro/examples/fault_diagnosis/sine_model.tflite")
print("Basic model is %d bytes" % basic_model_size)
quantized_model_size = os.path.getsize("tensorflow/lite/micro/examples/fault_diagnosis/sine_model_quantized.tflite")
print("Quantized model is %d bytes" % quantized_model_size)
difference = basic_model_size - quantized_model_size
print("Difference is %d bytes" % difference)
