std::string encryptor(std::string encrypt_input)
{
	char raw_anal;
	int conv_raw;
	std::stringstream ss;
	int length_passw;
	std::string length_passw_str;
	std::string encrypted_password;
	
	int point_in_str = 0;

    encrypted_password.erase();

	length_passw = encrypt_input.length();

	try
	{		
		while (length_passw > 0)
		{
			length_passw--;
			raw_anal = encrypt_input[point_in_str];
			point_in_str++;
			conv_raw = raw_anal;
			
			std::string cal_length;
			
			ss.clear();
			ss << conv_raw;
			ss >> cal_length;
			
			int length = cal_length.length();
			std::string length_str;
			std::string conv_raw_str;
			
			conv_raw_str.erase();
			
			ss.clear();
			ss << conv_raw;
			ss >> conv_raw_str;
			
			ss.clear();
			ss << length;
			ss >> length_str;
			
			encrypted_password = encrypted_password + length_str;
			encrypted_password = encrypted_password + conv_raw_str;
		}
		
		length_passw = encrypt_input.length();
		
		length_passw_str.erase();
		ss.clear();
		ss << length_passw;
		ss >> length_passw_str;
		
		encrypted_password = encrypted_password + "x";
		encrypted_password = encrypted_password + length_passw_str;

		if (encrypted_password.empty())
		{
			log_message("Cannot encrypt: " + encrypt_input, LOG_TYPES::LOG_ERROR);
		}
		
		return encrypted_password;	
	}
	catch (std::out_of_range e)
	{
		std::string errmsg = e.what();
		log_message("encryptor error: " + errmsg, LOG_TYPES::LOG_ERROR);
	}
	return "";
}