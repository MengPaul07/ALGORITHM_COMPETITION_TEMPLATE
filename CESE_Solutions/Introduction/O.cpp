// #include <bits/stdc++.h>
// using namespace std;
// //#define int long long

// bool ok(int n, int a, int b, int diff)
// {

//     if (a + b > n)
//     {
//         printf("NO\n");
//         return 0;
//     }
//     if (a == 0 && b == 0)
//     {
//         printf("Yes\n");
//         return 1;
//     }
//     else if (a + b < n)
//     {
//         if (a >= n - diff || b >= n - diff)
//         {
//             printf("No\n");
//             return 0;
//         }
//     }
//     printf("Yes\n");
//     return 1;
// }

// signed main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int t;
//     scanf("%d",&t);
//     while(t--){
//         vector<int> va, vb;
//         int n, a, b;
//         scanf("%d %d %d", &n, &a, &b);
//         int diff = n - a - b;
//         if(ok(n,a,b,diff)){
//             for (int i = 1; i <= n;i++){
//                 va.push_back(i);
//                 vb.push_back(i);
//             }
//                 for (int i = diff; i < diff+a;i++){
//                     swap(va[i], va[i + 1]);
//                 }
//                 for (int i = diff+a; i <diff+a+b-1; i++)
//                 {
//                     swap(vb[i], vb[i + 1]);
//                 }
//             for(auto i:va)
//                 printf("%d ", i);
//             printf("\n");
//             for(auto i:vb)
//                 printf("%d ", i);
//             printf("\n");
//         }
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

bool ok(int n, int a, int b, int diff)
{
    if (a + b > n)
        return 0;
        
    if (a == 0 && b == 0)
        return 1;

    else if (a + b < n)
        if (a >= n - diff || b >= n - diff)
            return 0;
    return 1;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, a, b;
        scanf("%d %d %d", &n, &a, &b);
        int k = n - a - b;
        if (!ok(n, a, b,k))
        {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        vector<int> A, B; 
        for (int i = 1; i <= k; ++i)
            A.push_back(i); 
        for (int i = k + 1; i <= k + b; ++i)
            A.push_back(i); 
        for (int i = k + b + 1; i <= n; ++i)
            A.push_back(i);
     
        for (int i = 1; i <= k; ++i)
            B.push_back(i); 
        for (int i = n - b + 1; i <= n; ++i)
            B.push_back(i); 
        for (int i = k + 1; i <= k + a; ++i)
            B.push_back(i); 

            
        for (int num : A)
            printf("%d ", num);
        printf("\n");
        for (int num : B)
            printf("%d ", num);
        printf("\n");
    }
    return 0;
}