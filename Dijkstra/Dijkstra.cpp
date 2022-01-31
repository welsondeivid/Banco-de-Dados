#include <bits/stdc++.h>
#include <vector>
#define INF 9999999

using namespace std;

void Dijkstra (int inicio, vector<vector<pair<int, int>>> &grafo, vector<int> &dist, vector<int> &visit)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Fila;
    
    dist[inicio] = 0;
    
    Fila.push({dist[inicio], inicio});
    
    while (!Fila.empty())
    {
        int vertice = Fila.top().second;
        Fila.pop();
        
        if (visit[vertice] == 0)
        {
            visit[vertice] = 1;
        
            for (auto const &prox : grafo[vertice])
            {
                int peso = prox.first;
                int vertice2 = prox.second;
    
                if (dist[vertice2] > dist[vertice] + peso)
                {
                    dist[vertice2] = dist[vertice] + peso;
                    Fila.push({dist[vertice2], vertice2});
                }
            }
        }
    }
    
    //cout << "O menor custo de " << inicio << " para " << fim << ": " << dist[fim];
}

int main()
{
    int n, m, u, v, peso, inicio;
    char c;
    cin >> n >> m; 
    
    vector<int> dist;
    vector<int> visit;
    vector<vector<pair<int, int>>> grafo;
    
    grafo.resize(n);
    dist.resize(n);
    visit.resize(n);
    
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        scanf ("%c", &c);
        
        if (c == ' ')   cin >> peso;
        
        else    peso = 1;
        
        grafo[u].push_back ({peso, v});
        grafo[v].push_back ({peso, u});
    }
    
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        visit[i] = 0;
    }
    
    cin >> inicio;
    
    if (inicio < 0 || inicio >= n)
    {
        cout << "Vertice nao pertence ao grafo";
        return 0;
    }
    
    Dijkstra (inicio, grafo, dist, visit);
    
    for (int i = 0; i < n; i++)
    {
        if (i != inicio)
        {
            cout << "O menor custo de " << inicio << " para " << i << ": ";
        
            if (dist[i] == INF)     cout << "Infinita" << endl;
            
            else    cout << dist[i] << endl;
        }
    }

    return 0;
}
