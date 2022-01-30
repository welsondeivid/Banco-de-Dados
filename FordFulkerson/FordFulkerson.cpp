#include <bits/stdc++.h>

using namespace std;

int busca(vector<vector<int>> grafo, int qVert, vector<vector<int>> res, int inicio, int fim, int par[])
{
    int visitados[qVert];
    visitados[inicio] = 1;
    
    queue<int> fila;
    fila.push(inicio);
    
    memset(visitados, 0, sizeof(int) *qVert);

    int primeiro;

    while (!fila.empty())
    {
        primeiro = fila.front();
        fila.pop();
        
        for (int i = 0; i < qVert; i++)
        {
            if (res[primeiro][i] > 0 && (visitados[i] == 0))
            {
                par[i] = primeiro;
                visitados[i] = 1;
                fila.push(i);
            }
        }
    }
    return visitados[fim];
}

void FordFulkerson(vector<vector<int>> grafo, int qVert, int inicio, int fim)
{
    int aux, fMax = 0;
    int *par = new int[qVert];
    
    vector<vector<int>> res;
    
    res.resize(qVert);
    
    for (int i = 0; i < qVert; i++)
    {
        res[i].resize(qVert);
        
        for (int j = 0; j < qVert; j++)
        {
            res[i][j] = grafo[i][j];
        }
    }
    
    while (busca(grafo, qVert, res, inicio, fim, par) == 1)
    {
        int fluxo = 999999;
        for (int i = fim; i != inicio; i = par[i])
        {
            aux = par[i];
            
            if (res[aux][i] < fluxo)
            {
                fluxo = res[aux][i];
            }
        }
        
        for (int i = fim; i != inicio; i = par[i])
        {
            aux = par[i];
            res[aux][i] -= fluxo;
            res[i][aux] += fluxo;
        }
        fMax += fluxo;
    }
    cout << "Maior fluxo possivel: " << fMax;
}

int main()
{
    vector<vector<int>> Grafo;
    
    int u, v, peso, qVert, qAresta, inicio, fim;
    char c;
    
    cin >> qVert >> qAresta;
    
    Grafo.resize(qVert);
    
    for (int i = 0; i < qVert; i++)
    {
        Grafo[i].resize(qVert);
    }
    
    cin >> inicio >> fim;
    
    for (int i = 0; i < qAresta; i++)
    {
        cin >> u >> v;
        scanf ("%c", &c);
        
        if (c == ' ')   cin >> peso;
        
        else    peso = 1;
        
        Grafo[u][v] = peso;
    }
    
    FordFulkerson(Grafo, qVert, inicio, fim);
    return 0;
}
