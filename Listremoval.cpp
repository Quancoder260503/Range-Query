#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n;
ll c[sz];
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
int main() {
    cin>>n;
    st.init(n+1);
    for (int i=1;i<=n;i++){
        cin>>c[i];
        st.upd(i,1);
    } int q=pow(2,ceil(log2(n)));
    for (int i=1;i<=n;i++){
          int a;cin>>a;
          int j=st.bis(1,0,q-1,a);
          st.upd(j,0);
          cout <<c[j]<<" ";
    }
}    