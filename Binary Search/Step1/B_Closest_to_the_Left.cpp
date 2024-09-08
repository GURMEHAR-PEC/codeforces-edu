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
int getIndex(vector<int>& v1,int &target){
    int n = v1.size();
    int start=0,end=n-1,ans=-1;
    while(start<=end){
        int mid = (start)+(end-start)/2;
        if(v1[mid]<=target){
            ans = mid;
            start = mid+1;
        }
        else end = mid-1;
    }
    return ans+1;
}
void solve(){
    int n,k;
    cin>>n>>k;
    vector<int> v1(n,0);
    ivec(v1);
    vector<int> q(k,0);
    ivec(q);
    for(auto it:q){
        cout<<getIndex(v1,it)<<"\n";
    }
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}