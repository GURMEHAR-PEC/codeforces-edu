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


bool isPossible(int cost,vector<pair<int,int>> adj[],int n,int m,int d){
    queue<pair<int,int>> q1;
    vector<int> vis(n+1,0);
    q1.push({1,0});
    vis[1]=0;
    while(!q1.empty()){
        auto it = q1.front();
        if(it.first == n) return true;
        if(it.second == d) return false;
        q1.pop();
        int node = it.first;
        int steps = it.second;
        for(auto adjnode : adj[node]){
            if(!vis[adjnode.first] && adjnode.second <= cost){
                q1.push({adjnode.first,steps+1});
                vis[adjnode.first]=1;
            }
        }


    }
    return false;
}

bool dfs(int node,vector<pair<int,int>> adj[],int n,int m,int d,int ans,vector<int>& path,vector<int>& vis){
    
    if(node == n){
        path.push_back(node);
        return true;
    }
    if(d == 0) return false;
    vis[node]=1;
    for(auto it:adj[node]){
        if(!vis[it.first] && it.second <= ans){
            if(dfs(it.first,adj,n,m,d-1,ans,path,vis)){
                path.push_back(node);
                return true;
            }
        }
    }
    vis[node]=0;
    return false;
}
void solve(){
    int n,m,d;
    cin>>n>>m>>d;
    vector<pair<int,int>> adj[n+1];
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
    }
    int start = 0,end = 1e10;
    int ans=-1;
    while(start<=end){
        

        int mid = (start)+(end-start)/2;
        if(isPossible(mid,adj,n,m,d)){
 
            ans = mid;
            end = mid-1;
        }
        else start = mid+1;
    }
    if(ans == -1) cout<<ans<<"\n";
    else{
    
        vector<int> path;
        vector<int> vis(n+1,0);
        bool value = dfs(1,adj,n,m,d,ans,path,vis);
        cout<<path.size()-1<<"\n";
        reverse(path.begin(),path.end());
        for(auto it:path) cout<<it<<" ";
        cout<<"\n";
    }
    
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}