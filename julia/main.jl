include("createRep.jl")
include("translateMove.jl")
include("helper.jl")

using Flux
using Flux: params
using Random

using StatsBase
using Statistics

# Define the function to create the input data
function create_input_data(g::Game)

    return g.horizontal_placement, g.vertical_placement, g.player_pos, g.p1_walls_left, g.p2_walls_left, g.p1_won
end

# Function to prepare the data for the model
function prepare_data(horWallMatrix::Array{Bool, 2}, verWallMatrix::Array{Bool, 2}, playerPos::Array{Int, 2}, int1::Int, int2::Int)
    horWallMatrix_flat = horWallMatrix[:]
    verWallMatrix_flat = verWallMatrix[:]
    playerPos_flat = playerPos[:]
    input_data = vcat(horWallMatrix_flat, verWallMatrix_flat, playerPos_flat, [int1, int2])
    return input_data
end


# Generate synthetic data for training
function generate_synthetic_data(num_samples, rounds, folder, batchsize = 1)
    X = []
    y = []

    samples_taken = 0

    while samples_taken < num_samples

        progress_bar(samples_taken, num_samples)

        r = rand(1:rounds)
        file_path = "../$(folder)/round_$(r).txt"
        g = Game(file_path)

        while !g.game_over && samples_taken < num_samples
            randomNum = rand(0:div(length(g.lines),5))
            plural_next_moves!(g, randomNum)
            horWallMatrix, verWallMatrix, playerPos, p1Walls, p2Walls, OUTPUT = create_input_data(g)

            tensor3D = cat(horWallMatrix, verWallMatrix, playerPos, dims=3)
            push!(X, (tensor3D, Float32(p1Walls), Float32(p2Walls)))
            push!(y, OUTPUT)
            samples_taken += 1
        end
    end

    y = reshape(y, 1, :)  # Reshape y to match the expected shape (column vector)
    X = reshape(X, :, size(X)[1])

    # Print dimensions for debugging
    println("X dims: ", size(X))
    println("y dims: ", size(y))

    return Flux.Data.DataLoader((X,y), batchsize=batchsize, shuffle=true)
end



# Define a basic CNN model
function build_cnn()
    return Chain(
        x -> cat(x..., dims=4),
        Conv((3, 3), 3=>16, relu, pad=(1, 1), dilation=(1, 1)),  # 3x3 convolution, 3 input channels, padding = 1, dilation = 1
        # MaxPool((3, 3)),              # Max pooling 3x3
        # Conv((3, 3), 16=>32, relu),   # 3x3 convolution, 16 input channels, 32 output channels
        MaxPool((3, 3)),              # Max pooling 3x3
        x -> reshape(x, :, size(x, 4)),  # Flatten to 2D array (vectorize)
    )
end

# Define a model combining CNN with Dense layers and input preprocessing
function build_combined_model()
    cnn_model = build_cnn()

    return Chain(
        # x -> cat(cnn_model(getindex.(x, 1)), getindex.(x, 2), getindex.(x, 3), dims=1),  # Pass tensor3D through CNN model, keep integers intact
        x -> begin
            cnn_output = cnn_model(getindex.(x, 1))  # Pass tensor3D through CNN model
            int1 = getindex.(x, 2)  # Extract int1
            int2 = getindex.(x, 3)  # Extract int2
            cat(cnn_output, int1, int2, dims=1)  # Flatten CNN output and concatenate integers
        end,
        Dense(146, 64, relu),   # Dense layer 1: 2592 inputs (36*24), 64 outputs
        Dense(64, 32, relu),     # Dense layer 2: 64 inputs, 32 outputs
        Dense(32, 1),            # Dense layer 3: 32 inputs, 1 output
        x -> σ.(x) .> 0.5        # Output layer with sigmoid activation for binary classification
    )
end

# Training function
function train_model(data_loader, epochs)
    optimizer = ADAM()
    for epoch in 1:epochs
        for batch in data_loader
            x,y = batch
            # println(size(cat(getindex.(x, 1)..., dims=4)))
            # println(size(getindex.(x, 2)))
            # println(typeof(getindex.(x, 2)))
            Flux.train!(loss_fn, params(model), [(x, y)], optimizer)
        end
        println("Epoch $epoch complete")
    end
end

function runtest(test_rounds::Int)
    correct = 0
    falsepos = 0
    falseneg = 0
    actual = 0

    data_loader = generate_synthetic_data(test_rounds, 1000, test_folder, 1)
    for (x,y) in data_loader
        TRUTH = y[1][1]
        prediction = model(x)
        pred = prediction[1]
        println("\nPrediction: ", pred)
        println("Actual: ", TRUTH)
        if pred == TRUTH
            correct += 1
        elseif pred == false
            falseneg += 1
        else
            falsepos += 1
        end

        if TRUTH == true
            actual += 1
        end

    end

    accuracy = Float64(correct) / test_rounds  # Convert correct to Float64 for accurate division
    falsepos_rate = Float64(falsepos) / test_rounds  # Convert correct to Float64 for accurate division
    falseneg_rate = Float64(falseneg) / test_rounds  # Convert correct to Float64 for accurate division
    # Print statements with accuracy
    println("\n\n")
    println("Total     $(test_rounds)")
    println("True      $(actual)\n")

    println("Correct   $(correct)")
    println("Accuracy  $(accuracy)\n")

    println("False Pos $(falsepos)")
    println("rate      $(falsepos_rate)\n")

    println("False Neg $(falseneg)")
    println("rate      $(falseneg_rate)")
end





TRAIN_FOLDER = "saved_games/2024-06-24_(20:46)_(path-search | path-search)"
TRAIN_NUM_DATA_SAMPLES = 1200
TRAIN_BATCH_SIZE = 8
EPOCHS = 100


test_folder = "saved_games/2024-06-27_(21:01)_(path-search | path-search)"
TEST_NUM_DATA_SAMPLES = 1000


# Build the model
model = build_combined_model()

# Loss function
loss_fn(x, y) = Flux.binarycrossentropy(model(x), y)
# Generate synthetic data
data_loader = generate_synthetic_data(TRAIN_NUM_DATA_SAMPLES, 1000, TRAIN_FOLDER, TRAIN_BATCH_SIZE)

# Train the model
train_model(data_loader, EPOCHS)


runtest(TEST_NUM_DATA_SAMPLES)