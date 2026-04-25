#include <vector>
using namespace std;

namespace UnionFind
{
    int find(vector<int> &parent, int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent, parent[x]);
        return parent[x];
    }

    bool unite(vector<int> &parent, int x, int y)
    {
        int rx = find(parent, x);
        int ry = find(parent, y);
        if (rx == ry)
            return false;
        parent[ry] = rx;
        return true;
    }
}