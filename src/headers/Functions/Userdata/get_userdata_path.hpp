std::string getUserProfile()
{
    std::string userProfile = std::getenv("USERPROFILE");
    if (userProfile.empty()) {
        log_message("cannot get USERPROFILE path", LogTypes::LOG_ERROR);
        return "";
    }

    log_message("get USERPROFILE path successfully", LogTypes::LOG_INFO);
    return userProfile;
}