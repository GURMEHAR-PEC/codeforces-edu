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


class SegmentTree
{
    public:
    vector<int> seg;
    
    SegmentTree(int n)
    {
        seg.resize(4 * n + 1);
    }
    void build(int index, int low, int high, vector<int>& arr)
    {
        if (low == high)
        {
            seg[index] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * index + 1, low, mid, arr);
        build(2 * index + 2, mid + 1, high, arr);
        seg[index] = seg[2 * index + 1] + seg[2 * index + 2];
    }

    int query(int index, int low, int high, int value)
    {
        if(low == high) return low;

        int mid = (low+high)>>1;
        if(seg[2*index+1] >= value+1) return query(2*index+1,low,mid,value);
        return query(2*index+2,mid+1,high,value-seg[2*index+1]);
    }

    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] = 0;
            return;
        }
        int mid = (low + high) >> 1;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val );
        else
            update(2 * ind + 2, mid + 1, high, i, val);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
};

void solve(){
    int n;
    cin>>n;
    vector<int> v1(n,0);
    ivec(v1);
    vector<int> v2(n,1);
    SegmentTree s1(n);
    s1.build(0,0,n-1,v2);
    vector<int> ans(n,0);


    for(int i=n-1;i>=0;i--){
        int k = i-v1[i];
        ans[i] = 1+s1.query(0,0,n-1,k);
        s1.update(0,0,n-1,ans[i]-1,0);

    }

    for(auto it:ans){
        cout<<it<<" ";
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