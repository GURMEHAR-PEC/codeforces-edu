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
    int maxele = 0;
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
        }
        for(int i=0;i<=n;i++){
            info[i].maxele = i;
            info[i].size=1;
        }
    }
    int findUPar(int node){
        if(node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    void UnionBySize(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v) return;
        if(info[ulp_u].size < info[ulp_v].size){
            parent[ulp_u] = ulp_v;
            info[ulp_v].size += info[ulp_u].size;
            info[ulp_v].maxele = max(info[ulp_v].maxele,info[ulp_u].maxele);
        }
        else{
            parent[ulp_v] = ulp_u;
            info[ulp_u].size += info[ulp_v].size;
            info[ulp_u].maxele = max(info[ulp_u].maxele,info[ulp_v].maxele);
        }
    }

    int getNearest(int node){
        int parentNode = findUPar(node);
        return info[parentNode].maxele;
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    DisjointSet ds1(n+1);
    for(int i=0;i<m;i++){
        char op;
        int node;
        cin>>op>>node;
        if(op ==  '?'){
            int ans = ds1.getNearest(node);
            if(ans == n+1) cout<<-1<<"\n";
            else cout<<ans<<"\n"; 
        }
        else{
            ds1.UnionBySize(node,node+1);
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