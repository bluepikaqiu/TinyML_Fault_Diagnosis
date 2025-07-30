import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn import preprocessing


# #PCA
# from sklearn.decomposition import PCA
# from sklearn.neighbors import KNeighborsClassifier

# X = np.empty((100,2))
# X[:,0] = np.random.uniform(0., 100., size=100)
# X[:,1] = 0.75 * X[:,0] + 3. + np.random.normal(0, 10., size=100)

# #Initiall instance and import the number of the main composition
# pca = PCA(n_components=1)
# pca.fit(X)
# print(pca.components_)

# #dimensionality reduction
# X_reduction = pca.transform(X)
# print(X_reduction.shape)

# digits = datasets.load_digits()
# X = digits.data
# y = digits.target

# #default test 25%
# X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=666)

# knn_clf = KNeighborsClassifier()
# knn_clf.fit(X_train, y_train)
# print(knn_clf.score(X_test, y_test))


# #maintain 2 dimensions
# pca = PCA(n_components=2)
# pca.fit(X_train)
# X_train_reduction = pca.transform(X_train)
# X_test_reduction = pca.transform(X_test)

# knn_clf = KNeighborsClassifier()
# knn_clf.fit(X_train_reduction, y_train)
# print(knn_clf.score(X_test_reduction, y_test))

# #maintain 64 dimensions
# pca = PCA(n_components=X_train.shape[1])
# pca.fit(X_train)
# print(pca.explained_variance_ratio_)


# plt.plot([i for i in range(X_train.shape[1])], 
#          [np.sum(pca.explained_variance_ratio_[:i+1]) for i in range(X_train.shape[1])])
# plt.show()

# pca = PCA(0.95)
# pca.fit(X_train)
# print(pca.n_components_)

# X_train_reduction = pca.transform(X_train)
# X_test_reduction = pca.transform(X_test)
# knn_clf = KNeighborsClassifier()
# knn_clf.fit(X_train_reduction, y_train)

#Autoencoder
folder = r'C:\Users\Yanfeng\Downloads\NASA_Bearing_Dataset\2nd_test'
data_dir = folder + r'\2nd_test'
merged_data = pd.DataFrame()

for filename in os.listdir(data_dir):
    print(filename)
    dataset = pd.read_csv(os.path.join(data_dir, filename),sep = '\t')
    dataset_mean_abs = np.array(dataset.abs().mean())
    dataset_mean_abs = pd.DataFrame(dataset_mean_abs.reshape(1,4))
    dataset_mean_abs.index = [filename]
    merged_data = pd.concat([merged_data, dataset_mean_abs])

merged_data.reset_index(inplace=True)
merged_data.columns = ['Datetime', 'Bearing 1', 'Bearing 2', 'Bearing 3', 'Bearing 4']
merged_data.sort_values(by='Datetime', inplace=True)
print(merged_data)
merged_data.to_csv(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\2nd_test_resample_10minutes.csv')

#import resample datasets
merged_data = pd.read_csv(r'Z:\tflite-micro\tensorflow\lite\micro\examples\fault_diagnosis\2nd_test_resample_10minutes.csv', index_col='Datetime', usecols=['Datetime','Bearing 1', 'Bearing 2', 'Bearing 3', 'Bearing 4'])
merged_data.index = pd.to_datetime(merged_data.index, format='%Y.%m.%d.%H.%M.%S')
print(merged_data.head())

#split the dataset
dataset_train = merged_data['2004-02-12 10:32:39': '2004-02-13 23:52:39']
dataset_test = merged_data['2004-02-13 23:52:39':]
dataset_train.plot()
plt.show()

scaler = preprocessing.MinMaxScaler()
X_train = pd.DataFrame(scaler.fit_transform(dataset_train), columns=dataset_train.columns, index=dataset_train.index)

#random shuffle training data
X_train.sample(frac=1)
X_test = pd.DataFrame(scaler.transform(dataset_test), columns=dataset_test.columns, index=dataset_test.index)

#using Keras and tf to create model
import tensorflow as tf
import keras.models
import keras.layers

tf.random.set_seed(1)
activation_function = 'relu'

#input layer(4 dimensions):
model = keras.models.Sequential() 

#first hidden layer, connected to input vector
model.add(keras.layers.Dense(10, activation=activation_function, kernel_initializer='glorot_uniform', kernel_regularizer=keras.regularizers.l2(0.0), input_shape=(X_train.shape[1],)))

#second hidden layer
model.add(keras.layers.Dense(2, activation=activation_function))

#third hidden layer
model.add(keras.layers.Dense(10, activation=activation_function))

#output layer
model.add(keras.layers.Dense(X_train.shape[1]))

model.compile(loss='mse', optimizer='adam')
print(model.summary())

#train model for xx epochs, batch size of xx
num_epochs = 500
batch_size = 20

history = model.fit(np.array(X_train), np.array(X_train), batch_size=batch_size, epochs=num_epochs, validation_split=0.1, verbose=1)
plt.plot(history.history['loss'], label='Training Loss')
plt.plot(history.history['val_loss'], label='Validation Loss')
plt.legend(loc='upper right')
plt.ylabel('loss(mse)')
plt.show()

X_pred = model.predict(np.array(X_train))
X_pred = pd.DataFrame(X_pred, index=X_train.index, columns=X_train.columns)
score = pd.DataFrame(index=X_train.index)
score['Loss_MAE'] = np.mean(np.abs(X_pred - X_train), axis=1)
sns.displot(score['Loss_MAE'], kde=True)
plt.show()

X_pred = model.predict(np.array(X_test))
X_pred = pd.DataFrame(X_pred, index=X_test.index, columns=X_test.columns)

threshold = 0.3

score = pd.DataFrame(index=X_test.index)
score['Loss_MAE'] = np.mean(np.abs(X_pred - X_test), axis=1)
score['Threshold'] = threshold
score['Anomaly'] = score['Loss_MAE'] > score['Threshold']
print(score.head())

X_pred_train = model.predict(np.array(X_train))
X_pred_train = pd.DataFrame(X_pred_train, index=X_train.index, columns=X_train.columns)

score_train = pd.DataFrame(index=X_train.index)
score_train['Loss_MAE'] = np.mean(np.abs(X_pred_train - X_train), axis=1)
score_train['Threshold'] = threshold
score_train['Anomaly'] = score_train['Loss_MAE'] > score_train['Threshold']

score = pd.concat([score_train, score])
print(score.head())
score.plot()
plt.show()

