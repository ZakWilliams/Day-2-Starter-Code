#include <string>

std::string transformChar(const char in_char) { //Transliterates numbers into text and capitalises all words
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