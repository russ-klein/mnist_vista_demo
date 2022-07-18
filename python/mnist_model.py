# Baseline MLP for MNIST dataset
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Conv2D, Flatten
from keras.utils import np_utils
import numpy as np
import random

#===============================================================================#
# MNIST CNN definition                                                          #
# --------------------                                                          #
#                                                                               #
# Can be modified to increase or decrease number of layer, number of channels   #
# supported layers are Conv2D, Dense, and Flatten.  Suppoted kernel sizes are   #
# 3, 5, and 7                                                                   #
#                                                                               #
#===============================================================================#

def mnist_model(num_classes):
  # create model
  model = Sequential()
  model.add(Conv2D(10, (3,3), use_bias=False, padding="same", activation="relu", input_shape=(28,28,1)))
  model.add(Conv2D(3, (3,3), use_bias=False, padding="same", activation="relu"))
  model.add(Flatten())
  model.add(Dense(num_classes, use_bias=False, kernel_initializer='normal', activation='softmax'))
  # Compile model
  model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
  return model


#===============================================================================#
# Create and train the MNIST CNN                                                #
# ------------------------------                                                #
#                                                                               #
# Default epochs is 10, batch_size is 200.  Increase epochs and batch size for  #
# better inferencing, 20 to 30 epochs is good for generating final weights      #
#                                                                               #
#===============================================================================#


def create_and_train(epochs=10, batch_size=200, verbose=1):

  # load data
  (X_train, y_train), (X_test, y_test) = mnist.load_data()

  X_train = X_train.reshape((X_train.shape[0], X_train.shape[1], X_train.shape[2], 1)).astype('int32');
  X_test = X_test.reshape((X_test.shape[0], X_test.shape[1], X_test.shape[2], 1)).astype('int32');

  # normalize inputs from 0-255 to 0-1
  X_train = X_train / 255
  X_test = X_test / 255

  # one hot encode outputs
  y_train = np_utils.to_categorical(y_train)
  y_test = np_utils.to_categorical(y_test)

  num_classes = y_test.shape[1]

  model = mnist_model(num_classes)

  model.fit(X_train, y_train, validation_data=(X_test, y_test), epochs=epochs, batch_size=batch_size, verbose=verbose)
  scores = model.evaluate(X_test, y_test, verbose=0)
  print("Baseline Error: %.2f%%" % (100-scores[1]*100))
  return model



def print_mnist_image(image):
  local_image = image.reshape(28,28).copy()
  for row in range(28):
    for col in range(28):
      print('{:3d} '.format(int(local_image[row][col]*255.0)), end='')
    print(' ')
  print(' ')



def predict(model, image=None, label=None):

  if (image == None):
    # load data
    (X_train, y_train), (X_test, y_test) = mnist.load_data()

    index = random.randrange(0, X_test.shape[0])
    image = X_test[index].reshape(1, 28, 28, 1)
    label = y_test[index]

    image = image / 255.0

  print_mnist_image(image)

  p = model.predict(image.reshape(1,28,28,1))
  p = p[0]

  print('Label:  ', label)
  print(' ')
  print('Predictions: ')

  for i in range(10):
    print('p[{:d}] = {:6.4f} '.format(i, p[i]))

def check_model_accuracy(model, samples = 4000):

  # load data
  (X_train, y_train), (X_test, y_test) = mnist.load_data()

  X_train = X_train.reshape((X_train.shape[0], X_train.shape[1], X_train.shape[2], 1)).astype('int32');
  X_test = X_test.reshape((X_test.shape[0], X_test.shape[1], X_test.shape[2], 1)).astype('int32');

  # normalize inputs from 0-255 to 0-1
  X_train = X_train / 255
  X_test = X_test / 255

  # pick samples from test data
  test_sample_indicies = random.sample(range(0, len(y_test)), k=samples)

  X_check = X_test[test_sample_indicies];
  y_check = y_test[test_sample_indicies];

  correct_predictions = 0

  for i in range(samples):
    features = X_check[i].reshape(1, 28, 28, 1)
    label = y_check[i]
    if label == np.argmax(model.predict(features)):
      correct_predictions += 1

  return correct_predictions/samples      
  

def save_weights(model, weight_name="mnist_weights"):
  model.save_weights(weight_name)


def load_weights(model, weight_name="mnist_weights"):
  model.load_weights(weight_name)


