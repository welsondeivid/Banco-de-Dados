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

void caminho(int qVert, int arestas[][qVert-1], int pesos[][qVert-1], int percorridos[], int mcaminho[], int atual, int final, int pTotal, int cont, int *mcusto)
{
    int cheio, atualVist;
    
    cheio = Vet_Cheio(percorridos, 0, qVert); // Verifica se o vetor está cheio, ou seja, passou por todos os vértices
    atualVist = procurar(percorridos, atual, 0, qVert); // Verifica se já visitou o vértice atual
    
    //Procuramos pelo menor custo e salvamos o caminho correspondente
    if (atual == final)
    {
        if (*mcusto == 0 || *mcusto > pTotal)
        {
            *mcusto = pTotal;
            
            for (int i = 0; i < qVert; i++)
            {
                mcaminho[i] = percorridos[i];
            }
        }
        return;
    }
    
    // Se a aresta não existir, o vetor estiver cheio ou este ja foi visitado: retorna
    if (atual == 0 || cheio == 1 || atualVist == 1) return;
    
    else
    {
        adicionarVetor(percorridos, atual, 0);
        
        //Anda nas adjacências
        for (int i = 0; i < qVert-1; i++)
        {
            caminho(qVert, arestas, pesos, percorridos, mcaminho, arestas[atual-1][i], final, pTotal + pesos[atual-1][i], cont+1, mcusto);
        }
        
        percorridos[cont] = 0; //Zerando vetor se passou por todas as adjacências
    }
}

int main()
{
    int qVert, qArest, inicio, fim, mcusto = 0;
    scanf ("%d %d\n", &qVert, &qArest);
    
    int graus[qVert], percorridos[qVert], cont_arestas[qVert], mcaminho[qVert];
    int arestas[qVert][qVert-1], pesos[qVert][qVert-1];
    
    // preencher todos os vetores com 0's
    for (int i = 0; i < qVert; i++)
    {
        graus[i] = 0;
        cont_arestas[i] = 0;
        percorridos[i] = 0;
        
        for (int j = 0; j < qVert - 1; j++)
        {
            arestas[i][j] = 0;
            pesos[i][j] = 0;
        }
    }
    
    Grafo (qVert, arestas, pesos, graus, cont_arestas, qArest, 0);
    
    scanf ("%d %d", &inicio, &fim);
    if (inicio > qVert || inicio < 0 || fim > qVert || fim < 0)
    {
        printf ("Erro 404: Vertice(s) lido(s) nao pertence(m) ao grafo");
        return 0;
    }
    
    caminho(qVert, arestas, pesos, percorridos, mcaminho, inicio, fim, 0, 0, &mcusto);
    
    if (mcusto == 0)
    {
        printf ("Distancia infinita");
        return 0;
    }
    
    printf ("Menor custo = %d\nMenor caminho: ", mcusto);
    for (int i = 0; i < qVert; i++)
    {
        if (mcaminho[i] != 0) printf ("%d ", mcaminho[i]);
    }
    printf ("%d\n", fim);
    
    return 0;
}
