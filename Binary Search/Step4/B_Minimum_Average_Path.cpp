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


vector<int> getTopoSort(vector<pair<int,int>> adj[],int n,int m){
    vector<int> vis(n+1,0),inDegree(n+1,0);
    vector<int> ans;
    queue<int> q1;
    for(int i=1;i<=n;i++){
        for(auto it:adj[i]){
            inDegree[it.first]++;
        }
    }
    for(int i=1;i<=n;i++){
        if(inDegree[i] == 0){
            q1.push(i);
            vis[i]=1;
        }
    }

    while(!q1.empty()){
        auto it = q1.front();
        q1.pop();
        ans.push_back(it);
        for(auto adjnode : adj[it]){
            if(!vis[adjnode.first]){
                inDegree[adjnode.first]--;
                if(inDegree[adjnode.first] == 0){
                    q1.push(adjnode.first);
                    vis[adjnode.first]=1;
                }
            }
        }
    }
    return ans;

}
bool isPossible(double mid,vector<pair<int,int>> adj[],int n,int m,vector<int>& toposort){
    vector<double> dist(n+1,1e10);
    dist[1]=0;

    for(auto node : toposort){
        for(auto it:adj[node]){
            if(dist[node] + it.second - mid < dist[it.first]){
                dist[it.first] = dist[node]+it.second-mid;
            }
        }
    }

    return dist[n] <= 0;
}


vector<int> getPath(double value,vector<pair<int,int>> adj[],int n,int m,vector<int>& toposort){
    vector<double> dist(n+1,1e10);
    dist[1]=0;
    vector<int> parents(n+1,-1);
    vector<int> ans;

    for(auto node : toposort){
        for(auto it:adj[node]){
            if(dist[node] + it.second - value < dist[it.first]){
                dist[it.first] = dist[node] + it.second - value;
                parents[it.first] = node;
            }
        }
    }

    int currNode = n;
    while(currNode!=-1){
        ans.push_back(currNode);
        currNode = parents[currNode];
    }





    reverse(ans.begin(),ans.end());
    return ans;
}
void solve(){
    int n,m;
    cin>>n>>m;

    vector<pair<int,int>> adj[n+1];
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
    }

    vector<int> toposort;
    toposort = getTopoSort(adj,n,m);
    double start = 0,end = 110;
    for(int i=0;i<100;i++){
        double mid = (start)+(end-start)/2;
        if(isPossible(mid,adj,n,m,toposort)){
            end = mid;
        }
        else start = mid;
    }

    vector<int> path = getPath(end,adj,n,m,toposort);
    cout<<path.size()-1<<"\n";
    for(auto it:path) cout<<it<<" ";
    cout<<"\n";
    // for(auto it:toposort) cout<<it<<" ";
    // cout<<"\n"; 

    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}