#include <bits/stdc++.h>
using namespace std;


const double rho = 28;       
const double sigma = 10.0;      
const double betaa = 8.0 / 3.0; 
const double t_max = 50.0;      // Maximum simulation time
const double h = 0.01;          // Step size for Euler's method

// Function dx/dt
double dxdt(double x, double y) {
    return sigma * (y - x);
}

// Function dy/dt
double dydt(double x, double y, double z) {
    return x * (rho - z) - y;
}

// Function dz/dt
double dzdt(double x, double y, double z) {
    return x * y - betaa * z;
}

int main() {
    // Initial conditions
    double x = 1.0, y =1.0, z = 1.0, t = 0.0;

    // Output file to store Lorenz attractor data
    ofstream dataFile("lorenz_data.txt");
 
    // Euler's method loop
    while (t <= t_max) {
        // Write current state to file
        dataFile << t << " " << x << " " << y << " " << z << endl;

        // Update values using Euler's method
        double x_new =x+h*dxdt(x, y);
        double y_new=y+h*dydt(x, y, z);
        double z_new=z+h*dzdt(x, y, z);

        // Advance variables
        x = x_new;
        y = y_new;
        z = z_new;
        t += h;
    }

    
    dataFile.close();

    // Gnuplot commands to visualize the Lorenz attractor
    string gnuplotCommand3D =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_3d_4.png'; "
        "set title '3D Lorenz Attractor'; "
        "set xlabel 'X'; set ylabel 'Y'; set zlabel 'Z'; "
        "set grid; set view 60,30; "
        "splot 'lorenz_data.txt' using 2:3:4 with lines title 'Lorenz Attractor';\"";
    system(gnuplotCommand3D.c_str());

    string gnuplotCommandXY =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_xy_4.png'; "
        "set title 'Lorenz Attractor (XY Plane)'; "
        "set xlabel 'X'; set ylabel 'Y'; "
        "set grid; "
        "plot 'lorenz_data.txt' using 2:3 with lines title 'XY Projection';\"";
    system(gnuplotCommandXY.c_str());

    string gnuplotCommandXZ =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_xz_4.png'; "
        "set title 'Lorenz Attractor (XZ Plane)'; "
        "set xlabel 'X'; set ylabel 'Z'; "
        "set grid; "
        "plot 'lorenz_data.txt' using 2:4 with lines title 'XZ Projection';\"";
    system(gnuplotCommandXZ.c_str());

    string gnuplotCommandYZ =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_yz_4.png'; "
        "set title 'Lorenz Attractor (YZ Plane)'; "
        "set xlabel 'Y'; set ylabel 'Z'; "
        "set grid; "
        "plot 'lorenz_data.txt' using 3:4 with lines title 'YZ Projection';\"";
    system(gnuplotCommandYZ.c_str());
}

