#include <stdio.h>

/*Vvertice	Avertice, vertice-1		Pvertice, vertice-1
1	        2 3 4 6 0	            5 4 2 6 0
2	        1 5 4 0 0	            5 1 7 0 0
3	        1 5 0 0 0	            4 6 0 0 0
4	        1 2 6 0 0	            2 1 1 0 0
5	        2 3 0 0 0	            7 6 0 0 0
6	        1 4 0 0 0	            6 1 0 0 0*/

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

int Clique (int tam, int arestas[][tam-1], int percorridos[], int cont, int qElementos)
{
    int x = 0;
    
    // cada elemento vai verificar se tem ligação com todos os outros
    for (int i = 0; i < qElementos; i++)
    {
        for (int j = 0; j < qElementos; j++)
        {
            // se forem iguais ex.: 1 e 1, eu não verifico pq nao é multigrafo krai
            if (percorridos[i] != percorridos[j])
            {
                // para cada aresta
                for (int k = 0; k < tam-1; k++)
                {
                    // verificar se fazem aresta, se sim eu posso ir pro prox num
                    if (arestas[percorridos[i]-1][k] == percorridos[j])
                    {
                        x = 1;
                        break;
                    }
                }
                
                if (x == 0) // não forma aresta e posso vazar, não é uma clique
                {
                    return 0;
                }
                // reiniciar para cada vertice que verifica
                x = 0;
            }
        }
    }
    
    return qElementos;
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

void removerVetor(int vetor[], int num, int cont)
{
    if (num == vetor[cont])
    {
        vetor[cont] = 0;
        return;
    }
    else
    {
        removerVetor(vetor, num, cont+1);
    }
}

int comp(int qVertices, int arestas[][qVertices-1], int complementar[][qVertices-1], int n_vistos[])
{
    int qtd;
    for (int i = 0; i < qVertices; i++)
    {
        qtd = 0;
        removerVetor(n_vistos, i+1, 0);
        for (int j = 0; j < qVertices-1; j++)
        {
            removerVetor(n_vistos, arestas[i][j], 0);
        }
        
        for (int k = 0; k < qVertices; k++)
        {
            if (n_vistos[k] != 0)
            {
                complementar[i][qtd] = n_vistos[k];
                qtd++;
            }
            n_vistos[k] = k+1;
            //printf("%i ", n_vistos[k]);
        }
    }
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

void caminho(int qVertices, int arestas[][qVertices-1], int pesos[][qVertices-1], int percorridos[], int Maxclique[], int atual, int pTotal, int final, int cont, int *cmax)
{
    int cheio, atualVist;
    
    cheio = total(percorridos, 0, qVertices);
    
    atualVist = procurar(percorridos, atual, 0, qVertices);
    
    //printf("%d %d\n", atual, atualVist);
    //printf("*%d*\n", cont);
    
    if (atual == final && cont != 0)
    {
        int tamanho = 0;
        for (int i = 0; i < qVertices; i++)
        {
            if (percorridos[i] != 0)
            {
                tamanho++;
            }
            //printf ("%d ", percorridos[i]);
        }
        if (tamanho > 2)
        {
            int Mclique = Clique (qVertices, arestas, percorridos, 0, tamanho);
            
            if (Mclique > *cmax)
            {
                for (int i = 0; i < qVertices; i++)
                {
                    Maxclique[i] = percorridos[i];
                }
                *cmax = Mclique;
            }
            //printf ("\n%d", *cmax);
        }
        //printf ("\n");
    }
    
    else if (atual == 0 || cheio == 1 || atualVist == 1) // se o vetor estiver cheio, ou este ja foi visitado retorna
    {
        return;
    }
    else
    {
        adicionarVetor(percorridos, atual, 0);
        
        for (int i = 0; i < qVertices-1; i++)
        {
            caminho(qVertices, arestas, pesos, percorridos, Maxclique, arestas[atual-1][i], pTotal + pesos[atual-1][i], final, cont+1, cmax);
        }
        //Print lindjo
        /*for (int i = 0; i < qVertices; i++)
        {
            printf ("%d ", percorridos[i]);
        }
        printf ("\n");*/
            
        percorridos[cont] = 0; //Zerando vetor se passou por todas as adjacências
        
        /*for (int i = 0; i < qVertices; i++)
        {
            printf ("%d ", percorridos[i]);
        }            
        printf ("\n");*/
        //printf ("SAIU\n");
    }
}

int main()
{
    int vert, ares, x;
    int cmax = 0;
    
    scanf ("%d %d\n", &vert, &ares);
    
    if (ares == 0)
    {
        printf ("Grafo Desconexo\nConjunto Independente: ");
        
        for (int i = 0; i < vert; i++)
        {
            printf ("%d ", i+1);
        }
        return 0;
    }
    
    int graus[vert], percorridos[vert], n_vistos[vert], Maxclique[vert], cont_arestas[vert];
    int complementar[vert][vert-1], arestas[vert][vert-1], pesos[vert][vert-1];
    
    // preencher todos os vetores com 0's
    for (int i = 0; i < vert; i++)
    {
        graus[i] = 0;
        cont_arestas[i] = 0;
        percorridos[i] = 0;
        Maxclique[i] = 0;
        n_vistos[i] = i+1;
        
        for (int j = 0; j < vert - 1; j++)
        {
            arestas[i][j] = 0;
            pesos[i][j] = 0;
            complementar[i][j] = 0;
        }
    }
    
    ler_string (vert, arestas, pesos, graus, cont_arestas, ares, 0);
    
    for (int i = 1; i < vert; i++)
    {
        caminho(vert, arestas, pesos, percorridos, Maxclique, i, 0, i, 0, &cmax);  
    }
    
    // na clique maxima precisa colocar verificando todas as arestas 2 2, 3 3 etc.. colocar num for (num vert)

    if (cmax == 0)
    {
        for (int i = 0; i < vert; i++)
        {
            for (int j = 0; j < vert-1; j++)
            {
                if (arestas[i][j] != 0)
                {
                    printf ("Tamanho da Clique Maxima: 2\nClique: %i %i", i+1, arestas[i][j]);
                    return 0;
                }
            }
        }
    }
    
    printf ("Tamanho da Clique Maxima: %d\nClique: ", cmax);
    
    for (int i = 0; i < vert; i++)
    {
        if (Maxclique[i] != 0)  printf ("%d ", Maxclique[i]);
    }
    
    // COMPLEMENTAR
    comp(vert, arestas, complementar, n_vistos);
    
    printf("\nComplementar:\n");
    for (int i = 0; i < vert; i++)
    {
        for (int j = 0; j < vert-1; j++)
        {
            printf("%i ", complementar[i][j]);
        }
        printf("\n");
    }
    
    cmax = 0;
    for (int i = 1; i < vert; i++)
    {
        caminho(vert, complementar, pesos, percorridos, Maxclique, i, 0, i, 0, &cmax);  
    }
    
    // clique maxima do complementar:
    if (cmax == 0)
    {
        printf("Nao possui conjunto independente");
        return 0;
    }
    printf ("Tamanho do conjunto independente maximo: %d\nConjunto: ", cmax);
    
    for (int i = 0; i < vert; i++)
    {
        if (Maxclique[i] != 0)  printf ("%d ", Maxclique[i]);
    }
    
    return 0;
}
