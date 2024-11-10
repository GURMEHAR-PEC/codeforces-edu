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
struct node{
    int wt=0,cost=0;
};
void solve(){
    int n,m,s,A,B;
    cin>>n>>m>>s>>A>>B;
    vector<int> a(n,0),b(m,0);
    ivec(a);
    ivec(b);
    vector<node> v;
    int sz = n+m;
    sort(all(a));
    sort(all(b));
    for(auto it:a){
        node n1;
        n1.cost = it;
        n1.wt = A;
        v.push_back(n1);
    }
    reverse(all(b));
    for(auto it:b){
        node n1;
        n1.cost = it;
        n1.wt = B;
        v.push_back(n1);
    }
    int i=0,j=0;
    int currCost=0,maxCost=0,currW=0;
    while(j<sz){
        if(currW + v[j].wt <= s){
            currCost += v[j].cost;
            currW += v[j].wt;
            maxCost = max(maxCost,currCost);
            j++;
        }
        else{
            if(i==j) i++,j++;
            else{
                currCost -= v[i].cost;
                currW -= v[i].wt;
                maxCost = max(maxCost,currCost);
                i++;
            }
        }
    }
    cout<<maxCost<<"\n";
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}