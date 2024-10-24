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
    int cnt=0;
    bool prefix = false;
    bool suffix = false;
    int sum=0;
};

class LazySegTree{
    vector<node> seg;
    vector<int> lazy;
    public:
    LazySegTree(int n){
        seg.resize(4*n);
        lazy.resize(4*n,-1);
    }

    void build(int ind,int low,int high,vector<int>& arr){
        if(low == high){
            seg[ind].cnt = (arr[low]==1);
            seg[ind].prefix = (arr[low]==1);
            seg[ind].suffix = (arr[low]==1);
            seg[ind].sum = arr[low];
            return;
        }

        int mid = (low+high)>>1;
        build((ind<<1)+1,low,mid,arr);
        build((ind<<1)+2,mid+1,high,arr);
        node newnode;
        newnode.cnt = seg[2*ind+1].cnt + seg[2*ind+2].cnt - (seg[2*ind+1].suffix & seg[2*ind+2].prefix);
        newnode.prefix = seg[2*ind+1].prefix;
        newnode.suffix = seg[2*ind+2].suffix;
        newnode.sum = seg[2*ind+1].sum + seg[2*ind+2].sum;
        seg[ind] = newnode;

    }

    void update(int ind,int low,int high,int l,int r,int val){
        if(lazy[ind]!=-1){
            seg[ind].cnt = (lazy[ind]==1);
            seg[ind].prefix = (lazy[ind]==1);
            seg[ind].suffix = (lazy[ind]==1);
            seg[ind].sum = (high-low+1)*lazy[ind];
            if(low!=high){
                lazy[(ind<<1)+1] = lazy[ind];
                lazy[(ind<<1)+2] = lazy[ind];
            }
            lazy[ind]=-1;
        }

        if(high <l || r<low) return;

        if(low >= l && high<=r){
            seg[ind].cnt = (val==1);
            seg[ind].prefix = (val==1);
            seg[ind].suffix = (val==1);
            seg[ind].sum = (high-low+1)*val;
            if(low!=high){
                lazy[(ind<<1)+1] = val;
                lazy[(ind<<1)+2] = val;
            }
            return;
        }

        int mid = (low+high)>>1;
        update((ind<<1)+1,low,mid,l,r,val);
        update((ind<<1)+2,mid+1,high,l,r,val);
        node newnode;
        newnode.cnt = seg[2*ind+1].cnt + seg[2*ind+2].cnt - (seg[2*ind+1].suffix & seg[2*ind+2].prefix);
        newnode.prefix = seg[2*ind+1].prefix;
        newnode.suffix = seg[2*ind+2].suffix;
        newnode.sum = seg[2*ind+1].sum + seg[2*ind+2].sum;
        seg[ind] = newnode;
    }

    node query(int ind,int low,int high,int l,int r){
        if(lazy[ind]!=-1){
            seg[ind].cnt = (lazy[ind]==1);
            seg[ind].prefix = (lazy[ind]==1);
            seg[ind].suffix = (lazy[ind]==1);
            seg[ind].sum = (high-low+1)*lazy[ind];
            if(low!=high){
                lazy[(ind<<1)+1] = lazy[ind];
                lazy[(ind<<1)+2] = lazy[ind];
            }
            lazy[ind]=-1;
        }

        if(high<l || r<low){
            node ans;
            return ans;
        }

        if(low>=l && high<=r) return seg[ind];
        int mid = (low+high)>>1;
        node left = query((ind<<1)+1,low,mid,l,r);
        node right = query((ind<<1)+2,mid+1,high,l,r);
        node ans;
        ans.cnt = left.cnt + right.cnt - (left.suffix & right.prefix);
        ans.prefix = left.prefix;
        ans.suffix = right.suffix;
        ans.sum = left.sum + right.sum;
        return ans;
    }
};

int sz = 1e6;
int range = 5*1e5;
void solve(){
    int n;
    cin>>n;
    vector<int> v1(sz,0);
    LazySegTree s1(sz);
    s1.build(0,0,sz-1,v1);
    for(int i=0;i<n;i++){
        char color;
        int l,r;
        cin>>color>>l>>r;
        l += range;
        s1.update(0,0,sz-1,l,l+r-1,(color == 'B'));
        node ans = s1.query(0,0,sz-1,0,sz-1);
        cout<<ans.cnt<<" "<<ans.sum<<"\n";
    }
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}