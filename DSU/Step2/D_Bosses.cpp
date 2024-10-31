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

struct node{
    int size=0;
    int depth=0;
};
class DisjointSet{
    vector<int> rank,parent;
    vector<node> info;
public:
    DisjointSet(int n){
        rank.resize(n+1,0);
        parent.resize(n+1);
        info.resize(n+1);
        for(int i=0;i<=n;i++){
            parent[i] = i;
            info[i].depth=0;
            info[i].size=1;
        } 
    }
    int findUPar(int node){
        if(node == parent[node]) return node;
        int newParent = findUPar(parent[node]);
        if(newParent == parent[node]) return parent[node];
        int oldParent = parent[node];
        parent[node] = newParent;
        info[node].depth += (info[oldParent].depth+info[newParent].depth);
        return parent[node];
    }
    
    void UnionBySize(int u,int v){
        
            parent[u] = v;
            info[v].size += info[u].size;
            info[u].depth += (1+info[v].depth);
        
        
    }
    int getHeight(int node){
        int newparent = findUPar(node);
        return info[node].depth;
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    DisjointSet ds1(n);
    for(int i=0;i<m;i++){
        int a;
        cin>>a;
        if(a==1){
            int u,v;
            cin>>u>>v;
            ds1.UnionBySize(u,v);
        }
        else{
            int c;
            cin>>c;
            cout<<ds1.getHeight(c)<<"\n";
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