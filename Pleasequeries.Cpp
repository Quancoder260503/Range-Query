//TLE version.
#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 4e5 + 10;
const int mod = 1e9 + 7;
long long n,m,k,q;
int ord[63];
long long a[N + 1];
int prime[62] ={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};
struct BIT {
    int data[N];
    void update(int idx, int val) {
        while (idx < N) {
            data[idx] += val;
            idx += idx & -idx;
        }
    }
    void update(int l, int r, int val) {
        update(l, val);
        update(r + 1, -val);
    }
    long long query(int idx) {
        long long res = 0;
        while (idx > 0) {
            res += data[idx];
            idx -= idx & -idx;
        }
        return res;
    }
};
struct LazyBIT {
    BIT bitAdd, bitSub;
    void upd(int l, int r, int val) {
        bitAdd.update(l, r, val);
        bitSub.update(l, r, (1ll)*(l - 1) * val);
        bitSub.update(r + 1, (1ll)*(-r + l - 1) * val);
    }
    long long query(long long idx) {
        return idx * bitAdd.query(idx) - bitSub.query(idx);
    }
    long long query(long long l, long long r) {
        return query(r) - query(l - 1);
    }
} fw[63];

long long binpow(long long a, long long b){
    if(b == 0) return 1;
    long long ans = 1;
    while(b > 0){
         if(b & 1) ans = ans % mod * a % mod;
         a = a % mod * a % mod;
         b >>= 1;
    }
    return ans;
}
int main(){
     scanf("%d%d",&n,&q);  
     int cnt = 0;
     for(int i = 1; i <= n; i++){ 
          scanf("%d",&a[i]);
          int num = a[i];
          for(int j = 0; j < 62 and prime[j] <= num; j++){
              int count = 0;
              while(num % prime[j] == 0){
                   count++;
                   num = num / prime[j]; 
              }
              fw[j].upd(i,i,count); 
          }
     }
     for(int i = 1; i <= q; i++){
          string s; cin>>s;
          if(s == "TOTIENT"){
              int l,r; scanf("%d%d",&l,&r);
              long long ans = 1;
              for(int j = 0; j < 62; j++){
                   long long val = fw[j].query(l,r);
                   if(val < 1) continue;
                   ans = ans % mod * binpow(prime[j],val - 1) % mod * (prime[j] - 1) % mod;
              }
              printf("%d \n",ans);
          }
          else{
                int l,r,x; scanf("%d%d%d",&l,&r,&x);
                int num = x;
                for(int j = 0; j < 62 and prime[j] <= num; j++){
                     int count = 0;
                     while(num % prime[j] == 0){
                        count++;
                        num = num / prime[j]; 
                     }
                     fw[j].upd(l,r,count); 
                }
          }
     }
}
