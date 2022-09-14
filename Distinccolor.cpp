#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
ll a[sz];
ll c[sz];
int st[sz];
int en[sz];
ll ans[sz];
map<int,int>M;
vector<ll>adj[sz];
vector<array<int,3>>query1;
ll n,q;
ll timer=0;
void dfs(int node, int parent) {
    a[timer]=c[node];
	st[node] = timer++;
	for (int i : adj[node]) {
		if (i != parent) {
			dfs(i, node);
		}
	}
	en[node] = timer-1;
}
template<class T> struct Seg {
	const T ID = 0; T comb(T a, T b) { return a+b; }
	int n; vector<T> seg;
	void init(int _n) { n = _n; seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) {
		seg[p += n] +=val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = comb(ra,seg[l++]);
			if (r&1) rb = comb(seg[--r],rb);
		}
		return comb(ra,rb);
	}
};
Seg<int>segtree;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>c[i];
    } for (int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        --u,--v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    } 
     dfs(0,-1);
     segtree.init(n);
     for (int i=0;i<n;i++){
         query1.push_back({st[i],en[i],i});
     } 
      sort(query1.begin(),query1.end());
      reverse(query1.begin(),query1.end());
      int cur=n-1;
      for (auto e:query1){
          while (cur>=e[0]){
              if(M.count(a[cur])) segtree.upd(M[a[cur]],-1);
              M[a[cur]]=cur;
              segtree.upd(cur,1);
              cur--;
          }
          ans[e[2]]=segtree.query(e[0],e[1]);
      }
      for(int i=0;i<n;i++){
          cout <<ans[i]<<" ";
      }
}