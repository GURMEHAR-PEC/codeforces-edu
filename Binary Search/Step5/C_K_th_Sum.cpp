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

bool isPossible(int mid,vector<int>& v1,vector<int>& v2,int n,int k){
    int cnt=0;
    for(int i=0;i<n;i++){
        if(v1[i] > mid) break;
        else{
            int search = mid - v1[i];
            int start=0,end=n-1,ans=-1;
            while(start<=end){
                int mid = (start)+(end-start)/2;
                if(v2[mid] < search){
                    ans = mid;
                    start = mid+1;
                }
                else end = mid-1;
            }
            cnt += (ans+1);
        }
    }


    return cnt<=k;
}
void solve(){
    int n,k;
    cin>>n>>k;
    k--;
    vector<int> v1(n,0);
    ivec(v1);
    vector<int> v2(n,0);
    ivec(v2);
    sort(all(v1));
    sort(all(v2));
    int start = v1[0]+v2[0];
    int end = v1[n-1]+v2[n-1];
    int ans = start;
    while(start<=end){
        int mid = (start)+(end-start)/2;
        if(isPossible(mid,v1,v2,n,k) && !isPossible(mid+1,v1,v2,n,k)){
            ans = mid;
            break;
        }
        else if(isPossible(mid,v1,v2,n,k) && isPossible(mid,v1,v2,n,k)){
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