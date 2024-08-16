std::string formatPathForSystem(std::string path)
{
    if (path.find(' ') != std::string::npos)
    {
        return "\"" + path + "\"";
    }
    return path;
}