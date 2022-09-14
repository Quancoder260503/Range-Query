#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=3e5+1;
const int MAXN=1e6;
int n,q;
int dp[MAXN+1];
ll a[sz];
ll treemx[sz<<2];
ll treetot[sz<<2];
void build(int l=1,int r=n,int p=1){
    if(l==r){
        treemx[p]=treetot[p]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,2*p);
    build(mid+1,r,2*p+1);
    treemx[p]=max(treemx[2*p],treemx[2*p+1]);
    treetot[p]=treetot[2*p]+treetot[2*p+1];
}
void update(int L,int R,int l=1,int r=n,int p=1){
    if(treemx[p]<=2) return;
    if(l==r){
        treemx[p]=treetot[p]=dp[treemx[p]];
        return;
    }
    int mid=(l+r)>>1;
    if(L<=mid)update(L,R,l,mid,2*p);
    if(R>mid) update(L,R,mid+1,r,2*p+1);
    treemx[p]=max(treemx[2*p],treemx[2*p+1]);
    treetot[p]=treetot[2*p]+treetot[2*p+1];
}
ll querys(int L,int R,int l=1,int r=n,int p=1){
    if(L<=l and r<=R) return treetot[p];
    int mid=(l+r)>>1;
    ll ans=0;
    if(L<=mid) ans+=querys(L,R,l,mid,2*p);
    if(R>mid)  ans+=querys(L,R,mid+1,r,2*p+1);
    return ans;
}
int main(){
     cin>>n>>q;
     int maxval=0;
     for(int i=1;i<=n;i++) cin>>a[i];
     for(int i=2;i<=MAXN;i++) dp[i]=2;
     ll x=0;
     dp[1]=1;
     for(int i=2;i<=sqrt(MAXN);i++){
         x=i*i; dp[x]--;
         while(x<MAXN){
             dp[x]+=2;
             x+=i;
         }
     }
     build();
     for(int i=1;i<=q;i++){
         int t,u,v;cin>>t>>u>>v;
         if(t==1) update(u,v);
         if(t==2){
             ll res=querys(u,v);
             cout<<res<<endl;
         }
     }
}