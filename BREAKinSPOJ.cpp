// vammo vammo...chinna dfs func ki entha drama chesano.....atlast...arthamaindi.

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 90900

int t;
int n,m;
int a,b;
vector<int> graph[N];
vector<int> rev_graph[N];
vector<bool> vis(N);
vector<int> s;
int subset=1;
vector<int> batch(N);
vector<int> value(N);
set<int> sub_tree[N];
int maxx;
int total;
vector<int> fin(N);

void setMemories()
{
    for(int i=0;i<N;i++)
    {
        graph[i].clear();
        rev_graph[i].clear();
        vis[i]=false;
        batch[i]=0;
        value[i]=0;
        fin[i]=0;
        sub_tree[i].clear();
    }
    s.clear();
    subset=1;
    maxx=0;
    total=0;
}

void dfs1(int u)
{
    vis[u]=true;
    for(int i : graph[u])
    {
        if(!vis[i]) dfs1(i);
    }
    s.insert(s.begin(),u);
}

void dfs2(int u)
{
    vis[u]=false;
    batch[u]=subset;
    for(int i : rev_graph[u])
    {
        if(vis[i]) dfs2(i);
    }
}

int dfs3(int u)
{
    vis[u]=true;
    int total=0;
    for(int i : graph[u])
    {
        if(!vis[i]) 
        {
            total+=dfs3(i);
        }
    }
    return total+1;
}

int32_t main()
{
    ios_base::sync_with_stdio(false),cin.tie(NULL);
    cin>>t;
    while(t--)
    {
        setMemories();
        cin>>n>>m;
        for(int i=1;i<=m;i++)
        {
            cin>>a>>b;
            graph[b].push_back(a);
            rev_graph[a].push_back(b);
        }
        for(int i=1;i<=n;i++)
        {
            if(!vis[i]) dfs1(i);
        }
        for(int i=0;i<s.size();i++)
        {
            if(vis[s[i]]) dfs2(s[i]);
            subset++;
        }
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
        for(int i=1;i<=n;i++)
        {
            value[batch[i]]++;
        }
        for(int i=0;i<N;i++) vis[i]=false;
        for(int i=1;i<=n;i++)
        {
            if(fin[batch[i]]==0)
            {
                for(int i=0;i<N;i++) vis[i]=false;
                fin[batch[i]]=dfs3(i);   
                if(fin[batch[i]]>maxx) maxx=fin[batch[i]];
            }
        }
        for(int i=1;i<=n;i++)
        {
            if(fin[batch[i]]==maxx) cout<<i<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
