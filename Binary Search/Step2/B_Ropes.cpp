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

bool isPossible(double mid,vector<double>& v1,int k){
    int cnt=0;
    for(auto it:v1){
        cnt += (it)/mid;

    }
    return cnt>=k;
}
void solve(){
    int n,k;
    cin>>n>>k;
    vector<double> v1(n,0);
    ivec(v1);
    double start=0,end = 1e8;
    for(int i=1;i<=100;i++){
        double mid = (start)+(end-start)/2;
        if(isPossible(mid,v1,k)){
            start = mid;
        }
        else end = mid;
    }
    cout<<setprecision(20)<<start<<"\n";
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}


