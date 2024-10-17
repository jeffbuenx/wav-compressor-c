# 🎧 WAV Compressor

**Autor:** *Jefferson E. M. Bueno*

### 🔗 Repositório: [WAV Compressor](https://github.com/voidashi/wav-compressor-c)

---

## 📜 Descrição

Este projeto implementa a compressão de arquivos de áudio no formato **WAV** usando a **Transformada Discreta de Fourier (DFT)**. A compressão é realizada removendo coeficientes de frequência menos significativos, mantendo apenas os `T` mais importantes. Após a compressão, o áudio é reconstruído e salvo em um novo arquivo comprimido.

---

## 🚀 Funcionalidades

- 🔍 **Leitura de arquivos WAV**, ignorando o cabeçalho.
- ⚙️ **Transformada Discreta de Fourier (DFT)** para converter o sinal do domínio do tempo para o domínio da frequência.
- 📊 **Ordenação e compressão** dos coeficientes de Fourier, removendo os menos significativos.
- 🎛️ **Reconstrução do sinal de áudio** comprimido usando a **Transformada Inversa de Fourier (IDFT)**.
- 💾 **Criação de um novo arquivo WAV comprimido**.

---

## ⚙️ Como Usar

### 1️⃣ Clone o repositório:

```bash
git clone https://github.com/voidashi/wav-compressor-c.git
```

### 2️⃣ Compile o projeto:

```bash
gcc main.c compressor.c -o wav_compressor -lm
```

### 3️⃣ Execute o programa:

```bash
./wav_compressor
```

O programa solicitará:
- O **nome do arquivo WAV** a ser comprimido (exemplo: `audio.wav`).
- O **número `T` de coeficientes** mais significativos a serem mantidos.

#### Exemplo de execução:

```
audio.wav
500
```

O arquivo comprimido será salvo como **`audio_comp.wav`** na pasta atual.

---

## 🔧 Requisitos

- **Compilador GCC** (para compilar o código C).
- Biblioteca padrão `math.h` (para operações matemáticas).
- Arquivos de áudio no formato **WAV** para compressão.

---

## 🔬 Explicação Técnica: Transformada de Fourier

A **Transformada Discreta de Fourier (DFT)** é uma técnica matemática que transforma um sinal do domínio do tempo (uma sequência de amostras de áudio) para o domínio da frequência. Esse processo permite que se descubra quais frequências estão presentes no sinal e suas respectivas magnitudes. Para a compressão de áudio, a DFT é utilizada para identificar e ordenar as frequências mais importantes.

### Etapas do Processo de Compressão:

1. **Aplicação da DFT**:
   O sinal de áudio, que originalmente está no domínio do tempo (sequência de amostras), é transformado em um conjunto de coeficientes que representam as frequências presentes no áudio. Cada coeficiente da DFT tem uma parte real e uma parte imaginária, formando um número complexo.

2. **Ordenação dos Coeficientes**:
   Os coeficientes obtidos pela DFT são ordenados de acordo com a sua magnitude (ou intensidade). As frequências mais importantes têm coeficientes de maior magnitude, enquanto as menos importantes têm coeficientes menores.

3. **Remoção de Frequências**:
   Para comprimir o áudio, apenas os `T` coeficientes com maior magnitude são preservados. Os coeficientes menos significativos (com menor magnitude) são zerados, eliminando frequências menos importantes, reduzindo o tamanho do arquivo.

4. **Reconstrução com a IDFT**:
   Após a remoção dos coeficientes desnecessários, a **Transformada Inversa de Fourier (IDFT)** é aplicada para reconstruir o sinal no domínio do tempo, gerando uma versão comprimida do áudio original.

### Exemplo de Compressão

- **Entrada**: Um arquivo de áudio **WAV** (ex: `audio.wav`).
- **Transformação**: A DFT transforma o áudio no domínio da frequência. Após isso, o número `T` de coeficientes mais importantes é mantido.
- **Saída**: Um arquivo comprimido, **audio_comp.wav**, é gerado utilizando a IDFT.

---

## 🎯 Exemplo de Uso

1. **Entrada**: Arquivo de áudio WAV (`audio.wav`).
2. **Compressão**: Seleção dos `T` coeficientes mais importantes.
3. **Saída**: Arquivo comprimido chamado `audio_comp.wav`.

---

## 💡 Contribuições

Contribuições são sempre bem-vindas! Se você encontrou um problema ou tem uma sugestão, sinta-se à vontade para abrir uma **issue** ou enviar um **pull request**.

---

## 📜 Licença

Este projeto está licenciado sob a **MIT License**.

---
