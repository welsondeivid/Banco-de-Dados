#include <stdio.h>

void Grafo (int qVert, int arestas[][qVert - 1], int cont_arestas[], int qArest, int cont)
{
    int vert, ares;
    char c;
    
    if (cont < qArest)
    {
        scanf ("%d %d", &vert, &ares);  // sempre vai ter os dois primeiros números
        scanf ("%c", &c); //caractere de teste
        
        if (c == ' ')  // se o escaneado foi um espaço tem mais 1 número
        {
            getchar();
        }

        arestas[vert-1][cont_arestas[vert-1]] = ares;
        arestas[ares-1][cont_arestas[ares-1]] = vert;
        
        cont_arestas[ares-1] += 1;
        cont_arestas[vert-1] += 1;
        
        Grafo (qVert, arestas, cont_arestas, qArest, cont+1);
    }
    return;
}

int Vet_Cheio(int percorridos[], int contador, int tamanho)
{
    if (contador == tamanho)    return 1;
    
    else
    {
        if (percorridos[contador] == 0) return 0;
        
        else    return Vet_Cheio(percorridos, contador + 1, tamanho);
    }
}

int procurar(int percorridos[], int num, int contador, int tamanho)
{
    if (contador == tamanho)    return 0;
    
    else
    {
        if (num == percorridos[contador])   return 1;
        
        else    return procurar(percorridos, num, contador + 1, tamanho);
    }
}

void adicionarVetor(int percorridos[], int num, int contador)
{
    if (percorridos[contador] == 0) percorridos[contador] = num;
    
    else    adicionarVetor(percorridos, num, contador + 1);
}

void removerVetor(int vetor[], int num, int cont)
{
    if (num == vetor[cont])
    {
        vetor[cont] = 0;
        return;
    }
    else    removerVetor(vetor, num, cont+1);
}

int comp(int qVertices, int arestas[][qVertices-1], int complementar[][qVertices-1], int n_vistos[])
{
    // qtd de arestas, pq quero adicionar na coluna 0 da aresta se puder
    int qtd;
    for (int i = 0; i < qVertices; i++)
    {
        qtd = 0;
        // passei pelo i
        removerVetor(n_vistos, i+1, 0);
        
        for (int j = 0; j < qVertices-1; j++)
        {
            // passei pela aresta (j) do i
            removerVetor(n_vistos, arestas[i][j], 0);
        }
        
        for (int k = 0; k < qVertices; k++)
        {
            if (n_vistos[k] != 0)
            {
                // o que não foi contemplado no grafo vai participar do complementar
                complementar[i][qtd] = n_vistos[k];
                qtd++;
            }
            // preencher o vetor com todos os vértices
            n_vistos[k] = k+1;
        }
    }
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
                    // percorridos[i] - 1 (o 1 está na posição 0) e vai verificar todas as arestas k dele
                    if (arestas[percorridos[i]-1][k] == percorridos[j])
                    {
                        // se formou aresta não preciso ver o resto
                        x = 1;
                        break;
                    }
                }
                
                // não forma aresta e posso vazar, não é uma clique
                if (x == 0) return 0;
                
                // reiniciar para cada vertice que verifica
                x = 0;
            }
        }
    }
    
    return qElementos;
}

void caminho(int qVertices, int arestas[][qVertices-1], int percorridos[], int Maxclique[], int atual, int final, int cont, int *cmax)
{
    int cheio, atualVist;
    
    cheio = Vet_Cheio(percorridos, 0, qVertices);
    atualVist = procurar(percorridos, atual, 0, qVertices);
    
    // cont != 0, pois na primeira interação como a clique é um ciclo atual == final
    if (atual == final && cont != 0)
    {
        int tamanho = 0;
        for (int i = 0; i < qVertices; i++)
        {
            if (percorridos[i] != 0)
            {
                tamanho++;
            }
        }
        // nao consideramos uma clique de 2, fazemos um caso especial para isso na main()
        if (tamanho > 2)
        {
            int Mclique = Clique (qVertices, arestas, percorridos, 0, tamanho);
            
            // se for maior ela vai tomar o lugar da anterior
            if (Mclique > *cmax)
            {
                for (int i = 0; i < qVertices; i++)
                {
                    Maxclique[i] = percorridos[i];
                }
                *cmax = Mclique;
            }
        }
    }
    
    // se a aresta não existir, se o vetor estiver cheio, ou este ja foi visitado, retorna
    // else if porque mesmo achando uma clique ela pode ser maior ainda
    else if (atual == 0 || cheio == 1 || atualVist == 1)    return;
    else
    {
        adicionarVetor(percorridos, atual, 0);
        
        for (int i = 0; i < qVertices-1; i++)
        {
            caminho(qVertices, arestas, percorridos, Maxclique, arestas[atual-1][i], final, cont+1, cmax);
        }
        
        percorridos[cont] = 0; //Zerando vetor se passou por todas as adjacências
    }
}

