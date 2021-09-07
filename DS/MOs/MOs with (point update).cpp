#include<bits/stdc++.h>
using namespace std;
#define D(x) cerr<<__LINE__<<" : "<<#x<<" -> "<<x<<endl
#define ll long long

const int MAX = 1e5+7;            ///Check Every Time
int n, m, k, tc, q;
int arr[MAX], blkId[MAX], last[MAX];

struct Query {
    int l, r, t, id;
    Query() {}
    Query(int x,int y,int tt, int i) {
        l=x, r=y, t = tt, id=i;
    }
    bool operator<(const Query other) const {
        int aL = blkId[l], bL = blkId[other.l];
        int aR = blkId[r], bR = blkId[other.r];

        return aL == bL ? aR == bR ? t < other.t : aR < bR : aL < bL;
    }
};

struct Update {
    int pos, prv, now;
    Update() {}
    Update(int _a, int _b, int _c) {
        pos = _a, prv = _b, now = _c;
    }
};

struct MO {
    int unique_values, L, R, N, T, block_s = 2200; /// 320 is acceptable
    vector < Query > queries;
    vector < Update> updates;
    int freq[MAX+5], upsz, Q, perQ[MAX];

    MO(int n) {
        L = 0, R = -1, T = 0, Q = 0;
        unique_values = 0;
        N = n;
        block_s = pow(n, 2.0/3); /// n^(2/3) block size
        memset(freq, 0, sizeof (freq));
        for(int i=0; i<=n; i++) blkId[i] = i/block_s;
    }

    void fix(int pos, int val) {
        if(L <= pos and pos <= R) {
            del(pos);
            arr[pos] = val;
            add(pos);
        } else arr[pos] = val;
    }

    void add(int idx) {
        freq[arr[idx]]++;
        if(freq[arr[idx]] == 1) unique_values++;
    }

    void del(int idx) {
        if(freq[arr[idx]] == 1) unique_values--;
        freq[arr[idx]]--;
    }

    void add_query(int _q) {
        updates.push_back({-1,-1,-1});
        for(int i = 0, j = 0; i < _q; i++) {
            int type, lf, rf, pos, val;
            scanf("%d",&type);
            if(type == 1) {
                scanf("%d%d",&lf,&rf);
                lf--, rf--;
                upsz = updates.size() - 1;
                queries.push_back({lf, rf, upsz, j});
                j++;
            } else {
                scanf("%d%d",&pos,&val);
                pos--;
                updates.push_back({pos, last[pos], val});
                last[pos] = val;
            }
        }
        Q = queries.size(), upsz = updates.size();
    }

    void process_query() {
        sort(queries.begin(), queries.end());
        for(int i = 0; i < queries.size(); i++) {
            while(queries[i].t > T) ++T, fix(updates[T].pos, updates[T].now); ///do update
            while(queries[i].t < T) fix(updates[T].pos, updates[T].prv), --T; ///undo update

            while(queries[i].l < L) add(--L);
            while(queries[i].l > L) del(L++);
            while(queries[i].r < R) del(R--);
            while(queries[i].r > R) add(++R);

            perQ[queries[i].id] = unique_values;  ///Always check what you want to store
        }
    }
};


signed main() {
    scanf("%d",&n);
    for(int i = 0; i < n; i++) scanf("%d",&arr[i]), last[i] = arr[i];
    scanf("%d",&q);
    MO mos(n);
    mos.add_query(q);
    mos.process_query();
    for(int i = 0; i < mos.Q; i++)
        printf("%lld\n",mos.perQ[i]);
    return 0;
}
