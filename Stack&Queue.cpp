namespace MonotonicStack
{
    // 单调栈：寻找每个元素右边第一个比它大的元素的索引
    // 如果不存在，则为 -1
    vector<int> nextGreaterElement(const vector<int> &nums)
    {
        int n = nums.size();
        vector<int> res(n, -1);
        stack<int> s; // 存储索引
        for (int i = 0; i < n; ++i)
        {
            while (!s.empty() && nums[s.top()] < nums[i])
            {
                res[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        return res;
    }
}

namespace MonotonicQueue
{
    // 单调队列：滑动窗口最大值
    vector<int> maxSlidingWindow(const vector<int> &nums, int k)
    {
        deque<int> q; // 存储索引
        vector<int> res;
        for (int i = 0; i < nums.size(); ++i)
        {
            // 移除滑出窗口的元素
            if (!q.empty() && q.front() == i - k)
            {
                q.pop_front();
            }
            // 保持队列单调递减（队首最大）
            while (!q.empty() && nums[q.back()] < nums[i])
            {
                q.pop_back();
            }
            q.push_back(i);
            // 记录窗口最大值
            if (i >= k - 1)
            {
                res.push_back(nums[q.front()]);
            }
        }
        return res;
    }