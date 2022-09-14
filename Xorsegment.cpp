#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
const int sz=1e5+1;
typedef long long ll;
int mod,n,q;
ll a[sz];
int tree[sz<<2][21];
int treelz[sz<<2][21];
void push_down(int ord,int p,int l,int mid,int r){
    if(treelz[p][ord]!=0 and r!=l){
           treelz[2*p][ord]^=treelz[p][ord];
           treelz[2*p+1][ord]^=treelz[p][ord];
           tree[2*p][ord]=mid-l+1-tree[2*p][ord];
           tree[2*p+1][ord]=r-mid-tree[2*p+1][ord];
           treelz[p][ord]=0;
        }
}
void update(int ord, int L, int R, int l=1,int r=n,int p=1){
    if(L>r or R<l) return;
    if(L<=l and r<=R){
          treelz[p][ord]^=1;
          tree[p][ord]=r-l+1-tree[p][ord];
          return;
    }
    int mid=(l+r)>>1;
    push_down(ord,p,l,mid,r);
    update(ord,L,R,l,mid,2*p);
    update(ord,L,R,mid+1,r,2*p+1);
    tree[p][ord]=tree[2*p+1][ord]+tree[2*p][ord];
}
int query(int ord,int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l) return 0;
    if(L<=l and r<=R) return tree[p][ord];
    
    int mid=(l+r)>>1;
    push_down(ord,p,l,mid,r);
    return query(ord,L,R,l,mid,2*p)+query(ord,L,R,mid+1,r,2*p+1);
}
int main(){
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=0;i<=20;i++){
        for(int j=1;j<=n;j++){
            if( (a[j]>>i)& 1) update(i,j,j);
        }
    }
    cin>>q;
    for(int i=1;i<=q;i++){
        int t;cin>>t;
        if(t==1){
            int u,v;cin>>u>>v;
            ll res=0;
            for(int j=0;j<=20;j++){
                res+=(ll) query(j,u,v)*(1ll<<j);
            }
            cout<<res<<endl;
        }
        else{
            int u,v,x;cin>>u>>v>>x;
            for(int j=0;j<=20;j++){
                if((x>>j)&1) update(j,u,v);
            }
        }
    }
}