import keras.callbacks
import keras.optimizers
import keras.regularizers
import numpy as np
import random
import time
import matplotlib.pyplot as plt
import seaborn as sns
import tensorflow as tf
import keras.models
import keras.layers

from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix
from joblib import load

#paradiams and configuration
#make sure standard Library and Numpy possess the same seed as tensorflow library
tf.random.set_seed(1)
random.seed(1)
np.random.seed(1)

#detect if there existing available GPU
device = "GPU" if tf.config.list_physical_devices('GPU') else "CPU"
print(f'Device: {device}')

""" 
#define preprocessing function to parallelism
def preprocess(x, y):
    return x, y 
"""

#loading the dataset
def dataloder():
    #training set
    train_data = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_train_data')
    train_label = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_train_label')
    
    #validation set
    val_data = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_val_data')
    val_label = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_val_label')
    
    #test set
    test_data = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_test_data')
    test_label = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_test_label')
    
    """ 
    #loading the data
    train_loader = tf.data.Dataset.from_tensor_slices((train_data, train_label))
    #set the batch size and shuffle the dataset
    train_loader = train_loader.shuffle(buffer_size=len(train_data))
    #drop last if necessary
    train_loader = train_loader.batch(batch_size, drop_remainder=True)
    train_loader = train_loader.map(preprocess, num_parallel_calls=tf.data.experimental.AUTOTUNE)
    train_loader = train_loader.prefetch(tf.data.experimental.AUTOTUNE) #optimize loading
    
    val_loader = tf.data.Dataset.from_tensor_slices((val_data, val_label))
    val_loader = val_loader.shuffle(buffer_size=len(val_data))
    val_loader = val_loader.batch(batch_size=batch_size, drop_remainder=True)
    val_loader = val_loader.map(preprocess, num_parallel_calls=tf.data.experimental.AUTOTUNE)
    val_loader = val_loader.prefetch(tf.data.experimental.AUTOTUNE)
    
    test_loader = tf.data.Dataset.from_tensor_slices((test_data, test_label))
    test_loader = test_loader.batch(batch_size=batch_size, drop_remainder=True)
    test_loader = test_loader.map(preprocess, num_parallel_calls=tf.data.experimental.AUTOTUNE)
    test_loader = test_loader.prefetch(tf.data.experimental.AUTOTUNE)
    
    return train_loader, val_loader, test_loader 
    """
    return train_data, train_label, val_data, val_label, test_data, test_label

""" class CNN2D_VGG16(tf.keras.Model):
    def __init__(self, batch_size, input_channels=1):
        super(CNN2D_VGG16, self).__init__()
        self.input_channels = input_channels
        self.batch_size = batch_size
        self.conv_layers = self.make_layers()
        self.FConnect = keras.models.Sequential([keras.layers.Flatten(), keras.layers.Dense(4096, activation='relu'),
                                                   keras.layers.Dropout(0.5), keras.layers.Dense(4096, activation='relu'),
                                                   keras.layers.Dropout(0.5), keras.layers.Dense(10, activation='relu')])
    
    def make_layers(self):
        model = keras.models.Sequential()
        model.add(keras.layers.Conv2D(64, (3, 3), padding='same', activation='relu', input_shape=(32, 32, self.input_channels), kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.Conv2D(64, (3, 3), padding='same', activation='relu', kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.MaxPooling2D((2, 2)))
        
        model.add(keras.layers.Conv2D(128, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.Conv2D(128, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.MaxPooling2D((2, 2)))

        model.add(keras.layers.Conv2D(256, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.Conv2D(256, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.Conv2D(256, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.MaxPooling2D((2, 2)))

        model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.MaxPooling2D((2, 2)))        

        model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
        model.add(keras.layers.MaxPooling2D((2, 2)))
        
        model.add(keras.layers.Flatten())
        model.add(keras.layers.Flatten(), keras.layers.Dense(4096, activation='relu'))
        model.add(keras.layers.Dropout(0.5),)
        model.add(keras.layers.Flatten(), keras.layers.Dense(4096, activation='relu'))
        model.add(keras.layers.Dropout(0.5),)
        model.add(keras.layers.Dense(10, activation='relu'))               

        return model
    
    #fit method(forward and back) contains call(forward) & forward(forward)
    def call(self, input_seq):
        input_seq = tf.reshape(input_seq, (tf.shape(input_seq)[0], 32, 32, 1))
        features = self.conv_layers(input_seq)
        output = self.FConnect(features)
        return output """

