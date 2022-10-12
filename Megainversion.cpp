
 Download file
#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<
    T, null_type, less<T>,
    rb_tree_tag, tree_order_statistics_node_update
>;
const int sz=1e5+5;
int n;
int a[sz];
int pf[sz];
ll bit[sz];
ll bit1[sz];
Tree<int>tr;
ll sum(int i)
{
    ll c=0;
    for(++i; i > 0 ; i -= (i & -i))
        c= (c+bit[i]);
    return c;
}
ll sum1(int i)
{
    ll c=0;
    for(++i; i > 0 ; i -= (i & -i))
        c= (c+bit1[i]);
    return c;
}
void upd(int i,int dif)
{
    for(++i; i < sz ; i += (i & -i))
        bit[i] = (dif+bit[i]);
}
void upd1(int i,int dif)
{
    for(++i; i < sz ; i += (i & -i))
        bit1[i] = (dif+bit1[i]);
}
int main(){
    cin>>n;
    vector<array<int,2>>dp;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        dp.push_back({a[i],i});
    }
    sort(dp.rbegin(),dp.rend());
    ll cnt=0;
    for(auto x:dp){
         ll inv=sum(x[1]);
         ll t=sum1(x[1]);
         cnt+=t;
         upd(x[1],1);
         upd1(x[1],inv);
    }
    cout<<cnt<<endl;
}
