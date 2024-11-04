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
struct op{
    int u=-1,v=-1,state=-1,ans=-1;
};
class DisjointSet{
    vector<int> rank,parent,size;
    stack<op> s1;
public:
    DisjointSet(int n){
        rank.resize(n+1,0);
        parent.resize(n+1);
        size.resize(n+1,1);
        for(int i=0;i<=n;i++){
            parent[i] = i;
        } 
        op o1;
        o1.ans= n;
        s1.push(o1);
    }
    int findUPar(int node){
        if(node == parent[node]) return node;
        return findUPar(parent[node]);
    }
    int getCurrAns(){
        return s1.top().ans;
    }
    int UnionBySize(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v){
            op o1;
            o1.u = ulp_u;
            o1.v = ulp_v;
            o1.state = -1;
            o1.ans = getCurrAns();
            s1.push(o1);
            return o1.ans;
        }
        op o1;
        o1.u = ulp_u;
        o1.v = ulp_v;
        o1.ans = getCurrAns()-1;
        if(size[ulp_u] < size[ulp_v]){
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
            o1.state = 2;
        }
        else{
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
            o1.state=1;
        }
        s1.push(o1);
        return o1.ans;
    }
    void addPersist(){
        op o1;
        o1.ans = getCurrAns();
        s1.push(o1);
    }
    int rollback(){
        while(s1.top().u !=-1){
            auto it = s1.top();
            s1.pop();
            if(it.state == -1) continue;
            else if(it.state == 1){
                int ulp_u = it.u;
                int ulp_v = it.v;
                size[ulp_u] -= size[ulp_v];
                parent[ulp_v] = ulp_v;
            }
            else{
                int ulp_u = it.u;
                int ulp_v = it.v;
                size[ulp_v] -= size[ulp_u];
                parent[ulp_u] = ulp_u;
            }
        }

        auto it = s1.top();
        s1.pop();
        return it.ans;
    }
    
};
void solve(){
    int n,m;
    cin>>n>>m;
    DisjointSet ds1(n);
    for(int i=0;i<m;i++){
        string op;
        cin>>op;
        if(op == "persist"){
            ds1.addPersist();
        }
        else if(op == "union"){
            int u,v;
            cin>>u>>v;
            cout<<ds1.UnionBySize(u,v)<<"\n";
        }
        else{
            cout<<ds1.rollback()<<"\n";
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