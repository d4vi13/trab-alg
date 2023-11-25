#include "ordenacao.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void getNome(char nome[]) {
    // substitua por seu nome
    strncpy(nome, "Davi Campos Ribeiro", MAX_CHAR);
    // adicionada terminação manual para caso de overflow
    nome[MAX_CHAR - 1] = '\0';
}

void getNomeAlgoritmoExtra(char nomeAlg[]) {
    // substitua pelo nome do algoritmo que você escolheu
    strncpy(nomeAlg, "IntroSort", MAX_CHAR);
    nomeAlg[MAX_CHAR - 1] = '\0';
}

// a função a seguir deve retornar o seu número de GRR
unsigned int getGRR() { return 20232378; }

/*-------------FUNÇÕES UTILITÁRIAS-------------*/

void imprimeVetor(int vetor[],int tam){
    for(int i = 0; i < tam; i++)
        printf("%d ",vetor[i]);
    printf("\n");
    return;
}

// copia elementos do vetor2 para o vetor1, ambos de tamanho tam 
void copiaVetor(int vetor1[],int vetor2[],int tam){
    for (int i = 0; i < tam; i++)
        vetor1[i] = vetor2[i];
    return;
}

/*--------------------------------------------*/

/*-------------FUNÇÕES AUXILIARES-------------*/


void swap(int v[], int a, int b){
    int aux = v[b];
    v[b] = v[a];
    v[a] = aux;
}
// busca a posição onde deveria estar o elemnento
int buscaPosBinaria(int vetor[], int tam, int valor, long* numComparacoes){
    //caso base vetor unitario, retorna -1 caso valor < vetor[0]
    if (tam <= 1){
	    (*numComparacoes)++;
        return vetor[0] <=  valor ? 0 : -1;
    }
    
    int metade = tam/2;

    (*numComparacoes)++;
    // chamadas recursivas  
	if (valor < vetor[metade])
		return buscaPosBinaria(vetor, metade, valor, numComparacoes);
	return metade  + buscaPosBinaria(vetor+metade, tam-metade, valor, numComparacoes);
}



// merge um vetor dividido em duas metades ordenadas
unsigned long merge(int vetor[],int n,int m){
    int i = 0, j = m;
    unsigned long k = 0;
    int* vetorAux;
    vetorAux = (int*) malloc(n*sizeof(int));
    if (vetorAux == NULL){
        printf("Nao foi possivel alocar o vetor!\n");
        return 0;
    }

    while (k < n){
        //insere em vetorAux o menor dos elementos entre v[i] e v[j]
        if (j  >= n  || (i < m && vetor[i] < vetor[j])){
            vetorAux[k] = vetor[i];
            i++;
        }else{
            vetorAux[k] = vetor[j];
            j++;
        }
        k++;
    }
    
    //Coloca vetor mergido no vetor original
    copiaVetor(vetor,vetorAux,n);
    free(vetorAux);
    return k;
}

unsigned long mergeSort(int vetor[], int tam) {
    if (tam <= 1)
        return 0;

    int n = tam/2;
    
    return mergeSort(vetor,n) + mergeSort(vetor+n,tam-n) + merge(vetor,tam,n);
}

// bota elementos maior que o ultimo a direita dele, e os menores a esquerda dele
int particionar(int vetor[], int tam, unsigned long* numComparacoes){
    int m = 0;
    for(int i = 0; i < tam-1; i++){
        (*numComparacoes)++;
        if (vetor[i] <= vetor[tam-1]){
            swap(vetor, m,i);
            m++;
        }
    }
    swap(vetor,tam-1, m);
    return m;
}


unsigned long quickSort(int vetor[], int tam) {
    if (tam <= 1)
        return 0;
    unsigned long comparacoes;
    int m = particionar(vetor,tam,&comparacoes);
    return quickSort(vetor,m) + quickSort(vetor+m,tam-m) + m;

}


int esquerda(int i){
    return 2*i + 1;
}

int direita(int i){
    return 2*(i+1);
}

