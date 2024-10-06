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
        seg[index] = max(seg[2 * index + 1], seg[2 * index + 2]);
    }

    int query(int index, int low, int high, int value, int limit)
    {
        if(limit > high) return -1;
        if(low == high){
            if(seg[index] >= value) return low;
            else return -1;
        }
        int mid = (low+high)>>1;
        if(seg[2*index+1] >= value){
            int leftvalue = query(2*index+1,low,mid,value,limit);
            if(leftvalue != -1) return leftvalue;
        }
        
        if(seg[2*index+2] >= value){
            int rightvalue = query(2*index+2,mid+1,high,value,limit);
            if(rightvalue != -1) return rightvalue;
        }


        return -1;
    }

    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] = val;
            return;
        }
        int mid = (low + high) >> 1;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val );
        else
            update(2 * ind + 2, mid + 1, high, i, val);
        seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> v1(n,0);
    ivec(v1);
    SegmentTree s1(n);
    s1.build(0,0,n-1,v1);
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        if(a==1){
            s1.update(0,0,n-1,b,c);
        }
        else{
            cout<<s1.query(0,0,n-1,b,c)<<"\n";
        }
    }
    
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}