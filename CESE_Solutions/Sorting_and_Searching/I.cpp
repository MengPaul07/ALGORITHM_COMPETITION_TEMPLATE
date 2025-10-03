
/*用数学归纳法证明贪心正确
对任意current 如果coins[i]<=current=sum+1
前k个已经凑出 则1,2,3···,k+coins[i]可以表示出[current,current+coins[i]]的所有值。 
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> coins(n);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    sort(coins.begin(), coins.end());

    long long current = 1;
    for (int i = 0; i < n; i++)
    {
        if (coins[i] > current)
        {
            break;
        }
        current += coins[i];
    }

    cout << current << '\n';
    return 0;
}




// nums 0 1 2 3 
// curr 1 2 4 7