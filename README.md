# wav-compressor-c

## FIXME: Formula da inversa ligeiramente incorreta

## Audios WAV
WAV ou WAVE (Waveform Audio File Format), é um subconjunto da especificação da
Microsoft Resource Interchange File Format (RIFF) para armazenamento de arquivos
de áudio digital. O formato não aplica qualquer compressão a sequência de bytes e ar
mazena as gravações de áudio com diferentes taxas de amostragem e taxas de bits. Tem
sido e é um dos formatos padrão para CDs de áudio. Os arquivos WAVE são maiores
em tamanho do que os novos formatos, tais como MP3, que utilizam compressão com
perdas para reduzir o tamanho do arquivo, mantendo a mesma qualidade de áudio.

## Ondas sonoras digitalmente
Como ondas sonoras são representadas em formato digital? Basicamente,
imaginando ondas sonoras, a amplitude de uma onda num dado momento é convertido
em dados binários, representados por valores numéricos, que podemos chamar de "sam
ple". Logo, o conjunto destes valores, são análogos ao formato da onda.


## Transformada Discreta de Fourier
Uma das ferramentas mais úteis na análise e processamento de sinais como áudio é
a Transformada Discreta de Fourier. Essa transformada permite obter um coeficiente
(que é um par de valores, ou seja, um valor complexo) para cada sample (amplitude do
diafragma do microfone) do sinal de áudio original. Como uma onda sonora pode ser
representada por uma combinação de várias ondas senoidais, de forma grosseira, esses
coeficientes representam a quantidade de uma determinada onda senoidal presente na
onda original, desde aquelas de menor frequência (sons mais graves), até as de maior
frequência (sons mais agudos).

## Inversa da Transformada Discreta de Fourier
Uma das propriedades importantes de uma TDF é a possibilidade de invertê-la. A teoria
da TDF diz que é possível reconstruir o áudio original a partir da representação desse
sinal em somas de funções senoidais, ou seja, conseguimos reconstruir o sinal de áudio a
partir da soma de senos e cossenos (representados na equação pela exponencial complexa).
O interessante dessa técnica é que, em geral, o vetor de coeficiente (após a Transfor
mada) são esparsos (possuem muitos valores nulos, ou próximos de zero). Dessa forma,
perceba que, se precisarmos transferir o áudio para outro computador, podemos, apenas,
transferir os T coeficientes mais importantes e suas posições originais no vetor (ou seja,
antes de ordená-lo), além, é claro, do número total de coeficientes. No outro computador,
poderíamos recuperar essas informações, criar um vetor para conter os coeficientes mais
importantes e aqueles menos importantes que terão valor igual a zero. Em seguida, apli
caríamos a Inversa da Transformada Discreta de Fourier e obteríamos uma aproximação
do sinal de áudio.

## Ou seja...
Perceba que assim, transferiríamos uma quantidade muito menor de dados para o
computador destino e poderíamos, ainda, reconstituir o áudio e ouvi-lo. Tratando-se
assim, de uma Compressão de Áudio.


## Uso do programa
A entrada do programa consiste em 2 valores, em linhas diferentes.
O primeiro é o nome do áudio wav a ser comprimido
O segundo é o número de coeficientes que devem ser utilizados na compressão
