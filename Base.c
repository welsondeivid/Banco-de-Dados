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
    int vert, ares, n = 1, x, y, vert_anterior = 1;
    scanf ("%d %d", &vert, &ares);
    int vertices[vert], graus[vert], cont_arestas[vert], arestas[vert][vert-1], pesos[vert][vert-1];
    
    //preencher graus com 0's
    for (int i = 0; i < vert; i++)
    {
        graus[i] = 0;
        cont_arestas[i] = 0;
    }
    
    //preencher vetor vertices
    for (int i = 0; i < vert; i++)
    {
        vertices[i] = n;
        n++;
        //printf ("%d\n", vertices[i][0]);
    }

    for (int i = 0; i < vert; i++)
    {
        for (int j = 0; j < vert - 1; j++)
        {
            arestas[i][j] = 0;
        }
    }
    
    //preencher graus de cada vértice e a matriz arestas
    for (int i = 0; i < ares; i++)
    {
        scanf ("%d %d\n", &x, &y);
        //printf ("%d %d\n", x, y);
        graus[x-1] += 1;
        graus[y-1] += 1;
        
        arestas[x-1][cont_arestas[x-1]] = y;
        arestas[y-1][cont_arestas[y-1]] = x;
        
        cont_arestas[y-1] += 1;
        cont_arestas[x-1] += 1;
    }

    // printar arestas
    for (int i = 0; i < vert; i++)
    {
        for (int j = 0; j < vert - 1; j++)
        {
            printf("%i ", arestas[i][j]);
        }
        printf ("\n");
    }
    
    //print
    for (int i = 0; i < vert; i++)
    {
        printf ("%d ", graus[i]);
    }
    return 0;
}
