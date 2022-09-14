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
ll segtree[4*sz];
ll regtree[4*sz];
void build(int node = 1, int l = 1, int r = n) {
	if (l == r){
        segtree[node]=a[l]+l;
        regtree[node]=a[l]-l;
    }
	else {
		int mid = (l + r)>>1;
		build(node * 2, l, mid);
		build(node * 2 + 1, mid + 1, r);
		segtree[node]=min(segtree[node * 2],segtree[node * 2 + 1]);
        regtree[node]=min(regtree[node * 2],regtree[node * 2 + 1]);
	}
}
void update(ll val,int pos,int l=1,int r=n,int node=1){
        if(l>r) return;
        if(l==r){
            segtree[node]=val+l;
            regtree[node]=val-l;
        }
        else{
            int mid=(l+r)>>1;
            if(pos>mid) update(val,pos,mid+1,r,node*2+1);
            else update(val,pos,l,mid,node*2);
            segtree[node]=min(segtree[node*2],segtree[node*2+1]);
            regtree[node]=min(regtree[node*2],regtree[node*2+1]);
        }
}
ll query(int L,int R,bool act ,int l=1,int r=n,int node=1){
    if(L<=l and r<=R){
        if(act) return segtree[node];
        else return regtree[node];
    }
    if(L>r or R<l) return 1e9;
    int mid=(l+r)>>1;
    return min(query(L,R,act,mid+1,r,node*2+1),query(L,R,act,l,mid,node*2));
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    build();
    for(int i=0;i<q;i++){
        ll u,v,t;cin>>t;
        if(t==1){
            cin>>u>>v;
            update(v,u);
        }else{
            cin>>u;
            ll d0=query(1,u,0)+u;
            ll d1=query(u,n,1)-u;
            cout<<min(d0,d1)<<endl;
        }
    }  
}