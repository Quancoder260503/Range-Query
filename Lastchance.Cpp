#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
const int inf=1e7+1;
const int lg=31;
int n,m,k;
map<ll,ll>cnt;
map<ll,ll>rr;
string s;
int cnt_v[sz];
int cnt_c[sz];
int vowel[5]={97,101,105,111,117};
int pf[sz];
vector<int>dp;
template<class T> struct Segtree {
    const T ID=inf;
    T comb(T a,T b){ return min(a,b);}
    int n;vector<int>seg;
    void init(int p){n=p;seg.assign(2*n,ID);}
    void pull(int p){seg[p]=comb(seg[2*p],seg[2*p+1]);}
    void upd(int p ,T val){
        p+=n;
        seg[p]=comb(val,seg[p]);
        for (p/=2;p;p/=2) pull(p);
    }
    T query(int l,int r){
        T ra=ID;T rb=ID;
        for (l+=n,r+=n+1;l<r;l/=2,r/=2){
            if (l&1) ra=comb(ra,seg[l++]);
            if (r&1) rb=comb(rb,seg[--r]);
        }
       return comb(ra,rb);
    }
};
Segtree<int>seg;
int main(){
    cin>>s;
    int n=s.length();
    seg.init(n<<2);
    for(int i=0;i<s.length();i++){
         int as_val=s[i]-'a';
         if(as_val<0) as_val+=32;
         as_val+=97;
         bool v=0;
         for(int j=0;j<5;j++){
             if(vowel[j]==as_val){
                 cnt_v[i+1]++;
                 v=1;
                 break;
             }
         }
         if(!v) cnt_c[i+1]++;
         if(i>0) cnt_v[i+1]+=cnt_v[i], cnt_c[i+1]+=cnt_c[i];
         int idx=2*cnt_c[i+1]-cnt_v[i+1];
         dp.push_back(idx);
    }
    dp.push_back(0);
    sort(dp.begin(),dp.end());
    dp.erase(unique(dp.begin(),dp.end()),dp.end());
    for(int i=0;i<dp.size();i++) rr[dp[i]]=i+1;
    seg.upd(rr[0],0);
    int ans = 0;
    for(int i=1;i<=n;i++){
        int idx=2*cnt_c[i]-cnt_v[i];
        int pos=rr[idx];
        int mn=seg.query(1,pos);
        if(i+1>mn) cnt[i-mn]++;
        ans=max(ans,i-mn);
        seg.upd(pos,i);
        //cout<<idx<<' '<<pos<<' '<<mn<<' '<<ans<<' '<<i<<endl;
    }
    if(!ans) cout<<"No solution";
    else cout<<ans<<' '<<cnt[ans]<<endl;
} 
