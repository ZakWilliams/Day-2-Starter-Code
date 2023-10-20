#include <cctype>
#include <iostream>
#include <string>
#include <vector>

//Transliteration function
std::string transliteration(const char in_char);
bool processCommandLine(const std::vector<std::string>& args, bool& helpRequested, bool& versionRequested, std::string& inputFileName, std::string& outputFileName);

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
    std::string inputText;

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::cerr << "[warning] input from file ('" << inputFile
                  << "') not implemented yet, using stdin\n";
    }

    // loop over each character from user input
    while (std::cin >> inputChar) {
        inputText += transliteration(inputChar);      
        // If the character isn't alphabetic or numeric, DONT add it
    }

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
        std::cerr << "[warning] output to file ('" << outputFile
                  << "') not implemented yet, using stdout\n";
    }

    // Print out the transliterated text
    std::cout << inputText << std::endl;

    // No requirement to return from main, but we do so for clarity and consistency
    return 0;
}
//=====================================================================================================================================================================================
//                                      FUNCTION DEFINITIONS BELOW
//=====================================================================================================================================================================================
bool processCommandLine( //True/False instructs program whether to continue, other values are edited within the function
    const std::vector<std::string>& args, 
    bool& helpRequested, 
    bool& versionRequested, 
    std::string& inputFileName, 
    std::string& outputFileName
    ) {
        const std::size_t num_args{args.size()};
        for (std::size_t i{1}; i < num_args; ++i) {
            if (args[i] == "-h" || args[i] == "--help") {helpRequested = true;}
            else if (args[i] == "--version") {versionRequested = true;}
            else if (args[i] == "-i") { //input file handling
                // Next element is filename unless "-i" is the last argument
                if (i == num_args - 1) {
                    std::cerr << "[error] -i requires a filename argument" << std::endl;
                    return false; // exit main with non-zero return to indicate failure
                } else {
                    inputFileName = args[i + 1]; // Got filename, so assign value and advance past it
                    ++i;
                }
            }
            else if (args[i] == "-o") { // Handle output file option
                // Next element is filename unless "-o" is the last argument
                if (i == num_args - 1) {
                    std::cerr << "[error] -o requires a filename argument" << std::endl;
                    return false; // exit main with non-zero return to indicate failure
                } else {
                    outputFileName = args[i + 1]; // Got filename, so assign value and advance past it
                    ++i;
                }
            } else { // Have an unknown flag to output error message and return non-zero
                std::cerr << "[error] unknown argument '" << args[i] << "'\n"; // exit status to indicate failure
                return false;
            }
        }
    return true;
    }


std::string transliteration(const char in_char) { //Transliterates numbers and capitalizes
    std::string return_string{};
    if (std::isalpha(in_char)) {
        return_string = std::toupper(in_char);
    }

    // Transliterate digits to English words
    if (std::isdigit(in_char)) {
        switch (in_char) {
            case '0':
                return_string = "ZERO";
                break;
            case '1':
                return_string = "ONE";
                break;
            case '2':
                return_string = "TWO";
                break;
            case '3':
                return_string = "THREE";
                break;
            case '4':
                return_string = "FOUR";
            break;
            case '5':
                return_string = "FIVE";
                break;
            case '6':
                return_string = "SIX";
                break;
            case '7':
                return_string = "SEVEN";
                break;
            case '8':
                return_string = "EIGHT";
                break;
            case '9':
                return_string = "NINE";
                break;
        }
    }
    return return_string;
}