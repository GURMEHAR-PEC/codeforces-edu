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
    int depth=0;
    int size=0;
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
        int oldParent = parent[node];
        parent[node] = newParent;
        if(oldParent == newParent) return parent[node];


        info[node].depth += (info[newParent].depth+info[oldParent].depth);
        return parent[node];
    }

    void UnionBySize(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        bool b1 = ((info[u].depth%2) == (info[v].depth%2));
        if(ulp_u == ulp_v) return;
        if(info[ulp_u].size > info[ulp_v].size){
            info[ulp_u].size += info[ulp_v].size;
            parent[ulp_v] = ulp_u;
            info[ulp_v].depth += (info[ulp_u].depth+b1);
        }
        else{
            info[ulp_v].size += info[ulp_u].size;
            parent[ulp_u] = ulp_v;
            info[ulp_u].depth += (info[ulp_v].depth+b1);
        }
    }

    bool check(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v){
            return (info[u].depth%2 == info[v].depth%2);
        }
        return false;
    }
    void debug(int n){
        for(int i=0;i<=n;i++){
            cout<<info[i].depth<<" ";
        }
        cout<<'\n';
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    DisjointSet ds1(n);
    int ans=-1;
    bool check = false;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        if(ds1.check(u,v)){
            if(!check){
                ans = i+1;
                check = true;
            }
            
        }
        else{
            ds1.UnionBySize(u,v);
        }
        // ds1.debug(n);
    }
    cout<<ans<<"\n";
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}