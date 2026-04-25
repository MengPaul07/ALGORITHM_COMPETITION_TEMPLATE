namespace Sorting
{
    // 归并排序
    // arr: 待排序数组, tmp: 辅助数组, l: 左边界, r: 右边界
    void mergeSort(vector<int> &arr, vector<int> &tmp, int l, int r)
    {
        if (l >= r)
            return;
        int mid = (l + r) >> 1;
        mergeSort(arr, tmp, l, mid);
        mergeSort(arr, tmp, mid + 1, r);
        int i = l, j = mid + 1, k = 0;
        while (i <= mid && j <= r)
        {
            if (arr[i] <= arr[j])
                tmp[k++] = arr[i++];
            else
                tmp[k++] = arr[j++];
        }
        while (i <= mid)
            tmp[k++] = arr[i++];
        while (j <= r)
            tmp[k++] = arr[j++];
        for (i = l, k = 0; i <= r; i++, k++)
            arr[i] = tmp[k];
    }

    // 快速排序
    // arr: 待排序数组, l: 左边界, r: 右边界
    void quickSort(vector<int> &arr, int l, int r)
    {
        if (l >= r)
            return;
        int i = l - 1, j = r + 1, x = arr[(l + r) >> 1];
        while (i < j)
        {
            do
                i++;
            while (arr[i] < x);
            do
                j--;
            while (arr[j] > x);
            if (i < j)
                swap(arr[i], arr[j]);
        }
        quickSort(arr, l, j);
        quickSort(arr, j + 1, r);
    }
}