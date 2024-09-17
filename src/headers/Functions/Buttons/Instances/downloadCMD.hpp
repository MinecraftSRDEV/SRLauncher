size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::ofstream* os = static_cast<std::ofstream*>(userp);
    os->write(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

size_t WriteCallback2(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    size_t oldLength = s->size();
    try {
        s->resize(oldLength + newLength);
    } catch (std::bad_alloc &e) {
        // handle memory problem
        return 0;
    }

    std::copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);
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

std::string fetchHTML(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback2);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

size_t findIgnoreCase(const std::string& data, const std::string& toSearch, size_t pos = 0) {
    auto it = std::search(
        data.begin() + pos, data.end(),
        toSearch.begin(), toSearch.end(),
        [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
    );
    if (it != data.end()) return it - data.begin();
    else return std::string::npos;
}

void extractListItems(const std::string& htmlContent) {
    
    // HtmlParser parser;

    // shared_ptr<HtmlDocument> doc = parser.Parse(htmlContent.c_str(), htmlContent.size());

    // std::vector<shared_ptr<HtmlElement>> center = doc->GetElementByClassName("center");

    // if(!center.empty()){
    //     std::cout << center[0]->GetName() << std::endl;
    //     std::cout << center[0]->GetAttribute("id") << std::endl;
    // }
    // else
    // {
    //     std::cout << "empty" << std::endl;
    // }

    // size_t ulStartPos = 0;
    // size_t ulEndPos = 0;

    // // Szukanie każdego <ul>
    // while ((ulStartPos = findIgnoreCase(htmlContent, "<ul", ulEndPos)) != std::string::npos) {
    //     ulEndPos = findIgnoreCase(htmlContent, "</ul>", ulStartPos);
    //     if (ulEndPos == std::string::npos) break;

    //     // Przetwarzanie zawartości <ul>
    //     size_t liStartPos = ulStartPos;
    //     size_t liEndPos = ulStartPos;

    //     // Szukanie każdego <li> w obrębie znalezionego <ul>
    //     while ((liStartPos = findIgnoreCase(htmlContent, "<li", liEndPos)) != std::string::npos && liStartPos < ulEndPos) {
    //         liEndPos = findIgnoreCase(htmlContent, "</li>", liStartPos);
    //         if (liEndPos == std::string::npos || liEndPos > ulEndPos) break;

    //         // Wyodrębnienie zawartości <li>
    //         size_t liContentStart = htmlContent.find('>', liStartPos) + 1;
    //         size_t liContentEnd = liEndPos;
    //         if (liContentStart < liContentEnd) {
    //             std::string liContent = htmlContent.substr(liContentStart, liContentEnd - liContentStart);
    //             std::cout << liContent << std::endl;
    //         }
    //     }
    // }
}

void display_version_log()
{
    std::string url = "https://slimerancher.fandom.com/wiki/Game_Versions/Version_1.0.0"; // Replace with the target URL
    std::string htmlContent = fetchHTML(url);
    // std::cout << htmlContent << std::endl;

    if (!htmlContent.empty()) {
        extractListItems(htmlContent);
    } else {
        std::cerr << "Failed to fetch content from the URL." << std::endl;
    }
}