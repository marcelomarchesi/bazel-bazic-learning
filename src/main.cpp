#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <cstring>

using json = nlohmann::json;

extern "C" void print_message(const char* message);

void listMessages(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    json j;
    file >> j;
    file.close();

    if (!j.is_array()) {
        std::cerr << "Error: JSON file does not contain an array" << std::endl;
        return;
    }

    for (size_t i = 0; i < j.size(); ++i) {
        std::cout << i << ": " << j[i].get<std::string>() << std::endl;
    }
}

void removeMessage(const std::string& filename, size_t index) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    json j;
    file >> j;
    file.close();

    if (!j.is_array()) {
        std::cerr << "Error: JSON file does not contain an array" << std::endl;
        return;
    }

    if (index >= j.size()) {
        std::cerr << "Error: Index " << index << " out of range (0-" << j.size()-1 << ")" << std::endl;
        return;
    }

    j.erase(j.begin() + index);

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not save file " << filename << std::endl;
        return;
    }

    outFile << j.dump(4);
    outFile.close();
    std::cout << "Message at index " << index << " removed successfully" << std::endl;
}

void printUsage(const char* progName) {
    std::cout << "Usage: " << progName << " <file> [-l | --list | -r <index> | --remove <index>]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -l, --list          List all messages in the JSON file" << std::endl;
    std::cout << "  -r, --remove <index> Remove the message at the specified index" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    // This is a call to Rust code!
    print_message("MARCELO VIEIRA MARCHESI");

    std::string filename = argv[1];

    if (argc == 2) {
        printUsage(argv[0]);
        return 1;
    }

    if (strcmp(argv[2], "-l") == 0 || strcmp(argv[2], "--list") == 0) {
        if (argc != 3) {
            printUsage(argv[0]);
            return 1;
        }
        listMessages(filename);
    }
    else if (strcmp(argv[2], "-r") == 0 || strcmp(argv[2], "--remove") == 0) {
        if (argc != 4) {
            printUsage(argv[0]);
            return 1;
        }
        try {
            size_t index = std::stoul(argv[3]);
            removeMessage(filename, index);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: Invalid index" << std::endl;
            return 1;
        }
    }
    else {
        printUsage(argv[0]);
        return 1;
    }

    return 0;
}