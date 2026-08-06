// KMP Algorithm
namespace KMP
{
vector<int> buildLps(const string &pat) {
    int m = (int)pat.length();
    vector<int> lps(m);
    int len = 0;
    lps[0] = 0; // lps[i]: pat[0..i] 的最长真前后缀长度

    int i = 1;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// 返回所有匹配起点下标（0-based）
vector<int> searchAll(const string &txt, const string &pat) {
    if (pat.empty()) return {};
    int m = (int)pat.length();
    int n = (int)txt.length();

    vector<int> lps = buildLps(pat);
    vector<int> pos;

    int i = 0;
    int j = 0;
    while (i < n) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == m) {
            pos.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return pos;
}
}

void solve(){
    string s,t;
    cin >> s >> t;

    int n = sz(s),m = sz(t);

    string p = t;

    t = t + '#' + s;

    vector<int> lps(sz(t));

    int i = 1,len = 0;
    while(i < sz(t)){
        if(t[i] == t[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if(len){
                len = lps[len - 1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }

    for(int i = m + 1;i < sz(t);i++){
        if(lps[i] == m){
            cout << i - 2 * m + 1 << endl;
        }
    }

    // 输出模式串自己的前缀函数
    for(int i = 0;i < m;i++){
        cout << lps[i] << " ";
    }
    cout << endl;
}

