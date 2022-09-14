#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n;
ll t;
ll a[sz];
ll pre=0;
ll ans1,ans;
bool pick[sz];
array<ll,2>id[sz];
vector<ll>to[sz];
template<class T> struct Seg {
    const T ID=0;
    T comb(T a,T b){return a+b;}
    int n;vector<ll>seg;
    void init(int p){n=pow(2,ceil(log2(p)));seg.assign(2*n,ID);}
    void pull(int p){seg[p]=comb(seg[2*p],seg[2*p+1]);}
    void upd(int p ,T val){
        seg[p+=n]=val;
        for (p/=2;p;p/=2){
            pull(p);
        }
    }
    T query(int l,int r){
        T ra=ID;T rb=ID;
        for (l+=n,r+=n+1;l<r;l/=2,r/=2){
            if (l&1) ra=comb(ra,seg[l++]);
            if (r&1) rb=comb(rb,seg[--r]);
        }return comb(ra,rb);
    } 
    T bis(int i ,int l,int r,int k){
        if (l>r) return -1;
        if (seg[i]==k and l==r) return abs(i-n);
        int mid=(l+r)/2;
        if (seg[2*i]>=k) return bis(2*i,l,mid,k);
        else return bis(2*i+1,mid+1,r,k-seg[2*i]);
    }
};
Seg<ll>st;
int main(){
    cin>>n;
    st.init(2*n);
    for(int i=0;i<n;i++){
        id[i][0]=id[i][1]=-1;
    }
    for(int i=0;i<2*n;i++){
        ll x;cin>>x; x--;
        if (id[x][0]==-1) id[x][0]=i;
        else {if (id[x][1]==-1) id[x][1]=i;}
    } sort(id,id+n);
      for(int i=0;i<n;i++){
          ans+=st.query(0,id[i][1])-st.query(0,id[i][0]);
          st.upd(id[i][1],1);
      } 
    cout<<ans;
}