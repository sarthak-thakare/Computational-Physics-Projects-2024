#include<bits/stdc++.h>
using namespace std;

bool det(vector<vector<double>>A,vector<double>x,vector<double>B,double n){
    vector<double>res(n,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res[i]+=A[i][j]*x[j];
        }
        res[i]-=B[i];
    }
    float ans=0;
    for(double i=0;i<n;i++){
        ans+=(res[i]*res[i]);
    }
    return sqrt(ans)>1e-5;
}

vector<double>jacobi(vector<vector<double>>A,vector<double>B,vector<double>x,double n){
    vector<double>x1(n,0);

    int count=0;
    while(det(A,x,B,n) and count<100){
    for(int i=0;i<n;i++){
        double sum=0;
        for(int j=0;j<n;j++){
            if(i!=j)sum+=A[i][j]*x[j];
        }
            x1[i]=(B[i]-sum)/A[i][i];
    }
    x=x1;
    count++;
    }
    if(count==100){
        cout << "Jacobi method did not converge within 100 iterations." << endl;
    }

    return x;    
}

vector<double>gauss_seidel(vector<vector<double>>A,vector<double>B,vector<double>x,double n){
    vector<double>x2(n,0);

    int count=0;
    while(det(A,x,B,n) and count<100){
    for(int i=0;i<n;i++){
        double sum=0;
        for(int j=0;j<n;j++){
            if(i!=j){
                if(j<i)sum+=A[i][j]*x2[j];
                else sum+=A[i][j]*x[j];
            }
        }
            x2[i]=(B[i]-sum)/A[i][i];
    }
    x=x2;
    count++;
    }
    if(count ==100){
        cout << "Gauss-Seidel method did not converge within 100 iterations." << endl;
    }
    return x;
}


int main(){
    int n; // no. of equations
    cout<<"no of eqn";
    cin>>n;
    vector<vector<double>>A(n,vector<double>(n));
    vector<double>B(n);
    vector<double>x1(n),x2(n);
    vector<double>x(n);
    
    cout<<"eqn";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>A[i][j];
        }
        cin>>B[i];
    }

    // initial guess
    for(int i=0;i<n;i++){
        cin>>x[i];
    }

    x1=jacobi(A,B,x,n);
    x2=gauss_seidel(A,B,x,n);

    cout<<"Jacobi:"<<endl;
    for(double num:x1){
        cout<<num<<" ";
    }
    cout<<endl;

    cout<<"gauss_seidel:"<<endl;
    for(double num:x2){
        cout<<num<<" ";
    }
}