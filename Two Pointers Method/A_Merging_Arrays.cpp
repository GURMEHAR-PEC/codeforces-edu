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
    int n,m;
    cin>>n>>m;
    vector<int> v1(n,0);
    vector<int> v2(m,0);
    ivec(v1);
    ivec(v2);
    int i=0,j=0;
    while(i<n && j<m){
        if(v1[i] < v2[j]){
            cout<<v1[i]<<" ";
            i++;
        }
        else{
            cout<<v2[j]<<" ";
            j++;
        }
    }
    while(i<n){
        cout<<v1[i]<<" ";
        i++;
    }
    while(j<m){
        cout<<v2[j]<<" ";
        j++;
    }
    cout<<"\n";
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}