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
    int mini = INT_MAX;
    int maxi = INT_MIN;
    int cnt=0;
};
class DisjointSet{
    vector<int> parent;
    vector<node> size;
public:
    DisjointSet(int n){
    
        parent.resize(n+1);
        size.resize(n+1);
        for(int i=0;i<=n;i++){
            parent[i] = i;
        } 
        for(int i=0;i<=n;i++){
            size[i].cnt = 1;
            size[i].maxi = i;
            size[i].mini = i;
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
        if(size[ulp_u].cnt < size[ulp_v].cnt){
            parent[ulp_u] = ulp_v;
            size[ulp_v].cnt += size[ulp_u].cnt;
            size[ulp_v].maxi = max(size[ulp_v].maxi,size[ulp_u].maxi);
            size[ulp_v].mini = min(size[ulp_v].mini,size[ulp_u].mini);

        }
        else{
            parent[ulp_v] = ulp_u;
            size[ulp_u].cnt += size[ulp_v].cnt;
            size[ulp_u].maxi = max(size[ulp_v].maxi,size[ulp_u].maxi);
            size[ulp_u].mini = min(size[ulp_v].mini,size[ulp_u].mini);
        }
    }
    node getinfo(int number){
        return size[number];
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    DisjointSet ds1(n);
    for(int i=0;i<m;i++){
        string op;
        cin>>op;
        if(op == "union"){
            int u,v;
            cin>>u>>v;
            ds1.UnionBySize(u,v);
        }
        else{
            int nodeNumber;
            cin>>nodeNumber;
            int parentNode = ds1.findUPar(nodeNumber);
            node ans = ds1.getinfo(parentNode);
            cout<<ans.mini<<" "<<ans.maxi<<" "<<ans.cnt<<"\n";
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