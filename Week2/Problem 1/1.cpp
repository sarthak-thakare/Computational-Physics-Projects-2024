#include <bits/stdc++.h>
using namespace std;

// Function to compute dy2/dx
double get_IVP2(double x, double y1, double y2) {
    return sin(x)+2*cos(x)-3*y1-4*y2;
}


// Exact solution for comparison
double value(double x) {
    return sin(x)/2+(0.25)*exp(-3*x)+(0.75)*exp(-x);
}

// Runge-Kutta 4th Order Method
vector<double> rk4(double x, double y1, double y2, double h) {
    double k1_y1, k2_y1, k3_y1, k4_y1;
    double k1_y2, k2_y2, k3_y2, k4_y2;

    k1_y1 = y2;
    k1_y2 = get_IVP2(x, y1, y2);

    k2_y1 = y2 + 0.5 * h * k1_y2;
    k2_y2 = get_IVP2(x + 0.5 * h, y1 + 0.5 * h * k1_y1, k2_y1);

    k3_y1 = y2 + 0.5 * h * k2_y2;
    k3_y2 = get_IVP2(x + 0.5 * h, y1 + 0.5 * h * k2_y1, k3_y1);

    k4_y1 = y2 + h * k3_y2;
    k4_y2 = get_IVP2(x + h, y1 + h * k3_y1,k4_y1);

    vector<double> ans(3, 0);
    ans[0] = x + h;
    ans[1] = y1 + (h / 6.0) * (k1_y1 + 2 * k2_y1 + 2 * k3_y1 + k4_y1);
    ans[2] = y2 + (h / 6.0) * (k1_y2 + 2 * k2_y2 + 2 * k3_y2 + k4_y2);

    return ans;
}

int main() {
    double h = 0.1;

    // Euler's Method Output Files
    ofstream outFileEuler1("results1.txt");
    ofstream outFileEuler2("results2.txt");
    ofstream actualEuler("actual_euler.txt");

    // Euler's Method
    for (int k = 0; k < 2; k++) {
        double x = 0, y1 = 1, y2 = -1;

        while (x <= 10) {
            double actual = value(x);
            if (k == 0) {
                outFileEuler1 << fixed << setprecision(6) << x << " " << y1 << endl;
                actualEuler << fixed << setprecision(6) << x << " " << actual << endl;
            } else {
                outFileEuler2 << fixed << setprecision(6) << x << " " << y1 << endl;
            }

            double f1 = y2;
            double f2 = get_IVP2(x, y1, y2);

            y2 += f2 * h;
            y1 += f1 * h;
            x += h;
        }

        h /= 10;
    }

    outFileEuler1.close();
    outFileEuler2.close();
    actualEuler.close();

    // RK4 Method Output Files
    ofstream outFileRK4("results_rk4.txt");
    ofstream actualRK4("actual_rk4.txt");

    double x = 0, y1 = 1, y2 = -1;
    h = 0.1;

    while (x <= 10) {
        double actual = value(x);
        outFileRK4 << fixed << setprecision(6) << x << " " << y1 << endl;
        actualRK4 << fixed << setprecision(6) << x << " " << actual << endl;

        vector<double> temp = rk4(x, y1, y2, h);
        x = temp[0];
        y1 = temp[1];
        y2 = temp[2];
    }

    outFileRK4.close();
    actualRK4.close();

    // Gnuplot for Euler's Method
    string gnuplotCommandEuler =
        "gnuplot -p -e \""
        "set terminal pngcairo size 800,600; "
        "set output 'output_euler.png'; "
        "set xlabel 'x'; set ylabel 'y'; "
        "set title 'Euler Method vs Exact Solution'; "
        "plot 'results1.txt' with lines title 'h=0.1', "
        "'results2.txt' with lines title 'h=0.01', "
        "'actual_euler.txt' with lines title 'Exact';\"";
    system(gnuplotCommandEuler.c_str());

    // Gnuplot for RK4
    string gnuplotCommandRK4 =
        "gnuplot -p -e \""
        "set terminal pngcairo size 800,600; "
        "set output 'output_rk4.png'; "
        "set xlabel 'x'; set ylabel 'y'; "
        "set title 'RK4 Method vs Exact Solution'; "
        "plot 'results_rk4.txt' with lines title 'RK4 h=0.1', "
        "'actual_rk4.txt' with lines title 'Exact';\"";
    system(gnuplotCommandRK4.c_str());

    return 0;
}

