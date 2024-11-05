UserData parseProfileData()
{
    VDFParser vdf(steam_default_path.string() + "/config/loginusers.vdf");

    auto ProfileJson = JSON::parse(vdf.toJSON(vdf.getRoot()));

    UserData data;

    for (const auto& pair : ProfileJson.getObject().at("users").getObject())
    {
        data.uid = pair.first;
        if (data.uid != "users")
        {
            if (ProfileJson.getObject().at("users").getObject().at(data.uid).getObject().at("AccountName").getString() == SteamProfile_name_textbox.getText())
            {
                break;
            }
            else
            {
                continue;
            }
        }
    }

    // data.uid = ProfileJson.getObject().at("users").getObject().at(data.uid);

    data.accountName = ProfileJson.getObject().at("users").getObject().at(data.uid).getObject().at("AccountName").getString();
    data.personalName = ProfileJson.getObject().at("users").getObject().at(data.uid).getObject().at("PersonaName").getString();

    steam_profile_AccountName_text.setString("Account name: " + data.accountName);
    steam_profile_PersonalName_text.setString("Personal name: " + data.personalName);
    steam_profile_UID_text.setString("Steam UID: " + data.uid);

    if (fs::exists(steam_default_path.string() + "/config/avatarcache/" + data.uid + ".png") && fs::is_regular_file(steam_default_path.string() + "/config/avatarcache/" + data.uid + ".png"))
    {
        userAvatar_tx.loadFromFile(steam_default_path.string() + "/config/avatarcache/" + data.uid + ".png");
        steam_profile_icon.setTexture(userAvatar_tx);
    }
    return data;
}

int getUserOfflineMode()
{
    try
    {
        VDFParser vdf(steam_default_path.string() + "/config/loginusers.vdf");

        auto ProfileJson = JSON::parse(vdf.toJSON(vdf.getRoot()));
        std::string uid;

        for (const auto& pair : ProfileJson.getObject().at("users").getObject())
        {
            uid = pair.first;
            if (uid != "users")
            {
                if (ProfileJson.getObject().at("users").getObject().at(uid).getObject().at("AccountName").getString() == SteamProfile_name_textbox.getText())
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
        }

        if (ProfileJson.getObject().at("users").getObject().at(uid).getObject().at("WantsOfflineMode").getString() == "1")
        {
            steam_profile_offline_status_text.setString("OFFLINE mode: enabled");
            return result_offline;
        }
        else
        {
            steam_profile_offline_status_text.setString("OFFLINE mode: disabled");
            return result_online;
        }
    }
    catch (std::runtime_error e)
    {
        log_message("Cannot read Steam userdata: " + std::string(e.what()), LogTypes::LOG_ERROR);
        steam_profile_offline_status_text.setString("OFFLINE mode: unknown");
        return result_fail;
    }

    steam_profile_offline_status_text.setString("OFFLINE mode: unknown");
    return result_fail;
}

bool getSteamProfile()
{
    SteamAccountSettingsUI::steam_profile_AccountName_text.setString("");
    SteamAccountSettingsUI::steam_profile_UID_text.setString("");
    SteamAccountSettingsUI::steam_profile_PersonalName_text.setString("");
    SteamAccountSettingsUI::steam_profile_offline_status_text.setString("");
    SteamAccountSettingsUI::steam_profile_icon.setTexture(profile_icon_tx);
    if (fs::exists(steam_default_path) && fs::is_directory(steam_default_path))
    {
        try
        {
            user_offline_mode = getUserOfflineMode();
            if (!parseProfileData().uid.empty())
            {
                Profile_warning_text.setString("");
                return true;
            }
            else
            {
                throw(std::runtime_error("cannot get user data"));
            }
        }
        catch (std::runtime_error e)
        {
            log_message("Cannot read Steam userdata: " + std::string(e.what()), LogTypes::LOG_ERROR);
            Profile_warning_text.setString("Cannot get informations about steam user with given name.\nIf steam is installed and user logged, check steam directory path.");
            return false;
        }
        catch (std::out_of_range e)
        {
            log_message("Cannot read Steam userdata: " + std::string(e.what()), LogTypes::LOG_ERROR);
            Profile_warning_text.setString("Cannot get informations about steam user with given name.\nIf steam is installed and user logged, check steam directory path.");
            return false;
        }   
    }
    else
    {
        Profile_warning_text.setString("Cannot get informations about steam user with given name.\nIf steam is installed and user logged, check steam directory path.");
        return false;
    }
    
    Profile_warning_text.setString("Cannot get informations about steam user with given name.\nIf steam is installed and user logged, check steam directory path.");
    return false;
}

void getSteamAccountStats()
{
    bool result = getSteamProfile();
}