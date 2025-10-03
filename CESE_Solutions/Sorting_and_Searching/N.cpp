#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int x, n;
    cin >> x >> n;
  
    set<int> lights;
    lights.insert(0);
    lights.insert(x);

    multiset<int> lengths;
    lengths.insert(x - 0);


    for (int i = 0; i < n; ++i)
    {
        int p;
        cin >> p;
    
        auto it_r = lights.upper_bound(p);
        auto it_l = prev(it_r);

        int r = *it_r;
        int l = *it_l;
 
        lengths.erase(lengths.find(r - l));

        lengths.insert(p - l);
        lengths.insert(r - p);
        lights.insert(p);

        cout << *lengths.rbegin() << " ";
    }

    return 0;
}