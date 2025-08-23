#include <vector>
#include <iostream>
#include <functional>

class SegmentTree {
public:
    SegmentTree(const std::vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 0, 0, n - 1);
    }

    void update(int index, int value) {
        update(0, 0, n - 1, index, value);
    }

    int query(int left, int right) {
        return query(0, 0, n - 1, left, right);
    }

private:
    std::vector<int> tree;
    int n;

    void build(const std::vector<int>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            build(data, 2 * node + 1, start, mid);
            build(data, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void update(int node, int start, int end, int index, int value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (index <= mid) {
                update(2 * node + 1, start, mid, index, value);
            } else {
                update(2 * node + 2, mid + 1, end, index, value);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) {
            return 0; // Neutral element for sum
        }
        if (left <= start && end <= right) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int p1 = query(2 * node + 1, start, mid, left, right);
        int p2 = query(2 * node + 2, mid + 1, end, left, right);
        return p1 + p2;
    }
};