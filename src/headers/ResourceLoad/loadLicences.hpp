void readLicenseFile(const std::string& path)
{
    std::ifstream file;
    file.open(path);
    std::string outLine;
    while(getline(file, outLine))
    {
        SettingsElemets::subcats::licences::licenseField.addText(outLine);
    }
    file.close();
}

void loadLicences()
{
    SettingsElemets::subcats::licences::licenseField.unlockQueue();

    SettingsElemets::subcats::licences::licenseField.addText("SFML");
    readLicenseFile("./assets/externalLicenses/sfml.txt");
    
    SettingsElemets::subcats::licences::licenseField.addText("\n");
    SettingsElemets::subcats::licences::licenseField.addText("\n");

    SettingsElemets::subcats::licences::licenseField.addText("SFML-GUI");
    readLicenseFile("./assets/externalLicenses/sfml-gui.txt");

    SettingsElemets::subcats::licences::licenseField.addText("\n");
    SettingsElemets::subcats::licences::licenseField.addText("\n");

    SettingsElemets::subcats::licences::licenseField.addText("DepotDownloader");
    readLicenseFile("./assets/externalLicenses/depot-downloader.txt");
}