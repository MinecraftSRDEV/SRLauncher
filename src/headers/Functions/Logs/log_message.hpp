namespace ConsoleElements
{
    sfg::Textfield console;
}

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
        case LogTypes::LOG_ERROR:
        {
            log_output = " [ERROR] ";
            if (display_log_colors == true)
            {
                std::cout << RED;    
            }
            break;
        }
        case LogTypes::LOG_INFO:
        {
            log_output = " [INFO] ";
            if (display_log_colors == true)
            {
                std::cout << CYAN;    
            }
            break;
        }
        case LogTypes::LOG_WARN:
        {
            log_output = " [WARNING] ";
            if (display_log_colors == true)
            {
                std::cout << YELLOW;    
            }
            break;
        }
        case LogTypes::LOG_EXCEPTION:
        {
            log_output = " [EXCEPTION] ";
            if (display_log_colors == true)
            {
                std::cout << RED;
            }
            break;
        }
        default:
        {
            log_output = " [INFO] ";
            if (display_log_colors == true)
            {
                std::cout << CYAN;    
            }
            break;
        }
    }

    log_output += std::to_string(cur_H) + ":" + std::to_string(cur_M) + ":" + std::to_string(cur_S) + " " + message;

    ConsoleElements::console.addText(log_output);

    std::cout << log_output;
    if (display_log_colors == true)
    {
        std::cout << CLEAR;
    }
    std::cout << std::endl;
    logs[logs.size() + 1] = log_output;
}