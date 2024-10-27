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
    vector<vector<int>> groups;
    vector<int> result;
public:
    DisjointSet(int n){
        rank.resize(n+1,0);
        parent.resize(n+1);
        size.resize(n+1,1);
        result.resize(n+1,-1);
        groups.resize(n+1);
        for(int i=0;i<=n;i++){
            groups[i].push_back(i);
        }
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
    void UnionBySize(int u,int v,int time){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        int leader = findUPar(1);

        if(ulp_u == ulp_v) return;

        if(ulp_u == leader){
            for(auto it:groups[ulp_v]) result[it] = time;
        }
        else if(ulp_v == leader) {
            for(auto it:groups[ulp_u]) result[it] = time;
        }


        if(size[ulp_u] > size[ulp_v]){
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
            for(auto it:groups[ulp_v]){
                groups[ulp_u].push_back(it);
            }
            groups[ulp_v].clear();
        }
        else{
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
            for(auto it:groups[ulp_u]){
                groups[ulp_v].push_back(it);
            }
            groups[ulp_u].clear();
        }


    }

    void getResult(int n){
        for(int i=1;i<=n;i++){
            cout<<result[i]<<"\n";
        }

    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<pair<int,int>> monkeys(n+1);
    vector<int> m1(m+1),m2(m+1);
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        monkeys[i+1] = {x,y};
    }
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        m1[i+1] = x;
        if(y==1){
            m2[i+1] = monkeys[x].first;
            monkeys[x].first=-1;
        }
        else{
            m2[i+1] = monkeys[x].second;
            monkeys[x].second=-1;
        }
    }


    DisjointSet ds1(n);

    for(int i=1;i<=n;i++){
        if(monkeys[i].first !=-1){
            ds1.UnionBySize(i,monkeys[i].first,-1);
        }
        if(monkeys[i].second != -1){
            ds1.UnionBySize(i,monkeys[i].second,-1);
        }
    }
    for(int i=m;i>=1;i--){
        ds1.UnionBySize(m1[i],m2[i],i-1);
    }
    ds1.getResult(n);



    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}