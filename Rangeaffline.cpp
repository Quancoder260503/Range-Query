#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=5e5+1;
const int mod=998244353;
int n,x,k,i,j,w,q;
ll a[sz];
struct node{
    ll val;
    ll lzadd;
    ll lzadd1;
    node(){};
};
node tree[sz<<2];
void push(int p){
    tree[p].val=tree[2*p+1].val+tree[2*p].val;
}
void pushdown(int p,int l,int mid,int r){
     if(tree[p].lzadd!=0){
         tree[2*p].val=tree[2*p].val%mod*tree[p].lzadd%mod+(mid-l+1)%mod*tree[p].lzadd1%mod;
         tree[2*p+1].val=tree[2*p+1].val%mod*tree[p].lzadd%mod+(r-mid)%mod*tree[p].lzadd1%mod;
         tree[2*p].lzadd=tree[2*p].lzadd%mod*tree[p].lzadd%mod;
         tree[2*p].lzadd1=tree[2*p].lzadd1%mod*tree[p].lzadd%mod+tree[p].lzadd1%mod;
         tree[2*p+1].lzadd=tree[2*p+1].lzadd%mod*tree[p].lzadd%mod;
         tree[2*p+1].lzadd1=tree[2*p+1].lzadd1%mod*tree[p].lzadd%mod+tree[p].lzadd1%mod;
         tree[p].lzadd=1;tree[p].lzadd1=0;
     }
}
void build(int l=1,int r=n,int node=1){
    tree[node].lzadd=1;
    if(l==r){
        tree[node].val=a[l];
        return;
    }else{
        int mid=(l+r)>>1;
        build(l,mid,node*2);
        build(mid+1,r,node*2+1);
        push(node);
        return;
    }
}
void add(ll x,ll y,int L,int R,int l=1,int r=n,int node=1){
    if(l>R or L>r) return;
    if(L<=l and r<=R){
        tree[node].val=(r-l+1)%mod*y%mod+tree[node].val*x%mod;
        tree[node].lzadd=x%mod*tree[node].lzadd%mod;
        tree[node].lzadd1=x%mod*tree[node].lzadd1%mod+y;
        return;        
    }
        int mid=(l+r)>>1;
        pushdown(node,l,mid,r);
        add(x,y,L,R,l,mid,node*2);
        add(x,y,L,R,mid+1,r,node*2+1);
        push(node);
        return;
}
ll query(int L,int R,int l=1,int r=n,int node=1){
    if(l>R or L>r) return 0;
    if(L<=l and r<=R) return tree[node].val;
    int mid=(l+r)>>1;
    pushdown(node,l,mid,r);
    return query(L,R,l,mid,2*node)%mod+query(L,R,mid+1,r,2*node+1)%mod;
}
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    build();
    for(int i=0;i<q;i++){
        int t;cin>>t;
        if(t==0){
            ll l,r,b,c; cin>>l>>r>>b>>c;
            b%=mod;c%=mod;
            add(b,c,l+1,r);
        } else{
            ll l,r;cin>>l>>r;
            ll res=query(l+1,r)%mod;
            cout<<res<<endl;
        }
    }
}