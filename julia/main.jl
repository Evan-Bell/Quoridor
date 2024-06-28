include("createRep.jl")
include("translateMove.jl")
include("helper.jl")


train_folder = "saved_games/2024-06-24_(20:46)_(path-search | path-search)"
test_folder = "saved_games/2024-06-27_(21:01)_(path-search | path-search)"

# # # Specify the file path
# file_path = "../saved_games/2024-06-24_(20:31)_(randomBot | path-search)/round_1.txt"

using Flux
using Flux: params
using Random

using StatsBase
using Statistics

# Define the function to create the input data
function create_input_data(g::Game)

    return g.horizontal_placement, g.vertical_placement, g.player1_pos, g.player2_pos, g.p1_walls_left, g.p2_walls_left, g.p1_won
end

# Function to prepare the data for the model
function prepare_data(vec1::Array{Bool, 2}, vec2::Array{Bool, 2}, tuple1::Tuple{Int, Int}, tuple2::Tuple{Int, Int}, int1::Int, int2::Int)
    vec1_flat = vec1[:]
    vec2_flat = vec2[:]
    input_data = vcat(vec1_flat, vec2_flat, [tuple1..., tuple2...], [int1, int2])
    return input_data
end

# Generate synthetic data for training
function generate_synthetic_data(num_samples, rounds)
    X = []
    y = []

    samples_taken = 0

    println("Collecting $(num_samples) samples")

    while samples_taken < num_samples

        progress_bar(samples_taken, num_samples)

        r = rand(1:rounds)
        file_path = "../$(train_folder)/round_$(r).txt"
        g = Game(file_path)
        while !g.game_over
            randomNum = rand(0:div(length(g.lines),5))
            plural_next_moves!(g, randomNum)
            vec1, vec2, tuple1, tuple2, int1, int2, OUTPUT = create_input_data(g)
            input_data = prepare_data(vec1, vec2, tuple1, tuple2, int1, int2)
            push!(X, input_data)
            push!(y, OUTPUT)
            samples_taken += 1
        end
    end

    # Convert lists to matrices
    X = reduce(hcat, X)'
    X = Float32.(X)  # Concatenate vectors horizontally and transpose to get (num_samples, num_features)
    y = Float32.(y)       # Ensure y is a Float32 array for Flux compatibility
    y = reshape(y, 1, :)  # Reshape y to match the expected shape (column vector)
    X = reshape(X, size(X)[2], :)

    # Print dimensions for debugging
    println("X dims: ", size(X))
    println("y dims: ", size(y))

    return Flux.Data.DataLoader((X,y), batchsize=32, shuffle=true)
end

# Create the model
model = Chain(
    Dense(168, 64, relu),
    Dense(64, 32, relu),
    Dense(32, 1),
    x -> σ.(x) .> 0.5
)

# Loss function
loss_fn(x, y) = Flux.binarycrossentropy(model(x), y)

# Training function
function train_model(data_loader, epochs)
    optimizer = ADAM()
    for epoch in 1:epochs
        for batch in data_loader
            x,y = batch
            Flux.train!(loss_fn, params(model), [(x, y)], optimizer)
        end
        println("Epoch $epoch complete")
    end
end

# Generate synthetic data
data_loader = generate_synthetic_data(3000, 1000)

# Train the model
train_model(data_loader, 10000)


function runtest(test_rounds::Int)
    correct = 0
    falsepos = 0
    falseneg = 0
    total = 0

    while total < test_rounds

        randInt = rand(1:1000)
        # Test the model with new data
        file_path = "../$(test_folder)/round_$(randInt).txt"
        g = Game(file_path)
        vec1, vec2, tuple1, tuple2, int1, int2, OUTPUT = create_input_data(g)
        input_data = prepare_data(vec1, vec2, tuple1, tuple2, int1, int2)
        prediction = model(input_data)


        pred = prediction[1]
        println("\nPrediction: ", pred)
        println("Actual: ", OUTPUT)
        total += 1
        if pred == OUTPUT
            correct += 1
        elseif pred == false
            falseneg += 1
        else
            falsepos += 1
        end

    end

    accuracy = Float64(correct) / total  # Convert correct to Float64 for accurate division
    falsepos_rate = Float64(falsepos) / total  # Convert correct to Float64 for accurate division
    falseneg_rate = Float64(falseneg) / total  # Convert correct to Float64 for accurate division
    # Print statements with accuracy
    println("\n\n")
    println("Total     $(total)\n")

    println("Correct   $(correct)")
    println("Accuracy  $(accuracy)\n")

    println("False Pos $(falsepos)")
    println("rate      $(falsepos_rate)\n")

    println("False Neg $(falseneg)")
    println("rate      $(falseneg_rate)")
end

runtest(1000)