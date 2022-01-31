#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
vector<int> par, krk;

int fset (int x)
{
    if (par[x] != x)
    {
        par[x] = fset(par[x]);
    }
    return par[x];
}

void uset (int x, int y)
{
    if (krk[x] >= krk[y])
    {
        par[y] = x;
        
        if (krk[x] == krk[y])
        {
            krk[x]++;
        }
    }
    else
    {
        par[x] = y;
    }
}

void Kruskal (vector <vector<pair<int,int>>> listaAdjacencia, vector <pair<int, pair<int,int>>> listaAresta, int m)
{
    vector <pair<int, pair<int,int>>> arvore;
    for (int v = 0; v < listaAdjacencia.size(); v++)
    {
        par[v] = v;
        krk[v] = 0;
    }
    for (auto aresta : listaAresta)
    {
        if (fset(aresta.second.first) != fset(aresta.second.second))
        {
            arvore.push_back(aresta);
            uset(fset(aresta.second.first), fset(aresta.second.second));
        }
    }
    
    int Pmin = 0;
    cout << "Arvore: " << endl;
    for (int i = 0; i < arvore.size(); i++)
    {
        Pmin += arvore[i].first;
        cout << arvore[i].second.first << " -> " << arvore[i].second.second << " = " << arvore[i].first << endl;  
    }
    cout << endl << "Peso AGM = " << Pmin; 
}

int main()
{
    int n, m, u, v, peso;
    
    vector <vector<pair <int,int>>> listaAdjacencia;
    vector <pair<int, pair <int,int>>> listaAresta;

    cin >> n >> m;

    listaAdjacencia.resize(n);
    par.resize(n);
    krk.resize(n);

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> peso;
        listaAdjacencia[u].push_back(pair<int,int>(v, peso));
        listaAdjacencia[v].push_back(pair<int,int>(u, peso));
        listaAresta.push_back(make_pair(peso, pair<int,int>(u,v)));
    }

    sort(listaAresta.begin(), listaAresta.end());

    Kruskal(listaAdjacencia, listaAresta, m);

    return 0;
}
