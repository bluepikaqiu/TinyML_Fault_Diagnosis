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
""" 
tf.random.set_seed(1)
random.seed(1)
np.random.seed(1) """

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
    train_data = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_12K_1797_10c_MSFE_train')
    train_label = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_train_label')
    
    #validation set
    val_data = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_12K_1797_10c_MSFE_val')
    val_label = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_1024_10c_val_label')
    
    #test set
    test_data = load(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\CWRU_12K_1797_10c_MSFE_test')
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

#define CNN-2D model
def CNN2D():
    model = keras.models.Sequential()
    model.add(keras.layers.Conv2D(16, (3, 3), padding='same', activation='relu', input_shape=(9, 9, 1))) #kernel_regularizer=keras.regularizers.l2(5e-4)
    model.add(keras.layers.BatchNormalization()) # must add, accelerate convergence
    model.add(keras.layers.MaxPooling2D((2, 2)))
    model.add(keras.layers.Flatten())
    model.add(keras.layers.Dense(32, activation='relu'))
    #model.add(keras.layers.Dropout(0.5))
    model.add(keras.layers.Dense(10, activation='softmax'))
    
    return model
    
""" def CNN1D():
    model = tf.keras.Sequential([keras.layers.Conv1D(16, kernel_size=3, input_shape=(81, 1), padding='same', activation='relu'),
                                 keras.layers.BatchNormalization(),
                                 keras.layers.MaxPooling1D(pool_size=2),
                                 keras.layers.Flatten(),
                                 keras.layers.Dense(32, activation='relu'),
                                 keras.layers.Dense(10, activation='softmax')])
    return model """

def model_train(batch_size, model, epoch_n, train_data, train_label, val_data, val_label):
    #training set
    #data stacking, convert 1 * 1024 sequences to 32 * 32 sequences
    train_data = tf.reshape(train_data, (-1,9,9,1))

    #validation set
    #data stacking, convert 1 * 1024 sequences to 32 * 32 sequences
    val_data = tf.reshape(val_data, (-1,9,9,1))
    
    #print pre-trained model
    """ model_pre = tf.keras.models.load_model(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\best_model.h5')
    loss ,accuracy = model_pre.evaluate(test_data, test_label)
    print("(TEST SET) loss, accuracy: ", loss, accuracy)
    """   
    
    checkpoint_cb = tf.keras.callbacks.ModelCheckpoint(
    r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\edge_intelligence\CWRU_DATASET\best_model.h5',
    save_best_only=True,
    monitor='val_loss',
    mode='min',
    verbose=0
    )
    
    #set optimizer and learning rate
    adam = keras.optimizers.Adam(lr=0.001)
    
    #model compile
    model.compile(loss = 'sparse_categorical_crossentropy', optimizer = adam, metrics = ['accuracy']);

    #print as summary of the model's architecture
    model.summary()
    
    #compute model running time
    start_time = time.time()
    history = model.fit(train_data, train_label, batch_size=batch_size, epochs=epoch_n, validation_data=(val_data, val_label), callbacks=[checkpoint_cb])
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
def evaluation_test_data(model, test_data, test_label):
    #test set
    #data stacking, convert 1 * 1024 sequences to 32 * 32 sequences
    test_data = tf.reshape(test_data, (-1,9,9,1))
    
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
epoch_n = 150
train_data, train_label, val_data, val_label, test_data, test_label = dataloder()
model = CNN2D()
history = model_train(batch_size, model, epoch_n, train_data, train_label, val_data, val_label)
loss_metrics_curve(history, epoch_n)
evaluation_test_data(model, test_data, test_label)
