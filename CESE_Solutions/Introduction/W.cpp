#include <bits/stdc++.h>
using namespace std;

int a[26] = {0};
int dcnt = 0;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s, ss;
    cin >> s;

    for (int i = 0; i < s.length(); i++)
    {
        a[s[i] - 'A']++;
    }
    for (int i = 0; i < 26; i++)
        if (a[i] % 2 == 1)
            dcnt++;

    if (dcnt > 1)
        cout << "NO SOLUTION";

    else
    {
        for (int i = 0; i < 26; i++)
            if (a[i])
                for (int j = 0; j < a[i] / 2; j++)
                {
                    ss += char(i + 'A');
                }
        for (int i = 0; i < 26;i++){
            if(a[i]%2==1)
                ss += char(i + 'A');
        }
        for (int i = 25; i >=0; i--)
        {
            for (int j = 0; j < a[i] / 2; j++)
            {
                ss += char(i + 'A');
            }
        }
    cout << ss;
    }
    return 0;
}

