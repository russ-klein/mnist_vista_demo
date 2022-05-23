import mnist_model
import write_weights

model = mnist_model.create_and_train()
write_weights.write_header_file(model)

