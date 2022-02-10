#include <bits/stdc++.h>
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

int Kruskal (vector <vector<pair<int,int>>> listaAdjacencia, vector <pair<int, pair<int,int>>> listaAresta, int m, bool s, char Saida[])
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

    if (s)
    {
        FILE *out;
        out = fopen (Saida, "w");
        if (out == NULL)
        {
            cout << "Erro, nao foi possivel abrir o arquivo de saida" << endl;
            return 0;
        }

        fprintf (out, "Arvore:\n");

        for (int i = 0; i < arvore.size(); i++)
        {
            Pmin += arvore[i].first;
            fprintf (out, "%d -- %d, peso = %d\n", arvore[i].second.first, arvore[i].second.second, arvore[i].first);
        }

        fprintf (out, "Peso da AGM: %d", Pmin);

        fclose(out);
    }
    else
    {
        cout << "Arvore: " << endl;
        for (int i = 0; i < arvore.size(); i++)
        {
            Pmin += arvore[i].first;
            cout << arvore[i].second.first << " -- " << arvore[i].second.second << ", peso = " << arvore[i].first << endl;  
        }

        cout << "Peso da AGM: " << Pmin;
    }
    
    return 0;
}

int Ler_Arquivo (FILE *arq, char *ch, char verif[])
{
    int num = 0;

    fscanf (arq, "%s", verif);
    num = stoi(verif);
    *ch = fgetc(arq);

    return num;
}

int main(int argc, char *argv[])
{
    int n, m, u, v, peso;
    char ch, Entrada[255], Saida[255], verif[5];

    bool s = false, ent = false;
    
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-f") == 0)
            {
                strcpy (Entrada, argv[i+1]);
                ent = true;
                i++;
            }
            else if (strcmp(argv[i], "-o") == 0)
            {
                strcpy (Saida, argv[i+1]);
                s = true;
                i++;
            }
            else if (strcmp(argv[i], "-h") == 0)
            {
                cout << "-f Pegar a entrada de um arquivo definido pelo usuario" << endl;
                cout << "-o Mostra a saida no arquivo definido pelo usuario" << endl;

                return 0;
            }
        }
    }

    FILE *arq;

    if (!ent)
    {
        cout << "Digite o nome do arquivo de entrada com a extensao: ";
        cin >> Entrada;
    }

    arq = fopen (Entrada, "r");
    
    if (arq == NULL)
    {
        cout << "Erro, nao foi possivel abrir o arquivo" << endl;
        return 0;
    }

    vector <vector<pair <int,int>>> listaAdjacencia;
    vector <pair<int, pair <int,int>>> listaAresta;

    n = Ler_Arquivo (arq, &ch, verif);
    m = Ler_Arquivo (arq, &ch, verif);

    listaAdjacencia.resize(n);
    par.resize(n);
    krk.resize(n);

    for (int i = 0; i < m; i++)
    {
        u = Ler_Arquivo (arq, &ch, verif);
        v = Ler_Arquivo (arq, &ch, verif);
        
        if (ch == ' ')   peso = Ler_Arquivo (arq, &ch, verif);
        else    peso = 1;
        
        listaAdjacencia[u].push_back(pair<int,int>(v, peso));
        listaAdjacencia[v].push_back(pair<int,int>(u, peso));
        listaAresta.push_back(make_pair(peso, pair<int,int>(u,v)));
    }

    fclose(arq);

    sort(listaAresta.begin(), listaAresta.end());

    Kruskal(listaAdjacencia, listaAresta, m, s, Saida);

    return 0;
}
