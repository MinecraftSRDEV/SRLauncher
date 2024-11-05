template<typename T>
void readBinary(std::ifstream &file, T &value) {
    file.read(reinterpret_cast<char*>(&value), sizeof(T));
}

std::string readString(std::ifstream &file, int length) {
    std::vector<char> buffer(length);
    file.read(buffer.data(), length);
    return std::string(buffer.begin(), buffer.end());
}

WorldData LoadWorld(const std::string& filepath) {
    WorldData worldData = {};
    
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << filepath << std::endl;
        return worldData;
    }

    int32_t num;
    
    // Odczyt wersji mapy (int16)
    readBinary(file, worldData.version);
    
    // Odczyt, czy poziom jest zablokowany (bool)
    readBinary(file, worldData.levelLocked);
    
    if (worldData.levelLocked) {
        // Odczyt długości hasła (int32)
        int32_t passwordLength;
        readBinary(file, passwordLength);
        
        // Odczyt hasła (string o długości passwordLength)
        worldData.levelPassword = readString(file, passwordLength);
    }
    
    // Pominięcie wartości RemoveWorld (bool)
    file.seekg(1, std::ios::cur);
    
    // Odczyt ilości obiektów (int32)
    readBinary(file, worldData.objectCount);

    // Pomiń dane dotyczące obiektów
    for (int i = 0; i < worldData.objectCount; ++i) {
        int32_t stringLength, num5;
        readBinary(file, stringLength);
        
        // Pomiń nazwę obiektu
        file.seekg(stringLength, std::ios::cur);
        
        // Pomiń resztę danych o obiekcie
        file.seekg(4 + 12 + 12 + 12, std::ios::cur);
    }

    // Odczyt ilości spawnerów (int32)
    readBinary(file, worldData.spawnerCount);

    // Pomiń dane dotyczące spawnerów
    for (int i = 0; i < worldData.spawnerCount; ++i) {
        // Pomiń pozycję spawnera (Vector3)
        file.seekg(12, std::ios::cur);
        
        // Pomiń MinSpawns, MaxSpawns, SpawnInterval, SpawnIdCount (int32, float, int32)
        file.seekg(4 + 4 + 4 + 4, std::ios::cur);
        
        int32_t spawnIdCount;
        readBinary(file, spawnIdCount);
        
        // Pomiń listę SpawnIds
        file.seekg(4 * spawnIdCount, std::ios::cur);
    }

    file.close();
    return worldData;
}