# 🎧 WAV Compressor  

*A DFT-based audio compression tool for WAV files, balancing file size reduction with perceptual quality.*  

[![C](https://img.shields.io/badge/Language-C-informational?style=flat&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))  
[![License](https://img.shields.io/badge/License-MIT-green?style=flat)](LICENSE)  

---

## 📦 Features  

### **Core Functionality**  
- **WAV File Support**: Read and process standard PCM WAV files (header-aware).  
- **Frequency Domain Compression**: Leverage Discrete Fourier Transform (DFT) to isolate significant frequencies.  
- **Threshold-Based Filtering**: Retain only the top `T` coefficients for efficient compression.  
- **Lossy Reconstruction**: Rebuild audio using Inverse DFT (IDFT) to generate compressed output.  

### **Key Advantages**  
- **Mathematically Grounded**: DFT/IDFT ensures scientifically sound compression.  
- **Adjustable Compression**: Customize the trade-off between file size and audio quality via the `T` parameter.  
- **Lightweight**: No external dependencies beyond standard C libraries.  

---

## 🚀 Getting Started  

### **Clone the Repository**  
```bash  
git clone https://github.com/voidashi/wav-compressor-c.git  
```  

### **Compile the Code**  
Link the math library explicitly:  
```bash  
gcc main.c compressor.c -o wav_compressor -lm  
```  

### **Run the Compressor**  
Execute the binary and follow prompts:  
```bash  
./wav_compressor  
```  
**Input Example:**  
```  
audio.wav   # Input filename  
500         # Retain top 500 coefficients  
```  
**Output:** `audio_comp.wav` (compressed version).  

**Note:** Test with short audio clips first to evaluate quality impact!  

---

## 🧠 Technical Overview  

### **How DFT Compression Works**  
1. **Time → Frequency Domain**:  
   DFT converts audio samples into complex frequency coefficients.  
2. **Coefficient Ranking**:  
   Sort coefficients by magnitude (most to least significant).  
3. **Threshold Filtering**:  
   Discard all but the top `T` coefficients; zero others.  
4. **Reconstruction**:  
   Apply IDFT to convert filtered coefficients back to time-domain samples.  

### **Trade-Offs**  
- **Higher `T`**: Better quality, larger file.  
- **Lower `T`**: Smaller file, potential artifacts.  

---

## 🛠️ Usage Tips  
- **Ideal Use Case**: Speech/tonal audio (preserves dominant frequencies well).  
- **Avoid**: Highly complex audio (orchestral, heavy percussion) unless using high `T`.  
- **Verify**: Always listen to `audio_comp.wav` to assess perceptual quality.  

---

## 🤝 Contributing  
Found a bug or improvement?  
- Open an **Issue** for feature requests or problem reports.  
- Submit a **Pull Request** for tested, well-commented fixes.  

---

## 📄 License  
MIT Licensed - See [LICENSE](LICENSE) for details.  

---  

*Compression meets clarity—simplifying audio without losing essence.*
