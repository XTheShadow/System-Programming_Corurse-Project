# System Programming Project

## Description
This project is a system-level application written in C++ that implements a multithreaded text-to-speech (TTS) system. The application converts input text into speech output by leveraging concurrent processing with multiple threads, improving efficiency and responsiveness with each successive version.


## Features
  - Efficient text-to-speech conversion
  - Multithreading with dynamic thread allocation
  - Thread pool management for concurrency
  - Work-stealing algorithm for optimal load balancing
  - Logging system for debugging and analysis


## Why This Project?
  Text-to-speech systems are widely used in accessibility features for visually impaired individuals, language learning tools, and navigation systems. By integrating multithreading, this application efficiently processes large volumes of text, enhancing performance and responsiveness. Each version of the software is optimized to be faster than the previous one, ensuring continuous improvements.


## Installation
  1. Ensure you have a C++ compiler (GCC, Clang, or MSVC) installed.
  2. Clone the repository or extract the files from the provided archive.
  3. Navigate to the project directory and compile the source files:
     ```sh
     g++ -o tts_project main.cpp module1.cpp module2.cpp -lpthread
  4. Run the executable:
      ```sh
     ./tts_project

## Usage
  - Execute the compiled program from the terminal.
  - Input text to convert it into speech.
  - Logs and output files are stored in the designated directories.


## Dependencies
  - C++ Standard Library
  - POSIX system calls (for Linux/MacOS)
  - pthreads (for multi-threading support)

    
## License
This project is licensed under the MIT License.
