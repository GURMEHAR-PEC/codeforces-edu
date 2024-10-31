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
    int color=0;
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
            info[i].color=0;
            info[i].depth=0;
            info[i].size=1;
        } 
    }
    int findUPar(int node){
        if(node == parent[node]) return parent[node];
        int newParent = findUPar(parent[node]);
        int oldParent = parent[node];
        parent[node] = newParent;
        if(newParent == oldParent) return parent[node];

        info[node].depth += (info[oldParent].depth+info[newParent].depth);
        if((info[node].depth%2) == (info[newParent].depth%2)){
            info[node].color = info[newParent].color;
        }
        else info[node].color = !info[newParent].color;
        return parent[node];
    }
    void UnionBySize(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v) return;
        if(info[ulp_u].size > info[ulp_v].size){
            info[ulp_u].size += info[ulp_v].size;
            parent[ulp_v] = ulp_u;
            bool b1 = (info[ulp_u].depth%2 == info[u].depth%2 && info[ulp_v].depth%2 == info[v].depth%2);
            bool b2 = (info[ulp_u].depth%2 != info[u].depth%2 && info[ulp_v].depth%2 != info[v].depth%2);
            if(b1 | b2){
                info[ulp_v].depth += info[ulp_u].depth+1;
                info[ulp_v].color = !info[ulp_u].color;
            }
            else{
                info[ulp_v].depth += info[ulp_u].depth;
                info[ulp_v].color = info[ulp_u].color;
            }
        }
        else{
            info[ulp_v].size += info[ulp_u].size;
            parent[ulp_u] = ulp_v;
            bool b1 = (info[ulp_u].depth%2 == info[u].depth%2 && info[ulp_v].depth%2 == info[v].depth%2);
            bool b2 = (info[ulp_u].depth%2 != info[u].depth%2 && info[ulp_v].depth%2 != info[v].depth%2);
            if(b1 | b2){
                
                info[ulp_u].depth += info[ulp_v].depth+1;
                info[ulp_u].color = !info[ulp_v].color;
            }
            else{
                info[ulp_u].depth += info[ulp_v].depth;
                info[ulp_u].color = info[ulp_v].color;
            }
        }
    }

    bool checkColor(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(info[u].color == info[v].color) return true;
        return false;
    }
    void print(int n){
        for(int i=0;i<=n;i++){
            cout<<parent[i]<<" ";
        }
        cout<<"\n";
        for(int i=0;i<=n;i++){
            cout<<info[i].color<<" ";
        }
        cout<<"\n";
        for(int i=0;i<=n;i++){
            cout<<info[i].depth<<" ";
        }
        cout<<"\n";
        for(int i=0;i<=n;i++){
            cout<<info[i].size<<" ";
        }
        cout<<"\n";
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    DisjointSet ds1(n);
    int cnt=0;
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        if(a==0){
            int u = (b+cnt)%n;
            int v = (c+cnt)%n;
            if(u==0) u=n;
            if(v == 0) v=n;
            ds1.UnionBySize(u,v);
        }
        else{
            int u = (b+cnt)%n;
            int v = (c+cnt)%n;
            if(u==0) u=n;
            if(v==0) v=n;
            if(ds1.checkColor(u,v)){
                cnt++;
                cout<<"YES"<<"\n";
            }
            else cout<<"NO"<<"\n";
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
