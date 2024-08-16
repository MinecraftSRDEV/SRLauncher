std::string reduceBackslashes(std::string input)
{
    std::string result;
    bool lastWasBackslash = false;

    for (char c : input)
    {
        if (c == '\\')
        {
            if (!lastWasBackslash)
            {
                result += c;
                lastWasBackslash = true;
            }
        }
        else
        {
            result += c;
            lastWasBackslash = false;
        }
    }

    return result;
}