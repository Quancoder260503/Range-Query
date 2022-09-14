#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
int n,m;
template<class T> struct Seg {
    const T ID=1e18;
    T comb(T a,T b){return min(a,b);}
    int n;vector<int>seg;
    void init(int p){n=p;seg.assign(2*n,ID);}
    void pull(int p){seg[p]=comb(seg[2*p],seg[2*p+1]);}
    void upd(int p ,T val){
        seg[p+=n]=val;
        for (p/=2;p;p/=2) pull(p);
    }
    T query(int l,int r){
        T ra=ID;T rb=ID;
        for (l+=n,r+=n+1;l<r;l/=2,r/=2){
            if (l&1) ra=comb(ra,seg[l++]);
            if (r&1) rb=comb(rb,seg[--r]);
        }return comb(ra,rb);
    }
};
Seg<ll>st;
int main() {
    cin>>n>>m;
    st.init(n+1);
    for(int i=1;i<=n;i++){
        int a;cin>>a;
        st.upd(i,a);
    } for (int i=1;i<=m;i++){
         int t,a,b;
         cin>>t>>a>>b;
         if (t==1) st.upd(a,b);
         else cout <<st.query(a,b)<<endl;
    }
}