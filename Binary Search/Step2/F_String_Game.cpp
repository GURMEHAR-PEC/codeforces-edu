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

bool isPossible(int mid,string &t,string &p,vector<int>& pos,int n){
    vector<int> removed(n,0);
    for(int i=0;i<mid;i++){
        removed[pos[i]-1]=1;
    }

    string rem;
    for(int i=0;i<n;i++){
        if(removed[i]==0) rem += t[i];
    }

    int b = p.length();
    int a = rem.length();
    int i=0,j=0;
    while(i<a && j<b){
        if(rem[i] == p[j]){
            i++,j++;
        }
        else i++;
    }
    if(j == b) return true;
    return false;
}
void solve(){
    string t;
    string p;
    cin>>t>>p;
    int n = t.length();
    vector<int> pos(n,0);
    ivec(pos);

    int start=0,end = n;
    int ans=0;
    while(start<=end){
        int mid = (start)+(end-start)/2;
        if(isPossible(mid,t,p,pos,n)){
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