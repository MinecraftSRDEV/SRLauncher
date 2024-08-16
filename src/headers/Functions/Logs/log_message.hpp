void log_message(std::string message, int type)
{
    std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	
    int cur_H = now->tm_hour;
	int cur_M = now->tm_min;
	int cur_S = now->tm_sec;

    std::string type_string;
    std::string log_output;

    
    switch(type)
    {
        case LOG_TYPES::LOG_ERROR:
        {
            log_output = " [ERROR] ";
            std::cout << Red;
            break;
        }
        case LOG_TYPES::LOG_INFO:
        {
            log_output = " [INFO] ";
            std::cout << Cyan;
            break;
        }
        case LOG_TYPES::LOG_WARN:
        {
            log_output = " [WARNING] ";
            std::cout << Yellow;
            break;
        }
        default:
        {
            log_output = " [INFO] ";
            std::cout << Cyan;
            break;
        }
    }

    log_output += std::to_string(cur_H) + ":" + std::to_string(cur_M) + ":" + std::to_string(cur_S) + " " + message;

    std::cout << log_output << Clear << std::endl;
    logs[logs.size() + 1] = log_output;
}