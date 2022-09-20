typedef struct coef_temp coef_t;

unsigned char* read_wav_data(char* fname);
double complex *DFT(unsigned char *audio, int length);
unsigned char *IDFT(coef_t *vet_coef, int length);
void mergesort_coef(coef_t *v, int ini, int fim);
void descobre_magnitude(coef_t *vet_coef, int length);
void zera_maior_T(coef_t *vet_coef, int length, int T);
void move_pos_orig(coef_t *vet_coef, int T);
coef_t *cria_vet_coef(int length, double complex *vet_q);
int conta_menor_zero(coef_t *vet_coef, int length);
void print_output(coef_t *vet_coef, int T, int length, int Nzero);
void cria_audio(unsigned char* data_comp, int length, char* fname);