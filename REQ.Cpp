#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 1;
const int M = 1e6 + 5;
const int mod = 1e9 + 7; 
long long n,m,k,q,b,c,d;
typedef pair<long long,pair<long long,long long>>queries;
bool primes[M + 1];
vector<long long>fact[M + 1]; 
long long a[N + 1]; 
long long mul[M + 1];
long long era[M + 1]; 
long long ans[N + 1]; 
vector<queries>query;
long long binpow(long long a,long long b){
     if(b == 0) return 1; 
     long long ans = 1; 
     while(b > 0){
           if(b & 1) ans = ans % mod * a % mod;
           a = a % mod * a % mod;
           b >>= 1;
     }
     return ans; 
}
template<class T> struct Seg {
    const T ID = 1;
    T comb(T a,T b){return a % mod * b % mod;}
    int n; 
    vector<long long>seg;
    void init(int p){
        n = p; 
        seg.assign(2 * n, ID);
    }
    void pull(int p){
         seg[p]= comb(seg[2*p] , seg[2*p + 1]);
    }
    void upd(int p ,T val){
        seg[p + n] = seg[p + n] % mod * val % mod;
        p += n; 
        for (p /= 2; p ; p /= 2){
            pull(p);
        }
    }
    T query(int l,int r){
        T ra = ID; T rb = ID;
        for (l += n , r += n + 1; l < r; l /= 2, r /= 2){
            if (l & 1) ra = comb(ra,seg[l++]);
            if (r & 1) rb = comb(rb,seg[--r]);
        }
        return comb(ra,rb);
    }
};
Seg<long long>st;
bool cmp(queries &a ,queries &b){
     return a.second.first < b.second.first; 
}
int main(){   
        scanf("%d",&n); 
        st.init(n + 1);
        for(int i = 1; i <= n; i++){
            scanf("%d",&a[i]);
            st.upd(i,a[i]);
        }
        for(int i = 2; i < M; i++){
              if(primes[i]) continue;
              for(int j = i ; j < M; j += i){
                    fact[j].push_back(i); 
                    if(j > i) primes[j] = 1;
              }
        }
        scanf("%d",&q);
        for(int i = 1; i <= q; i++){
              int u,v; scanf("%d%d",&u,&v);
              query.push_back({i,{u,v}});
        }
        for(int i = 1; i < M; i++){
             mul[i] = (1 - binpow(i,mod - 2) + mod) % mod; 
             era[i] = (1 + binpow(i - 1, mod - 2) + mod) % mod; 
        }
        sort(query.rbegin(),query.rend(),cmp); 
        map<long long,long long>mp; 
        long long cur = n;
        ///cout<<fact[10].size()<<endl;
        for(int i = 0; i < query.size(); i++){
                while(cur >= query[i].second.first){
                    for(int j = 0; j < fact[a[cur]].size(); j++){
                        long long num = fact[a[cur]][j];
                        ///cout<<num<<' '<<mp[num]<<' '<<era[num]<<endl;
                        if(mp.count(num)) st.upd(mp[num],era[num]);
                        mp[num] = cur;
                        st.upd(cur,mul[num]);
                    }
                    cur--;
                }
                ans[query[i].first] = st.query(query[i].second.first,query[i].second.second); 
        }
        for(int i = 1; i <= q; i++) printf("%d \n",ans[i]);
}
