#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200005; int a[N],nxt[N],windowMax[N]; int stk[N],que[N],top,head,tail;
// nxt[i]：右侧第一个严格更大元素，O(n)
// 求每个位置右侧第一个严格更大的元素下标。
void nextGreater(int n){
    top = 0;
    for(int i = n;i >= 1;i--){
        while(top && a[stk[top]] <= a[i])top--;
        nxt[i] = top ? stk[top] : -1;
        stk[++top] = i;
    }
}
// windowMax[1..n-k+1]，O(n)
// 用单调队列求所有长度为 k 的滑动窗口最大值。
void slidingWindowMax(int n, int k){
    head = tail = 1;
    for(int i = 1;i <= n;i++){
        while(head < tail && que[head] <= i - k)head++;
        while(head < tail && a[que[tail - 1]] <= a[i])tail--;
        que[tail++] = i;
        if(i >= k)windowMax[i - k + 1] = a[que[head]];
    }
}
