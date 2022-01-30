#include <bits/stdc++.h>
#define PMAX 99999

using namespace std;

void Prim(vector<pair<int, int>> grafo[], int n)
{
    int pesos[n];
    int caminho[n];
    int visitados[PMAX];

    for (int i = 0; i < n; i++) 
    {
        caminho[i] = -1;
        pesos[i] = PMAX;
    }

    pesos[0] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Fila;

    Fila.push({pesos[0], 0});

    while (true)
    {
        int atual = -1;

        while (!Fila.empty())
        {
            int Vert_atual = Fila.top().second;
            Fila.pop();

            if (visitados[Vert_atual] == 0)
            {
                atual = Vert_atual;
                break;
            }
        }
        if (atual == -1)    break;

        visitados[atual] = 1;

        for (int i = 0; i < grafo[atual].size(); i++)
        {
            int vizinho = grafo[atual][i].first;

            int Vert_atual = grafo[atual][i].second;

            if (pesos[Vert_atual] > vizinho && visitados[Vert_atual] == 0)
            {
                pesos[Vert_atual] = vizinho;
                caminho[Vert_atual] = atual;
                Fila.push({pesos[Vert_atual], Vert_atual});
            }
        }
    }

    int PesoT = 0;
    
    cout << "Arvore:" << endl;
    for (int i = 1; i < n; i++)
    {
        cout << caminho[i] << " -> " << i << " = " << pesos[i] << endl;
    }

    for (int i = 0; i < n; i++) 
    {
        PesoT += pesos[i];
    }
    cout << "Peso da AGM: " << PesoT;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> grafo[n];
    
    int u, v, peso;

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> peso;

        grafo[u].push_back({peso, v});
        grafo[v].push_back({peso, u});
    }

    Prim(grafo, n);
    return 0;
}
