void rundate_get()
{
    std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);

    run_YEAR = (now->tm_year + 1900);
    run_MONTH = (now->tm_mon + 1);
    run_DAY = now->tm_mday;
    run_H = now->tm_hour;
    run_M = now->tm_min;
    run_S = now->tm_sec;
}