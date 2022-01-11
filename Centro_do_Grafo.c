#include <stdio.h>

void Grafo (int qVert, int arestas[][qVert - 1], int pesos[][qVert - 1], int graus[], int cont_arestas[], int qArest, int cont)
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
        
        graus[vert-1] += 1;
        graus[ares-1] += 1;
        
        cont_arestas[ares-1] += 1;
        cont_arestas[vert-1] += 1;
        
        Grafo (qVert, arestas, pesos, graus, cont_arestas, qArest, cont+1);
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

void caminho(int qVertices, int arestas[][qVertices-1], int pesos[][qVertices-1], int percorridos[], int atual, int final, int pTotal, int cont, int *mcusto)
{
    int cheio, atualVist;
    
    cheio = Vet_Cheio(percorridos, 0, qVertices);
    atualVist = procurar(percorridos, atual, 0, qVertices);
    
    if (atual == final)
    {
        // cont diz a quantidade de vertices (a excentricidade é o dada pelo nº de vertices)
        if (*mcusto == 0 || *mcusto > cont)
        {
            *mcusto = cont;
        }
        return;
    }
    
    // Se não existir aresta, se o vetor estiver cheio, ou este ja foi visitado, retorna
    if (atual == 0 || cheio == 1 || atualVist == 1) return;
    
    else
    {
        adicionarVetor(percorridos, atual, 0);
        
        for (int i = 0; i < qVertices-1; i++)
        {
            caminho(qVertices, arestas, pesos, percorridos, arestas[atual-1][i], final, pTotal + pesos[atual-1][i], cont+1, mcusto);
        }
        percorridos[cont] = 0; //Zerando vetor se passou por todas as adjacências
    }
}

int main()
{
    int qVert, qArest, Mdist = 0, mExc = 0, mcusto = 0;
    
    scanf ("%d %d\n", &qVert, &qArest);
    int graus[qVert], percorridos[qVert], cont_arestas[qVert], excentricidade[qVert];
    int arestas[qVert][qVert-1], pesos[qVert][qVert-1];
    
    // preencher todos os vetores com 0's
    for (int i = 0; i < qVert; i++)
    {
        graus[i] = 0;
        cont_arestas[i] = 0;
        percorridos[i] = 0;
        
        for (int j = 0; j < qVert-1; j++)
        {
            arestas[i][j] = 0;
            pesos[i][j] = 0;
        }
    }
    
    Grafo (qVert, arestas, pesos, graus, cont_arestas, qArest, 0);

    for (int i = 1; i <= qVert; i++)
    {
        for (int j = 1; j <= qVert; j++)
        {
            if (i != j) // 1 com 1, 2 com 2, ..., i com i não tem aresta
            {
                // reset
                mcusto = 0;
                
                caminho(qVert, arestas, pesos, percorridos, i, j, 0, 0, &mcusto);
                
                // qual for a adjacente mais longe eu fico guardando
                if (mcusto > Mdist) Mdist = mcusto;
            }
        }
        // depois que passar por todos os vértices adjacentes a i e verificar a distância pro vértice mais longe
        // guardamos esse valor
        excentricidade[i-1] = Mdist;
        
        // na primeira interação ou quando achar uma menor guardo para facilitar achar o centro
        if (mExc == 0 || excentricidade[i-1] < mExc)    mExc = excentricidade[i-1];
        
        // reset
        Mdist = 0;
    }
    
    printf("Centro do Grafo: ");
    for (int i = 0; i < qVert; i++)
    {
        if (mExc == excentricidade[i])  printf("%i ", i+1);
    }
    
    return 0;
}
