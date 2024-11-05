struct Playtime {
    sf::Int64 miliseconds = 0;
    sf::Int64 seconds = 0;
    sf::Int64 minutes = 0;
    sf::Int64 hours = 0;
};

Playtime calcPlaytime(sf::Int64 playTimeMiliseconds)
{
    Playtime time;

    long long totalMilliseconds = playTimeMiliseconds;

    time.hours = totalMilliseconds / (sf::Int64(1000) * sf::Int64(60) * sf::Int64(60));
    totalMilliseconds %= (sf::Int64(1000) * sf::Int64(60) * sf::Int64(60));

    time.minutes = totalMilliseconds / ((1000) * (60));
    totalMilliseconds %= (sf::Int64(1000) * sf::Int64(60));

    time.seconds = totalMilliseconds / sf::Int64(1000);
    totalMilliseconds %= sf::Int64(1000);

    time.miliseconds = totalMilliseconds;

    return time;
}