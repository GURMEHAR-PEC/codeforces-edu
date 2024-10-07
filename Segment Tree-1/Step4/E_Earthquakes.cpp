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
        seg[index] = min(seg[2 * index + 1], seg[2 * index + 2]);
    }

    int query(int index, int low, int high, int l, int r,int p,int n)
    {
        if (r < low || high < l)
            return 0;

        if (low  == high){
            if(seg[index] <= p){
                update(0,0,n-1,low,1e12);
                return 1;
            }
        }
        int mid = (low + high) / 2;

        if(seg[index] <= p){

            int sum1=0,sum2=0;

            if(seg[2*index+1] <= p){
                sum1 = query(2*index+1,low,mid,l,r,p,n);
            }
            if(seg[2*index+2] <= p){
                sum2 = query(2*index+2,mid+1,high,l,r,p,n);
            }
            return sum1+sum2;
        }
        return 0;
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
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};
void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> v1(n,1e12);

    SegmentTree s1(n);
    s1.build(0,0,n-1,v1);
    for(int i=0;i<q;i++){
        int a;
        cin>>a;
        if(a==1){
            int b,c;
            cin>>b>>c;
            s1.update(0,0,n-1,b,c);
        }
        else{
            int l,r,p;
            cin>>l>>r>>p;
            cout<<s1.query(0,0,n-1,l,r-1,p,n)<<"\n";
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