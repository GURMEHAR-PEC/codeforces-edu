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
    int maxi=0;
    int mini=0;
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
            info[i].maxi=i;
            info[i].mini=i;
            info[i].size=1;
        } 
    }
    int findUPar(int node){
        if(node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    void pointUnion(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v) return;

        if(info[ulp_u].size > info[ulp_v].size){
            parent[ulp_v] = ulp_u;
            info[ulp_u].size += info[ulp_v].size;
            info[ulp_u].maxi = max(info[ulp_u].maxi,info[ulp_v].maxi);
            info[ulp_u].mini = min(info[ulp_u].mini,info[ulp_v].mini);

        }
        else{
            parent[ulp_u] = ulp_v;
            info[ulp_v].size += info[ulp_u].size;
            info[ulp_v].maxi = max(info[ulp_u].maxi,info[ulp_v].maxi);
            info[ulp_v].mini = min(info[ulp_u].mini,info[ulp_v].mini);
        }
    }
    void rangeUnion(int u,int v){
        int ulp_v = findUPar(v);
        int ulp_u = findUPar(u);
        if(ulp_u == ulp_v) return;

        if(u >=  info[ulp_v].mini){
            pointUnion(ulp_u,ulp_v);
        }
        else{
            int temp = info[ulp_v].mini;
            pointUnion(ulp_u,ulp_v);
            for(int node = u+1;node<temp;node++){
                if(info[ulp_u].size > info[ulp_v].size) pointUnion(ulp_u,node);
                else pointUnion(ulp_v,node);
            }
        }

    }

    void print(int n){
        for(int i=0;i<=n;i++){
            cout<<parent[i]<<" ";
        }
        cout<<"\n";
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
            ds1.pointUnion(u,v);
        }
        else if(a==2){
            int u,v;
            cin>>u>>v;
            ds1.rangeUnion(u,v);
        }
        else{
            int u,v;
            cin>>u>>v;
            if(ds1.findUPar(u) != ds1.findUPar(v)) cout<<"NO"<<"\n";
            else cout<<"YES"<<"\n";
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