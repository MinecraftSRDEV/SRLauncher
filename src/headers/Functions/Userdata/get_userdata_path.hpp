std::string getUserProfile()
{
    std::string userProfile = std::getenv("USERPROFILE");
    if (userProfile.empty()) {
        std::cerr << "Nie można pobrać ścieżki USERPROFILE." << std::endl;
        return "";
    }

    return userProfile;
}