#define CNN-2D(VGG-16) model
#conv_arch = ((2, 64), (2, 128), (3, 256), (3, 512), (3, 512))
def CNN2D_VGG16():
    model = keras.models.Sequential()
    model.add(keras.layers.Conv2D(64, (3, 3), padding='same', activation='relu', input_shape=(32, 32, 1), kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.Conv2D(64, (3, 3), padding='same', activation='relu', kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.BatchNormalization()) # must add, accelerate convergence
    model.add(keras.layers.MaxPooling2D((2, 2)))

    model.add(keras.layers.Conv2D(128, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.Conv2D(128, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.BatchNormalization())
    model.add(keras.layers.MaxPooling2D((2, 2)))

    model.add(keras.layers.Conv2D(256, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.Conv2D(256, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.Conv2D(256, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.BatchNormalization())
    model.add(keras.layers.MaxPooling2D((2, 2)))

    model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.BatchNormalization())
    model.add(keras.layers.MaxPooling2D((2, 2)))        

    model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.Conv2D(512, (3, 3), padding='same', activation='relu',kernel_regularizer=keras.regularizers.l2(5e-4)))
    model.add(keras.layers.BatchNormalization())
    model.add(keras.layers.MaxPooling2D((2, 2)))

    model.add(keras.layers.Flatten())
    model.add(keras.layers.Dense(4096, activation='relu'))
    model.add(keras.layers.Dropout(0.5))
    model.add(keras.layers.Dense(4096, activation='relu'))
    model.add(keras.layers.Dropout(0.5))
    model.add(keras.layers.Dense(10, activation='softmax'))
    
    return model
    
""" def CNN1D():
    model = tf.keras.Sequential([keras.layers.Conv1D(16, kernel_size=3, input_shape=(1024, 1), padding='same', activation='relu'),
                                 keras.layers.MaxPooling1D(pool_size=2),
                                 keras.layers.Conv1D(32, kernel_size=3, input_shape=(1024, 1), padding='same', activation='relu'),
                                 keras.layers.MaxPooling1D(pool_size=2),
                                 keras.layers.Flatten(),
                                 keras.layers.Dense(128, activation='relu'),
                                 keras.layers.Dense(10, activation='softmax')])
    return model """

#define loss function and optimization function
def scheduler(epoch):
    learning_rate = 0.01
    if epoch < epoch_n * 0.4:
        learning_rate = learning_rate
        return learning_rate
    if epoch < epoch_n * 0.8:
        learning_rate = learning_rate * 0.1
        return learning_rate
    return learning_rate * 0.01

def model_train(batch_size, model, epoch_n, train_data, train_label, val_data, val_label):
    """ 
    #sample size
    train_size = len(train_loader) * batch_size
    val_size = len(val_loader) * batch_size 
    """
    #training set
    #data stacking, convert 1 * 1024 sequences to 32 * 32 sequences
    train_data = tf.reshape(train_data, (-1,32,32,1))

    #validation set
    #data stacking, convert 1 * 1024 sequences to 32 * 32 sequences
    val_data = tf.reshape(val_data, (-1,32,32,1))
    
    sgd = keras.optimizers.SGD(lr=0.01, momentum=0.9, nesterov=True)
    change_lr = keras.callbacks.LearningRateScheduler(schedule=scheduler)

    #model compile
    model.compile(loss = 'sparse_categorical_crossentropy', optimizer = sgd, metrics = ['accuracy']);

    #print as summary of the model's architecture
    model.summary()
    
    #compute model running time
    start_time = time.time()
    history = model.fit(train_data, train_label, batch_size=batch_size, epochs=epoch_n, callbacks = [change_lr], validation_data=(val_data, val_label))
    print(f'\nDuration: {time.time() - start_time:.0f} seconds')
    
    return history

#record loss and metrics curve over epochs
def loss_metrics_curve(history, epoch_n):
    loss = history.history['loss']
    val_loss = history.history['val_loss']
    epochs = range(1, epoch_n + 1)

    plt.figure()
    plt.subplot(1, 2, 1)
    plt.plot(epochs, loss, 'g', label='Training Loss')
    plt.plot(epochs, val_loss, 'b', label = 'Validation Loss')
    plt.title('Training and Validation Loss')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend()

    acc = history.history['accuracy']
    val_acc = history.history['val_accuracy']
    plt.subplot(1, 2, 2)
    plt.plot(epochs, acc, 'g', label='Training Accuracy')
    plt.plot(epochs, val_acc, 'b', label='Validation Accuracy')
    plt.title('Training and Validation Accuracy')
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy')
    plt.legend()
    plt.show()    

#predictions and evaluation based on test dataset
def evaluation_test_data(epoch_n, model, test_data, test_label):
    #test set
    #data stacking, convert 1 * 1024 sequences to 32 * 32 sequences
    test_data = tf.reshape(test_data, (-1,32,32,1))
    
    #Calculate and print the loss on our test dataset
    loss ,accuracy = model.evaluate(test_data, test_label)
    print("(TEST SET) loss, accuracy: ", loss, accuracy)
    
    #make predications based on our test dataset
    predictions = model.predict(test_data)
    #get prediction labels for the category
    predicted_labels = np.argmax(predictions, axis=1)
    #evaluation index(precision, recall, f1-score,etc.)
    report = classification_report(test_label.numpy(), predicted_labels, digits=4)
    print(report)
    
    #confusion matrix
    confusion_mat = confusion_matrix(test_label.numpy(), predicted_labels)
    #mapping between original tags and custom tags
    label_mapping = {0: 'DE_normal', 1: 'DE_7_inner', 2: 'DE_7_ball', 3: 'DE_7_outer', 4: 'DE_14_inner', 5: 'DE_14_ball', 6: 'DE_14_outer', 7: 'DE_21_inner', 8: 'DE_21_ball', 9: 'DE_21_outer'}
    plt.figure()
    sns.heatmap(confusion_mat, xticklabels=label_mapping.values(), yticklabels=label_mapping.values(), annot=True, fmt='d', cmap='gray')
    plt.show()

#instance
batch_size = 32
epoch_n = 100
train_data, train_label, val_data, val_label, test_data, test_label = dataloder()
model = CNN2D_VGG16()
history = model_train(batch_size, model, epoch_n, train_data, train_label, val_data, val_label)
loss_metrics_curve(history, epoch_n)
evaluation_test_data(epoch_n, model, test_data, test_label)
