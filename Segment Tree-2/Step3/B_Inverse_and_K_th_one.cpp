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

class LazySegTree
{
    vector<int> seg, lazy;

public:
    LazySegTree(int n)
    {
        seg.resize(4 * n);
        lazy.resize(4 * n);
    }

    void build(int ind, int low, int high, vector<int>& arr)
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
    void propogate(int ind,int low,int high){
        if (lazy[ind] != 0)
        {
            seg[ind] = (high-low+1) - seg[ind];
            if (low != high)
            {
                lazy[(ind << 1) + 1] = (lazy[(ind << 1) + 1] + 1) % 2;
                lazy[(ind << 1) + 2] = (lazy[(ind << 1) + 2] + 1) % 2;
            }
            lazy[ind] = 0;
        }
    }
    void update(int ind, int low, int high, int l, int r)
    {
        
        propogate(ind,low,high);
        if (high < l || r < low)
            return;

        if (low >= l && high <= r)
        {
            seg[ind] = (high - low + 1) - seg[ind];
            if (low != high)
            {
                lazy[(ind << 1) + 1] = (lazy[(ind << 1) + 1] + 1) % 2;
                lazy[(ind << 1) + 2] = (lazy[(ind << 1) + 2] + 1) % 2;
            }
            return;
        }

        int mid = (low + high) >> 1;
        update((ind << 1) + 1, low, mid, l, r);
        update((ind << 1) + 2, mid + 1, high, l, r);
        seg[ind] = seg[(ind << 1) + 1] + seg[(ind << 1) + 2];
    }

    int query(int ind, int low, int high, int k)
    {
        propogate(ind,low,high);

        if(low == high) return low;
        int mid = (low + high) >> 1;

        propogate(2*ind+1,low,mid);
        propogate(2*ind+2,mid+1,high);
        if(seg[2*ind+1] >= k+1) return query(2*ind+1,low,mid,k);

        else return query(2*ind+2,mid+1,high,k-seg[2*ind+1]);
        return 0;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> v1(n, 0);

    LazySegTree s1(n);
    s1.build(0,0,n-1,v1);
    for (int i = 0; i < m; i++)
    {
        int a;
        cin >> a;
        if (a == 1)
        {
            int l, r;
            cin >> l >> r;
            s1.update(0,0,n-1,l,r-1);
        }
        else
        {
            int k;
            cin>>k;
            cout<<s1.query(0,0,n-1,k)<<"\n";
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