#include<bits/stdc++.h>
using namespace std;


// Function to compute the derivatives 
void van_der_pol(double x,double y,double mu,double dxdt,double dydt) {
    dxdt= mu*(x-(1.0/3.0)*x*x*x-y);
    dydt=x/mu;
}

// Euler's method
void euler_method(double mu,double dt,int steps,vector<double>time,vector<double>x_vals,vector<double>y_vals) {
    double x = 2.0, y = 0.0; // Initial conditions
    for (int i = 0; i < steps; ++i) {
        double dxdt, dydt;
        van_der_pol(x, y, mu, dxdt, dydt);
        x += dxdt * dt;
        y += dydt * dt;

        time.push_back(i * dt);
        x_vals.push_back(x);
        y_vals.push_back(y);
    }
}

// RK4 method
void rk4_method(double mu,double dt,int steps,vector<double>time,vector<double>x_vals,vector<double>y_vals) {
    double x = 2.0, y = 0.0; // Initial conditions
    for (int i = 0; i < steps; ++i) {
        double k1x, k1y, k2x, k2y, k3x, k3y, k4x, k4y;
        van_der_pol(x,y,mu,k1x,k1y);

        double x2=x+0.5*k1x*dt;
        double y2=y+0.5*k1y*dt;
        van_der_pol(x2, y2, mu, k2x, k2y);

        double x3=x+0.5*k2x*dt;
        double y3=y+0.5*k2y*dt;
        van_der_pol(x3, y3, mu, k3x, k3y);

        double x4=x+k3x*dt;
        double y4=y+k3y*dt;
        van_der_pol(x4, y4, mu, k4x, k4y);

        x += (dt / 6.0) * (k1x + 2 * k2x + 2 * k3x + k4x);
        y += (dt / 6.0) * (k1y + 2 * k2y + 2 * k3y + k4y);

        time.push_back(i * dt);
        x_vals.push_back(x);
        y_vals.push_back(y);
    }
}

double value(double x){
    return x-x*x*x/3;
}

// Write data to a file for GNUplot
void write_data(string filename,vector<double>time,vector<double>x_vals,vector<double>y_vals) {
    ofstream file(filename);
    for (int i = 0; i < time.size(); ++i) {
        double actual=value(x_vals[i]);
        file << time[i] << " " << x_vals[i] << " " << y_vals[i] << " " << actual << "\n";
    }
    file.close();
}

int main() {
    double mu = 7.0, dt = 0.1;
    int steps = 1000;

    vector<double> time_euler, x_euler, y_euler,time_rk4, x_rk4, y_rk4;

    // Solve using Euler's method
    euler_method(mu,dt,steps,time_euler,x_euler,y_euler);

    // Solve using RK4 method
    rk4_method(mu,dt,steps,time_rk4,x_rk4,y_rk4);

    // Write data for Euler's method
    write_data("euler_data.txt",time_euler,x_euler,y_euler);

    // Write data for RK4 method
    write_data("rk4_data.txt",time_rk4,x_rk4,y_rk4);

    
    string gnuplotCommand =
        "gnuplot -p -e \""
        "set terminal pngcairo size 1200,800; "
        "set output 'van_der_pol.png'; "
        "set multiplot layout 2,2 title 'Van der Pol Oscillator'; "
        
        
        "set xlabel 'x'; set ylabel 'y'; "
        "set title 'y vs x'; "
        "plot 'euler_data.txt' using 2:3 with lines title 'Euler', "
        "'rk4_data.txt' using 2:4 with lines title 'Exact', "
        "'rk4_data.txt' using 2:3 with lines title 'RK4'; "


        "set xlabel 'Time (t)'; set ylabel 'x'; "
        "set title 'x vs t'; "
        "plot 'euler_data.txt' using 1:2 with lines title 'Euler', "
        "'rk4_data.txt' using 1:2 with lines title 'RK4'; "

        "set xlabel 'Time (t)'; set ylabel 'y'; "
        "set title 'y vs t'; "
        "plot 'euler_data.txt' using 1:3 with lines title 'Euler', "
        "'rk4_data.txt' using 1:3 with lines title 'RK4'; "

        "unset multiplot;\"";

    // Execute gnuplot command
    system(gnuplotCommand.c_str());


}
