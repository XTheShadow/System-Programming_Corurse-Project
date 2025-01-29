#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <filesystem>
#include <sstream>
#include <memory>

namespace fs = std::filesystem;

// Function to use eSpeak to convert text to speech and save it to a WAV file
void synthesizeAudio(const std::string& text, const std::string& outputFilename) {
    std::ostringstream command;
    command << "espeak \"" << text << "\" -w " << outputFilename;
    int result = system(command.str().c_str());
    if (result != 0) {
        std::cerr << "Error: Command execution failed with code " << result << std::endl;
    }
}

void textToSpeech(const fs::path& filepath) {
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filepath << std::endl;
        return;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::unique_ptr<char[]> buffer(new (std::nothrow) char[size + 1]);
    if (!buffer) {
        std::cerr << "Memory allocation failed for file: " << filepath << std::endl;
        return;
    }

    if (!file.read(buffer.get(), size)) {
        std::cerr << "Could not read the file: " << filepath << std::endl;
        return;
    }
    buffer[size] = '\0';
    file.close();

    // Generate output filename by replacing .txt with .wav
    std::string outputFilename = "v3_" + filepath.stem().string() + ".wav";

    // Call the audio synthesis function
    synthesizeAudio(buffer.get(), outputFilename);
}

int main() {
    std::string directory;
    std::cout << "Enter the directory path: ";
    std::getline(std::cin, directory);

    // Check if the directory exists
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        std::cerr << "The directory does not exist or is not a directory: " << directory << std::endl;
        return 1;
    }

    std::vector<std::thread> threads;

    // Iterate over .txt files in the directory and create threads to process them
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".txt") {
            threads.emplace_back(textToSpeech, entry.path());
        }
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Audio synthesis complete for all .txt files in the directory." << std::endl;

    return 0;
}
