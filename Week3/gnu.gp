set terminal pngcairo size 800, 600
set output 'plot_1_-2.png'

set title 'Potential Field due to Two Charges'
set xlabel 'Y'
set ylabel 'X'
set cblabel 'Potential'

# Define a smooth color palette resembling the example
set palette rgbformulae 21,22,23

# Set the range of the color bar to highlight the field
set cbrange [-1:1]  # Adjust based on your data; [-1:1] is an example.

# Use 2D projection for a flat potential field map
set view map

# Plot the potential field from the data file
plot 'field_sparse.txt' using 2:1:3 with image

# Reset output
set output
