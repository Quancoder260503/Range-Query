#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const ll inf=1e9+1;
ll n,q,m,t,f,x,k,cnt;
vector<ll>cor;
vector<array<ll,3>>point;
struct node{
    int  left;
    int  right;
    int val;
}
tree[sz*40];
int ro[sz*40];
void update(int p,int l,int r,int &idx){
    if(!idx) idx=++cnt;
    //tree[idx].val++;
    if(l==r){
        tree[idx].val+=1;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(p,l,mid,tree[idx].left);
    else update(p,mid+1,r,tree[idx].right);
    tree[idx].val+=1;
}
ll query(int L,int R,int l,int r,int p){
    if(!p) return 0;
    if(L<=l and r<=R) return tree[p].val;
    ll res=0;
    int mid=(l+r)>>1;
    if(L<=mid) res+=query(L,R,l,mid,tree[p].left);
    if(mid<R)  res+=query(L,R,mid+1,r,tree[p].right);
    return res;
}
int main(){
     cin>>n>>k;
     cnt=0;
     for(int i=1;i<=n;i++){
         ll u,v,w; cin>>u>>v>>w;
         cor.push_back(w); cor.push_back(w-k); cor.push_back(w+k);
         point.push_back({v,u,w});
     }
     sort(cor.begin(),cor.end());
     sort(point.rbegin(),point.rend());
     cor.erase(unique(cor.begin(),cor.end()),cor.end());
     ll comp=0;
     ll ans=0;
     for(auto p:point){
         int le=lower_bound(cor.begin(),cor.end(),p[2]-k)-cor.begin()+1;
         int ri=lower_bound(cor.begin(),cor.end(),p[2]+k)-cor.begin()+1; 
        // cout<<le<<" "<<ri<<endl;
          int L=max(comp,p[1]-p[0]);
          int R=min(inf, p[1]+p[0]);
         for(int j=le;j<=ri;j++){
             if(!ro[j]) continue;
             ans+=query(L,R,0,inf,ro[j]);
         }
         int pos=lower_bound(cor.begin(),cor.end(),p[2])-cor.begin()+1;
         update(p[1],0,inf,ro[pos]);
        // cout<<pos<<endl;
     }
     cout<<ans<<endl;
}