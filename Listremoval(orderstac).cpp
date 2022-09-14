#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n,q;
ll c[sz];
ll bit[sz];
using namespace __gnu_pbds;
template<class T> using Tree = tree<T, null_type, less<T>, 
	rb_tree_tag, tree_order_statistics_node_update>; 
int main() {
    cin>>n;
    Tree<int>st;
    for(int i=0;i<n;i++){
         cin>>c[i];
        st.insert(i);
    } for (int i=0;i<n;i++){
         int a;cin>>a;a--;
         int j=*st.find_by_order(a);
         cout <<c[j]<<" ";
         st.erase(j);
    }
}  