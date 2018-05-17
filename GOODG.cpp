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
#include <bitset>

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

#define N 1000001
#define mod 1000000007
#define inf 1e15

typedef long long ll;
typedef unsigned long long ull;

const ll isQuery=-1e13;

class Line
{
public:
    ll m,c;
    double xLeft;
    Line(ll mm,ll cc)
    {
        m=mm,c=cc;
        xLeft=-inf;
    }
    bool operator<(const Line &b) const
    {
        if(b.xLeft!=isQuery)
            return m<b.m;
        return xLeft<b.m;
    }
};

class convexHull
{
    set<Line> s;
    
    bool isParallel(Line a,Line b)
    {
        return a.m==b.m;
    }
    
    double intersect(Line a,Line b)
    {
        return (1.0*b.c-a.c)/(1.0*a.m-b.m);
    }
    
    bool hasPrev(set<Line>::iterator it)
    {
        return it!=s.begin();
    }
    
    bool hasNext(set<Line>::iterator it)
    {
        return it!=s.end()&&next(it)!=s.end();
    }
    
    bool irrelevant(set<Line>::iterator it)
    {
        return hasPrev(it)&&hasNext(it)&&intersect(*prev(it),*next(it))>=intersect(*it,*next(it));
    }
    
    void setXLeft(set<Line>::iterator it)
    {
        if(hasPrev(it))
        {
            Line temp=*it;
            temp.xLeft=intersect(*prev(it),temp);
            s.insert(s.erase(it),temp);
        }
    }
    
public:
    void addLine(Line a)
    {
        auto it=s.lower_bound(a);
        if(it!=s.end()&&isParallel(*it,a))
        {
            if(a.c>it->c)
                it=s.erase(it);
            else
                return;
        }
        if(hasPrev(it))
            a.xLeft=intersect(a,*prev(it));
        it=s.insert(it,a);
        if(irrelevant(it))
        {
            s.erase(it);
            return;
        }
        while(hasNext(it)&&irrelevant(next(it)))
            s.erase(next(it));
        while(hasPrev(it)&&irrelevant(prev(it)))
            s.erase(prev(it));
        setXLeft(it);
        if(hasNext(it))
            setXLeft(next(it));
    }
    
    ll query(ll x)
    {
        Line a(x,0);
        a.xLeft=isQuery;
        auto it=s.lower_bound(a);
        it=prev(it);
        return it->m*x+it->c;
    }
};

ll dp[N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
//    freopen("Input.txt","r",stdin);
//    freopen("Output.txt","w",stdout);
    int n;
    convexHull hull;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        ll a,b;
        cin>>a>>b;
        if(i==1)
            dp[i]=max(dp[i],a-b);
        else
            dp[i]=max(dp[i],a-b+hull.query(i));
        hull.addLine(Line(-b,(i+1)*b+dp[i]));
    }
    cout<<hull.query(n+1)<<endl;
    return 0;
}
