function progress_bar(current::Int, total::Int)
  # Clear previous progress bar (move cursor up one line and clear it)
  if current > 1
      print("\u001b[1A")  # Move cursor up one line
      print("\u001b[2K")  # Clear current line
  end

  # Calculate percentage progress
  progress_percent = round(Int, 100 * current / total)

  # Print the progress bar with current and total count
  println("Progress: [", "#"^progress_percent, " "^(100 - progress_percent), "] ",
          current, "/", total, " (", progress_percent, "%)")

  # Simulate some work (replace this with your actual work)
  sleep(0.1)
end

# # Example usage
# total_iterations = 50  # Replace with your total number of iterations/tasks
# for i in 1:total_iterations
#   progress_bar(i, total_iterations)
# end
