size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::ofstream* os = static_cast<std::ofstream*>(userp);
    os->write(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

void downloadSteamCMD()
{
    CURL* curl;
    CURLcode res;
    std::string url = "https://steamcdn-a.akamaihd.net/client/installer/steamcmd.zip"; // Podaj URL pliku ZIP
    fs::path path = defaultDir / "temp";
    std::string outfilename = path.string() + "/cmd.zip"; // Nazwa pliku wyjściowego

    std::ofstream ofs(outfilename, std::ios::binary);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ofs);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);

        std::string zipFilePath = outfilename;
        fs::path steamcmdpath = defaultDir / "SteamCMD";
        std::string outputFolder = steamcmdpath.string();
    }

    ofs.close();
}