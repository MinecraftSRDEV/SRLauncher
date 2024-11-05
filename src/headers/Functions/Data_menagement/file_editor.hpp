// struct fileInputData {
//     int seekLine = -34872832479832423984;
//     std::string seekString;
//     std::string keyString;
//     std::map <std::string, std::string> fileContent;
// };
// int editFile(const std::string& filePath, std::vector<fileInputData> data)
// {
//     std::fstream file;
//     file.open(filePath);
//     if (file.is_open())
//     {
//         for (const auto& fileData : data)
//         {
//             if (fileData.seekLine != -34872832479832423984)
//             {
//                 file.seekp(fileData.seekLine);
//             }
//             else if (!fileData.seekString.empty())
//             {
//                 std::string line;
//                 while(getline(file, line))
//                 {
//                     if (line == fileData.seekString)
//                     {
                        
//                     }
//                 }
//             }
//             else if (!fileData.keyString.empty())
//             {
//                 std::string line;
//                 while(getline(file, line))
//                 {
//                     if (line == fileData.seekString)
//                     {
                        
//                     }
//                 }
//             }
//         }
//     }

//     return -1;
// }

struct fileJsonContent {
    std::string value;
    int type;
    std::string overwrite;
};

enum JSONEDIT {
    KEYDELETE = 32742394
};

int editJsonFile(const std::string& path, std::vector<fileJsonContent> jsonContent)
{
    try
    {
        auto json = JSON::parseFromFile(path);

        std::map <std::string, fileJsonContent> dataBuffer;

        for (const auto& jsonPair : json.getObject())
        {
            dataBuffer[jsonPair.first].type = json.getObject().at(jsonPair.first).getType();

            if (jsonPair.second.getType() == JSON::Number)
            {
                dataBuffer[jsonPair.first].value = std::to_string(jsonPair.second.getNumber());
            }
            else if (jsonPair.second.getType() == JSON::Bool)
            {
                dataBuffer[jsonPair.first].value = std::to_string(jsonPair.second.getNumber());
            }
            else if (jsonPair.second.getType() == JSON::String)
            {
                dataBuffer[jsonPair.first].value = jsonPair.second.getString();
            }
        }

        for (const auto& itr : jsonContent)
        {
            dataBuffer[itr.value].value = itr.overwrite;
            dataBuffer[itr.value].type = itr.type;
        }

        JSONEncoder::JSONObject jsonOutput;

        for (const auto& pair : dataBuffer)
        {
            if (pair.second.type == JSON::String)
            {
                jsonOutput.add(pair.first, new JSONEncoder::JSONString(pair.second.value));
            }
            else if (pair.second.type == JSON::Number)
            {
                jsonOutput.add(pair.first, new JSONEncoder::JSONNumber(std::stoi(pair.second.value)));
            }
            else if (pair.second.type == JSON::Bool)
            {
                jsonOutput.add(pair.first, new JSONEncoder::JSONBool(std::stoi(pair.second.value)));
            }
            else if (pair.second.type == JSONEDIT::KEYDELETE)
            {
                
            }
        }

        std::string output = JSONEncoder::formatJson(jsonOutput.stringify());

        std::ofstream saveFile;
        saveFile.open(path);
        saveFile << output;
        saveFile.close();

        return 1;
    }
    catch (std::exception e) {}

    return -1;
}

void updateJson()
{
    // editJsonFile("asdf", {{{"value1"},{JSON::String},{"test1"}},{}});
}