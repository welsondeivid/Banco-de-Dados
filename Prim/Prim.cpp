#include <bits/stdc++.h>
#define PMAX 99999

using namespace std;

struct Distancia
{
   int custo;
   int indice1;
   int indice2;
};

bool DistanciaMenor(const Distancia& p1, const Distancia& p2)
{
   return p1.custo < p2.custo;
}

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
            int Vert_vizinho = Fila.top().second;
            Fila.pop();

            if (visitados[Vert_vizinho] == 0)
            {
                atual = Vert_vizinho;
                break;
            }
        }
        if (atual == -1)    break;

        visitados[atual] = 1;

        for (int i = 0; i < grafo[atual].size(); i++)
        {
            int p_vizinho = grafo[atual][i].first;

            int Vert_vizinho = grafo[atual][i].second;

            if (pesos[Vert_vizinho] > p_vizinho && visitados[Vert_vizinho] == 0)
            {
                pesos[Vert_vizinho] = p_vizinho;
                caminho[Vert_vizinho] = atual;
                Fila.push({pesos[Vert_vizinho], Vert_vizinho});
            }
        }
    }

    int PesoT = 0;
    
    cout << "Arvore:" << endl;
    vector<Distancia> vet;
    for (int i = 1; i < n; i++)
    {
        vet.push_back({pesos[i], caminho[i], i});
        cout << caminho[i] << " -- " << i << ", peso = " << pesos[i] << endl;
    }

    for (int i = 0; i < n; i++) 
    {
        PesoT += pesos[i];
    }
    cout << "Peso da AGM: " << PesoT << endl;
    
    sort(vet.begin(), vet.end(), DistanciaMenor);
    
    for (const auto& v : vet)
    {
        cout << v.indice1 << " -- " << v.indice2 << ", peso = " << v.custo << endl;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    
    vector<pair<int, int>> grafo[n];
    
    int u, v, peso;
    char c;

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;
        scanf("%c", &c);
        
        if (c == ' ')   cin >> peso;
        else    peso = 1;

        grafo[u].push_back({peso, v});
        grafo[v].push_back({peso, u});
    }

    Prim(grafo, n);
    return 0;
}
