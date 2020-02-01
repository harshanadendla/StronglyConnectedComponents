//baaboi..graphs gurinchi baga nerpindi idi....4 days pattindi...idea pattesa...logic pattesa...but implementation rala...
//dfs lo vis check marchipoya...nenu over complicate chesa.....graph representation baga arthamaindi...adj matrix.
//scc and maximum path sum in a graph nerchukunna.

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 1000000007
#define N 100009

int n,m,a,b;
int costs[N];
vector<int> graph[N],rev_graph[N];
vector<int> s;
vector<bool> vis(N,false);
int subset=1;
vector<int> batch(N);
vector<int> value(N,0);
set<int> sub_tree[N];

void dfs1(int u)
{
    vis[u]=true;
    for(int i=0;i<graph[u].size();i++)
    {
        if(!vis[graph[u][i]]) dfs1(graph[u][i]);
    }
    s.insert(s.begin(),u);
}

void dfs2(int u)
{
    vis[u]=false;
    batch[u]=subset;
    for(int i=0;i<rev_graph[u].size();i++)
    {
        if(vis[rev_graph[u][i]]) dfs2(rev_graph[u][i]);
    }
}

void dfs3(int u)
{
    vis[u]=true;
    int total=0;
    for(int i : sub_tree[u])
    {
        if(!vis[i]) dfs3(i);
        total=max(total,value[i]);
    }
    value[u]+=total;
}

int32_t main()
{
    ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>costs[i];
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        graph[a].push_back(b);
        rev_graph[b].push_back(a);
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i]) dfs1(i);
    }
    for(int i=0;i<s.size();i++)
    {
        if(vis[s[i]]) 
        {
            dfs2(s[i]);
            subset++;
        }
    }
    for(int i=1;i<=n;i++)
    {
        value[batch[i]]+=costs[i];
    }
    for(int i=0;i<vis.size();i++) vis[i]=false;
    for(int i=1;i<=n;i++)
    {
        for(int j : graph[i])
        {
            if(batch[i]!=batch[j])
            {
                sub_tree[batch[i]].insert(batch[j]);
            }
        }
    }
    for(int i=0;i<vis.size();i++) vis[i]=false;
    for(int i=1;i<=subset;i++)
    {
        if(!vis[i]) dfs3(i);
    }
    for(int i=1;i<=n;i++)
    {
        cout<<value[batch[i]]<<" ";
    }
    cout<<"\n";
    return 0;
}
