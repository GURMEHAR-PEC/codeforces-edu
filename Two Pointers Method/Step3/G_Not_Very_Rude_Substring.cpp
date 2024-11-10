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
    int cnt_a=0;
    int cnt_b=0;
    int inv=0;
};
class SegmentTree
{
    public:
    vector<node> seg;
    
    SegmentTree(int n)
    {
        seg.resize(4 * n + 1);
    }
    void build(int index, int low, int high,string &s)
    {
        if (low == high)
        {
            if(s[low] == 'a'){
                node n1;
                n1.cnt_a++;
                seg[index] = n1;
            }
            else if(s[low]=='b'){
                node n2;
                n2.cnt_b++;
                seg[index] = n2;
            }
            return;
        }
        int mid = (low + high) / 2;
        build(2 * index + 1, low, mid, s);
        build(2 * index + 2, mid + 1, high, s);
        node ans;
        ans.inv = seg[2*index+1].inv + seg[2*index+2].inv + seg[2*index+1].cnt_a*seg[2*index+2].cnt_b;
        ans.cnt_a = seg[2*index+1].cnt_a + seg[2*index+2].cnt_a;
        ans.cnt_b = seg[2*index+1].cnt_b + seg[2*index+2].cnt_b;
        seg[index] = ans;
    }

    node query(int index, int low, int high, int l, int r)
    {
        if (r < low || high < l){
            node n1;
            return n1;
        }
        if (low >= l && high <= r)
            return seg[index];

        int mid = (low + high) / 2;

        node left = query(2 * index + 1, low, mid, l, r);
        node right = query(2 * index + 2, mid + 1, high, l, r);
        node ans;
        ans.inv = left.inv + right.inv + left.cnt_a*right.cnt_b;
        ans.cnt_a = left.cnt_a + right.cnt_a;
        ans.cnt_b = left.cnt_b + right.cnt_b;
        return ans;
    }
};
void solve(){
    int n,c;
    cin>>n>>c;
    string s;
    cin>>s;
    SegmentTree s1(n);
    s1.build(0,0,n-1,s);
    int i=0,j=0,maxLen=0;
    while(j<n){
        if(s1.query(0,0,n-1,i,j).inv <= c){
            maxLen = max(maxLen,j-i+1);
            j++;
        }
        else{
            if(i==j) i++,j++;
            else i++;
        }
    }
    cout<<maxLen<<"\n";
    
}
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}