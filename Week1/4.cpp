#include <bits/stdc++.h>
using namespace std;


double get_IVP(double x,double y){
    return x*x*x*exp(-2*x)-2*y;
}

double value(double x){
    return (exp(-2*x)/4)*(x*x*x*x+4);
}

int main(){

    
    double h=0.1;

    ofstream outFile1("results1.txt");
    ofstream outFile2("results2.txt");
    ofstream outFile3("results3.txt");

    ofstream actual1("actual.txt");
  
    

    for(int k=0;k<3;k++){   
        double y=1;
        double x=0;
        
        for(int i=0;i<=10;i++){
        x=double(i)/10;
        double f=get_IVP(x,y);
        double actual=value(x);  
        y=y+f*h;
        if(k==0){outFile1<< x << " " << y << endl;
                actual1<<x<<" "<<actual<<endl;
        }
        else if(k==1){
            outFile2<< x << " " << y << endl;
        }
        else {outFile3<< x << " " << y << endl;
        }
        }
        h/=2;
        }

        outFile1.close();
        outFile2.close();
        outFile3.close();
        actual1.close();
        string gnuplotCommand = "gnuplot -p -e \""
                                    "set terminal pngcairo size 800,600; "  
                                    "set output 'output_4.png'; "
                                    "set xlabel 'x';"
                                    "set ylabel 'y';"
                                    "plot 'results1.txt' with lines title 'h=0.1', "
                                    "'results2.txt' with lines title 'h=0.05', "
                                    "'results3.txt' with lines title 'h=0.025',"
                                    "'actual.txt' with lines title 'actual', \"";

        system(gnuplotCommand.c_str());

}
