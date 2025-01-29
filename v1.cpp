#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

// Function to use eSpeak to convert text to speech and save it to a WAV file
void synthesizeAudio(const std::string& text, const std::string& outputFilename) {
    std::string command = "espeak \"" + text + "\" -w " + outputFilename;
    system(command.c_str());
}

int main() {
    std::string filename;
    std::cout << "Enter the filename (with path if necessary): ";
    std::getline(std::cin, filename);

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return 1;
    }

    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Check if the file is empty
    if (text.empty()) {
        std::cerr << "The file is empty or could not be read: " << filename << std::endl;
        return 1;
    }

    // Call the audio synthesis function
    synthesizeAudio(text, "output.wav");

    std::cout << "Audio synthesis complete. Output saved to output.wav" << std::endl;

    return 0;
}

