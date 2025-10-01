namespace dateFormat
{
    struct dateInStr
    {
        std::string YEAR;
        std::string MONTH;
        std::string DAY;
        std::string HOUR;
        std::string MINUTE;
        std::string SECONDS;
    };

    struct dateInNum
    {
        int YEAR;
        int MONTH;
        int DAY;
        int HOUR;
        int MINUTE;
        int SECONDS;
    };

    dateInNum numeratic;

    dateInStr stringfied;

    std::string getStringfiedDateString()
    {
        return std::string(stringfied.YEAR + "_" + stringfied.DAY + "_" + stringfied.MONTH + "_" + stringfied.HOUR + "_" + stringfied.MINUTE + "_" + stringfied.SECONDS);
    }

    bool getDateAtRun()
    {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);

        numeratic.YEAR = (now->tm_year + 1900);
        numeratic.MONTH = (now->tm_mon + 1);
        numeratic.DAY = now->tm_mday;
        numeratic.HOUR = now->tm_hour;
        numeratic.MINUTE = now->tm_min;
        numeratic.SECONDS = now->tm_sec;

        try
        {
            stringfied.YEAR = std::to_string(numeratic.YEAR);
            stringfied.MONTH = std::to_string(numeratic.MONTH);
            stringfied.DAY = std::to_string(numeratic.DAY);
            stringfied.HOUR = std::to_string(numeratic.HOUR);
            stringfied.MINUTE = std::to_string(numeratic.MINUTE);
            stringfied.SECONDS = std::to_string(numeratic.SECONDS);
        }
        catch(const std::exception& e)
        {
            log_message("Cannot stringfy date format", LOG_ERROR);
            return false;
        }

        return true;
    }
}