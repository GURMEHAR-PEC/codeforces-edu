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

class LazySegTree{
    vector<int> seg,lazy;
    public:
    LazySegTree(int n){
        seg.resize(4*n);
        lazy.resize(4*n);
    }

    void build(int ind,int low,int high,vector<int>& arr){
        if(low == high){
            seg[ind] = arr[low];
            return;
        }

        int mid = (low+high)>>1;
        build((ind<<1)+1,low,mid,arr);
        build((ind<<1)+2,mid+1,high,arr);
        seg[ind] = max(seg[(ind<<1)+1],seg[(ind<<1)+2]);

    }
    void propogate(int ind,int low,int high){
        if(lazy[ind]!=0){
            seg[ind] += lazy[ind];
            if(low!=high){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind]=0;
        }
    }
    void update(int ind,int low,int high,int l,int r,int val){
        propogate(ind,low,high);

        if(high <l || r<low) return;

        if(low >= l && high<=r){
            seg[ind] += val;
            if(low!=high){
                lazy[(ind<<1)+1] += val;
                lazy[(ind<<1)+2] += val;
            }
            return;
        }

        int mid = (low+high)>>1;
        update((ind<<1)+1,low,mid,l,r,val);
        update((ind<<1)+2,mid+1,high,l,r,val);
        seg[ind] = max(seg[(ind<<1)+1],seg[(ind<<1)+2]);
    }

    int query(int ind,int low,int high,int limit,int value){
        propogate(ind,low,high);

        if(limit > high) return -1;

        if(low == high){
            if(seg[ind] >= value) return low;
            return -1;
        }
        int mid = (low+high)>>1;

        propogate(2*ind+1,low,mid);
        propogate(2*ind+2,mid+1,high);
        int leftvalue = -1,rightvalue=-1;
        if(seg[2*ind+1] >= value){
            leftvalue = query(2*ind+1,low,mid,limit,value);

        }
        if(leftvalue!=-1) return leftvalue;
        if(seg[2*ind+2] >= value){
            rightvalue = query(2*ind+2,mid+1,high,limit,value);

        }
        if(rightvalue!=-1) return rightvalue;
        return -1;
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> v1(n,0);
    LazySegTree s1(n);
    s1.build(0,0,n-1,v1);
    for(int i=0;i<m;i++){
        int a;
        cin>>a;
        if(a==1){
            int l,r,v;
            cin>>l>>r>>v;
            s1.update(0,0,n-1,l,r-1,v);
        }
        else{
            int x,l;
            cin>>x>>l;
            cout<<s1.query(0,0,n-1,l,x)<<"\n";
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