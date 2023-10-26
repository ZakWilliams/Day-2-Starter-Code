#include <string>

std::string runCaesarCipher(
    const std::string& inputText,
    const size_t key,
    const bool encrypt) {
        std::string outputText{""};
        int intCastValue{0};
        if (encrypt) { //if in encryption mode
            for (char character : inputText) {
                intCastValue = static_cast<int>(character);
                intCastValue += key;
                if (intCastValue > 90) {intCastValue -= 26;}
                outputText += static_cast<char>(intCastValue);
            } 
        }
        if  (!encrypt) { //if in decryption mode
            for (char character : inputText) {
                intCastValue = static_cast<int>(character);
                intCastValue -= key;
                if (intCastValue < 65) {intCastValue += 26;}
                outputText += static_cast<char>(intCastValue);
            } 
        }
        return outputText;
    }
