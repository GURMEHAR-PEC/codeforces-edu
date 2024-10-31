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
    void unionByRank(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v) return ;
        if(rank[ulp_u] < rank[ulp_v]){
            parent[ulp_u] = ulp_v;
        }
        else if(rank[ulp_v] < rank[ulp_u]){
            parent[ulp_v] = ulp_u;
        }
        else{
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
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
};
void solve(){
    int n,m,s;
    cin>>n>>m>>s;
    vector<pair<int,pair<int,int>>> v1;
    vector<pair<int,pair<int,int>>> removed;
    int cnt=0;
    vector<int> ans;
    map<pair<int,int>,int> edgeNo;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        v1.push_back({w,{u,v}});
        edgeNo[{u,v}]=i+1;
    }

    sort(v1.rbegin(),v1.rend());
    DisjointSet ds1(n);
    for(int i=0;i<m;i++){
        int u = v1[i].second.first;
        int v = v1[i].second.second;
        int w = v1[i].first;
        if(ds1.findUPar(u)!=ds1.findUPar(v)){
            ds1.UnionBySize(u,v);
        }
        else{
            removed.push_back({w,{u,v}});
        }
    }
    reverse(removed.begin(),removed.end());
    for(int i=0;i<removed.size();i++){
        if(s >= removed[i].first){
            s -= removed[i].first;
            ans.push_back(edgeNo[{removed[i].second.first,removed[i].second.second}]);
        }
        else break;
    }


    cout<<ans.size()<<"\n";
    for(auto it:ans) cout<<it<<" ";
    cout<<"\n";
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}