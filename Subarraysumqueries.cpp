#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<map>
#include<vector>
#include<utility>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
ll n,m,q,s,t,k;
ll timer=1;
ll a[sz];
ll up[21][sz];
ll oc[21][sz];
ll dp[sz];
vector<ll>ans;
vector<array<ll,2>>adj[sz];
struct Node{
    ll gmax,lmax,rmax,smax;
    Node operator+(Node b){
        return{
            max(max(gmax,b.gmax),rmax+b.lmax),
            max(lmax,smax+b.lmax),
            max(b.rmax,rmax+b.smax),
            smax+b.smax,
        };
    }
};
Node segtree[4*sz];
void build(int node = 1, int l = 1, int r = n) {
	if (l == r) segtree[node] ={max(0ll,a[l]),max(0ll,a[l]),max(0ll,a[l]),a[l]};
	else {
		int mid = (l + r) / 2;
		build(node * 2, l, mid);
		build(node * 2 + 1, mid + 1, r);
		segtree[node] = segtree[node * 2]+ segtree[node * 2 + 1];
	}
}
void update(ll val,int pos,int l=1,int r=n,int node=1){
        if(l==r) segtree[node]={max(0ll,val),max(0ll,val),max(0ll,val),val};
        else{
            int mid=(l+r)>>1;
            if(pos>mid) update(val,pos,mid+1,r,node*2+1);
            else update(val,pos,l,mid,node*2);
            segtree[node]=segtree[node*2]+segtree[node*2+1];
        }
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    build();
    for(int i=0;i<q;i++){
        ll u,v;cin>>u>>v;
        update(v,u);
        cout<<segtree[1].gmax<<endl;
    }  
}