// Gurmehar Singh 

#include<bits/stdc++.h>
#include<algorithm>
// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
#define yes cout<<"Yes"<<"\n"
#define no cout<<"No"<<"\n"
#define nl cout<<"\n"
#define all(a) a.begin(),a.end()
#define ivec(vec) for(int i=0;i<vec.size();i++){cin>>vec[i];}
#define ovec(vec) for(int i=0;i<vec.size();i++){cout<<vec[i]<<" ";}
#define pb push_back
#define int long long
using ll=long long;
using ull=unsigned long long;
const int mod=1e9+7;
using namespace std;
// using namespace __gnu_pbds;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> pbds;  
// // (functions find_by_order, order_of_key)

class DisjointSet{
public:
    vector<int> parent;
    vector<int> size;
    vector<int> exp;
public:
    DisjointSet(int n){
        parent.resize(n+1);
        size.resize(n+1);
        exp.resize(n+1);
        for(int i=0;i<=n;i++){
            parent[i] = i;
        } 
    }
    int findUPar(int node){
        if(node == parent[node]) return node;
        int newParent = findUPar(parent[node]);
        if(newParent == parent[node]){
            parent[node] = newParent;
            return parent[node];
        }
        exp[node] += exp[parent[node]];
        parent[node] = newParent;
        return parent[node];
    }

    int getTotalExp(int node){
        int ans=0;
        if(node == parent[node]) return exp[node];
        return ans = (exp[node] + getTotalExp(parent[node]));
    }
    void UnionBySize(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v) return;
        if(size[ulp_u] < size[ulp_v]){
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
            exp[ulp_u] -= exp[ulp_v];
        }
        else{
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
            exp[ulp_v] -=  exp[ulp_u];
        }
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    DisjointSet ds1(n);

    for(int i=0;i<m;i++){
        string op;
        cin>>op;
        if(op == "add"){
            int node,value;
            cin>>node>>value;
            int parentnode = ds1.findUPar(node);
            ds1.exp[parentnode] += value;
        }
        else if(op == "join"){
            int u,v;
            cin>>u>>v;
            ds1.UnionBySize(u,v);
        }
        else{
            int u;
            cin>>u;
            cout<<ds1.getTotalExp(u)<<"\n";
        }


    }
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}