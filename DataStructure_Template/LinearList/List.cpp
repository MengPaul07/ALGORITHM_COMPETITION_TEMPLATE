#include <algorithm>
#include <array>

namespace LinearListArray
{
    const int MAXSIZE = 20;

    struct List
    {
        std::array<int, MAXSIZE> data{};
        int len = 0;
    };

    // 位置 pos 使用 1-based，下同
    bool get(const List &L, int pos, int &value)
    {
        if (pos < 1 || pos > L.len)
            return false;
        value = L.data[pos - 1];
        return true;
    }

    bool insert(List &L, int pos, int value)
    {
        if (L.len >= MAXSIZE)
            return false;
        if (pos < 1 || pos > L.len + 1)
            return false;

        for (int i = L.len - 1; i >= pos - 1; i--)
            L.data[i + 1] = L.data[i];
        L.data[pos - 1] = value;
        L.len++;
        return true;
    }

    bool erase(List &L, int pos, int &value)
    {
        if (pos < 1 || pos > L.len)
            return false;
        value = L.data[pos - 1];
        for (int i = pos; i < L.len; i++)
            L.data[i - 1] = L.data[i];
        L.len--;
        return true;
    }
}





