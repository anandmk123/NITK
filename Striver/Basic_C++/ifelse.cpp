#include <bits/stdc++.h>
using namespace std;
int main()
{
    int age;
    cin >> age;
    if (age >= 18)
    {
        cout << "You are an adult with age = " << age << "\n";
    }
    else
    {
        cout << "You are not an adult with age = " << age << "\n";
    }
    return 0;
}