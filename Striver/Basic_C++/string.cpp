#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s = "anand m k";
    int len = s.size(); // length of string
    s[1] = 'a';
    // s[5] = "a"; //can not use ""
    cout << s << endl;
    cout << len;
    return 0;
}