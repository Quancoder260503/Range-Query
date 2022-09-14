#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n,q;
ll c[sz];
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
    cin>>n>>q;
    st.init(n+1);
    for (int i=1;i<=n;i++){
        cin>>c[i];
        st.upd(i,c[i]-c[i-1]);
    } 
    for (int i=1;i<=q;i++){
        int t;cin>>t;
        if (t==1){
            int a,b,d;cin>>a>>b>>d;
            st.upd(a,d);st.upd(b+1,-d);
        } else{
            int a;cin>>a;
            cout <<st.query(1,a)<<endl;
        }
    }
}    