#include<bits/stdc++.h>
using namespace std;


float equation(float x) {
    return x*x-8*x+11;
}

float differentiate(float x) {
    return 2*x-8;
}

float raphson(float x0,int decimal_digits) {
    float precision=pow(10,-decimal_digits);
    float prev = 0;
    while(fabs(x0 - prev) >precision ) {
        float diff = differentiate(x0);    
        float temp = equation(x0);         
        prev = x0;                         
        x0 = x0 - temp / diff;             // Newton-Raphson formula
    }
    return x0;
}

int main() {
    float x0 = 6;                      // Initial guess
    int decimal_digits=5;
    float ans = raphson(x0,decimal_digits);            // Find the root using Newton-Raphson
    cout << fixed << setprecision(5) << ans << endl; // Print the result rounded to 5 decimal places
    return 0;
}
