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

void ler_string(char linha[], int qVertices, int arestas[][qVertices - 1], int pesos[][qVertices - 1],int cont_arestas[], int qArestas, int cont)
{
    char vert, ares, peso;
    int x, y, p;
    if (cont < qArestas)
    {
        scanf ("%c %c", &vert, &ares);  // sempre vai ter os dois primeiros números
        scanf ("%c", &peso);
        
        if (peso == ' ')  // se o escaneado foi um espaço tem mais 1 número
        {
            scanf("%c", &peso);
            getchar();
        }
        else
        {
            peso = '1';  // peso se não tiver mostrando
        }
        
        //Transformando em inteiros
        x = (int)vert - 48;
        y = (int)ares - 48;
        p = (int)peso - 48;

        arestas[x-1][cont_arestas[x-1]] = y;   // x é vertice, y é aresta
        arestas[y-1][cont_arestas[y-1]] = x;

        pesos[x-1][cont_arestas[x-1]] = p; //linha referente à mesma linha da matriz arestas
        pesos[y-1][cont_arestas[y-1]] = p; //coluna referente à mesma coluna da matriz arestas

        cont_arestas[y-1] += 1;
        cont_arestas[x-1] += 1;
        
        ler_string (linha, qVertices, arestas, pesos, cont_arestas, qArestas, cont+1);
    }
    return;
}

int main()
{
    int vert, ares, n = 1, x, y, vert_anterior = 1;
    scanf ("%d %d\n", &vert, &ares);
    int vertices[vert], graus[vert], cont_arestas[vert], arestas[vert][vert-1], pesos[vert][vert-1];
    
    // preencher arestas
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
    ler_string (linha, vert, arestas, pesos, cont_arestas, ares, 0);
    
    //preencher vetor vertices
    for (int i = 0; i < vert; i++)
    {
        vertices[i] = n;
        n++;
        //printf ("%d\n", vertices[i][0]);
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

    printf ("\n");
    
    // printar pesos
    for (int i = 0; i < vert; i++)
    {
        for (int j = 0; j < vert - 1; j++)
        {
            printf("%i ", pesos[i][j]);
        }
        printf ("\n");
    }
    
    /*print
    for (int i = 0; i < vert; i++)
    {
        printf ("%d ", graus[i]);
    }*/
    return 0;
}
