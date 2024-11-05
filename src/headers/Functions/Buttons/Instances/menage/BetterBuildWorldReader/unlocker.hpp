// Funkcja usuwająca łańcuch znaków z danych binarnych i zapisująca do nowego pliku
void removeStringFromBinaryFile(const std::string& inputFilePath, const std::string& outputFilePath, const std::string& targetString) {
    // Otwieranie pliku binarnego do odczytu
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Nie udało się otworzyć pliku: " << inputFilePath << std::endl;
        return;
    }

    // Przeniesienie danych z pliku do wektora bajtów
    std::vector<char> buffer((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    // Konwersja danych na std::string dla ułatwienia przetwarzania
    std::string data(buffer.begin(), buffer.end());
    size_t pos = 0;

    // Usunięcie wszystkich wystąpień targetString
    while ((pos = data.find(targetString, pos)) != std::string::npos) {
        data.erase(pos, targetString.size());
    }

    // Zapisanie zmodyfikowanych danych do nowego pliku
    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Nie udało się otworzyć pliku do zapisu: " << outputFilePath << std::endl;
        return;
    }

    outputFile.write(data.c_str(), data.size());
    outputFile.close();

    std::cout << "Plik został zmodyfikowany i zapisany jako: " << outputFilePath << std::endl;
}