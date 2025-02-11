# 🎧 WAV Compressor *in Pure C*

**DFT-based audio compression tool for WAV files with frequency domain processing**  
[![C](https://img.shields.io/badge/C-ISO_C11-blue?logo=c&logoColor=white)](https://iso.org/standard/74528.html)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![Math](https://img.shields.io/badge/Dependency-libm-critical)](https://www.gnu.org/software/libc/)

## 🎯 Key Features

### Core Capabilities
- **WAV Header Preservation** - Maintains original file structure
- **Frequency Domain Compression** - DFT/IDFT signal processing
- **Adaptive Thresholding** - Keep top `T` significant coefficients
- **Lossy Compression** - Controlled audio quality reduction

### Technical Highlights
- **Pure C Implementation** - Zero external dependencies
- **Portable Code** - Standard C11 compliance
- **Batch Processing** - Process multiple files sequentially

## 🛠️ Installation & Usage

### Compilation
```bash
git clone https://github.com/voidashi/wav-compressor-c.git
cd wav-compressor-c
gcc main.c compressor.c -o wav_compressor -lm
```

### Execution
```bash
./wav_compressor
# Follow prompts:
# 1) Input filename (e.g., audio.wav)
# 2) Threshold T (e.g., 500)
```

### Output
- Creates `audio_comp.wav` in working directory
- Preserves original sampling rate/bit depth
- Logs compression ratio to console

## 📚 Technical Deep Dive

### DFT Compression Pipeline
1. **Time Domain Input**  
   Read PCM samples from WAV file (header ignored)

2. **Frequency Transformation**  
   Apply Discrete Fourier Transform (DFT) on sample windows

3. **Coefficient Selection**  
   Keep top `T` coefficients by magnitude  
   `|F[k]| = sqrt(Re² + Im²)`

4. **Signal Reconstruction**  
   Inverse DFT (IDFT) to time domain

5. **WAV File Generation**  
   Write processed samples to new header-preserved file

### Mathematical Foundations
```c
// DFT Calculation
for k=0 to N-1:
    F[k] = Σₙ (x[n] * e^(-j2πkn/N))
    
// IDFT Reconstruction
x_compressed[n] = (1/N) Σₖ (F_filtered[k] * e^(j2πkn/N))
```

## 📊 Performance Considerations
- **Complexity**: O(N²) naive DFT implementation
- **Window Size**: Default 1024 samples
- **Quality Tradeoff**: Higher T = better fidelity + larger size

## 🤝 Contribution Guidelines
```bash
# Recommended workflow
1. Fork repository
2. Create feature branch
3. Add tests for new functionality
4. Submit pull request
```

**Focus Areas**  
- Optimized FFT implementation
- Parallel processing support
- Bitrate control options

## 📜 License
MIT Licensed - Full terms in [LICENSE](LICENSE)

Would you like me to create the companion DFT flow diagram concept?
