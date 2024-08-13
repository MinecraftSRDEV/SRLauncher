class JSON {
public:
    enum Type { Null, Object, Array, String, Number, Bool };

    JSON() : type(Null) {}
    JSON(const std::string& value) : type(String), stringValue(value) {}
    JSON(double value) : type(Number), numberValue(value) {}
    JSON(bool value) : type(Bool), boolValue(value) {}
    JSON(const std::unordered_map<std::string, JSON>& value) : type(Object), objectValue(value) {}
    JSON(const std::vector<JSON>& value) : type(Array), arrayValue(value) {}

    Type getType() const { return type; }
    const std::string& getString() const { return stringValue; }
    double getNumber() const { return numberValue; }
    bool getBool() const { return boolValue; }
    const std::unordered_map<std::string, JSON>& getObject() const { return objectValue; }
    const std::vector<JSON>& getArray() const { return arrayValue; }

    static JSON parse(const std::string& text);
    static JSON parseFromFile(const std::string& filePath);

private:
    Type type;
    std::string stringValue;
    double numberValue;
    bool boolValue;
    std::unordered_map<std::string, JSON> objectValue;
    std::vector<JSON> arrayValue;

    static JSON parseValue(const std::string& text, size_t& offset);
    static JSON parseObject(const std::string& text, size_t& offset);
    static JSON parseArray(const std::string& text, size_t& offset);
    static JSON parseString(const std::string& text, size_t& offset);
    static JSON parseNumber(const std::string& text, size_t& offset);
    static JSON parseBool(const std::string& text, size_t& offset);
    static void skipWhitespace(const std::string& text, size_t& offset);
    static void expectChar(const std::string& text, size_t& offset, char expected);
};

void JSON::skipWhitespace(const std::string& text, size_t& offset) {
    while (offset < text.size() && std::isspace(text[offset])) {
        ++offset;
    }
}

void JSON::expectChar(const std::string& text, size_t& offset, char expected) {
    skipWhitespace(text, offset);
    if (text[offset] != expected) {
        throw std::runtime_error(std::string("Expected '") + expected + "' but found '" + text[offset] + "'");
    }
    ++offset;
}

JSON JSON::parse(const std::string& text) {
    size_t offset = 0;
    skipWhitespace(text, offset);
    return parseValue(text, offset);
}

JSON JSON::parseFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    return parse(text);
}

JSON JSON::parseValue(const std::string& text, size_t& offset) {
    skipWhitespace(text, offset);
    if (text[offset] == '{') {
        return parseObject(text, offset);
    } else if (text[offset] == '[') {
        return parseArray(text, offset);
    } else if (text[offset] == '"') {
        return parseString(text, offset);
    } else if (text[offset] == 't' || text[offset] == 'f') {
        return parseBool(text, offset);
    } else if (std::isdigit(text[offset]) || text[offset] == '-') {
        return parseNumber(text, offset);
    } else {
        throw std::runtime_error("Invalid JSON value");
    }
}

JSON JSON::parseObject(const std::string& text, size_t& offset) {
    expectChar(text, offset, '{');
    std::unordered_map<std::string, JSON> object;
    while (text[offset] != '}') {
        skipWhitespace(text, offset);
        auto key = parseString(text, offset).getString();
        expectChar(text, offset, ':');
        object[key] = parseValue(text, offset);
        skipWhitespace(text, offset);
        if (text[offset] == ',') {
            ++offset; // Skip ','
        } else if (text[offset] != '}') {
            throw std::runtime_error("Expected '}' or ','");
        }
    }
    ++offset; // Skip '}'
    return JSON(object);
}

JSON JSON::parseArray(const std::string& text, size_t& offset) {
    expectChar(text, offset, '[');
    std::vector<JSON> array;
    while (text[offset] != ']') {
        skipWhitespace(text, offset);
        array.push_back(parseValue(text, offset));
        skipWhitespace(text, offset);
        if (text[offset] == ',') {
            ++offset; // Skip ','
        } else if (text[offset] != ']') {
            throw std::runtime_error("Expected ']' or ','");
        }
    }
    ++offset; // Skip ']'
    return JSON(array);
}

JSON JSON::parseString(const std::string& text, size_t& offset) {
    expectChar(text, offset, '"');
    std::string result;
    while (text[offset] != '"') {
        result += text[offset++];
    }
    ++offset; // Skip '"'
    return JSON(result);
}

JSON JSON::parseNumber(const std::string& text, size_t& offset) {
    size_t start = offset;
    if (text[offset] == '-') ++offset;
    while (offset < text.size() && std::isdigit(text[offset])) {
        ++offset;
    }
    if (offset < text.size() && text[offset] == '.') {
        ++offset;
        while (offset < text.size() && std::isdigit(text[offset])) {
            ++offset;
        }
    }
    return JSON(std::stod(text.substr(start, offset - start)));
}

JSON JSON::parseBool(const std::string& text, size_t& offset) {
    if (text.substr(offset, 4) == "true") {
        offset += 4;
        return JSON(true);
    } else if (text.substr(offset, 5) == "false") {
        offset += 5;
        return JSON(false);
    } else {
        throw std::runtime_error("Expected 'true' or 'false'");
    }
}