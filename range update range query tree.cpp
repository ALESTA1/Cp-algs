#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
#define pb push_back
#define ll long long int
#define repp(n) for (int i = 0; i < n; i++)
// typedef __int128 lll;
const ll MOD = 998244353;
const ll mod = 1e9 + 7;
const ll inf = 1e17;
#define rep(i, a, b) for (long long i = a; i < b; i++)



ll n,m;
const int maxN = 2e5 + 5;

int a[200010];

struct node {
	ll val;
	ll lzAdd;
	ll lzSet;
	node(){};
} tree[maxN << 2];

#define lc (p << 1)
#define rc (p << 1) + 1

inline void pushup(int p) {
	tree[p].val = tree[lc].val + tree[rc].val;
	return;
}

void pushdown(int p, int l, int mid, int r) {
	// lazy: range set
	if (tree[p].lzSet != 0) {
		tree[lc].lzSet = tree[rc].lzSet = tree[p].lzSet;
		tree[lc].val = (mid - l + 1) * tree[p].lzSet;
		tree[rc].val = (r - mid) * tree[p].lzSet;
		tree[lc].lzAdd = tree[rc].lzAdd = 0;
		tree[p].lzSet = 0;
	} else if (tree[p].lzAdd != 0) {  // lazy: range add
		if (tree[lc].lzSet == 0) tree[lc].lzAdd += tree[p].lzAdd;
		else {
			tree[lc].lzSet += tree[p].lzAdd;
			tree[lc].lzAdd = 0;
		}
		if (tree[rc].lzSet == 0) tree[rc].lzAdd += tree[p].lzAdd;
		else {
			tree[rc].lzSet += tree[p].lzAdd;
			tree[rc].lzAdd = 0;
		}
		tree[lc].val += (mid - l + 1) * tree[p].lzAdd;
		tree[rc].val += (r - mid) * tree[p].lzAdd;
		tree[p].lzAdd = 0;
	}
	return;
}

void build(int p, int l, int r) {
	tree[p].lzAdd = tree[p].lzSet = 0;
	if (l == r) {
		tree[p].val = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
	pushup(p);
	return;
}

void add(int p, int l, int r, int a, int b, ll val) {
	if (a > r || b < l) return;
	if (a <= l && r <= b) {
		tree[p].val += (r - l + 1) * val;
		if (tree[p].lzSet == 0) tree[p].lzAdd += val;
		else tree[p].lzSet += val;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(p, l, mid, r);
	add(lc, l, mid, a, b, val);
	add(rc, mid + 1, r, a, b, val);
	pushup(p);
	return;
}

void sett(ll p, ll l, ll r, ll a, ll b, ll val) {
	if (a > r || b < l) return;
	if (a <= l && r <= b) {
		tree[p].val = (r - l + 1) * val;
		tree[p].lzAdd = 0;
		tree[p].lzSet = val;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(p, l, mid, r);
	sett((p<<1), l, mid, a, b, val);
	sett((p<<1)+1, mid + 1, r, a, b, val);
	pushup(p);
	return;
}

ll query(ll p, ll l, ll r, ll a, ll b) {
	if (a > r || b < l) return 0;
	if (a <= l && r <= b) return tree[p].val;
	int mid = (l + r) >> 1;
	pushdown(p, l, mid, r);
	return query(lc, l, mid, a, b) + query(rc, mid + 1, r, a, b);
}
void solve(){

    cin>>n>>m;
    
    vector<ll> b(m);
    repp(n)cin>>a[i+1];
    repp(m)cin>>b[i];
    build(1, 1, n);
    for(int i=0;i<m;i++){

        ll box = b[i];
        ll balls = query(1,1,n,box+1,box+1);
        //cout<<balls<<endl;
        sett(1,1,n,box+1,box+1,0);
        ll ok = balls/n;
        add(1,1,n,1,n,ok);
        ok = balls%n;
        if(balls==0)continue;
        if(box+1+ok>=n){
            
            add(1,1,n,box+2,n,1);
            //lazy.make_update(box+1,n-1,1);
            ll t = n-(box+1);
            ok-=t;
            add(1,1,n,1,ok,1);
            //lazy.make_update(1,ok,1);
        }
        else{
            
            add(1,1,n,box+2,box+1+ok,1);
            //lazy.make_update(box+1,box+ok,1);
        }

    }


    for(int i=0;i<n;i++){

        cout<<query(1,1,n,i+1,i+1)<<" ";
        //cout<<lazy.make_query(i,i).val<<" ";
    }

}
int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // int t;
    // cin >> t;
    // while (t--)
    solve();

    return 0;
}
