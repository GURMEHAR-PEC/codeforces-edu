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
    public:
    vector<int> seg,lazy;
    public:
    LazySegTree(int n){
        seg.resize(4*n);
        lazy.resize(4*n,-1);
    }

    void update(int ind,int low,int high,int l,int r,int val){
        if(lazy[ind]!=-1){
            seg[ind] = lazy[ind];
            if(low!=high){
                lazy[(ind<<1)+1] = lazy[ind];
                lazy[(ind<<1)+2] = lazy[ind];
            }
            lazy[ind]=-1;
        }

        if(high <l || r<low) return;

        if(low >= l && high<=r){
            seg[ind] = val;
            if(low!=high){
                lazy[(ind<<1)+1] = val;
                lazy[(ind<<1)+2] = val;
            }
            return;
        }

        int mid = (low+high)>>1;
        update((ind<<1)+1,low,mid,l,r,val);
        update((ind<<1)+2,mid+1,high,l,r,val);
        
    }

    int query(int ind,int low,int high,int i){
        if(lazy[ind]!=-1){
            seg[ind] = lazy[ind];
            if(low!=high){
                lazy[(ind<<1)+1] = lazy[ind];
                lazy[(ind<<1)+2] = lazy[ind];
            }
            lazy[ind]=-1;
        }

        if(low == high) return seg[ind];

        int mid = (low+high)>>1;
        if(i<=mid){
            return query(2*ind+1,low,mid,i);
        }
        return query(2*ind+2,mid+1,high,i);
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> v1(n,0);

    LazySegTree s1(n);
    for(int i=0;i<m;i++){
        int a;
        cin>>a;
        if(a==1){
            int l,r,v;
            cin>>l>>r>>v;
            s1.update(0,0,n-1,l,r-1,v);
        }
        else{
            int b;
            cin>>b;
            cout<<s1.query(0,0,n-1,b)<<"\n";
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