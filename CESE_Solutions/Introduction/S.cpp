#include <bits/stdc++.h>
using namespace std;

char buf[1000005];
int abc[26];
bool abcc[26] = {0};

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (scanf("%s", buf) != 1)
        return 0;
    string s = buf;
    string ss;

    vector<int> v(26, 0);

    sort(s.begin(), s.end());
    int l = s.length();

    for (int i = 0; i < l; i++)
        ss.push_back(' ');

    for (int i = 0; i < l; i++)
        v[s[i] - 'A']++;

    for (int i : v)
        if (i > (l + 1) / 2)
        {
            printf("-1");
            return 0;
        }

    int pos = 0;
    for (int i = 0; i < s.length(); i++)
    {
        for (int j = 0; j < 26; j++)
            if (v[j] && !abcc[j])
            {
                ss[i] = char(j + 'A');
                v[j]--;
                memset(abcc, 0, sizeof(abcc));
                abcc[j] = 1;
                break;
            }
    }
    for (int i = 0; i < ss.length(); i++)
    {
        if (ss[i] == ' ')
            ss[i] = ss[i - 1];
    }

    for (int i = l - 1; i > 0; i--)
    {
        if (ss[i] == ss[i - 1])
            for (int j = i - 1; j >= 0; j--)
            {
                if (ss[j] != ss[i - 1])
                {
                    swap(ss[i - 1], ss[j]);
                    break;
                }
            }
    }
    printf("%s\n", ss.c_str());
    return 0;
}