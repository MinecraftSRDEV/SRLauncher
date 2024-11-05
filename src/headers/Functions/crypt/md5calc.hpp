std::string calcFileMD(const std::string& path)
{
    std::string md5Str;
    try
    {
        MD5 hash;
        md5Str = hash.calculateFromFile(path);
    }
    catch (std::exception e)
    {
        return "";
    }

    return md5Str;
}

void savemd5File(const std::string& destPath, const std::string& sourcePath)
{
    std::ofstream file;
    file.open(destPath + "/" + fs::path(sourcePath).filename().replace_extension().string() + ".md5");
    file << calcFileMD(sourcePath);
    file.close();
}