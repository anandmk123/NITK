#include<bits/stdc++.h>
using namespace std;

void addone(int &x,int a[]){
    x++;
    a[1]=3;
}


int main() {

    int x=5;
    int a[]={0,1};
    cout<<x<<endl;
    addone(x,a);
    cout<<x<<endl;
    cout<<a[1]<<endl;
    return 0;
}