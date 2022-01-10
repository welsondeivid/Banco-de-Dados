#include <stdio.h>

/*Vvertice	Avertice, vertice-1		Pvertice, vertice-1
1	        2 3 4 6 0	            5 4 2 6 0
2	        1 5 4 0 0	            5 1 7 0 0
3	        1 5 0 0 0	            4 6 0 0 0
4	        1 2 6 0 0	            2 1 1 0 0
5	        2 3 0 0 0	            7 6 0 0 0
6	        1 4 0 0 0	            6 1 0 0 0*/

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

void caminho(int qVert, int arestas[][qVert-1], int pesos[][qVert-1], int percorridos[], int mcaminho[], int atual, int final, int pTotal, int cont, int *ccusto)
{
    int cheio, atualVist;
    
    cheio = Vet_Cheio(percorridos, 0, qVert); //Verifica se já passamos por todos os vértices
    atualVist = procurar(percorridos, atual, 0, qVert); //Verifica se já passamos pelo vértice atual
    
    if (cheio == 1 && atual == final)
    {
        if (*ccusto == 0 || *ccusto > pTotal)
        {
            *ccusto = pTotal;
            
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
        
        //Percorre as adjacências
        for (int i = 0; i < qVert-1; i++)
        {
            caminho(qVert, arestas, pesos, percorridos, mcaminho, arestas[atual-1][i], final, pTotal + pesos[atual-1][i], cont+1, ccusto);
        }
        //Print percorridos aqui
        
        percorridos[cont] = 0; //Zerando vetor se passou por todas as adjacências
        
        //E aqui
    }
}

int Euler (int graus[], int cont, int tam) //Aplica Lema de Euler
{
    if (cont == tam)    return 1;
    
    else
    {
        if (graus[cont] % 2 != 0)   return 0;
        
        else    return Euler (graus, cont+1, tam);
    }
}

int Dirac (int graus[], int cont, int tam)// Aplica Teorema de Dirac
{
    if (cont == tam)    return 1;
    
    else
    {
        if ((float)graus[cont] < (tam/2.0)) return 0;
        
        else    return Dirac (graus, cont+1, tam);
    }
}

int main()
{
    int qVert, qArest, ccusto = 0;
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
    
    int D = Dirac (graus, 0, qVert);
    
    caminho(qVert, arestas, pesos, percorridos, mcaminho, 1, 1, 0, 0, &ccusto);
    
    int euleriano = Euler(graus, 0, qVert);
    
    if (euleriano == 1) printf ("Grafo Euleriano\n");
    
    else    printf ("Grafo nao Euleriano\n");
    
    if (D == 1) // Se o teorema funcionar, já sabemos que hamiltoniano
    {
        printf ("Grafo Hamiltoniano (pelo teorema de Dirac)\n");
        return 0;
    }
    
    //Se o teorema falhar, ainda checamos já que o teorema não é sse
    if (ccusto != 0)
    {
        printf ("Grafo Hamiltoniano\n");
        printf ("Exemplo de ciclo: ");
        
        for (int i = 0; i < qVert; i++)
        {
            printf ("%d ", mcaminho[i]);
        }
        printf ("1\nCusto: %d\n", ccusto);
    }
    else    printf ("Grafo nao Hamiltoniano\n");
    
    return 0;
}
