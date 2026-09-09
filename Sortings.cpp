#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 200005;
int a[N], tmp[N];

void mergeSort(int l, int r)
{
    if (l >= r)
        return;

    int mid = (l + r) >> 1;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);

    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (a[i] <= a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }
    while (i <= mid)
        tmp[k++] = a[i++];
    while (j <= r)
        tmp[k++] = a[j++];

    for (int p = l; p <= r; p++)
        a[p] = tmp[p];
}

void quickSort(int l, int r)
{
    if (l >= r)
        return;

    int i = l - 1, j = r + 1;
    int x = a[(l + r) >> 1];

    while (i < j)
    {
        do i++; while (a[i] < x);
        do j--; while (a[j] > x);
        if (i < j)
            swap(a[i], a[j]);
    }

    quickSort(l, j);
    quickSort(j + 1, r);
}
