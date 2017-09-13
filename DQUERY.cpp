#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <stack>
 
#define endl "\n"
#define si(a) scanf("%d",&a)
#define sii(a,b) scanf("%d %d",&a,&b)
#define siii(a,b,c) scanf("%d %d %d",&a,&b,&c)
#define sl(a) scanf("%lld",&a)
#define sll(a,b) scanf("%lld %lld",&a,&b)
#define pf printf
#define vi vector<int>
#define vii vector<pair<int,int> >
#define pii pair<int,int>
#define all(c) c.begin(),c.end()
#define ms(a,c) memset(a,c,sizeof(a))
#define tr(c,i) for(decltype((c).begin()) i=(c).begin();i!=(c).end();i++)
#define trr(c,i) for(decltype((c).rbegin()) i=(c).rbegin();i!=(c).rend();i++)
 
using namespace std;
 
#define N 30001
#define mod 1000000007
#define inf 1e9
 
typedef long long ll;
typedef unsigned long long ull;
 
int cur;
 
struct node
{
    int value,left,right;
 
    node(int v=0,int l=0,int r=0)
    {
        value=v;
        left=l;
        right=r;
    }
}nodes[20*N];
 
void build(int n,int l,int r)
{
    nodes[n].value=0;
    nodes[n].left=++cur;
    nodes[n].right=++cur;
    int mid=(l+r)>>1;
    if(l!=r)
        build(nodes[n].left,l,mid),build(nodes[n].right,mid+1,r);
}
 
int insert(int n,int l,int r,int p)
{
    if(l<=p&&r>=p)
    {
        int t=cur++;
        if(l==r)
        {
            nodes[t].left=nodes[t].right=0;
            nodes[t].value=nodes[n].value+1;
            return t;
        }
        int mid=(l+r)>>1;
        nodes[t].left=insert(nodes[n].left,l,mid,p);
        nodes[t].right=insert(nodes[n].right,mid+1,r,p);
        nodes[t].value=nodes[n].value+1;
        return t;
    }
    return n;
}
 
int query(int n,int l,int r,int v)
{
    if(v<l)
        return 0;
    if(v>=r)
        return nodes[n].value;
    int mid=(l+r)>>1;
    return query(nodes[n].left,l,mid,v)+query(nodes[n].right,mid+1,r,v);
}
 
int mp[N];
int data[N];
int last[N];
int head[N];
 
int main()
{
//    ios_base::sync_with_stdio(0);
//    cin.tie(0);
//    freopen("Input.txt","r",stdin);
//    freopen("Output.txt","w",stdout);
    ms(mp,0);
    int n,q;
    si(n);
    for(int i=0;i<n;i++)
        si(data[i]),last[i]=mp[data[i]],mp[data[i]]=i+1;
    cur=1;
    build(1,0,n-1);
    head[0]=1;
    for(int i=0;i<n;i++)
        head[i+1]=insert(head[i],0,n-1,last[i]);
    si(q);
    for(int i=0;i<q;i++)
    {
        int a,b;
        sii(a,b);
        pf("%d\n",query(head[b],0,n-1,a-1)-query(head[a-1],0,n-1,a-1));
    }
    return 0;
}
