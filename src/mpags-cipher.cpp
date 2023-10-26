//Standard sourced libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//Student created project headers
#include "MPAGSCipher/TransformChar.hpp"
#include "MPAGSCipher/ProcessCommandLine.hpp"
#include "MPAGSCipher/RunCaesarCipher.hpp"

int main(int argc, char* argv[])
{
    //============= COMMAND LINE ARGUMENTS HANDLING ==============================================================================================//
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments THIS IS TEST
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};

    //Implement COMMAND LINE ARGUMENT FUNCTION HERE
    bool correct_parsing{false};
    correct_parsing = processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile);
    if (!correct_parsing) {std::cout <<"ERR: issue in command line reading. \nExiting...\nExiting...\nExiting..."<< std::endl;return 1;} 

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
    //============= COMMAND LINE ARGUMENTS HANDLING ==============================================================================================//

    // Initialise variables
    int key{'x'};
    char inputChar{'x'};
    bool encrypt{true}, trigger{true};
    std::string inputLine{""}, terminalInput{""}, inputText{""}, translitText{""}, outputText{""};

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::ifstream in_file{inputFile};
        bool ok_to_read{in_file.good()};
        if (ok_to_read) { //read input text
            while (std::getline(in_file, inputLine)) {inputText += inputLine;}
            in_file.close();
        } else {std::cout << "ERR: issue with input file reading. \nExiting...\nExiting...\nExiting..." << std::endl; return 1;}
    } else {
        std::cout << "\nNo output file optionality detected, taking input from terminal (after submitting text for enciphering, press CTRL + D):\n" << std::endl;
        while (std::cin >> inputChar) {inputText += inputChar;}
    }

    //Choose key, and whether to encrypt or decrypt
    std::cout << "Do you wish to 'encrypt' or 'decrypt' the input text?" << std::endl;
    while (trigger) {
        std::getline(std::cin, terminalInput);
        if (terminalInput == "encrypt") {encrypt = true; trigger = false;} 
        else if (terminalInput == "decrypt") {encrypt = false; trigger = false;} 
        else {std::cout << "ERR: please enter exactly 'encrypt' or 'decrypt'"<<std::endl;}
    }

    trigger = true;
    std::cout << "What key (shift) do you wish to apply (please enter an integer between 0 and 25)?" << std::endl;
    while (trigger) {
        std::cin >> key;
        if (key >= 0 && key <= 25) {trigger = false;}
        else {std::cout << "ERR: please enter an integer between 0 and 25'"<<std::endl;}
    }

    //Loop over and transliterate inputText into outputText
    for (char character : inputText) {translitText += transformChar(character);}

    //Encipher output text -  from translit to output
    outputText = runCaesarCipher(translitText, key, encrypt);
    

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
