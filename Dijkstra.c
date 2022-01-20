#include <stdio.h>
#define INF 9999 

void Grafo (int qVert, int arestas[][qVert - 1], int pesos[][qVert - 1], int cont_arestas[], int qArest, int cont)
{
    int vert, ares, peso;
    char c;
    
    if (cont < qArest)
    {
        scanf ("%d %d", &vert, &ares);  // sempre vai ter os dois primeiros números
        scanf ("%c", &c); //caractere de teste
        
        if (c == ' ')  // se o escaneado foi um espaço tem mais 1 número
        {
            scanf("%d", &peso);
        }
        else
        {
            peso = 1;  // peso se não tiver 3 número na linha de entrada, peso não definido
        }

        arestas[vert-1][cont_arestas[vert-1]] = ares;
        arestas[ares-1][cont_arestas[ares-1]] = vert;

        pesos[vert-1][cont_arestas[vert-1]] = peso; //linha referente à mesma linha da matriz arestas
        pesos[ares-1][cont_arestas[ares-1]] = peso; //coluna referente à mesma coluna da matriz arestas
        
        cont_arestas[ares-1] += 1;
        cont_arestas[vert-1] += 1;
        
        Grafo (qVert, arestas, pesos, cont_arestas, qArest, cont+1);
    }
    return;
}

void ordenar_fila (int dist[], int fila[], int v, int qVert)
{
    
}

int fila_vazia (int fila[], int qVert, int cont)
{
    if (cont < qVert)
    {
        if (fila[cont] != 0)    return fila[cont];
        
        else    return fila_vazia (fila, qVert, cont+1);
    }
    else    return -1;
}

void Dijkstra (int qVert, int arestas[][qVert-1], int pesos[][qVert-1], int inicio)
{
    int vazia = 0; //fila_vazia (fila, qVert, 0);
    int u, v, aux, prior = 0;
    
    int visitado[qVert], dist[qVert], prev[qVert], fila[qVert];
    
    for (int i = 0; i < qVert; i++)
    {
        dist[i] = INF;
        prev[i] = -1;
        fila[i] = i+1;  //1 2 3 4 5
        visitado[i] = 0;
    }
    
    visitado[inicio - 1] = 1;
    dist[inicio - 1] = 0;
    
    aux = fila[0];
    fila[0] = inicio;
    fila[inicio - 1] = aux; //4 2 3 1 5
    
    while (vazia != -1)
    {
        u = vazia;
        fila[prior] = 0; //0 2 3 1 5
        
        for (int i = 0; i < qVert-1; i++)
        {
            if (arestas[u-1][i] == 0)   break;
            
            v = arestas[u-1][i] - 1;
            
            if (visitado[v] == 0)
            {
                if (dist[v] > dist[u] + pesos[u-1][i])
                {
                    dist[v] = dist[u] + pesos[u-1][i];
                    prev[v] = u;
                    
                    // 0 2 3 1 5
                    // 1 0 2 3 5
                    //
                    // 2 | inf | inf | 0 | inf
                    //
                    //ordenar_fila (dist, fila, v, qVert);
                }
            }
        }
        
        //vazia = fila_vazia (fila, qVert, 0);
    }
}

int main()
{
    int qVert, qArest, inicio;
    scanf ("%d %d\n", &qVert, &qArest);
    
    int cont_arestas[qVert], dist[qVert], prev[qVert], fila[qVert];
    int pesos[qVert][qVert-1], arestas[qVert][qVert-1];
    
    // preencher todos os vetores com 0's
    for (int i = 0; i < qVert; i++)
    {
        cont_arestas[i] = 0;
        
        for (int j = 0; j < qVert - 1; j++)
        {
            arestas[i][j] = 0;
            pesos[i][j] = 0;
        }
    }
    
    Grafo (qVert, arestas, pesos, cont_arestas, qArest, 0);
    
    scanf ("%d", &inicio);
    
    //Dijkstra (qVert, arestas, pesos, inicio);
    
    printf ("Arestas:\n");
    for (int i = 0; i < qVert; i++)
    {
        for (int j = 0; j < qVert - 1; j++)
        {
            printf ("%d ", arestas[i][j]);
        }
        printf ("\n");
    }
    printf ("\n");
    
    printf ("Pesos:\n");
    for (int i = 0; i < qVert; i++)
    {
        for (int j = 0; j < qVert - 1; j++)
        {
            printf ("%d ", pesos[i][j]);
        }
        printf ("\n");
    }
    
    return 0;
}
