#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=1001;
const int sz1=2e5+1;
int n,k,w,m,q;
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
vector<array<ll,3>>query;
ll a[sz1];
ll ans[sz1];
ll dp[sz1];
template<class T> struct Seg {
    const T ID=0;
    T comb(T a,T b){return a+b;}
    int n;vector<ll>seg;
    void init(int p){n=p;seg.assign(2*n,ID);}
    void pull(int p){seg[p]=comb(seg[2*p],seg[2*p+1]);}
    void upd(int p ,T val){
        seg[p+=n]+=val;
        for (p/=2;p;p/=2){
            pull(p);
        }
    }T query(int l,int r){
        T ra=ID;T rb=ID;
        for (l+=n,r+=n+1;l<r;l/=2,r/=2){
            if (l&1) ra=comb(ra,seg[l++]);
            if (r&1) rb=comb(rb,seg[--r]);
        }return comb(ra,rb);
    }
};
Seg<ll>st;
int main(){
    cin>>n>>q;
    st.init(n+1);
    map<ll,int>mp;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    
    } 
    for(int i=0;i<q;i++){
        ll u,v;cin>>u>>v;
        query.push_back({u,v,i});
    } sort(query.rbegin(),query.rend());
      ll cur=n;
      for(auto e:query){
         while (cur>=e[0]){
             if(mp.count(a[cur])) st.upd(mp[a[cur]],-1);
             mp[a[cur]]=cur;
             st.upd(cur,1);
             cur--;
         } ans[e[2]]=st.query(e[0],e[1]);
    } 
       for(int i=0;i<q;i++){
            cout<<ans[i]<<endl;
    }        
}