#include<bits/stdc++.h>
using namespace std;
#define D(x) cerr<<__LINE__<<" : " <<#x<<" -> "<<x<<endl
#define PPI pair< pair<int,int> ,int>
#define MAX 100007


struct SUFFIX_ARRAY {
    /// Caution : for 1e6 plc will be in globally
    int plc[18][MAX], suf[MAX], LCP[MAX];
    string s;
    vector< pair< pair<int,int>, int > > vp;
    int len, _rank, logn;
    SUFFIX_ARRAY(string _str) {
        s = _str;
        len = s.length();
        logn = ceil(log2(len)); ///ceil value nite hobe always
    }
    void radix_sort() {
        vector< pair< pair<int,int>, int > > a(len);
        vector<int> cnt(len), pos(len);
        pos[0] = 0;
        for(auto x: vp) cnt[x.first.second]++;
        for(int i = 1; i<len; i++) pos[i] = pos[i-1] + cnt[i-1];
        for(auto x: vp) {
            int i = x.first.second;
            a[pos[i]] = x;
            pos[i]++;
        }
        for(int i = 0; i<len; i++) cnt[i] = pos[i] = 0;
        for(auto x: a) cnt[x.first.first]++;
        for(int i = 1; i<len; i++) pos[i] = pos[i-1] + cnt[i-1];
        for(auto x: a) {
            int i = x.first.first;
            vp[pos[i]] = x;
            pos[i]++;
        }
    }
    void _fill(int idx) {
        _rank = 0;
        for(int i = 0; i<len; i++) {
            if(i) {
                PPI prv = vp[i-1], cur = vp[i];
                if(cur.first == prv.first) plc[idx][cur.second] = _rank;
                else plc[idx][cur.second] = ++_rank;

            } else {
                int pos = vp[i].second;
                plc[idx][pos] = _rank;
            }
        }
    }

    void suffix() {
        vp.clear();
        for(int i = 0; i<len; i++) {
            int pos = 1;
            if(s[i]>='0' and s[i]<='9') pos= pos +(int)s[i]-'0';
            else if(s[i]>='A' and s[i]<='Z') pos = pos+10 +(int)s[i]-'A';
            else if(s[i]>='a' and s[i]<='z')pos = pos + 36 + (int) s[i]-'a';
            if(s[i] == '#') pos = 0;
            vp.push_back({{pos,0},i});
        }
        sort(vp.begin(),vp.end());
        _fill(0);
        int mul = 1;
        for(int i = 1; i<=logn; i++) {
            vp.clear();
            for(int j = 0; j<len; j++) {
                int y = j+mul<len ? plc[i-1][j+mul] : 0;
                vp.push_back({{plc[i-1][j], y},j});
            }
            radix_sort();
            _fill(i);
            mul*=2;
        }
        for(int i = 0; i<len; i++) suf[plc[logn][i]] = i;
    } ///it can be done with 2 rows if we need to optimize memory

    int lcp(int x, int y) {
        int ret = 0;
        if(x == y) return len-x;
        for(int k = logn; k>=0 and x<len and y<len; k--) {
            if(plc[k][x] == plc[k][y]) x+= 1<<k, y+= 1<<k, ret+= 1<<k;
        }
        return ret;
    }
    void build_lcp(){
        suffix();
        LCP[0] = 0;
        for(int i = 1;i<len;i++){
            LCP[i] = lcp(suf[i-1],suf[i]);
        }
    }

    void print()
    {
        cout<<"plc Array :\n";
        for(int i = 0;i<=logn;i++){
            for(int j = 0;j<len;j++) cout<<plc[i][j]<<" ";
            cout<<endl;
        }
        cout<<"\nSuffix Array 1D:\n";
        for(int i = 0;i<len;i++) cout<<suf[i]<<" ";
        cout<<"\n\nLCP Array: \n";
        for(int i = 0;i<len;i++) cout<<LCP[i]<<" ";
        cout<<endl;
    }

    int no_distinct_substring()
    {
        int cnt = 0;
        for(int i = 1;i<len;i++){
            int temp = (len - suf[i]-1) - LCP[i];
            if(temp<0) temp = 0;
            cnt+=temp;
        }
        return cnt;
    }

    int lcs(int lim){ ///if two string
        int _lcs = 0;
        for(int i = 1;i<len;i++){
            if(suf[i]>lim and suf[i-1]>lim) continue;
            if(suf[i]<lim and suf[i-1]<lim) continue;
            if(suf[i] == lim or suf[i-1] == lim) continue;
            int temp = 0;
            if(suf[i]>lim) temp =  min((len - suf[i] - 1) - LCP[i],lim);
            else temp = min((len-lim-suf[i]-1)-LCP[i],lim);
            if(temp<0) temp = 0;


            _lcs = max(_lcs, temp);
        }
        return _lcs;
    }

     bool  isSubstring(string str) {
        int lo = 0, hi = len, mid;
        while(lo<=hi) {
            mid = (lo+hi)/2;
            if(s[suf[mid]] == str[0]) {
                int i = suf[mid], ln = 0, ck = 0, lim = str.length();
                while(ln<str.length() and i<len) {
                    if(s[i] == str[ln]) {
                        i++, ln++;
                        continue;
                    } else {
                        ck = 1;
                        if(s[i]<str[ln]) lo = mid+1;
                        else hi = mid-1;
                        break;
                    }
                }
                if(!ck and ln == str.length()) return true;
            } else if(s[suf[mid]]<str[0]) lo = mid+1;
            else hi = mid-1;
        }
        return false;
    }

};

string s, temp, str;
int main() {
    freopen("input.txt","r",stdin);
   // freopen("output.txt","w",stdout);
    bool flag = false;
    cin>>s;
    cin>>temp;
    str= s+ "#"+temp;
    /// str = s + "#" + s if we need to find LCP within a single string
    SUFFIX_ARRAY suf(str);
    suf.build_lcp();

    suf.print();
    D(suf.no_distinct_substring());
    D(suf.lcs(s.length()));
    D(suf.isSubstring("c"));
    return 0;
}
