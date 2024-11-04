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
struct Query
{
    int state = -1;
    int l = -1, r = -1;
    int ans = -1;
    int u=-1,v=-1;
};
struct op
{
    int u = -1, v = -1, ans = -1, state = -1;
};
map<int, int> queryAns;
class DisjointSet
{
    vector<int> rank, parent, size;
    stack<op> s1;

public:
    DisjointSet(int n)
    {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
        op o1;
        o1.ans = n;
        s1.push(o1);
    }
    int findUPar(int node)
    {
        if (node == parent[node])
            return node;
        return findUPar(parent[node]);
    }
    int getCurrVal()
    {
        return s1.top().ans;
    }
    void UnionBySize(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
        {
            op o1;
            o1.u = ulp_u, o1.v = ulp_v, o1.ans = getCurrVal(), o1.state = -1;
            s1.push(o1);
            return;
        }

        op o1;
        o1.u = ulp_u, o1.v = ulp_v, o1.ans = getCurrVal() - 1;
        if (size[ulp_u] < size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
            o1.state = 2;
        }
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
            o1.state = 1;
        }
        s1.push(o1);
    }
    void save()
    {
        op o1;
        o1.ans = getCurrVal();
        s1.push(o1);
    }
    void rollback()
    {
        while (s1.top().u != -1)
        {
            auto it = s1.top();
            s1.pop();
            if (it.state == -1)
                continue;
            else if (it.state == 1)
            {
                size[it.u] -= size[it.v];
                parent[it.v] = it.v;
            }
            else
            {
                size[it.v] -= size[it.u];
                parent[it.u] = it.u;
            }
        }
        s1.pop();
        
    }
    
    void work(int l, int r, vector<Query> &queries)
    {
        if (l == r)
        {
            save();
            // cout<<l<<" "<<getCurrVal()<<"\n";
            for(auto q:queries){
                if(q.state == 1 && q.l<=l && q.r>=l){
                    UnionBySize(q.u,q.v);
                }
            }
            for (auto q : queries)
            {
                if (q.state == 2 && q.l == l)
                {
                    // cout<<(findUPar(4) == findUPar(5))<<"\n";
                    queryAns[q.l] = getCurrVal();
                }
            }
            rollback();
            return;
        }
        save();
        vector<Query> queries2;
        for(auto q:queries){
            if(q.state == 1){
                if(q.r < l || q.l>r) continue;
                else if(l>=q.l && r<=q.r){
                    // if(q.u == 4 && q.v == 5){
                    //     cout<<q.l<<" "<<q.r<<"\n";
                    //     cout<<l<<" "<<r<<"\n";
                    //     cout<<"I am here"<<"\n";
                    // }
                    UnionBySize(q.u,q.v);
                }
                else{
                    queries2.push_back(q);
                }
            }
            else{
                if(q.l>=l && q.l<=r){
                    queries2.push_back(q);
                }
            }
        }
        int mid = (l+r)>>1;
        work(l,mid,queries2);
        work(mid+1,r,queries2);
        rollback();
    }
};

void solve()
{
    int n,m;
    cin>>n>>m;
    map<pair<int,int>,int> EdgeAdded;
    vector<Query> queries;
    int lastGet=-1;
    for(int i=0;i<m;i++){
        char operation;
        cin>>operation;
        if(operation == '+'){
            int u,v;
            cin>>u>>v;
            EdgeAdded[{min(u,v),max(u,v)}] = i;
        }
        else if(operation == '-'){
            int u,v;
            cin>>u>>v;
            int startValue = EdgeAdded[{min(u,v),max(u,v)}];
            EdgeAdded.erase({min(u,v),max(u,v)});
            Query q1;
            q1.l = startValue;
            q1.r = i-1;
            q1.state=1;
            q1.u = min(u,v);
            q1.v = max(u,v);
            queries.push_back(q1);
        }
        else{
            Query q1;
            q1.l = i;
            q1.state = 2;
            lastGet = i;
            queries.push_back(q1);
        }
    }
    int curr_t = m;
    for(auto it:EdgeAdded){
        Query q1;
        q1.state = 1;
        q1.l = it.second;
        q1.r = curr_t-1;
        q1.u = it.first.first;
        q1.v = it.first.second;
        queries.push_back(q1);
        curr_t++;
    }
    // for(auto it:queries){
    //     cout<<it.state<<"\n";
    //     cout<<it.u<<" "<<it.v<<"\n";
    //     cout<<it.l<<" "<<it.r<<"\n";
    // }
    
    DisjointSet ds1(n);
    if(lastGet!=-1) ds1.work(0,lastGet,queries);
    for(auto it:queryAns) cout<<it.second<<"\n";

}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}