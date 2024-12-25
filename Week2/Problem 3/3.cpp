#include <bits/stdc++.h>
using namespace std;

const double rho = 99.96;       
const double sigma = 10.0;      
const double betaa = 8.0 / 3.0; 
const double h = 0.001;          // Step size for Euler's method

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

//RK4 method
void rk4_step(double& x, double& y, double& z, double& t) {
    double k1x = h * dxdt(x, y);
    double k1y = h * dydt(x, y, z);
    double k1z = h * dzdt(x, y, z);

    double k2x = h * dxdt(x + 0.5 * k1x, y + 0.5 * k1y);
    double k2y = h * dydt(x + 0.5 * k1x, y + 0.5 * k1y, z + 0.5 * k1z);
    double k2z = h * dzdt(x + 0.5 * k1x, y + 0.5 * k1y, z + 0.5 * k1z);

    double k3x = h * dxdt(x + 0.5 * k2x, y + 0.5 * k2y);
    double k3y = h * dydt(x + 0.5 * k2x, y + 0.5 * k2y, z + 0.5 * k2z);
    double k3z = h * dzdt(x + 0.5 * k2x, y + 0.5 * k2y, z + 0.5 * k2z);

    double k4x = h * dxdt(x + k3x, y + k3y);
    double k4y = h * dydt(x + k3x, y + k3y, z + k3z);
    double k4z = h * dzdt(x + k3x, y + k3y, z + k3z);


    x += (k1x + 2*k2x + 2*k3x + k4x) / 6;
    y += (k1y + 2*k2y + 2*k3y + k4y) / 6;
    z += (k1z + 2*k2z + 2*k3z + k4z) / 6;

    t += h;
}

int main() {
    // Initial conditions
    double x_euler = 1.0, y_euler = 1.0, z_euler = 1.0;
    double x_rk4 = 1.0, y_rk4 = 1.0, z_rk4 = 1.0;
    double t = 0.0;

    // Output files to store Lorenz attractor data
    ofstream dataFileEuler("lorenz_data_euler.txt");
    ofstream dataFileRK4("lorenz_data_rk4.txt");
 
    int steps = 60000;
    // Euler method loop
    for (int i = 0; i < steps; ++i) {
        // Euler Method: Write current state to file
        dataFileEuler << t << " " << x_euler << " " << y_euler << " " << z_euler << endl;
        // Update values using Euler's method
        double x_new = x_euler + h * dxdt(x_euler, y_euler);
        double y_new = y_euler + h * dydt(x_euler, y_euler, z_euler);
        double z_new = z_euler + h * dzdt(x_euler, y_euler, z_euler);

        // Advance variables
        x_euler = x_new;
        y_euler = y_new;
        z_euler = z_new;
        t += h;
    }

    t = 0.0; 
    // RK4 method loop
    for (int i = 0; i < steps; ++i) {
        // RK4 Method: Write current state to file
        dataFileRK4 << t << " " << x_rk4 << " " << y_rk4 << " " << z_rk4 << endl;
        // Advance variables using RK4 method
        rk4_step(x_rk4, y_rk4, z_rk4, t);
    }

    dataFileEuler.close();
    dataFileRK4.close();

    // Gnuplot commands to visualize the Lorenz attractor

    // 3D Plot for Euler's method
    string gnuplotCommand3DEuler =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_3d_euler.png'; "
        "set title '3D Lorenz Attractor (Euler)'; "
        "set xlabel 'X'; set ylabel 'Y'; set zlabel 'Z'; "
        "set grid; set view 60,30; "
        "splot 'lorenz_data_euler.txt' using 2:3:4 with lines title 'Lorenz Attractor (Euler)';\"";
    system(gnuplotCommand3DEuler.c_str());

    // 3D Plot for RK4 method
    string gnuplotCommand3DRK4 =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_3d_rk4.png'; "
        "set title '3D Lorenz Attractor (RK4)'; "
        "set xlabel 'X'; set ylabel 'Y'; set zlabel 'Z'; "
        "set grid; set view 60,30; "
        "splot 'lorenz_data_rk4.txt' using 2:3:4 with lines title 'Lorenz Attractor (RK4)';\"";
    system(gnuplotCommand3DRK4.c_str());

    // XY Projection for Euler
    string gnuplotCommandXYEuler =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_xy_euler.png'; "
        "set title 'Lorenz Attractor (XY Plane - Euler)'; "
        "set xlabel 'X'; set ylabel 'Y'; "
        "set grid; "
        "plot 'lorenz_data_euler.txt' using 2:3 with lines title 'XY Projection (Euler)';\"";
    system(gnuplotCommandXYEuler.c_str());

    // XY Projection for RK4
    string gnuplotCommandXYRK4 =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_xy_rk4.png'; "
        "set title 'Lorenz Attractor (XY Plane - RK4)'; "
        "set xlabel 'X'; set ylabel 'Y'; "
        "set grid; "
        "plot 'lorenz_data_rk4.txt' using 2:3 with lines title 'XY Projection (RK4)';\"";
    system(gnuplotCommandXYRK4.c_str());

    // XZ Projection for Euler
    string gnuplotCommandXZEuler =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_xz_euler.png'; "
        "set title 'Lorenz Attractor (XZ Plane - Euler)'; "
        "set xlabel 'X'; set ylabel 'Z'; "
        "set grid; "
        "plot 'lorenz_data_euler.txt' using 2:4 with lines title 'XZ Projection (Euler)';\"";
    system(gnuplotCommandXZEuler.c_str());

    // XZ Projection for RK4
    string gnuplotCommandXZRK4 =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_xz_rk4.png'; "
        "set title 'Lorenz Attractor (XZ Plane - RK4)'; "
        "set xlabel 'X'; set ylabel 'Z'; "
        "set grid; "
        "plot 'lorenz_data_rk4.txt' using 2:4 with lines title 'XZ Projection (RK4)';\"";
    system(gnuplotCommandXZRK4.c_str());

    // YZ Projection for Euler
    string gnuplotCommandYZEuler =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_yz_euler.png'; "
        "set title 'Lorenz Attractor (YZ Plane - Euler)'; "
        "set xlabel 'Y'; set ylabel 'Z'; "
        "set grid; "
        "plot 'lorenz_data_euler.txt' using 3:4 with lines title 'YZ Projection (Euler)';\"";
    system(gnuplotCommandXZEuler.c_str());

    // YZ Projection for RK4
    string gnuplotCommandYZRK4 =
        "gnuplot -p -e \"" 
        "set terminal pngcairo size 800,600; "
        "set output 'lorenz_yz_rk4.png'; "
        "set title 'Lorenz Attractor (YZ Plane - RK4)'; "
        "set xlabel 'Y'; set ylabel 'Z'; "
        "set grid; "
        "plot 'lorenz_data_rk4.txt' using 3:4 with lines title 'YZ Projection (RK4)';\"";
    system(gnuplotCommandXZRK4.c_str());

}
