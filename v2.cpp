#include <iostream>
#include <fstream>
#include <string>
#include <thread>

// Function to use eSpeak to convert text to speech and save it to a WAV file
void synthesizeAudio(const std::string& text, const std::string& outputFilename) {
    std::string command = "espeak \"" + text + "\" -w " + outputFilename;
    system(command.c_str());
}

void textToSpeech(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Check if the file is empty
    if (text.empty()) {
        std::cerr << "The file is empty or could not be read: " << filename << std::endl;
        return;
    }

    // Call the audio synthesis function
    synthesizeAudio(text, "v2_output.wav");
}

int main() {
    std::string filename;
    std::cout << "Enter the filename (with path if necessary): ";
    std::getline(std::cin, filename);

    // Create a thread to run the textToSpeech function
    std::thread t(textToSpeech, filename);

    // Wait for the thread to finish
    t.join();

    std::cout << "Audio synthesis complete. Output saved to output.wav" << std::endl;

    return 0;
}

