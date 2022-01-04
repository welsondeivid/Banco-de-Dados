#include <stdio.h>

/*Vvertice	Avertice, vertice-1		Pvertice, vertice-1
1	2 3 4 6 0	5 4 2 6 0
2	1 5 4 0 0	5 1 7 0 0
3	1 5 0 0 0	4 6 0 0 0
4	1 2 6 0 0	2 1 1 0 0
5	2 3 0 0 0	7 6 0 0 0
6	1 4 0 0 0	6 1 0 0 0*/

// a linha 0 contém na matriz de arestas os números ligados ao 1, e na matriz de pesos o peso referente a cada aresta
// aresta[i][j] -> peso[i][j]

void Dirac (int graus[], int vert, int cont)
{
    if (cont == vert)
    {
        printf ("Grafo Hamiltoniano");
        return;
    }
    
    if (graus[cont] < vert/2)
    {
        printf ("Grafo não-Hamiltoniano");
        return;
    }
    else
    {
        Dirac (graus, vert, cont+1);
    }
}

void ler_string(char linha[], int qVertices, int arestas[][qVertices - 1], int pesos[][qVertices - 1], int graus[], int cont_arestas[], int qArestas, int cont)
{
    int vert, ares, peso;
    char c;
    
    if (cont < qArestas)
    {
        scanf ("%d %d", &vert, &ares);  // sempre vai ter os dois primeiros números
        scanf ("%c", &c);
        
        if (c == ' ')  // se o escaneado foi um espaço tem mais 1 número
        {
            scanf("%d", &peso);
        }
        else
        {
            peso = 1;  // peso se não tiver mostrando
        }

        arestas[vert-1][cont_arestas[vert-1]] = ares;
        arestas[ares-1][cont_arestas[ares-1]] = vert;

        pesos[vert-1][cont_arestas[vert-1]] = peso; //linha referente à mesma linha da matriz arestas
        pesos[ares-1][cont_arestas[ares-1]] = peso; //coluna referente à mesma coluna da matriz arestas
        
        graus[vert-1] += 1;
        graus[ares-1] += 1;
        
        cont_arestas[ares-1] += 1;
        cont_arestas[vert-1] += 1;
        
        ler_string (linha, qVertices, arestas, pesos, graus, cont_arestas, qArestas, cont+1);
    }
    return;
}

int main()
{
    int vert, ares, n = 1, x, y, vert_anterior = 1;
    scanf ("%d %d\n", &vert, &ares);
    int vertices[vert], graus[vert], cont_arestas[vert], arestas[vert][vert-1], pesos[vert][vert-1];
    
    // preencher arestas e pesos com 0's
    for (int i = 0; i < vert; i++)
    {
        for (int j = 0; j < vert - 1; j++)
        {
            arestas[i][j] = 0;
            pesos[i][j] = 0;
        }
    }

    //preencher graus com 0's
    for (int i = 0; i < vert; i++)
    {
        graus[i] = 0;
        cont_arestas[i] = 0;
    }

    char linha[3];
    ler_string (linha, vert, arestas, pesos, graus, cont_arestas, ares, 0);
    
    //preencher vetor vertices
    for (int i = 0; i < vert; i++)
    {
        vertices[i] = n;
        n++;
        //printf ("%d\n", vertices[i][0]);
    }

    // printar arestas
    /*for (int i = 0; i < vert; i++)
    {
        for (int j = 0; j < vert - 1; j++)
        {
            printf("%i ", arestas[i][j]);
        }
        printf ("\n");
    }
    printf ("\n");*/
    
    // printar pesos
    /*for (int i = 0; i < vert; i++)
    {
        for (int j = 0; j < vert - 1; j++)
        {
            printf("%i ", pesos[i][j]);
        }
        printf ("\n");
    }
    printf ("\n");*/
    
    //printar graus
    /*for (int i = 0; i < vert; i++)
    {
        printf ("%d ", graus[i]);
    }*/
    
    Dirac (graus, vert, 0);
    return 0;
}
