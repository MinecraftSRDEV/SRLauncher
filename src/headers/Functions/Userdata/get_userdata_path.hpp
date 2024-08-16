std::string getUserProfile()
{
    std::string userProfile = std::getenv("USERPROFILE");
    if (userProfile.empty()) {
        log_message("cannot get USERPROFILE path", LOG_TYPES::LOG_ERROR);
        return "";
    }

    log_message("get USERPROFILE path successfully", LOG_TYPES::LOG_INFO);
    return userProfile;
}