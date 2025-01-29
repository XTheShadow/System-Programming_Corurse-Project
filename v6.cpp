#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <memory>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

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
    std::string outputFilename = "v6_" + filepath.stem().string() + ".wav";

    // Call the audio synthesis function
    synthesizeAudio(buffer.get(), outputFilename);
}

class ThreadPool {
public:
    ThreadPool(size_t threads);
    ~ThreadPool();

    template<class F>
    void enqueue(F&& f);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};

ThreadPool::ThreadPool(size_t threads)
    : stop(false) {
    for (size_t i = 0; i < threads; ++i)
        workers.emplace_back(
            [this] {
                for (;;) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queueMutex);
                        this->condition.wait(lock,
                            [this] { return this->stop.load() || !this->tasks.empty(); });
                        if (this->stop.load() && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
            }
        );
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop.store(true);
    }
    condition.notify_all();
    for (std::thread& worker : workers)
        worker.join();
}

template<class F>
void ThreadPool::enqueue(F&& f) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);

        // don't allow enqueueing after stopping the pool
        if (stop.load())
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace(std::forward<F>(f));
    }
    condition.notify_one();
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

    const size_t numThreads = std::thread::hardware_concurrency();
    ThreadPool pool(numThreads);

    // Collect all .txt files in the directory before starting threads
    std::vector<fs::path> txtFiles;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".txt") {
            txtFiles.push_back(entry.path());
        }
    }

    // Enqueue tasks to the thread pool
    for (const auto& filepath : txtFiles) {
        pool.enqueue([filepath] {
            textToSpeech(filepath);
        });
    }

    return 0;
}

