std::tm convertStringToDate(const std::string& dateTimeString) {
    std::tm dateTime = {};
    
    if (dateTimeString.length() != 15) {
        throw std::invalid_argument("");
    }

    dateTime.tm_year = std::stoi(dateTimeString.substr(0, 4)) - 1900;
    dateTime.tm_mon = std::stoi(dateTimeString.substr(4, 2)) - 1;
    dateTime.tm_mday = std::stoi(dateTimeString.substr(6, 2));
    dateTime.tm_hour = std::stoi(dateTimeString.substr(8, 2));
    dateTime.tm_min = std::stoi(dateTimeString.substr(10, 2));
    dateTime.tm_sec = std::stoi(dateTimeString.substr(12, 2));

    return dateTime;
}

std::string convertTmToString(const std::tm& dateTime) {
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &dateTime);
    return std::string(buffer);
}