using Flux
using Flux: onecold, onehotbatch, throttle, params
import Pkg; Pkg.add("CUDA")
import Pkg; Pkg.add("MLDatasets")
import Pkg; Pkg.add("cuDNN")
using MLDatasets  # You can use this package to load datasets easily
using CUDA



# Define the CNN architecture
function create_cnn()
    return Chain(
        Conv((3, 3), 1=>32, relu),
        MaxPool((2, 2)),
        Conv((3, 3), 32=>64, relu),
        MaxPool((2, 2)),
        x -> reshape(x, :, size(x, 4)),
        Dense(7*7*64, 128, relu),
        Dense(128, 10),
    )
end

# Preprocess the data (you can customize this based on your dataset)
# Load the MNIST dataset
train_X, train_y = MNIST.traindata()
test_X, test_y = MNIST.testdata()


train_X = train_X |> gpu
test_X = test_X |> gpu

# Create the CNN model
model = create_cnn()
model = model |> gpu

# Define loss function and optimizer
loss(x, y) = Flux.crossentropy(model(x), y)
optimizer = Flux.ADAM(params(model))

# Training loop
function train_model(model, train_data, optimizer, loss_function, epochs)
    for epoch in 1:epochs
        @info "Epoch $epoch"
        println("Epoch $epoch")
        for (x, y) in train_data
            x, y = x |> gpu, y |> gpu  # Move input data to GPU if using GPU
            Flux.train!(loss_function, Flux.params(model), [(x, y)], optimizer)
        end
    end
end


println("start: ")

# Train the model
epochs = 10
train_model(model, train_X, optimizer, loss, epochs)

# Evaluation
function evaluate_model(model, test_data)
    accuracy = 0
    for (x, y) in test_data
        accuracy += sum(onecold(model(x)) .== onecold(y))
    end
    return accuracy / length(test_data)
end

test_accuracy = evaluate_model(model, test_X)
println("Test Accuracy: $test_accuracy")
