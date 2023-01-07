#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 2e5 + 1;
const int N = 4e5 + 10;
const int mod = 1e9 + 7;
long long n,m,k,q;
int a[N + 1]; 
int prime[62] ={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};
struct queries{
    int l,r,x;
    long long ans = 1;
} d[sz];
long long num[N + 1];
long long sum[N + 1];
void update(int x, long long  v, long long * bit){
        for (; x < N; x += x & -x) bit[x] += v;
}
long long query(int x, long long * bit){
       long long t = 0;
       for (; x; x -= x & -x) t += bit[x];
       return t;
}
void upd(int l, int r, long long x){  
       update(l, x, num);
       update(r + 1, -x, num);
       update(l, 1LL * (l - 1) * x, sum);
       update(r + 1, 1LL * (-r) * x, sum);
}
long long query(int l, int r){
     return (1LL * r * query(r, num) - query(r, sum)) - (1LL * (l - 1) * query(l - 1, num) - query(l - 1, sum));
}
void reset(){
        memset(num,0,sizeof(num));
        memset(sum,0,sizeof(sum));
}
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
     for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
     for(int i = 1; i <= q; i++){
            char s[10]; scanf("%s",&s);
            if(s[0] == 'T') scanf("%d%d",&d[i].l,&d[i].r);
            else scanf("%d%d%d",&d[i].l,&d[i].r,&d[i].x); 
     }
     for(int i = 0; i < 62; i++){
           reset(); 
           for(int j = 1; j <= n; j++){
                 int count = 0; 
                 while(a[j] % prime[i] == 0){
                      count++;
                      a[j] = a[j] / prime[i]; 
                 }
                 if(!count) continue;
                 upd(j,j,count);
           }       
           for(int j = 1; j <= q; j++){
                if(!d[j].x){
                     long long val = query(d[j].l,d[j].r);
                     if(!val) continue;
                     d[j].ans = d[j].ans % mod * binpow(prime[i],val - 1) % mod;
                     d[j].ans = d[j].ans % mod * (prime[i] - 1) % mod;
                }
                else{
                     int count = 0; int num = d[j].x;
                     while(num % prime[i] == 0){
                          num = num / prime[i];
                          count++;
                     }
                     if(!count) continue;
                     upd(d[j].l,d[j].r,count);
                }
           }
     }
     for(int i = 1; i <= q; i++){
          if(!d[i].x) printf("%d \n",d[i].ans);
     }
}
