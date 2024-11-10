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
void solve(){
    int n,s;
    cin>>n>>s;
    vector<int> w(n,0),c(n,0);
    ivec(w);
    ivec(c);
    int i=0,j=0,currW=0,currC=0,maxC=0;
    while(j<n){
        if(currW + w[j]<=s){
            currW += w[j];
            currC += c[j];
            maxC = max(maxC,currC);
            j++;
        }
        else{
            if(i==j) i++,j++;
            else{
                currW -= w[i];
                currC -= c[i];
                maxC = max(maxC,currC);
                i++;
            }
        }
    }
    cout<<maxC<<"\n";
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}