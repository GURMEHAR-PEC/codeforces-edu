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
    int sz;
    stack<op> s1;
public:
    DisjointSet(int n){
        rank.resize(n+1,0);
        parent.resize(n+1);
        size.resize(n+1,1);
        for(int i=0;i<=n;i++){
            parent[i] = i;
        } 
        sz=n;
        op o1;
        o1.ans = n;
        s1.push(o1);
    }
    int findUPar(int node){
        if(node == parent[node]) return node;
        return findUPar(parent[node]);
    }
    int getCurrVal(){
        return s1.top().ans;
    }
    void UnionBySize(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v){
            op o1;
            o1.u = ulp_u;
            o1.v = ulp_v;
            o1.ans = getCurrVal();
            o1.state=-1;
            s1.push(o1);
            return;
        }
        op o1;
        o1.u = ulp_u;
        o1.v = ulp_v;
        o1.ans = getCurrVal()-1;
        if(size[ulp_u] < size[ulp_v]){
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
            o1.state=2;
        }
        else{
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
            o1.state=1;
        }
        s1.push(o1);
    }
    void rollback(){
        while(s1.top().u != -1){
            auto it = s1.top();
            s1.pop();
            if(it.state == -1) continue;
            else if(it.state == 1){
                size[it.u] -= size[it.v];
                parent[it.v] = it.v;
            }
            else{
                size[it.v] -= size[it.u];
                parent[it.u] = it.u;
            }
        } 
    }
    void save(){
        op o1;
        o1.ans = getCurrVal();
        s1.push(o1);
    }
    void ResetDSU(int n){
        for(int i=0;i<=n;i++){
            size[i]=1;
            parent[i] = i;
        }
        while(!s1.empty()) s1.pop();
        op o1;
        o1.ans = n;
        s1.push(o1);
    }
};
void remove(int idx);
void add(int idx);
int get_answer();
int block_size;
struct Query{
    int l,r,idx;
    bool operator<(Query other) const{
        return make_pair(l/block_size,r) < make_pair(other.l/block_size,other.r);
    }
};
vector<int> mos_algo(vector<Query> queries,int n,int m,vector<pair<int,int>>& edges){
    vector<int> answers(queries.size());
    sort(queries.begin(),queries.end());
    
    int temp = block_size;
    int curr_block = block_size;
    DisjointSet ds1(n);
    for(Query q:queries){
        while(q.l >= curr_block){
            ds1.ResetDSU(n);
            curr_block += block_size;
            temp = curr_block;
        
        }
        if((q.l/block_size) == (q.r/block_size)){
            ds1.save();
            for(int i=q.l;i<=q.r;i++){
                ds1.UnionBySize(edges[i].first,edges[i].second);
            }
            answers[q.idx] = ds1.getCurrVal();
            ds1.rollback();
        }
        else{
            while(temp<=q.r){
                ds1.UnionBySize(edges[temp].first,edges[temp].second);
                temp++;
            }
            ds1.save();
            int i=q.l;
            while(i<curr_block){
                ds1.UnionBySize(edges[i].first,edges[i].second);
                i++;
            }
            answers[q.idx] = ds1.getCurrVal();
            ds1.rollback();
        } 
    }
    return answers;
}
void solve(){
    int n,m;
    cin>>n>>m;
    block_size = sqrt(m)+1;
    vector<pair<int,int>> edges;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        edges.push_back({u,v});
    }
    vector<Query> queries;
    int k;
    cin>>k;
    for(int i=0;i<k;i++){
        int l,r;
        cin>>l>>r;
        l--,r--;
        Query q1;
        q1.l = l;
        q1.r = r;
        q1.idx = i;
        queries.push_back(q1);
    }
    vector<int> ans = mos_algo(queries,n,m,edges);
    for(auto it:ans){
        cout<<it<<"\n";
    }
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}



