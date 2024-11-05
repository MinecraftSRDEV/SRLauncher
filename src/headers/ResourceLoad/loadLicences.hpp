void readLicenseFile(const std::string& path)
{
    std::ifstream file;
    file.open(path);
    std::string outLine;
    while(getline(file, outLine))
    {
        LicencesUI::licenseField.addText(outLine);
    }
    file.close();
}

void loadLicences()
{
    LicencesUI::licenseField.unlockQueue();

    LicencesUI::licenseField.addText("SFML");
    readLicenseFile("./assets/externalLicenses/sfml.txt");
    
    LicencesUI::licenseField.addText("\n");
    LicencesUI::licenseField.addText("\n");

    LicencesUI::licenseField.addText("SFML-GUI");
    readLicenseFile("./assets/externalLicenses/sfml-gui.txt");

    LicencesUI::licenseField.addText("\n");
    LicencesUI::licenseField.addText("\n");

    LicencesUI::licenseField.addText("DepotDownloader");
    readLicenseFile("./assets/externalLicenses/depot-downloader.txt");
}