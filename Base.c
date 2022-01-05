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

void ler_string(int qVertices, int arestas[][qVertices - 1], int pesos[][qVertices - 1], int graus[], int cont_arestas[], int qArestas, int cont)
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
        
        ler_string (qVertices, arestas, pesos, graus, cont_arestas, qArestas, cont+1);
    }
    return;
}

int total(int percorridos[], int contador, int tamanho)
{
    if (contador == tamanho)
    {
        return 1;
    }
    else
    {
        if (percorridos[contador] == 0)
        {
            return 0;
        }
        return total(percorridos, contador + 1, tamanho);
    }
}

int procurar(int percorridos[], int num, int contador, int tamanho)
{
    if (contador == tamanho)
    {
        return 0;
    }
    else
    {
        if (num == percorridos[contador])
        {
            return 1;
        }
        else
        {
            return procurar(percorridos, num, contador + 1, tamanho);
        }
    }
}

void adicionarVetor(int percorridos[], int num, int contador)
{
    if (percorridos[contador] == 0)
    {
        percorridos[contador] = num;
    }
    else
    {
        adicionarVetor(percorridos, num, contador + 1);
    }
}

void caminho(int qVertices, int arestas[][qVertices-1], int pesos[][qVertices-1], int percorridos[], int mcaminho[], int atual, int pTotal, int final, int cont, int *mcusto)
{
    int cheio, adjVist, atualVist;
    
    cheio = total(percorridos, 0, qVertices);
    atualVist = procurar(percorridos, atual, 0, qVertices);
    
    printf("%d %d\n", atual, atualVist);
    //printf("*%d*\n", cont);
    
    if (atual == final)
    {
        printf("(%d)\n", pTotal); // Custo total
        
        if (*mcusto == 0 || *mcusto > pTotal)
        {
            *mcusto = pTotal;
            
            for (int i = 0; i < qVertices; i++)
            {
                mcaminho[i] = percorridos[i];
            }
        }
        
        //Caminho da vitória
        /*printf ("vetor:");
        for (int i = 0; i < 6; i++)
        {
            printf ("%d ", percorridos[i]);
        }
        printf ("\n");*/
        
        return;
    }
    
    if (atual == 0 || cheio == 1 || atualVist == 1) // se o vetor estiver cheio, ou este ja foi visitado retorna
    {
        return;
    }
    else
    {
        adicionarVetor(percorridos, atual, 0);
        
        
        for (int i = 0; i < qVertices-1; i++)
        {
            //adjVist = procurar(percorridos, arestas[atual-1][i], 0, qVertices);
            //printf("%i\n", adjVist);
            
            caminho(qVertices, arestas, pesos, percorridos, mcaminho, arestas[atual-1][i], pTotal + pesos[atual-1][i], final, cont+1, mcusto);
            
            /*if (adjVist == 0)
            {
                caminho(qVertices, arestas, pesos, percorridos, arestas[atual-1][i], pTotal + pesos[atual-1][i], final);
            }*/
        }
        //Print lindjo
        /*for (int i = 0; i < 6; i++)
        {
            printf ("%d ", percorridos[i]);
        }
        printf ("\n");*/
            
        percorridos[cont] = 0; //Zerando vetor se passou por todas as adjacências
        
        /*for (int i = 0; i < 6; i++)
        {
            printf ("%d ", percorridos[i]);
        }            
        printf ("\n");*/
        printf ("SAIU\n");
    }
}

int main()
{
    int vert, ares, n = 1, x, y, inicio, fim;
    int mcusto = 0;
    
    scanf ("%d %d\n", &vert, &ares);
    int vertices[vert], graus[vert], percorridos[vert], cont_arestas[vert], arestas[vert][vert-1], pesos[vert][vert-1], mcaminho[vert];
    
    // preencher todos os vetores com 0's
    for (int i = 0; i < vert; i++)
    {
        graus[i] = 0;
        cont_arestas[i] = 0;
        percorridos[i] = 0;
        mcaminho[i] = 0;
        
        for (int j = 0; j < vert - 1; j++)
        {
            arestas[i][j] = 0;
            pesos[i][j] = 0;
        }
    }
    
    ler_string (vert, arestas, pesos, graus, cont_arestas, ares, 0);
    
    scanf ("%d %d", &inicio, &fim);
    
    if (inicio > vert || inicio < 0)
    {
        printf ("Erro 404: Vertice inicial nao pertence ao grafo");
        return 0;
    }
    
    caminho(vert, arestas, pesos, percorridos, mcaminho, inicio, 0, fim, 0, &mcusto);
    
    if (mcusto == 0)
    {
        printf ("\nDistancia infinita ou vertice(s) nao pertence(m) ao grafo");
        return 0;
    }
    
    printf ("\nMenor custo = %d\nMenor caminho: ", mcusto);
    for (int i = 0; i < vert; i++)
    {
        if (mcaminho[i] != 0) printf ("%d ", mcaminho[i]);
    }
    
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
    
    return 0;
}
