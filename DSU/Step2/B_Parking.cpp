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
    int size = 0;
    int maxi = 0;
};
class DisjointSet
{
    vector<int> rank, parent;
    vector<node> info;

public:
    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        info.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
            info[i].size = 1;
            info[i].maxi = i;
        }
    }
    int findUPar(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }
    void UnionBySize(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;
        if (info[ulp_u].size < info[ulp_v].size)
        {
            parent[ulp_u] = ulp_v;
            info[ulp_v].size += info[ulp_u].size;
            info[ulp_v].maxi = max(info[ulp_v].maxi, info[ulp_u].maxi);
        }
        else
        {
            parent[ulp_v] = ulp_u;
            info[ulp_u].size += info[ulp_v].size;
            info[ulp_u].maxi = max(info[ulp_u].maxi, info[ulp_v].maxi);
        }
    }

    int findmaxi(int node)
    {
        int parentnode = findUPar(node);
        return info[parentnode].maxi;
    }
};
void solve()
{
    int n;
    cin >> n;
    DisjointSet ds1(2 * n + 2);
    vector<int> v1(n, 0);
    ivec(v1);
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++)
    {

        if (ds1.findmaxi(v1[i]) <= n)
        {
            ans[i] = ds1.findmaxi(v1[i]);
            ds1.UnionBySize(ans[i], ans[i] + 1);
            if (ans[i] == n)
                ds1.UnionBySize(ans[i] + 1, ans[i] + 2);
            ds1.UnionBySize(ans[i] + n + 1, ans[i] + n + 2);
        }
        else
        {
            ans[i] = ds1.findmaxi(v1[i]);
            ds1.UnionBySize(ans[i], ans[i] + 1);
            ds1.UnionBySize(ans[i]-(n+1),ans[i]-n);
            ans[i] = ans[i] - (n+1);
        }
    }

    for(auto it:ans){
        cout<<it<<" ";
    }
    cout<<"\n";
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}