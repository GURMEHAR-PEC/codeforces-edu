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
int sz = 1e5+1;
void solve(){
    int n,k;
    cin>>n>>k;
    vector<int> v1(n,0);
    ivec(v1);
    vector<int> freq(sz,0);
    int cnt=0;
    int i=0,j=0;
    int ans=0;
    while(j<n){
        if(cnt + (freq[v1[j]]==0) <= k){
            ans += (j-i+1);
            if(freq[v1[j]]==0) cnt++;
            freq[v1[j]]++;
            j++;
        }
        else{
            if(i==j){
                i++,j++;
            }
            else{
                freq[v1[i]]--;
                if(freq[v1[i]]==0) cnt--;
                i++;
            }
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