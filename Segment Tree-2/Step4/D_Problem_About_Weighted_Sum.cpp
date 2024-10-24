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


class LazySegTreewithSimpleSum{
    vector<int> seg,lazy;
    public:
    LazySegTreewithSimpleSum(int n){
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
        seg[ind] = seg[(ind<<1)+1] + seg[(ind<<1)+2];

    }

    void update(int ind,int low,int high,int l,int r,int val){
        if(lazy[ind]!=0){
            seg[ind] += (high-low+1)*lazy[ind];
            if(low!=high){
                lazy[(ind<<1)+1] += lazy[ind];
                lazy[(ind<<1)+2] += lazy[ind];
            }
            lazy[ind]=0;
        }

        if(high <l || r<low) return;

        if(low >= l && high<=r){
            seg[ind] += (high-low+1)*val;
            if(low!=high){
                lazy[(ind<<1)+1] += val;
                lazy[(ind<<1)+2] += val;
            }
            return;
        }

        int mid = (low+high)>>1;
        update((ind<<1)+1,low,mid,l,r,val);
        update((ind<<1)+2,mid+1,high,l,r,val);
        seg[ind] = seg[(ind<<1)+1] + seg[(ind<<1)+2];
    }

    int query(int ind,int low,int high,int l,int r){
        if(lazy[ind]!=0){
            seg[ind] += (high-low+1)*lazy[ind];
            if(low!=high){
                lazy[(ind<<1)+1] += lazy[ind];
                lazy[(ind<<1)+2] += lazy[ind];
            }
            lazy[ind]=0;
        }

        if(high<l || r<low) return 0;

        if(low>=l && high<=r) return seg[ind];
        int mid = (low+high)>>1;
        int left = query((ind<<1)+1,low,mid,l,r);
        int right = query((ind<<1)+2,mid+1,high,l,r);
        return left+right;
    }
};
class LazySegTreewithProductSum{
    vector<int> seg,lazy;
    public:
    LazySegTreewithProductSum(int n){
        seg.resize(4*n);
        lazy.resize(4*n);
    }

    void build(int ind,int low,int high,vector<int>& arr){
        if(low == high){
            seg[ind] = (arr[low])*(low+1);
            return;
        }

        int mid = (low+high)>>1;
        build((ind<<1)+1,low,mid,arr);
        build((ind<<1)+2,mid+1,high,arr);
        seg[ind] = seg[(ind<<1)+1] + seg[(ind<<1)+2];

    }

    int getValue(int low,int high){
        low++,high++;
        int sum2 = ((high)*(high+1))/2;
        int sum1 = ((low-1)*(low))/2;
        return sum2-sum1;
    }
    void update(int ind,int low,int high,int l,int r,int val){
        if(lazy[ind]!=0){
            int getnumber = getValue(low,high);
            seg[ind] += (getnumber)*lazy[ind];
            if(low!=high){
                lazy[(ind<<1)+1] += lazy[ind];
                lazy[(ind<<1)+2] += lazy[ind];
            }
            lazy[ind]=0;
        }

        if(high <l || r<low) return;

        if(low >= l && high<=r){
            seg[ind] += getValue(low,high)*val;
            if(low!=high){
                lazy[(ind<<1)+1] += val;
                lazy[(ind<<1)+2] += val;
            }
            return;
        }

        int mid = (low+high)>>1;
        update((ind<<1)+1,low,mid,l,r,val);
        update((ind<<1)+2,mid+1,high,l,r,val);
        seg[ind] = seg[(ind<<1)+1] + seg[(ind<<1)+2];
    }

    int query(int ind,int low,int high,int l,int r){
        if(lazy[ind]!=0){
            seg[ind] += (getValue(low,high))*lazy[ind];
            if(low!=high){
                lazy[(ind<<1)+1] += lazy[ind];
                lazy[(ind<<1)+2] += lazy[ind];
            }
            lazy[ind]=0;
        }

        if(high<l || r<low) return 0;

        if(low>=l && high<=r) return seg[ind];
        int mid = (low+high)>>1;
        int left = query((ind<<1)+1,low,mid,l,r);
        int right = query((ind<<1)+2,mid+1,high,l,r);
        return left+right;
    }
};
void solve(){
    int n,m;
    cin>>n>>m;
    vector<int> v1(n,0);
    ivec(v1);
    LazySegTreewithProductSum s1(n);
    LazySegTreewithSimpleSum s2(n);
    s1.build(0,0,n-1,v1);
    s2.build(0,0,n-1,v1);
    for(int i=0;i<m;i++){
        int a;
        cin>>a;
        if(a==1){
            int l,r,v;
            cin>>l>>r>>v;
            l--,r--;
            s1.update(0,0,n-1,l,r,v);
            s2.update(0,0,n-1,l,r,v);
        }
        else{
            int l,r;
            cin>>l>>r;
            l--,r--;
            int ans = s1.query(0,0,n-1,l,r) - (l)*s2.query(0,0,n-1,l,r);
            cout<<ans<<"\n";
            
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