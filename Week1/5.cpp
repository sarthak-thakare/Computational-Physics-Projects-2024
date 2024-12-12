#include <bits/stdc++.h>
using namespace std;


double func(double x,double y){
    return x*x*x*exp(-2*x)-2*y;
}

double value(double x){
    return (exp(-2*x)/4)*(x*x*x*x+4);
}

vector<double> rk4(double x,double y,double h){
    vector<double>k(4,0);
    k[0]=func(x,y);
    k[1]=func(x+h/2,y+(h/2)*k[0]);
    k[2]=func(x+h/2,y+(h/2)*k[1]);
    k[3]=func(x+h,y+h*k[2]);
    vector<double>ans(2,0);
    ans[1]=y+(h/6)*(k[0]+2*k[1]+2*k[2]+k[3]);
    ans[0]=x+h;

    return ans;
}

int main(){

    double y=1;
    double x=0;
    double h=0.1;

    ofstream outFile1("results_5.txt");
    ofstream actual1("actual_5.txt");
  
    outFile1<< x << " " << y << endl;
    actual1<<x<<" "<<y<<endl;

    for(int i=0;i<10;i++){
        double f=func(x,y);
        vector<double>temp;
        temp=rk4(x,y,h);
        x=temp[0];
        y=temp[1];
        double actual=value(x);
    
        outFile1<< x << " " << y << endl;
        actual1<<x<<" "<<actual<<endl;
    }
    outFile1.close();
    actual1.close();
    string gnuplotCommand = "gnuplot -p -e \""
                                "set terminal pngcairo size 800,600; "  
                                "set output '5.png'; "
                                "set xlabel 'x';"
                                "set ylabel 'y';"
                                "plot 'results_5.txt' with lines title 'h=0.1', "
                                 "'actual_5.txt' with lines title 'actual', \"";

    system(gnuplotCommand.c_str());

}
