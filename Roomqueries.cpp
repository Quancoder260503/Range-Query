#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n,m,q;
ll a[sz];
ll pre=0;
ll ans1,ans;
bool pick[sz];
array<ll,2>id[sz];
vector<ll>to[sz];
ll segtree[4*sz];
void build(int node = 1, int l = 1, int r = n) {
	if (l == r) segtree[node] = a[l];
	else {
		int mid = (l + r) / 2;
		build(node * 2, l, mid);
		build(node * 2 + 1, mid + 1, r);
		segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
	}
}
void query(int val, int node = 1, int l = 1, int r = n){
    if(l==r){
        segtree[node]-=val;
        cout<<l<<" ";
    }
    else {
	int mid = (l + r) / 2;
    if(segtree[2*node]>=val) query(val, node * 2, l, mid);
    else query(val, node * 2 + 1, mid +1, r);
    segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
    }     
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    build();
    for(int i=0;i<q;i++){
        ll x;cin>>x;
        if (x>segtree[1]) cout <<0<<" ";
        else query(x);
    } 
}