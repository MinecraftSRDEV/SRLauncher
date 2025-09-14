void openInBrowser(const std::string& url)
{
    try
    {
        std::string open = url.substr(url.find("http"));
        ShellExecuteA(NULL, "open", open.c_str(), NULL, NULL, SW_SHOWNORMAL);    
    }
    catch(const std::exception& e) {}
}