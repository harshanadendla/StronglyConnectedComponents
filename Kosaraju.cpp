//Kosaraju's algorithm....dfs once....push vertices onto a stack according to their finish times
//transpose the graph....pop one by one from stack...dfs it while marking vis....each time you come out of 
//dfs yields you a set of new stringly connected components

#include<bits/stdc++.h>
using namespace std;
#define ll long long int

class graph
{
    int v;
    list<int> *adj;

        public:

    graph(int w)
    {
        v=w;
        adj=new list<int>[v+1];
    }

    void addEdge(int v,int w)
    {
        adj[v].push_back(w);
    }

    void fillOrder(int v,vector<bool> &vis,stack<int> &s)
    {
        vis[v]=true;

        for(auto i=adj[v].begin();i!=adj[v].end();i++)
        {
            if(!vis[*i])
            {
                fillOrder(*i,vis,s);
            }
        }
        s.push(v);
    }

    void dfs(int v,vector<bool> &vis,vector<int> &temp)
    {
        vis[v]=true;
        temp.push_back(v);

        for(auto i=adj[v].begin();i!=adj[v].end();i++)
        {
            if(!vis[*i])
            {
                dfs(*i,vis,temp);
            }
        }
    }

    graph getTranspose(int v)
    {
        graph g(v);
        for(int i=1;i<=v;i++)
        {
            for(auto j=adj[i].begin();j!=adj[i].end();j++)
            {
                g.adj[*j].push_back(i);
            }
        }
        return g;
    }

    void printThings(int v)
    {
        stack<int> s;
        vector<bool> vis(v+1,false);
        for(int i=1;i<=v;i++)
        {
            if(!vis[i])
            {
                this->fillOrder(i,vis,s);
            }
        }
        graph g=this->getTranspose(v);

        vector<vector<int>> res;
        vector<int> temp;
        for(int i=0;i<=v;i++) vis[i]=false;
        while(!s.empty())
        {
            int i=s.top();
            s.pop();
            if(!vis[i]) 
            {
                g.dfs(i,vis,temp);
                res.push_back(temp);
                temp.clear();
            }
        }
        for(int i=0;i<res.size();i++)
        {
            for(int j=0;j<res[i].size();j++)
            {
                cout<<res[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

};

int main()
{
    graph g(5);
    g.addEdge(2,1); 
    g.addEdge(1,3); 
    g.addEdge(3,2); 
    g.addEdge(1,4); 
    g.addEdge(4,5);
    g.printThings(5);
    return 0;
}
