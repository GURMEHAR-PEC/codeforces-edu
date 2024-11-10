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
stack<int> s1;
stack<bitset<1001>> s1_values;
stack<int> s2;
stack<bitset<1001>> s2_values;
void add(int j,vector<int>& v1){
    s2.push(v1[j]);
    if(s2_values.empty()){
        bitset<1001> b1;
        b1.set(0,1);
        b1 = (b1 | (b1<<v1[j]));
        
        s2_values.push(b1);
    }
    else{
        bitset<1001> b1 = s2_values.top();
        b1 = (b1 | (b1<<v1[j]));
        s2_values.push(b1);
    }
}

bool getVal(int s){
    if(s1_values.empty() && s2_values.empty()) return false;
    if(s1_values.empty()){
        return s2_values.top()[s];
    }
    if(s2_values.empty()) return s1_values.top()[s];

    bitset<1001> b1 = s1_values.top();
    bitset<1001> b2 = s2_values.top();
    for(int i=0;i<=s;i++){
        if(b1[i]==1 && b2[s-i]==1) return true;
    }
    return false;
}
void remove(int i,vector<int>& v1){
    if(s1_values.empty()){
        bitset<1001> b1;
        b1.set(0,1);
        while(!s2.empty()){
            s1.push(s2.top());
            b1 = (b1 | (b1<<(s2.top())));
            s1_values.push(b1);
            s2.pop();
            s2_values.pop();
        }
    }
    s1.pop();
    s1_values.pop();
}
void solve(){
    int n,s;
    cin>>n>>s;
    
    vector<int> v1(n,0);
    ivec(v1);
    int minLen = INT_MAX;
    int i=0,j=0;
    while(j<n){
        add(j,v1);
        while(getVal(s)){
        
            minLen = min(minLen,j-i+1);
            remove(i,v1);
            i++;
        }
        j++;
    }

    if(minLen == INT_MAX) cout<<-1<<"\n";
    else cout<<minLen<<"\n";
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}