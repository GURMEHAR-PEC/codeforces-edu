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

struct info{
    int arr[40] = {0};
};

class SegmentTree
{
    public:
    vector<info> seg;
    
    SegmentTree(int n)
    {
        seg.resize(4 * n + 1);
    }
    void build(int index, int low, int high, vector<int>& arr)
    {
        if (low == high)
        {
        
            seg[index].arr[arr[low]-1]++;
            return;
        }
        int mid = (low + high) / 2;
        build(2 * index + 1, low, mid, arr);
        build(2 * index + 2, mid + 1, high, arr);
        for(int i=0;i<40;i++){
            seg[index].arr[i] = seg[2*index+1].arr[i] + seg[2*index+2].arr[i];
        }
    }

    info query(int index, int low, int high, int l, int r)
    {
        if (r < low || high < l){
            info ele;
            return ele;
        }
            

        if (low >= l && high <= r)
            return seg[index];

        int mid = (low + high) / 2;

        info left = query(2 * index + 1, low, mid, l, r);
        info right = query(2 * index + 2, mid + 1, high, l, r);
        info newnode;
        for(int i=0;i<40;i++){
            newnode.arr[i] = left.arr[i] + right.arr[i];
        }
        return newnode;
    }

    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            info newnode;
            newnode.arr[val-1]++;
            seg[ind] = newnode;
            return;
        }
        int mid = (low + high) >> 1;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val );
        else
            update(2 * ind + 2, mid + 1, high, i, val);
        info newnode;
        for(int i=0;i<40;i++){
            newnode.arr[i] = seg[2*ind+1].arr[i] + seg[2*ind+2].arr[i];

        }
        seg[ind] = newnode;
        
    }
};
void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> v1(n,0);
    ivec(v1);

    SegmentTree s1(n);
    s1.build(0,0,n-1,v1);
    for(int i=0;i<q;i++){
        int a;
        cin>>a;
        if(a==1){
            int l,r;
            cin>>l>>r;
            l--,r--;
            info ans = s1.query(0,0,n-1,l,r);
            int cnt=0;
            for(int i=0;i<40;i++){
                if(ans.arr[i]!=0) cnt++;
            }
            cout<<cnt<<"\n";
        }
        else{
            int b,c;
            cin>>b>>c;
            b--;
            s1.update(0,0,n-1,b,c);
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