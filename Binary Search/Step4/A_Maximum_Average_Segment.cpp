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

bool isPossible(double x, vector<double> &v1, int n, int d)
{
    vector<double> prefix(n + 1, 0);
    
    for (int i = 1; i <= n; i++)
    {
        prefix[i] = prefix[i - 1] + v1[i - 1] - x;
    }
    vector<double> minPrefix(n + 1, 0);
    double mini = 1e9;
    for (int i = 0; i <= n; i++)
    {
        mini = min(mini, prefix[i]);
        minPrefix[i] = mini;
    }
    for (int r = d; r <= n; r++)
    {
        if (prefix[r] >= minPrefix[r - d])
        {
            return true;
        }
    }
    return false;
}
pair<int, int> getindex(double ans, vector<double> &v1, int n, int d)
{
    

    int a=0,b=0;
    vector<double> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        prefix[i] = prefix[i - 1] + v1[i - 1] - ans;
    }
    vector<double> minPrefix(n + 1, 0);
  
    double mini = 1e9;
    for (int i = 0; i <= n; i++)
    {
        mini = min(mini, prefix[i]);
        minPrefix[i] = mini;
    }
  
    for (int r = d; r <= n; r++)
    {
        if (prefix[r] >= minPrefix[r - d])
        {
         
            b=r;
            a=r-d;
            break;
        }
    }

    for(int i=0;i<=n;i++){
        if(minPrefix[i] == minPrefix[a]){
            a = i+1;
            break;
        }
    }
   
    return {a,b};
}
void solve()
{
    int n, d;
    cin >> n >> d;
    vector<double> v1(n, 0);
    ivec(v1);
    double start = 0;
    
    double end = 110;
    double ans = start;
    for(int i=0;i<110;i++){
        double mid = (start)+(end-start)/2;
        if(isPossible(mid,v1,n,d)){
            ans = mid;
            start = mid;
        }
        else end = mid;
    }
    pair<int, int> p1 = getindex(ans, v1, n, d);
    cout << p1.first << " " << p1.second << "\n";
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}