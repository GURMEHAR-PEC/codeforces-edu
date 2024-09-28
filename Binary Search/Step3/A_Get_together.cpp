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
bool isPossible(double time,vector<pair<double,double>>& v1,int n){
 

    double mindist=0,maxdist=0;
    bool hasmin = false,hasmax = false;
    for(int i=0;i<n;i++){
        if(hasmin){
            mindist = max(mindist,v1[i].first - time*v1[i].second);
        }
        else{
            mindist = v1[i].first -  time*v1[i].second;
            hasmin = true;

        }

        if(hasmax){
            maxdist = min(maxdist,v1[i].first + time*v1[i].second);
            

        }
        else{
            maxdist = v1[i].first + time*v1[i].second;
            hasmax = true;
        }
        
    }

    return mindist <= maxdist;

}
void solve(){
    int n;
    cin>>n;
    vector<pair<double,double>> v1;
    for(int i=0;i<n;i++){
        double x,y;
        cin>>x>>y;
        v1.push_back({x,y});
    }

    double start=0,end=1;

    while(!isPossible(end,v1,n)){
        end *= 2;
    }
    
    double ans=0;
    while(end-start > 1e-6){
        double mid = (start)+(end-start)/2.0;
        if(isPossible(mid,v1,n)){
            ans = mid;
            end = mid;
        }
        else start = mid;
    }

    cout<<setprecision(20)<<ans<<"\n";
}


int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}