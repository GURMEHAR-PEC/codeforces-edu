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

bool isPossible(int time,int x,int y,int n){
    if(time < min(x,y)) return false;
    int cnt=0;
    time -= min(x,y);
    cnt++;
    cnt += (time/x);
    cnt += (time/y);
    return cnt>=n;
}
void solve(){
    int n,x,y;
    cin>>n>>x>>y;

    int start=0,end=1;
    while(!isPossible(end,x,y,n)){
        end *= 2;
    }

    int ans=0;
    while(start<=end){
        int mid = (start)+(end-start)/2;
        if(isPossible(mid,x,y,n)){
            ans = mid;
            end = mid-1;
        }
        else start = mid+1;
    }
    cout<<ans<<"\n";
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}