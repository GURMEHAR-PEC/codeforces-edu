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
int MOD=0;
// using namespace __gnu_pbds;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> pbds;  
// // (functions find_by_order, order_of_key)

struct matrix{
    int a11=0,a12=0,a21=0,a22=0;
};

class SegmentTree
{
    public:
    vector<matrix> seg;
    
    SegmentTree(int n)
    {
        seg.resize(4 * n + 1);
    }
    void build(int index, int low, int high, vector<matrix> &arr)
    {
        if (low == high)
        {
            seg[index].a11 = arr[low].a11;
            seg[index].a12 = arr[low].a12;
            seg[index].a21 = arr[low].a21;
            seg[index].a22 = arr[low].a22;
            return;
        }
        int mid = (low + high) / 2;
        build(2 * index + 1, low, mid, arr);
        build(2 * index + 2, mid + 1, high, arr);
        seg[index].a11 = ((seg[2*index+1].a11*seg[2*index+2].a11)%MOD + (seg[2*index+1].a12*seg[2*index+2].a21)%MOD)%MOD;
        seg[index].a12 = ((seg[2*index+1].a11*seg[2*index+2].a12)%MOD + (seg[2*index+1].a12*seg[2*index+2].a22)%MOD)%MOD;
        seg[index].a21 = ((seg[2*index+1].a21*seg[2*index+2].a11)%MOD + (seg[2*index+1].a22*seg[2*index+2].a21)%MOD)%MOD;
        seg[index].a22 = ((seg[2*index+1].a21*seg[2*index+2].a12)%MOD + (seg[2*index+1].a22*seg[2*index+2].a22)%MOD)%MOD;
    }

    matrix query(int index, int low, int high, int l, int r)
    {
        if (r < low || high < l){
            matrix m1;
            m1.a11 = 1;
            m1.a22=1;
            m1.a12=0;
            m1.a21=0;
            return m1;
        }
            

        if (low >= l && high <= r)
            return seg[index];

        int mid = (low + high) / 2;

        matrix left = query(2 * index + 1, low, mid, l, r);
        matrix right = query(2 * index + 2, mid + 1, high, l, r);
        matrix ans;
        ans.a11 = ((left.a11*right.a11)%MOD + (left.a12*right.a21)%MOD)%MOD;
        ans.a12 = ((left.a11*right.a12)%MOD + (left.a12*right.a22)%MOD)%MOD;
        ans.a21 = ((left.a21*right.a11)%MOD + (left.a22*right.a21)%MOD)%MOD;
        ans.a22 = ((left.a21*right.a12)%MOD + (left.a22*right.a22)%MOD)%MOD;

        return ans;
    }

    
};
void solve(){
    int r,n,m;
    cin>>r>>n>>m;
    MOD = r;
    vector<matrix> v1(n);
    for(int i=0;i<n;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        v1[i].a11 = a;
        v1[i].a12 = b;
        v1[i].a21 = c;
        v1[i].a22 = d;
    }
    SegmentTree s1(n);
    s1.build(0,0,n-1,v1);

    for(int i=0;i<m;i++){
        int l,r;
        cin>>l>>r;
        l--,r--;
        matrix ans = s1.query(0,0,n-1,l,r);
        cout<<ans.a11<<" "<<ans.a12<<"\n";
        cout<<ans.a21<<" "<<ans.a22<<"\n";
        cout<<"\n";
    }
    
    
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}