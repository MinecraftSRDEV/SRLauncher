std::string runAssemblyReader(const std::string& path)
{
    std::string command = fs::path(runtime_directory / "assets" / "components" / "SRLAssemblyReader" / "bin" / "Release" / "net8.0" / "SRLAssemblyReader.exe").string() + " \"" +path+ "\"";

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return "";
    }

    std::vector<std::string> List;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        List.emplace_back(buffer);
    }

    std::string output = "Assembly references list\n\n";
    for(const auto& itr : List)
    {
        try
        {
            output += itr.substr(0, itr.find(", Culture"));
            output += "\n";
        }
        catch (std::exception e) {}
    }

    return output;
}