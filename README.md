# 🔊 System Programming Project  

## 📖 Description  
This project is a **system-level application** written in **C++** that implements a **multithreaded text-to-speech (TTS) system**. It converts input text into speech by leveraging **concurrent processing** with multiple threads, improving efficiency and responsiveness with each version.  

---

## 📌 Features  
 **Efficient text-to-speech conversion**  
 **Multithreading with dynamic thread allocation**  
 **Thread pool management** for optimized concurrency  
 **Work-stealing algorithm** for load balancing  
 **Logging system** for debugging and analysis  

---

## 🎯 Why This Project?  
🔹 Text-to-speech (TTS) systems play a crucial role in:  
   - **Accessibility** features for visually impaired users  
   - **Language learning** tools  
   - **Navigation systems**  
   - **AI-powered voice assistants**  

By integrating **multithreading**, this project **efficiently processes large volumes of text**, improving performance with each iteration. The goal is to **continuously optimize speed and responsiveness** over multiple versions.  

---

## 🛠️ Installation  

### ✅ Prerequisites  
-  **C++ compiler** (GCC, Clang, or MSVC)  
-  **POSIX Threads (pthreads)** (for Linux/macOS users)  

### 🚀 Setup & Installation  
1️. **Clone the repository**  
   ```sh
   git clone https://github.com/XTheShadow/SystemProgrammingProject.git
   cd SystemProgrammingProject
   ```
   
2️. **Compile the source files**  
   ```sh
   g++ -o tts_synthesizer v1.cpp -O3 -pthread
   ```

3️. **Run the executable**  
   ```sh
   ./tts_synthesizer
   ```

---

## 🚀 Usage  
 **Execute the compiled program** from the terminal  
 **Input text** to convert it into speech  
 **Logs and output files** are stored in the designated directories  

---

## 📚 Dependencies  
 * C++ Standard Library
 * POSIX system calls** (for Linux/macOS)  
 * pthreads** (for multi-threading support)  

---

## 📝 License  
This project is licensed under the **MIT License**.  
