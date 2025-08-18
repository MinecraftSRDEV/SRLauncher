std::string getBetterBuildUID(const fs::path& path)
{
    std::ifstream getUID;

    getUID.open(path.string() + "/UID.txt");
    std::string uid;
    getUID >> uid;
    getUID.close();
    return uid;
}