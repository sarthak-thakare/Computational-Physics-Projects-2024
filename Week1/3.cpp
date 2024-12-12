#include<bits/stdc++.h>
using namespace std;

double value(double x){
   return exp(2*x)+x-5;
}
int main(){
   double x0=0,x1=1,y=value(x0),x;

   while(fabs(y)>1e-5){
      double y0=value(x0),y1=value(x1);
      x=x1-((x0-x1)/(y0-y1))*y1;
      y=value(x);
      if(y*y0>=0){
         x0=x;
      }
      else{
         x1=x;
      }
   }
   cout<<fixed<<setprecision(3)<<x;
}