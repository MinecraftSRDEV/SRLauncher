void correctModsIndexesPosition(std::map <std::string, ModClass>& mods, std::map <int, std::string>& indexes)
{
    int pos = 0;
    int len = indexes.size() - 1;

    std::vector <int> indexesPositions;
    int indexPos = 20;

    while (pos < len)
    {
        indexesPositions.emplace_back(indexPos);
        indexPos += 95;
        pos++;
    }

    pos = 0;

    for (const auto& index : indexesPositions)
    {
        std::string indexName = indexes[pos];
        mods[indexName].changePosition(mods[indexName].getPOsition().x, index);
        pos++;
    }
}