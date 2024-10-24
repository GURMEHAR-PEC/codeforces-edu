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

class LazySegTree {
    vector<int> seg;
    vector<int> lazyAdd, lazyAssign;
    vector<bool> isAssign;  

public:
    LazySegTree(int n) {
        seg.resize(4*n);
        lazyAdd.resize(4*n, 0);
        lazyAssign.resize(4*n, 0);
        isAssign.resize(4*n, false);
    }

    void build(int ind, int low, int high, vector<int>& arr) {
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) >> 1;
        build((ind << 1) + 1, low, mid, arr);
        build((ind << 1) + 2, mid + 1, high, arr);
        seg[ind] = seg[(ind << 1) + 1] + seg[(ind << 1) + 2];
    }

    void propagate(int ind, int low, int high) {
        if (isAssign[ind]) {
        
            seg[ind] = (high - low + 1) * lazyAssign[ind];
            if (low != high) {
                lazyAssign[2*ind+1] = lazyAssign[ind];
                lazyAssign[2*ind+2] = lazyAssign[ind];
                isAssign[2*ind+1] = true;
                isAssign[2*ind+2] = true;
                lazyAdd[2*ind+1] = 0;  
                lazyAdd[2*ind+2] = 0;
            }
            isAssign[ind] = false;
        }
        if (lazyAdd[ind] != 0) {
        
            seg[ind] += (high - low + 1) * lazyAdd[ind];
            if (low != high) {
                lazyAdd[2*ind+1] += lazyAdd[ind];
                lazyAdd[2*ind+2] += lazyAdd[ind];
            }
            lazyAdd[ind] = 0;
        }
    }

    void updateAssignValue(int ind, int low, int high, int l, int r, int val) {
        propagate(ind, low, high);
        if (high < l || r < low) return;
        if (low >= l && high <= r) {
            isAssign[ind] = true;
            lazyAssign[ind] = val;
            lazyAdd[ind] = 0;
            propagate(ind, low, high);
            return;
        }
        int mid = (low + high) >> 1;
        updateAssignValue((ind << 1) + 1, low, mid, l, r, val);
        updateAssignValue((ind << 1) + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[(ind << 1) + 1] + seg[(ind << 1) + 2];
    }

    void updateAddValue(int ind, int low, int high, int l, int r, int val) {
        propagate(ind, low, high);
        if (high < l || r < low) return;
        if (low >= l && high <= r) {
            lazyAdd[ind] += val;
            propagate(ind, low, high);
            return;
        }
        int mid = (low + high) >> 1;
        updateAddValue((ind << 1) + 1, low, mid, l, r, val);
        updateAddValue((ind << 1) + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[(ind << 1) + 1] + seg[(ind << 1) + 2];
    }

    int query(int ind, int low, int high, int l, int r) {
        propagate(ind, low, high);
        if (high < l || r < low) return 0;
        if (low >= l && high <= r) return seg[ind];
        int mid = (low + high) >> 1;
        int left = query((ind << 1) + 1, low, mid, l, r);
        int right = query((ind << 1) + 2, mid + 1, high, l, r);
        return left + right;
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
            s1.updateAssignValue(0,0,n-1,l,r-1,v);
        }
        else if(a==2){
            int l,r,v;
            cin>>l>>r>>v;
            s1.updateAddValue(0,0,n-1,l,r-1,v);
        }
        else{
            int l,r;
            cin>>l>>r;
            cout<<s1.query(0,0,n-1,l,r-1)<<"\n";
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