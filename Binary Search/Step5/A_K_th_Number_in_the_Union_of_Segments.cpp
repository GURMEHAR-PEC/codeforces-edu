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

bool isPossible(int val,vector<pair<int,int>>& intervals,int n,int k){
    int cnt=0;
    for(auto it:intervals){
        if(it.first < val){
            cnt += min(it.second-it.first+1,val-it.first);
        }
    }


    return cnt<=k;
}
void solve(){
    int n,k;
    cin>>n>>k;
    int start = 1e10;
    int end = -1e10;
    vector<pair<int,int>> intervals;
    for(int i=0;i<n;i++){
        int l,r;
        cin>>l>>r;
        start = min(start,l);
        end = max(end,r);
        intervals.push_back({l,r});
    }
    int ans=start;
    while(start<=end){
        int mid = (start)+(end-start)/2;
        if(isPossible(mid,intervals,n,k) && !isPossible(mid+1,intervals,n,k)){
            ans = mid;
            break;
        }
        else if(isPossible(mid,intervals,n,k) && isPossible(mid+1,intervals,n,k)){
            ans = mid;
            start = mid+1;
        }
        else{
        
            end = mid-1;
        }
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