namespace Searching
{
    // 整数二分查找 (寻找左边界)
    // check(mid): 检查 mid 是否满足条件
    // 区间 [l, r] 被划分成 [l, mid] 和 [mid + 1, r] 时使用
    int binarySearchLeft(int l, int r, const function<bool(int)> &check)
    {
        while (l < r)
        {
            int mid = (l + r) >> 1;
            if (check(mid))
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }

    // 整数二分查找 (寻找右边界)
    // 区间 [l, r] 被划分成 [l, mid - 1] 和 [mid, r] 时使用
    int binarySearchRight(int l, int r, const function<bool(int)> &check)
    {
        while (l < r)
        {
            int mid = (l + r + 1) >> 1;
            if (check(mid))
                l = mid;
            else
                r = mid - 1;
        }
        return l;
    }

    // 实数二分查找
    // eps: 精度要求，通常比题目要求多 2 位
    double binarySearchReal(double l, double r, const function<bool(double)> &check, double eps = 1e-8)
    {
        while (r - l > eps)
        {
            double mid = (l + r) / 2;
            if (check(mid))
                r = mid;
            else
                l = mid;
        }
        return l;
    }
}