void maxHeapify(int h[], int i, int n,unsigned long* numComparacoes){
    int l,r,maior;
    l = esquerda(i);
    r = direita(i);

    if (l < n && h[l] > h [i])
        maior = l;
    else
        maior = i;
    if (r < n && h[r] > h[maior])
        maior = r;
    *numComparacoes += 2;
    
    if (maior != i){
        swap(h,i,maior);
        maxHeapify(h,maior,n,numComparacoes);
    }
}

void maxHeap(int h[], int n, unsigned long* numComparacoes){
    for (int i = (n-1)/2; i >= 0 ; i--)
        maxHeapify(h,i,n,numComparacoes);
}

unsigned long heapSort(int vetor[], int tam) {
    unsigned long comp = 0;
    maxHeap(vetor,tam,&comp);
    for (int i = tam-1; i >= 1; i--){
        swap(vetor, 0,i);
        maxHeapify(vetor,0,i,&comp);
    }
    return comp;
}

void countingSort(unsigned int vetor[], int tam, int maxVal) {
    int *r, *c, i;
    r = (int*)malloc(tam*sizeof(int));
    c = (int*)calloc(maxVal+1, sizeof(int));


    for(i = 0; i < tam; i++)
        c[vetor[i]] = c[vetor[i]] + 1;

    for(i = 1; i <= maxVal; i++)
        c[i] += c[i-1];

    for (i = tam-1; i >= 0; i--){
        r[c[vetor[i]]-1] = vetor[i];
        c[vetor[i]]--;
    }

    copiaVetor(vetor,r,tam);
    free(r);
    free(c);
    return;
}

// inseri um elemento na posição correta
long insert(int vetor[],int tam){
	long comparacoes = 0;
    
    //acha onde deve ser inserido o elemento
	int p = buscaPosBinaria(vetor,tam-1,vetor[tam-1],&comparacoes);
    
    // faz as trocas dos elementos para colocar o elemento na poisção p
	for (int i = tam-1; i > p+1 ; i--)
		swap(vetor,i,i-1);
	return comparacoes;
}

//insertion sort para ser usado no Tim Sort
long insertionSort(int vetor[], int tam){	
	if (tam < 1)
		return 0;
	return insertionSort(vetor,tam-1) + insert(vetor,tam); 
}



//Algoritimo escolhido foi o Tim Sort
unsigned long algoritmoExtra(int vetor[], int tam) {
    
    //calcular tamanho das runs
    int i,meio,final,runSize = pow(2,5);
    unsigned long comp = 0;
    //ordena runs usando insertion sort
    for (i = 0; i < tam; i+=runSize)
        comp += insertionSort(vetor+i,(runSize < tam-i)? runSize : tam-i); 

    //merge as run ordenadas anteriormente
    for (i = runSize; i < tam ; i = 2*i){
        for (int j = 0; j < tam; j +=2*i){
            meio =  i;
            final = j + 2*i - 1;
            final = (final < tam - 1) ? final : tam-1;
            comp += merge(vetor+j,final-j+1,meio);
        }
    }
    return comp;
}

void preencherAleatorio(int vet[], int numPos, int maxVal){
	int i;
	srand(time(0));
    for(i = 0; i < numPos; i++)
		vet[i] = rand()%maxVal;
}

#define RANGE 30

int main(){

    unsigned long comp = 0;
    int N = pow(2,28);
    clock_t start, end;//variáveis do tipo clock_t
    double total;
    int* vetor;

    printf("nome,tam,temp,comp\n");
    while(N){

        //printf("Tamanho: %d\n",N);  
        vetor = malloc(N*sizeof(int));

        srand(time(0));
        
        comp = 0;
        int s = 0;
        preencherAleatorio(vetor, N, pow(2,RANGE));
  
        //imprimeVetor(vetor,N);
    
        start = clock();//start recebe o "ciclo" corrente
        comp =0; 
        countingSort(vetor,N,pow(2,RANGE));
        end = clock();//end recebe o "ciclo" corrente
        //imprimeVetor(vetor,N);
        

        total = ((double)end - start)/CLOCKS_PER_SEC;
        printf("heap,%d,%f,%ld,   range%d\n",N,total,comp,vetor[N-1]-vetor[0]);
        
        free(vetor);
        N = N/(1.2);   
    }
    return 0;

}