//Standard sourced libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//Student created project headers
#include "MPAGSCipher/TransformChar.hpp"
#include "MPAGSCipher/ProcessCommandLine.hpp"

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments THIS IS TEST
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};

    //Implement COMMAND LINE ARGUMENT FUNCTION HERE
    bool correct_parsing{false};
    correct_parsing = processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile);
    if (!correct_parsing) {std::cout <<"ERR: issue in command line reading. \nExiting...\nExiting...\nExiting..."<< std::endl;return 1;} //This acts

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText{""};
    std::string outputText{""};

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::ifstream in_file{inputFile};
        bool ok_to_read{in_file.good()};
        if (ok_to_read) {in_file >> inputText; //Read inputText from file
        in_file.close();
        } else {std::cout << "ERR: issue with input file reading. \nExiting...\nExiting...\nExiting..." << std::endl; return 1;}
    } else {
        std::cout << "\nNo output file optionality detected, taking input from terminal (after submitting text for enciphering, press CTRL + D):\n" << std::endl;
        while (std::cin >> inputChar) {inputText += inputChar;}
    }

    //Loop over and transliterate inputText into outputText
    for (char character : inputText) {outputText += transformChar(character);}

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
        std::ofstream out_file{outputFile};
        bool ok_to_write{out_file.good()};
        if (ok_to_write) {std::cout << "Saving as " << outputFile << " ..." <<std::endl;
            out_file << outputText;
            out_file.close();
        } else {std::cout << "ERR: issue with output file reading. \nExiting...\nExiting...\nExiting..." << std::endl; return 1;} 
    } else {std::cout << "\nNo output file optionality detected, printing enciphered result in terminal:\n" << outputText << "\n" << std::endl;} //Print transliterated text if no output file

    // No requirement to return from main, but we do so for clarity and consistency.
    return 0;
}