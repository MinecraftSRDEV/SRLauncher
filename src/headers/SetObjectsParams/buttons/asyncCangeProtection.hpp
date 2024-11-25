void setUiProtection(bool state = false)
{
    MainCategory_button.setBlockState(state);
    InstancesCategory_button.setBlockState(state);
    SettingsCategory_button.setBlockState(state);
    VersionsCategory_button.setBlockState(state);

    launch_game_button.setBlockState(state);
}