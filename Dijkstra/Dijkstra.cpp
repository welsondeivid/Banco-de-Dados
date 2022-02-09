#include <bits/stdc++.h>
#include <string.h>
#include <vector>
#define INF 9999999

using namespace std;

struct Distancia
{
   int custo;
   int indice;
};


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

bool DistanciaMenor(const Distancia& p1, const Distancia& p2)
{
   return p1.custo < p2.custo;
}

int main(int argc, char *argv[])
{
	int inicio = 0, vef = 0;
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-i") == 0)
			{
				//cout << "INICIAL" << argv[i+1] << endl;
				inicio = stoi(argv[i+1]);
				i++;
			}
			else if (strcmp(argv[i], "-s") == 0)
			{
                vef = 1;
			}
			cout << i << ' ' << argv[i] << endl;
		}
	}
	
    int n, m, u, v, peso;
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
    
    if (inicio < 0 || inicio >= n)
    {
        cout << "Vertice nao pertence ao grafo";
        return 0;
    }
    
    Dijkstra (inicio, grafo, dist, visit);
    
	vector<Distancia> vet;

    // Crescente
    if (vef == 1)
    {
        for (int i = 0; i < n; i++)
        {
    		vet.push_back({dist[i], i});
        }
    	sort(vet.begin(), vet.end(), DistanciaMenor);
    
    	for (const auto& v : vet)
        {
            if (inicio != v.indice)
            {
                cout << "O menor custo de " << inicio << " para " << v.indice << ": ";
            
                if (v.custo == INF)     cout << "Infinita" << endl;
                
                else    cout << v.custo << endl;
            }
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (i != inicio)
            {
                cout << "O menor custo de " << inicio << " para " << i << ": ";
            
                if (dist[i] == INF)     cout << "Infinita" << endl;
                
                else    cout << dist[i] << endl;
            }
        }
    }
    
    return 0;
}
