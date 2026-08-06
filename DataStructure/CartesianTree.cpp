#include <bits/stdc++.h>
using namespace std;

namespace CartesianTree
{
    int n, root;
    vector<int> a, ls, rs;

    // 小根笛卡尔树，O(n) 单调栈建树
    void build(const vector<int> &arr)
    {
        a = arr;
        n = (int)a.size() - 1;
        ls.assign(n + 1, 0);
        rs.assign(n + 1, 0);
        stack<int> st;
        for (int i = 1; i <= n; ++i)
        {
            int last = 0;
            while (!st.empty() && a[st.top()] > a[i])
            {
                last = st.top();
                st.pop();
            }
            ls[i] = last;
            if (!st.empty())
                rs[st.top()] = i;
            else
                root = i;
            st.push(i);
        }
    }
}
