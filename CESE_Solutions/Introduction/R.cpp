#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--)
    {
        int k;
        cin >> k;

        int length = 1; 
        int count = 9;  
        int start = 1;  

        while (k > length * count)
        {
            k -= length * count;
            length++;
            count *= 10;
            start *= 10;
        }

        int number = start + (k - 1) / length;

        int digit_pos = (k - 1) % length;
        string num_str = to_string(number);
        cout << num_str[digit_pos] << endl;
    }

    return 0;
}