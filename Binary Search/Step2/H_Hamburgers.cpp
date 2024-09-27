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

bool isPossible(int mid,string &s,vector<int>& available,vector<int>& prices,int r){
    int cntB=0,cntS=0,cntC=0;
    for(auto it:s){
        if(it == 'B') cntB++;
        else if(it == 'S') cntS++;
        else cntC++;
    }

    cntB *= mid;
    cntS *= mid;
    cntC *= mid;

    int reqB=0,reqS=0,reqC=0;
    if(cntB > available[0]) reqB = cntB - available[0];
    if(cntS > available[1]) reqS = cntS - available[1];
    if(cntC > available[2]) reqC = cntC - available[2];
    return (reqB*prices[0] + reqS*prices[1] + reqC*prices[2]) <= r;

}
void solve(){
    string s;
    cin>>s;
    int start=0,end=1;
    vector<int> available(3,0),prices(3,0);
    cin>>available[0]>>available[1]>>available[2];
    cin>>prices[0]>>prices[1]>>prices[2];
    int r;
    cin>>r;
    while(isPossible(end,s,available,prices,r)){
        end *= 2;
    }

    int ans=0;
    while(start<=end){
        int mid = (start)+(end-start)/2;
        
        if(isPossible(mid,s,available,prices,r)){
            ans = mid;
            start = mid+1;
        }
        else end = mid-1;
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