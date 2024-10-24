// Gurmehar Singh

#include <bits/stdc++.h>
#include <algorithm>
// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
#define yes cout << "Yes" << "\n"
#define no cout << "No" << "\n"
#define nl cout << "\n"
#define all(a) a.begin(), a.end()
#define ivec(vec)                        \
    for (int i = 0; i < vec.size(); i++) \
    {                                    \
        cin >> vec[i];                   \
    }
#define ovec(vec)                        \
    for (int i = 0; i < vec.size(); i++) \
    {                                    \
        cout << vec[i] << " ";           \
    }
#define pb push_back
#define int long long
using ll = long long;
using ull = unsigned long long;
const int mod = 1e9 + 7;
using namespace std;
// using namespace __gnu_pbds;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> pbds;
// // (functions find_by_order, order_of_key)

struct node
{
    int a = 0, d = 0;
};
class LazySegTree
{
    vector<int> seg;
    vector<node> lazy;

public:
    LazySegTree(int n)
    {
        seg.resize(4 * n);
        lazy.resize(4 * n);
    }
    int getsum(node n, int sz)
    {
        int ans = ((sz) * (2 * (n.a) + (sz - 1) * (n.d))) / 2;
        return ans;
    }
    void build(int ind, int low, int high, vector<int> &arr)
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) >> 1;
        build((ind << 1) + 1, low, mid, arr);
        build((ind << 1) + 2, mid + 1, high, arr);
        seg[ind] = seg[(ind << 1) + 1] + seg[(ind << 1) + 2];
    }


     void propagate(int ind, int low, int high) {
        if (lazy[ind].a != 0 || lazy[ind].d != 0) {
            seg[ind] += getsum(lazy[ind], high - low + 1);
            if (low != high) {
                int mid = (low + high) >> 1;
                lazy[(ind << 1) + 1].a += lazy[ind].a;
                lazy[(ind << 1) + 1].d += lazy[ind].d;
                
                lazy[(ind << 1) + 2].a += lazy[ind].a + (mid + 1 - low) * lazy[ind].d;
                lazy[(ind << 1) + 2].d += lazy[ind].d;
            }
            lazy[ind] = {0, 0};  
        }
    }
    void update(int ind, int low, int high, int l, int r, int starterm, int cd)
    {
        if (lazy[ind].a != 0 || lazy[ind].d != 0)
        {
            seg[ind] += getsum(lazy[ind], high - low + 1);
            int mid = (low + high) >> 1;
            if (low != high)
            {
                lazy[2 * ind + 1].a += lazy[ind].a;
                lazy[2 * ind + 1].d += lazy[ind].d;
                lazy[2 * ind + 2].a += (lazy[ind].a + (mid + 1 - low) * lazy[ind].d);
                lazy[2 * ind + 2].d += lazy[ind].d;
            }
            lazy[ind].a = 0;
            lazy[ind].d = 0;
        }

        if (high < l || r < low)
            return;

        if (low >= l && high <= r)
        {
            lazy[ind].a += starterm + (low - l) * cd;
            lazy[ind].d += cd;
            propagate(ind, low, high);
            return;
        }

        int mid = (low + high) >> 1;
        update((ind << 1) + 1, low, mid, l, r, starterm, cd);
        update((ind << 1) + 2, mid + 1, high, l, r, starterm, cd);
        seg[ind] = seg[(ind << 1) + 1] + seg[(ind << 1) + 2];
    }

    int query(int ind, int low, int high, int l, int r)
    {
        if (lazy[ind].a != 0 || lazy[ind].d != 0)
        {
            seg[ind] += getsum(lazy[ind], high - low + 1);
            int mid = (low + high) >> 1;
            if (low != high)
            {
                lazy[2 * ind + 1].a += lazy[ind].a;
                lazy[2 * ind + 1].d += lazy[ind].d;
                lazy[2 * ind + 2].a += (lazy[ind].a + (mid + 1 - low) * lazy[ind].d);
                lazy[2 * ind + 2].d += lazy[ind].d;
            }
            lazy[ind].a = 0;
            lazy[ind].d = 0;
        }

        if (high < l || r < low)
            return 0;

        if (low >= l && high <= r)
            return seg[ind];
        int mid = (low + high) >> 1;
        int left = query((ind << 1) + 1, low, mid, l, r);
        int right = query((ind << 1) + 2, mid + 1, high, l, r);
        return left + right;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> v1(n, 0);
    LazySegTree s1(n);
    s1.build(0, 0, n - 1, v1);
    for(int i=0;i<m;i++){
        int a;
        cin>>a;
        if(a==1){
            int l,r,a,d;
            cin>>l>>r>>a>>d;
            s1.update(0,0,n-1,l-1,r-1,a,d);
        }
        else{
            int i;
            cin>>i;
            cout<<s1.query(0,0,n-1,i-1,i-1)<<"\n";
        }
    }
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
