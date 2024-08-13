#ifndef JSON_ENCODER_H
#define JSON_ENCODER_H

namespace JSONEncoder {

class JSONValue {
public:
    virtual std::string stringify() const = 0;
    virtual ~JSONValue() = default;
};

class JSONString : public JSONValue {
    std::string value;
public:
    JSONString(const std::string& value) : value(value) {}
    std::string stringify() const override {
        std::ostringstream oss;
        oss << "\"" << escape(value) << "\"";
        return oss.str();
    }
private:
    static std::string escape(const std::string& str) {
        std::ostringstream oss;
        for (char c : str) {
            switch (c) {
                case '"': oss << "\\\""; break;
                case '\\': oss << "\\\\"; break;
                case '\b': oss << "\\b"; break;
                case '\f': oss << "\\f"; break;
                case '\n': oss << "\\n"; break;
                case '\r': oss << "\\r"; break;
                case '\t': oss << "\\t"; break;
                default:
                    if ('\x00' <= c && c <= '\x1f') {
                        oss << "\\u" << std::hex << std::setw(4) << std::setfill('0') << (int)c;
                    } else {
                        oss << c;
                    }
            }
        }
        return oss.str();
    }
};

class JSONNumber : public JSONValue {
    double value;
public:
    JSONNumber(double value) : value(value) {}
    std::string stringify() const override {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
};

class JSONBool : public JSONValue {
    bool value;
public:
    JSONBool(bool value) : value(value) {}
    std::string stringify() const override {
        return value ? "true" : "false";
    }
};

class JSONNull : public JSONValue {
public:
    std::string stringify() const override {
        return "null";
    }
};

class JSONArray : public JSONValue {
    std::vector<JSONValue*> values;
public:
    void add(JSONValue* value) {
        values.push_back(value);
    }
    std::string stringify() const override {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < values.size(); ++i) {
            if (i > 0) oss << ",";
            oss << values[i]->stringify();
        }
        oss << "]";
        return oss.str();
    }
    ~JSONArray() {
        for (JSONValue* value : values) {
            delete value;
        }
    }
};

class JSONObject : public JSONValue {
    std::unordered_map<std::string, JSONValue*> values;
public:
    void add(const std::string& key, JSONValue* value) {
        values[key] = value;
    }
    std::string stringify() const override {
        std::ostringstream oss;
        oss << "{";
        bool first = true;
        for (const auto& pair : values) {
            if (!first) oss << ",";
            oss << "\"" << pair.first << "\":" << pair.second->stringify();
            first = false;
        }
        oss << "}";
        return oss.str();
    }
    ~JSONObject() {
        for (const auto& pair : values) {
            delete pair.second;
        }
    }
};

} // namespace JSONEncoder

#endif // JSON_ENCODER_H