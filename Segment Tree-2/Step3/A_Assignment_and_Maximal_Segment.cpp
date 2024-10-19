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

struct Node{
    int maxsum=0,prefsum=0,suffsum=0,tsum=0;
};

class LazySegTree{
    vector<Node> seg;
    vector<int> lazy;
    public:
    LazySegTree(int n){
        seg.resize(4*n);
        lazy.resize(4*n,1e10);
    }

    void build(int ind,int low,int high,vector<int>& arr){
        if(low == high){
            seg[ind].maxsum = max(0ll,arr[low]);
            seg[ind].prefsum = arr[low];
            seg[ind].suffsum = arr[low];
            seg[ind].tsum = arr[low];
            return;
        }

        int mid = (low+high)>>1;
        build((ind<<1)+1,low,mid,arr);
        build((ind<<1)+2,mid+1,high,arr);
        seg[ind].maxsum = max({0ll,seg[2*ind+1].maxsum,seg[2*ind+2].maxsum,seg[2*ind+1].suffsum + seg[2*ind+2].prefsum});
        seg[ind].prefsum = max(seg[2*ind+1].prefsum,seg[2*ind+1].tsum + seg[2*ind+2].prefsum);
        seg[ind].suffsum = max(seg[2*ind+2].suffsum,seg[2*ind+1].suffsum + seg[2*ind+2].tsum);
        seg[ind].tsum = seg[2*ind+1].tsum + seg[2*ind+2].tsum;

    }

    void update(int ind,int low,int high,int l,int r,int val){
        if(lazy[ind]!=1e10){
            if(lazy[ind]>=0){
                
                seg[ind].prefsum = seg[ind].suffsum = seg[ind].tsum = seg[ind].maxsum = (high-low+1)*lazy[ind];
            }
            else{
                seg[ind].maxsum = seg[ind].prefsum = seg[ind].suffsum = 0;
                seg[ind].tsum = (high-low+1)*lazy[ind];
            }
            if(low!=high){
                lazy[(ind<<1)+1] = lazy[ind];
                lazy[(ind<<1)+2] = lazy[ind];
            }
            lazy[ind]=1e10;
        }

        if(high <l || r<low) return;

        if(low >= l && high<=r){
            if(val>=0){
                seg[ind].prefsum = seg[ind].suffsum = seg[ind].tsum = seg[ind].maxsum = (high-low+1)*val;

            }
            else{
                seg[ind].maxsum = seg[ind].prefsum = seg[ind].suffsum = 0;
                seg[ind].tsum = (high-low+1)*val;
            }
            if(low!=high){
                lazy[(ind<<1)+1] = val;
                lazy[(ind<<1)+2] = val;
            }
            return;
        }

        int mid = (low+high)>>1;
        update((ind<<1)+1,low,mid,l,r,val);
        update((ind<<1)+2,mid+1,high,l,r,val);
        Node newnode;
        newnode.maxsum = max({0ll,seg[2*ind+1].maxsum,seg[2*ind+2].maxsum,seg[2*ind+1].suffsum + seg[2*ind+2].prefsum});
        newnode.prefsum = max(seg[2*ind+1].prefsum,seg[2*ind+1].tsum+seg[2*ind+2].prefsum);
        newnode.suffsum = max(seg[2*ind+2].suffsum,seg[2*ind+1].suffsum + seg[2*ind+2].tsum);
        newnode.tsum = seg[2*ind+1].tsum + seg[2*ind+2].tsum;
        seg[ind] = newnode;
    }

    Node query(int ind,int low,int high,int l,int r){
        if(lazy[ind]!=1e10){
            if(lazy[ind] >= 0){
                seg[ind].maxsum = seg[ind].prefsum = seg[ind].suffsum = seg[ind].tsum = (high-low+1)*lazy[ind];
            }
            else{
                seg[ind].maxsum = seg[ind].prefsum = seg[ind].suffsum = 0;
                seg[ind].tsum = (high-low+1)*lazy[ind];
            }
            if(low!=high){
                lazy[(ind<<1)+1] = lazy[ind];
                lazy[(ind<<1)+2] = lazy[ind];
            }
            lazy[ind]=1e10;
        }

        if(high<l || r<low){
            Node newnode;
            return newnode;
        }

        if(low>=l && high<=r) return seg[ind];
        int mid = (low+high)>>1;
        Node left = query((ind<<1)+1,low,mid,l,r);
        Node right = query((ind<<1)+2,mid+1,high,l,r);
        Node ans;
        ans.maxsum = max({0ll,left.maxsum,right.maxsum,left.suffsum+right.prefsum});
        ans.prefsum = max(left.prefsum,left.tsum + right.prefsum);
        ans.suffsum = max(right.suffsum,left.suffsum + right.tsum);
        ans.tsum = left.tsum + right.tsum;
        return ans;
    }
};


void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> v1(n,0);
    LazySegTree s1(n);
    s1.build(0,0,n-1,v1);
    for(int i=0;i<m;i++){
        int l,r,v;
        cin>>l>>r>>v;
        s1.update(0,0,n-1,l,r-1,v);
        cout<<s1.query(0,0,n-1,0,n-1).maxsum<<"\n";
    }
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    // 3 3 3 3 3
    // 3 -1 -1 3 3
    return 0;
}



