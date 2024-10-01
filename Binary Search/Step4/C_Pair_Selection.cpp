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

bool isPossible(double mid,vector<pair<double,double>>& v1,int n,int k){
    vector<double> v2;
    double psum=0;
    for(auto it:v1){
        v2.push_back(it.first - mid*it.second);
    }

    sort(v2.rbegin(),v2.rend());
    for(int i=0;i<k;i++){
        psum += v2[i];
    }

    return psum >=0;
}
void solve(){
    int n,k;
    cin>>n>>k;
    double start=0,end=1e10;

    vector<pair<double,double>> v1;
    for(int i=0;i<n;i++){
        double n1,n2;
        cin>>n1>>n2;
        v1.push_back({n1,n2});
    }

    for(int i=0;i<100;i++){
        double mid = (start)+(end-start)/2;
        if(isPossible(mid,v1,n,k)){
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