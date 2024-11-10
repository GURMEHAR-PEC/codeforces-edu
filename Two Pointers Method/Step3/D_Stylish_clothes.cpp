// Gurmehar Singh

#include <bits/stdc++.h>
#include <algorithm>
// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
#define yes cout << "Yes" << "\n"
#define no cout << "No" << "\n"
#define nl cout << "\n"
#define all(a) a.begin(), a.end()
#define ivec(vec)                        \
    for (int i = 0; i < vec.size(); i++) \
    {                                    \
        cin >> vec[i];                   \
    }
#define ovec(vec)                        \
    for (int i = 0; i < vec.size(); i++) \
    {                                    \
        cout << vec[i] << " ";           \
    }
#define pb push_back
#define int long long
using ll = long long;
using ull = unsigned long long;
const int mod = 1e9 + 7;
using namespace std;
// using namespace __gnu_pbds;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> pbds;
// // (functions find_by_order, order_of_key)
vector<set<int>> sets(4);
struct node{
    int ans=0;
    vector<int> values;
};
node getval(){
    vector<pair<int,int>> stuff;
    for(int i=0;i<4;i++){
        stuff.push_back({*sets[i].begin(),*sets[i].rbegin()});
    }
    int maxi = 0;
    for(int i=0;i<4;i++){
        maxi = max(maxi,stuff[i].second);
    }
    vector<int> maxVals;
    
    for(int i=0;i<4;i++){
        if(stuff[i].second == maxi){
            maxVals.push_back(i);
        }
    }
    int ans = INT_MAX;
    int maxmap=-1,minmap=-1;
    int temp=-1;
    for(auto it:maxVals){
        int maxiValue = stuff[it].second;
        int miniValue = INT_MAX;
        for(int j=0;j<4;j++){
            if(j == it) continue;
            if(stuff[j].first < miniValue){
                miniValue = stuff[j].first;
                temp = j;
            }
        }
        if(maxiValue - miniValue < ans){
            ans = maxiValue - miniValue;
            minmap = temp;
            maxmap = it;
        }
        
    }
    node n1;
    n1.ans = ans;
    vector<int> values(4,0);
    for(int i=0;i<4;i++){
        if(i == minmap){
            values[i] = stuff[i].first;
        }
        else{
            values[i] = stuff[i].second;
        }
    }
    n1.values = values;
    return n1;
}
void solve()
{
    int n1;
    cin >> n1;
    vector<int> v1(n1, 0);
    ivec(v1);
    int n2;
    cin >> n2;
    vector<int> v2(n2, 0);
    ivec(v2);
    int n3;
    cin >> n3;
    vector<int> v3(n3, 0);
    ivec(v3);
    int n4;
    cin >> n4;
    vector<int> v4(n4, 0);
    ivec(v4);
    int minDiff = INT_MAX;
    vector<pair<int, int>> v;
    for (auto it : v1){
        int t = sets[0].size();
        sets[0].insert(it);
        if(t!=sets[0].size()) v.push_back({it,0});
    }
    for (auto it : v2){
        int t = sets[1].size();
        sets[1].insert(it);
        if(t!=sets[1].size()) v.push_back({it,1});
    }
    for (auto it : v3){
        int t = sets[2].size();
        sets[2].insert(it);
        if(t!=sets[2].size()) v.push_back({it,2});
    }
    for (auto it : v4){
        int t = sets[3].size();
        sets[3].insert(it);
        if(t!=sets[3].size()) v.push_back({it,3});
    }
        
    sets[0].clear();
    sets[1].clear();
    sets[2].clear();
    sets[3].clear();
    sort(all(v));
    int n = v.size();
    int cnt = 0;
    int i = 0, j = 0;
    node ansnode;
    while (j < n)
    {
        if(sets[v[j].second].size() == 0) cnt++;
        sets[v[j].second].insert(v[j].first);
        while(cnt == 4){
            node newnode = getval();
            if(newnode.ans < minDiff){
                minDiff = newnode.ans;
                ansnode.ans = minDiff;
                ansnode.values = newnode.values;
            }
            sets[v[i].second].erase(v[i].first);
            if(sets[v[i].second].size() == 0) cnt--;
            i++;
        }

        j++;
    }
    // cout<<minDiff<<"\n";
    for(auto it:ansnode.values) cout<<it<<" ";
    cout<<"\n";
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}