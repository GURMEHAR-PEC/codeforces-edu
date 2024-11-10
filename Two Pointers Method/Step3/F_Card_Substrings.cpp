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
bool check(vector<int>& s_occ,vector<int>& t_occ){
    for(int i=0;i<26;i++){
        if(s_occ[i] > t_occ[i]) return false;
    }
    return true;
}
void solve(){
    int n,m;
    cin>>n>>m;
    string s,t;
    cin>>s>>t;
    int ans=0;
    vector<int> s_occ(26,0),t_occ(26,0);
    for(auto it:t) t_occ[it-'a']++;
    int i=0,j=0;
    while(j<n){
        s_occ[s[j]-'a']++;
        if(check(s_occ,t_occ)){
            ans += (j-i+1);
            j++;
        }
        else{
            s_occ[s[j]-'a']--;
            if(i==j) i++,j++;
            else{
                s_occ[s[i]-'a']--;
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