from keras.datasets import mnist
import random

# load data
(X_train, y_train), (X_test, y_test) = mnist.load_data()

f = open("testdata.bin", "wb")
for n in range(10000):
   f.write(y_test[n])
   f.write(X_test[n].reshape(X_test.shape[1]*X_test.shape[1]))

f.close()

