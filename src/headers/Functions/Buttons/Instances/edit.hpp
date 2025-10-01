void saveEditedInstance(std::string version, std::string newName, std::string instance_id, std::string iconId, std::string source_path = "")
{
    fs::path instPath = (instances_dir + "\\Slime Rancher_" + instances_list[instance_id].getID());
    auto json = JSON::parseFromFile(instPath.string() + "/info.json");

    JSONEncoder::JSONObject object;

    std::vector <fileJsonContent> content;
    fileJsonContent data;

    data.value = "name";
    data.type = JSON::String;
    data.overwrite = newName;
    content.emplace_back(data);

    data.value = "icon";
    data.type = JSON::String;
    data.overwrite = iconId;
    content.emplace_back(data);

    if (json.getObject().at("version").getString() != version)
    {
        data.value = "edited";
        data.type = JSON::String;
        data.overwrite = version;
        content.emplace_back(data);
    }
    else
    {
        data.value = "edited";
        data.type = JSONEDIT::KEYDELETE;
        data.overwrite = version;
        content.emplace_back(data);
    }

    editJsonFile(instPath.string() + "/info.json", content);
}

void edit_instance_function(std::string instance_id)
{
    // MessageBoxA(NULL, "Function not implemented yet", "Info", MB_ICONINFORMATION | MB_OK);

    if (mounted_instance == instances_list[instance_id].getID())
    {
        MessageBoxA(NULL, tr("IDS_MSG_EDINST_UNMOUNTFIRST").c_str(), "Error", MB_ICONERROR | MB_OK);
    }
    else
    {
        try
        {
            UI_current = EditInstanceMenu;
            fs::path instPath = (instances_dir + "\\Slime Rancher_" + instances_list[instance_id].getID());
            auto json = JSON::parseFromFile(instPath.string() + "/info.json");
            versions_list_ddl.setFromResult(json.getObject().at("version").getString());
            new_instance_name_textbox.setText(json.getObject().at("name").getString());

            std::string iconID;

            editInstanceSource.setString("");
            try
            {
                iconID = json.getObject().at("icon").getString();
            }
            catch (std::exception e) {}
            try
            {
                editInstanceSource.setString(json.getObject().at("source_path").getString());
            }
            catch (std::exception e) {}
            
            selected_instance = instance_id;    

            if (iconID.empty())
            {
                iconID = "pink";
            }
            iconBarScrollWhile(iconID);
        }
        catch (std::runtime_error e) {}
        catch (std::out_of_range e) {}   
    }
}

void setEditedInstace()
{
    try
    {
        saveEditedInstance(versions_list_ddl.getResult(), new_instance_name_textbox.getText(), selected_instance, getInstanceSelectedIcon(), editInstanceSource.getString());
        selected_instance.erase();
        UI_current = UiPages::InstancesMenu;
        refresh_instances_list();
        return;
    }
    catch (std::runtime_error e) {log_message("error code: " + std::string(e.what()), LogTypes::LOG_ERROR);}
    catch (std::out_of_range e) {log_message("error code: " + std::string(e.what()), LogTypes::LOG_ERROR);}
    MessageBoxA(NULL, tr("IDS_MSG_EDINST_FAIL").c_str(), "Error", MB_ICONERROR | MB_OK);
}