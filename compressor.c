#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

#include "compressor.h"


struct coef_temp{
    double complex q;
    int index;
    double magni;
};

/*
    Abre o arquivo binário
    E lê o seu conteúdo, sem o header
    para o vetor "data", retornando-o.
*/
unsigned char* read_wav_data(char* fname) {
    FILE* fp = fopen(fname, "rb");
    unsigned char buf4[4];

    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    int dataSize = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;

    unsigned char* data = malloc(sizeof(*data) * (dataSize));
    
    int i = 0;
    while (i < dataSize) {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);
    return data;
}

/*
    Utiliza a formula da transformação discreta de fourier
    para descobrir os valores dos coeficientes no do audio.
*/
double complex *DFT(unsigned char *audio, int length) {
    double complex *coef = (double complex *) calloc(length, sizeof(double complex));

    for (int k = 0; k < length; k++) {
        for (int n = 0; n < length; n++) {
            coef[k] += audio[n] * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }
    }
    return coef;
}

/*
    Transformação inversa de fourier,
    Para descomprimir o áudio armazenado no vetor de coeficientes
*/
unsigned char *IDFT(coef_t *vet_coef, int length) {
    double complex *coef = (double complex *) calloc(length, sizeof(double complex));
    unsigned char *audio = (unsigned char *) malloc(sizeof(unsigned char) * length);

    for (int n = 0; n < length; n++) {
        for (int k = 0; k < length; k++) {
            coef[n] += vet_coef[k].q * cexp((2.0 * M_PI * (((k+1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }
        audio[n] = (int)(coef[n] / (float)length);
    }
    free(coef);
    return audio;
}

/*
    Ordena o vetor de estruturas com base na magnitude
    de cada coeficiente "q" (double complex)
*/
void mergesort_coef(coef_t *v, int ini, int fim) {

	if (fim <= ini) return; //1 - caso base, vetor de um único elemento

	int c = (int) (fim+ini) / 2.0; //Calcula o centro

	// 2 - passo recursivo (divisao)
	mergesort_coef(v, ini, c);   //Chamada para a esquerda
	mergesort_coef(v, c+1, fim); //Chamada para a direita

    coef_t *aux = (coef_t*) malloc(sizeof(coef_t) * (fim-ini+1));

	int i = ini; // indice inicial da L1 (ini -> centro)
	int j = c+1; // indice inicial da L2 (centro+1 -> fim)
	int k = 0;   // indice do vetor auxiliar (0 ate fim-ini)

	// compara elementos das duas listas (subvetores) ordenados
	// enquanto houver elementos das DUAS listas para serem comparados
	while (i <= c && j <= fim) {

		if (v[i].magni >= v[j].magni) {
			aux[k] = v[i]; // copia elemento da L1
			i++; // movo para o proximo elemento da L1
		} else {
			aux[k] = v[j]; // copia elemento da L2
			j++;
		}
		k++;
	}

	// tenho uma das listas com elementos restantes
	// copio todos os restantes da L1
	while (i <= c) {
		aux[k] = v[i];
		i++; k++;
	}
	// copio todos os elementos da L2
	while (j <= fim) {
		aux[k] = v[j];
		j++; k++;
	}

	// aux contem a intercalacao do vetor v[ini:c] e v[c+1:fim]
	// copia de aux para o vetor original
	for (i = ini, k = 0; i <= fim; i++, k++) {
		v[i] = aux[k];
	}

	free(aux);
}

/*
    Calcula a magnitude de todos os elementos do vetor
    utilizando a fórmula da distância euclidiana.
*/
void descobre_magnitude(coef_t *vet_coef, int length){

    float a, b;

    for(int i = 0; i < length; i++){
        a = creal(vet_coef[i].q);
        b = cimag(vet_coef[i].q);
        vet_coef[i].magni = sqrt(pow(a, 2) + pow(b, 2));
    }
}

/*
    Zerar os coeficientes nas posicoes maiores ou iguais a T,
    atribuindo 0 * a constante _complex_I, e
    atribuindo -1 ao índice
*/
void zera_maior_T(coef_t *vet_coef, int length, int T){

    for(int i = T; i < length; i++){
        vet_coef[i].q = 0 * _Complex_I;
        vet_coef[i].index = -1;
    } 
}

/*
    Devolver os vetores às suas posições originais
    Trocando de posições o elemento existente com o
    Elemento na posição do seu índice
*/
void move_pos_orig(coef_t *vet_coef, int T){

    coef_t temp;
    for(int i = 0; i < T; i++){
        if(vet_coef[i].index >= 0){
            temp = vet_coef[vet_coef[i].index];
            vet_coef[vet_coef[i].index] = vet_coef[i];
            vet_coef[i] = temp;
        }
    }
}

/*
    Criar vetor da estrutura que irá guardar o valor original da posição do vetor
*/
coef_t *cria_vet_coef(int length, double complex *vet_q){
    coef_t *vet_coef = malloc(sizeof(coef_t) * (length));
    for(int i = 0; i < length; i++){
        vet_coef[i].q = vet_q[i];
        vet_coef[i].index = i;
    }
    return vet_coef;
}

/*
    Conta a quantidade de elementos menores ou iguais a zero tanto 
    na parte real quanto na parte imaginária no vetor dos coeficientes
*/
int conta_menor_zero(coef_t *vet_coef, int length){

    int num = 0;

    for(int i = 0; i < length; i++){
        if(creal(vet_coef[i].q) <= 0 && cimag(vet_coef[i].q) <= 0) num++;
    }
    return num;
}

/*
    Imprime o output requisitado pelo run.codes
*/
void print_output(coef_t *vet_coef, int T, int length, int Nzero){

    printf("%d\n", length);
    printf("%d\n", Nzero);

    for(int i = 0; i < T; i++){
        printf("%d\n", (int)vet_coef[i].magni);
    }
}

/*
    Cria um novo arquivo de audio após a descompressão
    Sendo esse muito semelhante ao audio original
*/
void cria_audio(unsigned char* data_comp, int length, char* fname){
    FILE* forig = fopen(fname, "rb");

    unsigned char* data = malloc((sizeof(*data) * length) + 44);

    //Copia o header do arquivo original para "data"
    int i = 0;
    while(i < 44){
        fread(&data[i++], sizeof(unsigned char), 1, forig);
    }
    fclose(forig);
    
    //Copia as informacoes do novo arquivo de audio para "data"
    int j = 0;
    while(j < length){
        data[i++] = data_comp[j++];
    }

    //Exporta "data" para um novo arquivo .wav
    char fdestname[16] = "audio_comp.wav";
    FILE* fdest = fopen(fdestname, "wb");
    fwrite (data, sizeof(unsigned char), length+44, fdest);

    free(data);
}