#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 100000

struct FenwickTree {
    vector<int> bit; // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.clear();
        bit.assign(n, 0);
    }

    int prefix_sum(int r) {
        int res = 0;
        while(r >= 0) {
            res += bit[r];
            r = (r & (r + 1)) - 1;
        }
        return res;
    }

    int range_sum(int l, int r) {
        return prefix_sum(r) - prefix_sum(l - 1);
    }

    void add(int idx, int delta) {
        while(idx < n) {
            bit[idx] += delta;
            idx = idx | (idx + 1);
        }
    }
};

int main()
{
    FenwickTree fw(8);
    vector<int>arr{1,2,3,4,5,6,7,8};
    for(int i = 0; i < arr.size(); i++) {
        fw.add(i, arr[i]);
    }
    cout << fw.range_sum(0, 7) << "\n";
    cout << fw.range_sum(5, 5) << "\n";
    cout << fw.range_sum(3, 6) << "\n";
    return 0;
}
