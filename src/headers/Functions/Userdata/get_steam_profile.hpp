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
            if (ProfileJson.getObject().at("users").getObject().at(data.uid).getObject().at("AccountName").getString() == SettingsElemets::subcats::steamAccount::profileName_textbox.getText())
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

    SettingsElemets::subcats::steamAccount::profileAccountName_text.setString(tr("IDS_TEXT_STEAMPROFILE_ACNAME") + data.accountName);
    SettingsElemets::subcats::steamAccount::profilePersonalName_text.setString(tr("IDS_TEXT_STEAMPROFILE_PERNAME") + data.personalName);
    SettingsElemets::subcats::steamAccount::profileUID_text.setString(tr("IDS_TEXT_STEAMPROFILE_UID") + data.uid);

    if (fs::exists(steam_default_path.string() + "/config/avatarcache/" + data.uid + ".png") && fs::is_regular_file(steam_default_path.string() + "/config/avatarcache/" + data.uid + ".png"))
    {
        SettingsElemets::subcats::steamAccount::userAvatar_tx.loadFromFile(steam_default_path.string() + "/config/avatarcache/" + data.uid + ".png");
        SettingsElemets::subcats::steamAccount::profileIcon.setTexture(SettingsElemets::subcats::steamAccount::userAvatar_tx);
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
                if (ProfileJson.getObject().at("users").getObject().at(uid).getObject().at("AccountName").getString() == SettingsElemets::subcats::steamAccount::profileName_textbox.getText())
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
            SettingsElemets::subcats::steamAccount::profileOffline_status_text.setString(tr("IDS_TEXT_STEAMPROFILE_OFFLINEMODE") + tr("IDS_ENABLED"));
            return result_offline;
        }
        else
        {
            SettingsElemets::subcats::steamAccount::profileOffline_status_text.setString(tr("IDS_TEXT_STEAMPROFILE_OFFLINEMODE") + tr("IDS_DISABLED"));
            return result_online;
        }
    }
    catch (std::runtime_error e)
    {
        log_message("Cannot read Steam userdata: " + std::string(e.what()), LogTypes::LOG_ERROR);
        SettingsElemets::subcats::steamAccount::profileOffline_status_text.setString(tr("IDS_TEXT_STEAMPROFILE_OFFLINEMODE") + tr("IDS_UNKNOWN"));
        return result_fail;
    }

    SettingsElemets::subcats::steamAccount::profileOffline_status_text.setString(tr("IDS_TEXT_STEAMPROFILE_OFFLINEMODE") + tr("IDS_UNKNOWN"));
    return result_fail;
}

bool getSteamProfile()
{
    SettingsElemets::subcats::steamAccount::profileAccountName_text.setString("");
    SettingsElemets::subcats::steamAccount::profileUID_text.setString("");
    SettingsElemets::subcats::steamAccount::profilePersonalName_text.setString("");
    SettingsElemets::subcats::steamAccount::profileOffline_status_text.setString("");
    SettingsElemets::subcats::steamAccount::profileIcon.setTexture(SettingsElemets::subcats::steamAccount::profile_icon_tx);
    if (fs::exists(steam_default_path) && fs::is_directory(steam_default_path))
    {
        try
        {
            user_offline_mode = getUserOfflineMode();
            if (!parseProfileData().uid.empty())
            {
                SettingsElemets::subcats::steamAccount::Profile_warning_text.setString("");
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
            SettingsElemets::subcats::steamAccount::Profile_warning_text.setString(tr("IDS_TEXT_STEAMPROFILE_GETINFO_FAIL"));
            return false;
        }
        catch (std::out_of_range e)
        {
            log_message("Cannot read Steam userdata: " + std::string(e.what()), LogTypes::LOG_ERROR);
            SettingsElemets::subcats::steamAccount::Profile_warning_text.setString(tr("IDS_TEXT_STEAMPROFILE_GETINFO_FAIL"));
            return false;
        }   
    }
    else
    {
        SettingsElemets::subcats::steamAccount::Profile_warning_text.setString(tr("IDS_TEXT_STEAMPROFILE_GETINFO_FAIL"));
        return false;
    }
    
    SettingsElemets::subcats::steamAccount::Profile_warning_text.setString(tr("IDS_TEXT_STEAMPROFILE_GETINFO_FAIL"));
    return false;
}

void getSteamAccountStats()
{
    bool result = getSteamProfile();
}