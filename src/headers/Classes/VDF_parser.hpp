class VDFParser {
public:
    struct VDFNode {
        std::unordered_map<std::string, std::string> attributes;
        std::unordered_map<std::string, VDFNode> children;
    };

    VDFParser(const std::string& filename) {
        parseFile(filename);
    }

    const VDFNode& getRoot() const {
        return root;
    }

    // Funkcja, która konwertuje węzeł VDF do formatu JSON
    std::string toJSON(const VDFNode& node, int indent = 0) const {
        std::string json = "{\n";
        bool first = true;
        
        // Konwertowanie atrybutów (pary klucz-wartość)
        for (const auto& attr : node.attributes) {
            if (!first) json += ",\n";
            json += std::string(indent + 1, '\t') + "\"" + attr.first + "\": \"" + attr.second + "\"";
            first = false;
        }

        // Konwertowanie zagnieżdżonych dzieci
        for (const auto& child : node.children) {
            if (!first) json += ",\n";
            json += std::string(indent + 1, '\t') + "\"" + child.first + "\": " + toJSON(child.second, indent + 1);
            first = false;
        }

        json += "\n" + std::string(indent, '\t') + "}";
        return json;
    }

private:
    VDFNode root;

    void parseFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file");
        }

        std::string line;
        std::vector<std::string> keyStack;  // Stos do obsługi bieżącej ścieżki kluczy
        VDFNode* currentNode = &root;

        while (getline(file, line)) {
            line = trim(line);
            if (line.empty()) continue;

            if (line == "{") {
                keyStack.push_back(keyStack.back());  // Dodaj ostatni klucz do stosu (nowy blok)
                currentNode = &currentNode->children[keyStack.back()];
            } 
            else if (line == "}") {
                keyStack.pop_back();  // Wróć do poprzedniego poziomu
                if (!keyStack.empty()) {
                    currentNode = &getNodeByKeyStack(root, keyStack);
                }
            } 
            else {
                size_t firstQuote = line.find('"');
                size_t secondQuote = line.find('"', firstQuote + 1);
                size_t thirdQuote = line.find('"', secondQuote + 1);
                size_t fourthQuote = line.find('"', thirdQuote + 1);

                if (thirdQuote == std::string::npos || fourthQuote == std::string::npos) {
                    // Znaleziono tylko klucz (dla nowego bloku)
                    std::string key = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
                    keyStack.push_back(key);
                } else {
                    // Znaleziono parę klucz-wartość
                    std::string key = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
                    std::string value = line.substr(thirdQuote + 1, fourthQuote - thirdQuote - 1);
                    currentNode->attributes[key] = value;
                }
            }
        }

        file.close();
    }

    // Pomocnicza funkcja do odszukania węzła na podstawie stosu kluczy
    VDFNode& getNodeByKeyStack(VDFNode& node, const std::vector<std::string>& keyStack) {
        VDFNode* currentNode = &node;
        for (const auto& key : keyStack) {
            currentNode = &currentNode->children[key];
        }
        return *currentNode;
    }

    // Funkcja pomocnicza do usuwania białych znaków
    std::string trim(const std::string& str) {
        const char* whitespace = " \t\n\r";
        size_t start = str.find_first_not_of(whitespace);
        size_t end = str.find_last_not_of(whitespace);
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }
};