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

int Prim(vector<pair<int, int>> grafo[], int n, bool s, char Saida[], bool crescente)
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
    FILE *out;
    vector<Distancia> vet;
    
    for (int i = 0; i < n; i++) 
    {
        PesoT += pesos[i];
    }
    if (s)
    {
        out = fopen (Saida, "w");
    	if (out == NULL)
	    {
	    	cout << "Erro, nao foi possivel abrir o arquivo de saida" << endl;
	    	return 0;
	    }
	    fprintf(out, "Arvore:\n");
	    if (crescente)
	    {
	        for (int i = 1; i < n; i++)
            {
                vet.push_back({pesos[i], caminho[i], i});
            }
            
            sort(vet.begin(), vet.end(), DistanciaMenor);
            
            for (const auto& v : vet)
            {
                fprintf(out, "%i -- %i,  peso = %i\n", v.indice1, v.indice2, v.custo);
            }
	    }
	    else
	    {
	        for (int i = 1; i < n; i++)
            {
                fprintf(out, "%i -- %i,  peso = %i\n", caminho[i], i, pesos[i]);
            }
	    }
	    fprintf(out, "Peso da AGM: %i\n", PesoT);

        fclose(out);
    }
    else
    {
        cout << "Arvore:" << endl;
	    if (crescente)
	    {
	        for (int i = 1; i < n; i++)
            {
                vet.push_back({pesos[i], caminho[i], i});
            }
            
            sort(vet.begin(), vet.end(), DistanciaMenor);
            
            for (const auto& v : vet)
            {
                cout << v.indice1 << " -- " << v.indice2 << ", peso = " << v.custo << endl;
            }
	    }
	    else
	    {
	        for (int i = 1; i < n; i++)
            {
                cout << caminho[i] << " -- " << i << ", peso = " << pesos[i] << endl;
            }
	    }
	    cout << "Peso da AGM: " << PesoT << endl;
    }
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
    bool crescente = false, s = false, ent = false;
    
    if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-s") == 0)
			{
				crescente = true;
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
				cout << "-s Mostra os pesos em ordem crescente" << endl;
				cout << "-f Pegar a entrada de um arquivo definido pelo usuario" << endl;
				cout << "-o Mostra a saida no arquivo definido pelo usuario" << endl; 
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
	
    n = Ler_Arquivo (arq, &ch, verif);
    m = Ler_Arquivo (arq, &ch, verif);
    
    vector<pair<int, int>> grafo[n];

    for (int i = 0; i < m; i++)
    {
        u = Ler_Arquivo (arq, &ch, verif);
        v = Ler_Arquivo (arq, &ch, verif);
        
        if (ch == ' ')   peso = Ler_Arquivo (arq, &ch, verif);
        else    peso = 1;

        grafo[u].push_back({peso, v});
        grafo[v].push_back({peso, u});
    }
    fclose(arq);

    Prim(grafo, n, s, Saida, crescente);
    return 0;
}
