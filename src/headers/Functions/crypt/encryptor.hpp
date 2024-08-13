// Funkcja pomocnicza do generowania losowego klucza
std::vector<int> generateRandomKey(int size) {
    std::vector<int> key(size);
    for (int i = 0; i < size; ++i) {
        key[i] = i;
    }
    std::random_shuffle(key.begin(), key.end());
    return key;
}

// Funkcja szyfrująca tekst
std::string encryptText(std::string text, std::vector<int>& key) {
    // Zamiana znaków na wartości ASCII
    std::string asciiText;
    for (char c : text) {
        asciiText += std::to_string(static_cast<int>(c)) + " ";
    }

    // Usunięcie ostatniej spacji
    if (!asciiText.empty()) {
        asciiText.pop_back();
    }

    // Generowanie losowego klucza
    key = generateRandomKey(asciiText.size());

    // Tworzenie zaszyfrowanego tekstu
    std::string encryptedText(asciiText.size(), ' ');
    for (size_t i = 0; i < asciiText.size(); ++i) {
        encryptedText[key[i]] = asciiText[i];
    }

    return encryptedText;
}

std::string decryptText(std::string encryptedText, const std::vector<int>& key) {
    // Tworzenie odszyfrowanego tekstu
    std::string asciiText(encryptedText.size(), ' ');
    for (size_t i = 0; i < encryptedText.size(); ++i) {
        asciiText[key[i]] = encryptedText[i];
    }

    // Zamiana wartości ASCII na znaki
    std::string text;
    std::string asciiValue;
    for (char c : asciiText) {
        if (c == ' ') {
            if (!asciiValue.empty()) {
                text += static_cast<char>(std::stoi(asciiValue));
                asciiValue.clear();
            }
        } else {
            asciiValue += c;
        }
    }
    if (!asciiValue.empty()) {
        text += static_cast<char>(std::stoi(asciiValue));
    }

    return text;
}

// Funkcja wyświetlająca klucz
std::string getKey(std::vector<int> key) {
    // std::cout << "Klucz do odszyfrowania: ";
    std::string keyoutput;
    keyoutput.erase();
    for (int i : key) {
        // std::cout << i << " ";
        keyoutput += std::to_string(i);
    }
    // std::cout << std::endl;
    return keyoutput;
}

std::string encryptor(std::string textinput)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> key;

    std::string output = encryptText(textinput, key);
    output += "|" + getKey(key);

    // std::cout << "output: " << output << std::endl;
    return output;
}