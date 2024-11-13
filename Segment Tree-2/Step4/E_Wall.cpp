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
    int mini = INT_MAX;
    int maxi = INT_MIN;
};
struct op
{
    int prevAdd = INT_MIN;
    int prevRemove = INT_MAX;
};
class LazySegTree
{
    vector<node> seg;
    vector<op> lazy;

public:
    LazySegTree(int n)
    {
        seg.resize(4 * n);
        lazy.resize(4 * n);
    }

    void build(int ind, int low, int high, vector<int> &arr)
    {
        if (low == high)
        {
            seg[ind].maxi = arr[low];
            seg[ind].mini = arr[low];
            return;
        }

        int mid = (low + high) >> 1;
        build((ind << 1) + 1, low, mid, arr);
        build((ind << 1) + 2, mid + 1, high, arr);
        seg[ind].maxi = max(seg[2 * ind + 1].maxi, seg[2 * ind + 2].maxi);
        seg[ind].mini = min(seg[2 * ind + 1].mini, seg[2 * ind + 2].mini);
    }

    void propogate(int ind, int low, int high)
    {
        if (lazy[ind].prevRemove != INT_MAX || lazy[ind].prevAdd != INT_MIN)
        {
            seg[ind].mini = min(max(lazy[ind].prevAdd, seg[ind].mini), lazy[ind].prevRemove);
            seg[ind].maxi = max(min(lazy[ind].prevRemove, seg[ind].maxi), lazy[ind].prevAdd);

            if (low != high)
            {
                lazy[2 * ind + 1].prevAdd = min(lazy[ind].prevRemove, max(lazy[2 * ind + 1].prevAdd, lazy[ind].prevAdd));
                lazy[2 * ind + 1].prevRemove = max(lazy[ind].prevAdd, min(lazy[2 * ind + 1].prevRemove, lazy[ind].prevRemove));
                lazy[2 * ind + 2].prevAdd = min(lazy[ind].prevRemove, max(lazy[2 * ind + 2].prevAdd, lazy[ind].prevAdd));
                lazy[2 * ind + 2].prevRemove = max(lazy[ind].prevAdd, min(lazy[2 * ind + 2].prevRemove, lazy[ind].prevRemove));
            }
            lazy[ind].prevRemove = INT_MAX;
            lazy[ind].prevAdd = INT_MIN;
        }
    }
    void update(int ind, int low, int high, int l, int r, op o1)
    {
        propogate(ind, low, high);

        if (high < l || r < low)
            return;

        if (low >= l && high <= r)
        {
            seg[ind].mini = min(max(o1.prevAdd, seg[ind].mini), o1.prevRemove);
            seg[ind].maxi = max(min(o1.prevRemove, seg[ind].maxi), o1.prevAdd);
            if (low != high)
            {
                lazy[2 * ind + 1].prevAdd = min(o1.prevRemove, max(lazy[2 * ind + 1].prevAdd, o1.prevAdd));
                lazy[2 * ind + 1].prevRemove = max(o1.prevAdd, min(lazy[2 * ind + 1].prevRemove, o1.prevRemove));
                lazy[2 * ind + 2].prevAdd = min(o1.prevRemove, max(lazy[2 * ind + 2].prevAdd, o1.prevAdd));
                lazy[2 * ind + 2].prevRemove = max(o1.prevAdd, min(lazy[2 * ind + 2].prevRemove, o1.prevRemove));
            }
            return;
        }

        int mid = (low + high) >> 1;
        update((ind << 1) + 1, low, mid, l, r, o1);
        update((ind << 1) + 2, mid + 1, high, l, r, o1);
        seg[ind].mini = min(seg[2 * ind + 1].mini, seg[2 * ind + 2].mini);
        seg[ind].maxi = max(seg[2 * ind + 1].maxi, seg[2 * ind + 2].maxi);
    }

    node query(int ind, int low, int high, int l, int r)
    {
        propogate(ind, low, high);

        if (high < l || r < low)
        {
            node n1;
            return n1;
        }

        if (low >= l && high <= r)
            return seg[ind];
        int mid = (low + high) >> 1;
        node left = query((ind << 1) + 1, low, mid, l, r);
        node right = query((ind << 1) + 2, mid + 1, high, l, r);
        node ans;
        ans.maxi = max(right.maxi, left.maxi);
        ans.mini = min(left.mini, right.mini);
        return ans;
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> v1(n, 0);
    LazySegTree s1(n);
    s1.build(0, 0, n - 1, v1);
    for (int i = 0; i < k; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (a == 1)
        {
            op o1;
            o1.prevAdd = d;
            s1.update(0, 0, n - 1, b, c, o1);
        }
        else
        {
            op o1;
            o1.prevRemove = d;
            s1.update(0, 0, n - 1, b, c, o1);
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << s1.query(0, 0, n - 1, i, i).maxi << "\n";
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
