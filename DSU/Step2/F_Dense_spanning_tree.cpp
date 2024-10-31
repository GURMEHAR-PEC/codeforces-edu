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
    vector<int> rank,parent,size;
public:
    DisjointSet(int n){
        rank.resize(n+1,0);
        parent.resize(n+1);
        size.resize(n+1,1);
        for(int i=0;i<=n;i++){
            parent[i] = i;
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
        if(size[ulp_u] < size[ulp_v]){
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else{
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
    int getsize(int node){
        int ulp = findUPar(node);
        return size[ulp];
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>> v1;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        v1.push_back({w,{u,v}});
    }
    sort(v1.begin(),v1.end());
    int ans = INT_MAX;
    for(int i=0;i<m;i++){
        DisjointSet ds1(n);
        int j=i;
        while(j<m && ds1.getsize(1)<n ){
            ds1.UnionBySize(v1[j].second.first,v1[j].second.second);
            j++;
        }

        if(ds1.getsize(1) == n){
            ans = min(ans,v1[j-1].first - v1[i].first);
        }


    }

    if(ans == INT_MAX) cout<<"NO"<<"\n";
    else{
        cout<<"YES"<<"\n";
        cout<<ans<<"\n";
    }
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}