int main()
{
    int qVert, qArest, x, cmax = 0, verificador = 0;
    
    scanf ("%d %d\n", &qVert, &qArest);
    
    if (qArest == 0)
    {
        printf ("Grafo Totalmente Desconexo\nConjunto Independente: ");
        
        for (int i = 0; i < qVert; i++)
        {
            printf ("%d ", i+1);
        }
        return 0;
    }
    
    int percorridos[qVert], n_vistos[qVert], Maxclique[qVert], cont_arestas[qVert];
    int complementar[qVert][qVert-1], arestas[qVert][qVert-1];
    
    // preencher todos os vetores com 0's
    for (int i = 0; i < qVert; i++)
    {
        cont_arestas[i] = 0;
        percorridos[i] = 0;
        Maxclique[i] = 0;
        n_vistos[i] = i+1;
        
        for (int j = 0; j < qVert - 1; j++)
        {
            arestas[i][j] = 0;
            complementar[i][j] = 0;
        }
    }
    
    Grafo (qVert, arestas, cont_arestas, qArest, 0);
    
    // não vai verificar o ultimo vertice, se o ultimo vertice participar de uma clique ele vai identificar em
    // outro vertice menor que ele
    for (int i = 1; i <= qVert; i++)
    {
        caminho(qVert, arestas, percorridos, Maxclique, i, i, 0, &cmax);
    }
    
    // na clique maxima precisa colocar verificando todas as arestas 2 2, 3 3 etc.. colocar num for (num vert)
    
    if (cmax == 0)
    {
        for (int i = 0; i < qVert; i++)
        {
            for (int j = 0; j < qVert-1; j++)
            {
                if (arestas[i][j] != 0)
                {
                    printf ("Tamanho da Clique Maxima: 2\nClique: %i %i\n", i+1, arestas[i][j]);
                    verificador = 1;
                    break;
                }
            }
            if (verificador == 1)
            {
                break;
            }
        }
    }
    
    if (verificador == 0)
    {
        if (cmax == 0)
        {
            printf ("Tamanho da Clique Maxima: 0");
        }
        else
        {
            printf ("Tamanho da Clique Maxima: %d\nClique: ", cmax);
    
            for (int i = 0; i < qVert; i++)
            {
                if (Maxclique[i] != 0)  printf ("%d ", Maxclique[i]);
            }
            printf("\n");
        }
    }
    
    // COMPLEMENTAR
    comp(qVert, arestas, complementar, n_vistos);
    
    /*printf("\nComplementar:\n");
    for (int i = 0; i < qVert; i++)
    {
        for (int j = 0; j < qVert-1; j++)
        {
            printf("%i ", complementar[i][j]);
        }
        printf("\n");
    }
    */
    
    cmax = 0;
    for (int i = 1; i <= qVert; i++)
    {
        caminho(qVert, complementar, percorridos, Maxclique, i, i, 0, &cmax);  
    }
    
    // clique maxima do complementar:
    if (cmax == 0)
    {
        for (int i = 0; i < qVert; i++)
        {
            for (int j = 0; j < qVert-1; j++)
            {
                if (complementar[i][j] != 0)
                {
                    printf ("Tamanho do conjunto independente Maximo: 2\nConjunto: %i %i\n", i+1, complementar[i][j]);
                    return 0;
                }
            }
        }
        
        printf ("Nao possui conjunto independente");
        return 0;
    }
    printf ("Tamanho do conjunto independente maximo: %d\nConjunto: ", cmax);
    
    for (int i = 0; i < qVert; i++)
    {
        if (Maxclique[i] != 0)  printf ("%d ", Maxclique[i]);
    }
    
    return 0;
}
