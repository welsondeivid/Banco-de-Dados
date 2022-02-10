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

int FordFulkerson(vector<vector<int>> grafo, int qVert, int inicio, int fim)
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
    return fMax;
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
    vector<vector<int>> Grafo;
    
    int u, v, peso, qVert, qAresta, inicio = 0, fim = 0;
    char ch, Entrada[255], Saida[255], verif[5];

    bool s = false, ent = false;
    
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-i") == 0)
            {
                inicio = stoi(argv[i+1]);
                i++;
            }
            else if (strcmp(argv[i], "-l") == 0)
            {
                fim = stoi(argv[i+1]);
                i++;
            }
            else if (strcmp(argv[i], "-f") == 0)
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
                cout << "-i Vertice inicial" << endl;
                cout << "-l Vertice final" << endl;
                cout << "-f Pegar a entrada de um arquivo definido pelo usuario" << endl;
                cout << "-o Mostra a saida no arquivo definido pelo usuario" << endl;

                return 0;
            }
        }
    }

    FILE *arq;
    FILE *out;

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
    
    qVert = Ler_Arquivo (arq, &ch, verif);
    qAresta = Ler_Arquivo (arq, &ch, verif);
    
    if (inicio < 0 || inicio >= qVert || fim < 0 || fim >= qVert)
    {
        if (s)  fprintf (out, "Vertice nao pertence ao grafo");
        else    cout << "Vertice nao pertence ao grafo";
        return 0;
    }

    Grafo.resize(qVert);
    
    for (int i = 0; i < qVert; i++)
    {
        Grafo[i].resize(qVert);
    }
    
    for (int i = 0; i < qAresta; i++)
    {
        u = Ler_Arquivo (arq, &ch, verif);
        v = Ler_Arquivo (arq, &ch, verif);
        
        if (ch == ' ')   peso = Ler_Arquivo (arq, &ch, verif);
        
        else    peso = 1;
        
        Grafo[u][v] = peso;
    }

    fclose(arq); 

    if (s)
    {
        out = fopen (Saida, "w");
        if (out == NULL)
        {
            cout << "Erro, nao foi possivel abrir o arquivo de saida" << endl;
            return 0;
        }

        fprintf (out, "O Maior Fluxo Possivel: %d", FordFulkerson(Grafo, qVert, inicio, fim));
        fclose(out);
    }

    else    cout << "O Maior Fluxo Possivel: " << FordFulkerson(Grafo, qVert, inicio, fim);;

    return 0;
}
