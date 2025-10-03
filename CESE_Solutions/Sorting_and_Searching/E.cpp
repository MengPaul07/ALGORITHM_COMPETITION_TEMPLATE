
//===================离散化差分======================

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<pair<int, int>> events; 

    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        events.push_back({a, 1});  
        events.push_back({b, -1}); 
    }

    sort(events.begin(), events.end(), [](const pair<int, int> &x, const pair<int, int> &y)
         {
        if (x.first == y.first) {
            return x.second < y.second; // 时间相同，-1排前面
        }
        return x.first < y.first; });

    int current = 0, max_customers = 0;

    for (auto &event : events)
    {
        current += event.second;
        max_customers = max(max_customers, current);
    }

    cout << max_customers << endl;
    return 0;
}


/*
1 +1
2 -1
3 -1
3 +1
*/