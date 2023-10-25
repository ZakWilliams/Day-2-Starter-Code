#include <string>
#include <vector>
#include <iostream>

bool processCommandLine( //Reads command line arguments and instructs program as to how to proceed
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