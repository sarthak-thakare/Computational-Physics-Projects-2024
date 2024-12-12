#include<bits/stdc++.h>
using namespace std;

double find_func(double radius,double theta){
    return  radius*(2*M_PI-theta)-4*radius*sin(theta/2);
}

double differentiate(double radius,double theta){
    return -radius-2*radius*cos(theta/2);
}

double find_theta(double radius,double theta){
    double prev=0;
    while(fabs(theta-prev)>1e-18){
        
        double func=find_func(radius,theta);
        double diff=differentiate(radius,theta);
        prev=theta;
        theta=theta-func/diff;
    }
    return theta;
}


int main(){
    double radius=1;
    double theta=M_PI/2;   //(guess)
    

    theta=find_theta(radius,theta);
    double chord=2*radius*sin(theta/2);
    
    cout<<fixed<<setprecision(18)<<chord;
    
}