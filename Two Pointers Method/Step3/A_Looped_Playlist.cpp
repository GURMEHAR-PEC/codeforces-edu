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
int getlen(int i,int j,int n){
    if(j>=i) return j-i+1;
    return (j-i+1+n);
}
void solve(){
    int n,p;
    cin>>n>>p;
    vector<int> v1(n,0);
    ivec(v1);
    int i=0,j=0;
    int minLen = INT_MAX;
    int minStart =-1;
    int currSum=0;
    int cnt=0;
    int tsum = 0;
    for(auto it:v1) tsum += it;
    cnt = p/tsum;
    p = p%tsum;
    
    while(j<2*n){
        currSum += v1[j%n];
        while(currSum>=p){
            if(j-i+1 < minLen){
                minLen = j-i+1;
                minStart = i%n;
            }
            currSum -= v1[i%n];
            i++;
        }
        j++;
    }
    if(minStart == -1) minStart=0;
    if(minLen == INT_MAX) minLen=0;
    cout<<minStart+1<<" "<<minLen+cnt*n<<"\n";
}





int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}