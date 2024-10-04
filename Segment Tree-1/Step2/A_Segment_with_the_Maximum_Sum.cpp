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

struct nodeInfo{
    int maxsum=0,prefsum=0,suffsum=0,tsum=0;
};

class SegmentTree
{
    public:
    vector<nodeInfo> seg;
    
    SegmentTree(int n)
    {
        seg.resize(4 * n + 1);
    }
    void build(int index, int low, int high, vector<int>& arr)
    {
        if (low == high)
        {
            seg[index].maxsum = max((ll)0,arr[low]);
            seg[index].prefsum = arr[low];
            seg[index].suffsum = arr[low];
            seg[index].tsum = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * index + 1, low, mid, arr);
        build(2 * index + 2, mid + 1, high, arr);
        seg[index].maxsum = max({(ll)0 ,seg[2*index+1].maxsum,seg[2*index+2].maxsum,seg[2*index+1].suffsum+seg[2*index+2].prefsum});
        seg[index].prefsum = max(seg[2*index+1].prefsum,seg[2*index+1].tsum + seg[2*index+2].prefsum);
        seg[index].suffsum = max(seg[2*index+2].suffsum,seg[2*index+2].tsum + seg[2*index+1].suffsum);
        seg[index].tsum = seg[2*index+1].tsum + seg[2*index+2].tsum;

        
    }

    int query(int index, int low, int high)
    {
        return seg[index].maxsum;
    }

    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind].maxsum = max((ll)0,val);
            seg[ind].prefsum = val;
            seg[ind].suffsum = val;
            seg[ind].tsum = val;
            return;
        }
        int mid = (low + high) >> 1;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val );
        else
            update(2 * ind + 2, mid + 1, high, i, val);
        seg[ind].maxsum = max({(ll)0,seg[2*ind+1].maxsum,seg[2*ind+2].maxsum,seg[2*ind+1].suffsum + seg[2*ind+2].prefsum});
        seg[ind].prefsum = max(seg[2*ind+1].prefsum,seg[2*ind+1].tsum + seg[2*ind+2].prefsum);
        seg[ind].suffsum = max(seg[2*ind+2].suffsum,seg[2*ind+2].tsum + seg[2*ind+1].suffsum);
        seg[ind].tsum = seg[2*ind+1].tsum + seg[2*ind+2].tsum;
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> v1(n,0);
    ivec(v1);
    SegmentTree sgt1(n);
    sgt1.build(0,0,n-1,v1);
    cout<<sgt1.query(0,0,n-1)<<"\n";
    
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        sgt1.update(0,0,n-1,a,b);
        cout<<sgt1.query(0,0,n-1)<<"\n";
    }
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}