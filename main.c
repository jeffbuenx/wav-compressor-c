/*
 *	Jefferson E. M. Bueno
 *      
 *      Compressão de áudios WAV
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

#include "compressor.h"


int main(void){

    char fname[12];                     //nome do arquivo de audio
    int T;                              //numero de coeficientes
    unsigned char* data = NULL;         //informacoes lidas a partir do audio
    int length;                         //tamanho do vetor de informacoes do audio
    double complex *vet_q = NULL;       //vetor de coeficientes a serem ordenados de maneira decrescente
    coef_t *vet_coef = NULL;            //vetor de estrutura que armazenará os coeficientes com seus indices
    unsigned char* data_comp = NULL;    //informacoes lidas a partir do audio
    int NZero;                          //Numero de coeficientes menores ou iguais a zero

    scanf("%s", fname);
    scanf("%d", &T);

    data = read_wav_data(fname);

    length = strlen((char*)data);

    vet_q = DFT(data, length);

    vet_coef = cria_vet_coef(length, vet_q);

    descobre_magnitude(vet_coef, length);

    mergesort_coef(vet_coef, 0, length-1);

    NZero = conta_menor_zero(vet_coef, length);

    zera_maior_T(vet_coef, length, T);

    print_output(vet_coef, T, length, NZero);
    
    move_pos_orig(vet_coef, T);

    data_comp = IDFT(vet_coef, length);

    cria_audio(data_comp, length, fname);


    free(data);
    free(vet_q);
    free(vet_coef);
    free(data_comp);

    return 0;
}
