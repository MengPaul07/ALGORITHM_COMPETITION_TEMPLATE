#include <cstring>
#include <string>
using namespace std;

namespace Trie
{
    const int N = 100000;
    int tr[N][26], endCnt[N], idx;

    void init()
    {
        memset(tr, 0, sizeof(tr));
        memset(endCnt, 0, sizeof(endCnt));
        idx = 1; // 1 号点作为根
    }

    void insert(const string &s)
    {
        int p = 1;
        for (char c : s)
        {
            int u = c - 'a';
            if (!tr[p][u])
                tr[p][u] = ++idx;
            p = tr[p][u];
        }
        endCnt[p]++;
    }

    int countWord(const string &s)
    {
        int p = 1;
        for (char c : s)
        {
            int u = c - 'a';
            if (!tr[p][u])
                return 0;
            p = tr[p][u];
        }
        return endCnt[p];
    }

    int countPrefix(const string &s)
    {
        int p = 1;
        int sum = 0;
        for (char c : s)
        {
            int u = c - 'a';
            if (!tr[p][u])
                break;
            p = tr[p][u];
            sum += endCnt[p];
        }
        return sum;
    }

    namespace ZeroOneTrie
    {
        const int B = 31;
        int tr[N][2], idx;

        void init()
        {
            memset(tr, 0, sizeof(tr));
            idx = 1;
        }

        void insert(int x)
        {
            int p = 1;
            for (int i = B; i >= 0; i--)
            {
                int u = (x >> i) & 1;
                if (!tr[p][u])
                    tr[p][u] = ++idx;
                p = tr[p][u];
            }
        }

        // 返回与 x 异或后的最大值
        int maxXor(int x)
        {
            int p = 1;
            int res = 0;
            for (int i = B; i >= 0; i--)
            {
                int u = (x >> i) & 1;
                int want = u ^ 1;
                if (tr[p][want])
                {
                    res = (res << 1) | 1;
                    p = tr[p][want];
                }
                else
                {
                    res <<= 1;
                    p = tr[p][u];
                }
            }
            return res;
        }
    }
}