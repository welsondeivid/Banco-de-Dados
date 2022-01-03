/*Vvertice	Avertice, vertice-1		Pvertice, vertice-1
1	2 3 4 6 0	5 6 7 1 0
2	1 5 4 0 0	x x x x x
3	1 5 0 0 0	x x x x x
4	1 2 6 0 0	x x x x x
5	2 3 0 0 0	x x x x x
6	1 4 0 0 0	x x x x x*/

#include <stdio.h>

int main()
{
    int vertice, aresta, n = 1, x, y;
    scanf ("%d %d", &vertice, &aresta);
    int vertices[vertice], graus[vertice], arestas[vertice][vertice-1], pesos[vertice][vertice-1];
    
    //preencher graus com 0's
    for (int i = 0; i < vertice; i++)
    {
        graus[i] = 0;
    }
    
    //preencher vetor vertices
    for (int i = 0; i < vertice; i++)
    {
        vertices[i] = n;
        n++;
        //printf ("%d\n", vertices[i][0]);
    }
    
    //preencher graus de cada vértice
    for (int i = 0; i < aresta; i++)
    {
        scanf ("%d %d\n", &x, &y);
        //printf ("%d %d\n", x, y);
        graus[x-1] += 1;
        graus[y-1] += 1;
    }
    
    //print
    for (int i = 0; i < vertice; i++)
    {
        printf ("%d ", graus[i]);
    }
    return 0;
}
