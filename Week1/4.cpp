#include <bits/stdc++.h>
using namespace std;

// Function to compute dy/dx
double get_IVP(double x, double y) {
    return x * x * x * exp(-2 * x) - 2 * y;
}

// solution for comparison
double value(double x) {
    return (exp(-2 * x) / 4) * (x * x * x * x + 4);
}

int main() {
    double h = 0.1; // Initial step size

    ofstream outFile1("results1.txt");
    ofstream outFile2("results2.txt");
    ofstream outFile3("results3.txt");
    ofstream actualFile("actual.txt");

    // Run Euler's method with three step sizes
    for (int k = 0; k < 3; k++) {
        double y = 1;  
        double x = 0; 

        while (x <= 1.0 ) { 
            double f = get_IVP(x, y);  
            double actual = value(x); 
            
            if (k == 0) {
                outFile1 << fixed << setprecision(6) << x << " " << y << endl;
                actualFile << fixed << setprecision(6) << x << " " << actual << endl;
            } else if (k == 1) {
                outFile2 << fixed << setprecision(6) << x << " " << y << endl;
            } else {
                outFile3 << fixed << setprecision(6) << x << " " << y << endl;
            }

            y = y + f * h; // Euler update
            x += h;        // Increment x
        }

        h /= 2; // Halve the step size for the next iteration
    }

    // Close all files
    outFile1.close();
    outFile2.close();
    outFile3.close();
    actualFile.close();

    // Generate Gnuplot command for visualization
    string gnuplotCommand =
        "gnuplot -p -e \""
        "set terminal pngcairo size 800,600; "
        "set output 'output_4.png'; "
        "set xlabel 'x'; "
        "set ylabel 'y'; "
        "set title 'Euler Method vs Exact Solution'; "
        "plot 'results1.txt' with lines title 'h=0.1', "
        "'results2.txt' with lines title 'h=0.05', "
        "'results3.txt' with lines title 'h=0.025', "
        "'actual.txt' with lines title 'Exact';\"";

    // Execute Gnuplot command
    system(gnuplotCommand.c_str());

    return 0;
}
