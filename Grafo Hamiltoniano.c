#include <stdio.h>

void Dirac (int num_adj[], int vertice, int cont)
{
    if (cont == vertice)
    {
        printf ("Grafo Hamiltoniano");
        return;
    }
    
    if (num_adj[cont] < vertice/2)
    {
        printf ("Grafo não-Hamiltoniano");
        return;
    }
    else
    {
        Dirac (num_adj, vertice, cont+1);
    }
}

int main()
{
    int vertice, aresta, n = 1, x, y;
    scanf ("%d %d", &vertice, &aresta);
    int num_adj[vertice], adj[vertice][aresta];
    
    //preencher num_adj com 0's
    for (int i = 0; i < vertice; i++)
    {
        num_adj[i] = 0;
    }
    
    //preencher coluna
    for (int i = 0; i < vertice; i++)
    {
        adj[i][0] = n;
        n++;
        //printf ("%d\n", adj[i][0]);
    }
    
    //preencher num_adj com os graus de cada vértice
    for (int i = 0; i < aresta; i++)
    {
        scanf ("%d %d\n", &x, &y);
        //printf ("%d %d\n", x, y);
        num_adj[x-1] += 1;
        num_adj[y-1] += 1;
        
    }
    
    //print
    for (int i = 0; i < vertice; i++)
    {
        //printf ("%d ", num_adj[i]);
    }
    
    Dirac (num_adj, vertice, 0);
    return 0;
}
