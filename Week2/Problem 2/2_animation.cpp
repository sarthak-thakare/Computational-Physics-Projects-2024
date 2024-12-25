#include<bits/stdc++.h>
using namespace std;

// Function to compute the derivatives of the Van der Pol oscillator
void van_der_pol(double x, double y, double mu, double &dxdt, double &dydt) {
    dxdt = mu * (x - (1.0 / 3.0) * x * x * x - y);
    dydt = x / mu;
}

// RK4 method
void rk4_method(double mu,double dt,int steps,const string filename) {
    ofstream file(filename);
    double x = 2.0, y = 0.0; // Initial conditions
    double time = 0.0;

    file << "# time x y\n";
    for (int i = 0; i <= steps; ++i) {
        file << time << " " << x << " " << y << "\n";

        double k1x, k1y, k2x, k2y, k3x, k3y, k4x, k4y;

        van_der_pol(x, y, mu, k1x, k1y);
        double x2 = x + 0.5 * k1x * dt;
        double y2 = y + 0.5 * k1y * dt;
        van_der_pol(x2, y2, mu, k2x, k2y);

        double x3 = x + 0.5 * k2x * dt;
        double y3 = y + 0.5 * k2y * dt;
        van_der_pol(x3, y3, mu, k3x, k3y);

        double x4 = x + k3x * dt;
        double y4 = y + k3y * dt;
        van_der_pol(x4, y4, mu, k4x, k4y);

        x += (dt / 6.0) * (k1x + 2 * k2x + 2 * k3x + k4x);
        y += (dt / 6.0) * (k1y + 2 * k2y + 2 * k3y + k4y);
        time += dt;
    }
    file.close();
}

int main() {
    double dt = 0.1;
    int steps = 1000;

    // Generate data for animation with varying mu
     for (double mu = 0.1; mu <= 4.0; mu += 0.1) {
        string filename = "rk4_mu_" + to_string(static_cast<int>(mu * 10)) + ".dat";
        rk4_method(mu, dt, steps, filename);
    }
}
