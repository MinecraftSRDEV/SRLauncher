std::string decryptor(std::string deencrypt_input)
{
	std::stringstream ss;
	std::stringstream ss2;
	int length_preconv;
	std::string number_str;
	int passw_length;
	int point_in_str = 0;
	std::string decrypted_string;

	try
	{	
		decrypted_string.erase(); 
		
		length_preconv = deencrypt_input.length() - 2;

		number_str += deencrypt_input[length_preconv];
		length_preconv++;
		number_str += deencrypt_input[length_preconv];

		passw_length = std::stoi(number_str);

		char read_var;
		char char_count;
		int count;
		int ascii_count;
		std::string str_count;
		std::string ascii_ready_var;
		char deencrypted_char;
		int count_2;
		
		int read_leng;
		
		while(passw_length > 0)
		{
			passw_length--;
			char_count = deencrypt_input[point_in_str];
			point_in_str++;	
			ss.clear();
			ss << char_count;
			ss >> count;
			ss.clear();
			ss << char_count;
			ss >> str_count;
			ss.clear();
			ss << str_count;
			ss >> count;
		
			for (count > 0; count--;)
			{
				read_var = deencrypt_input[point_in_str];
				point_in_str++;
				
				if (read_var != 'x')
				{
					ss.clear();
					ss << read_var;
					ss >> str_count;
					
					ascii_ready_var = ascii_ready_var + str_count;	
				}
				else
				{
					break;
				}
			}
			
			count_2 = std::stoi(ascii_ready_var);
			
			deencrypted_char = count_2;
			
			std::string str_dc;
			ss.clear();
			ss << deencrypted_char;
			ss >> str_dc;
			
			decrypted_string += str_dc;
			
			read_var = 0;
			char_count = ' ';
			count = 0;
			ascii_count = 0;
			ss.clear();
			str_count.clear();
			ascii_ready_var = " ";
			deencrypted_char = ' ';
		
		}
		
		std::string x_she;
		char past_x1;
		char past_x2;
		int past_x1_str;
		int past_x2_str;
		
		char chara;

		x_she = std::to_string(chara);

		if (x_she != "x")
		{
			
		}
		else
		{
			ss2.clear();
			ss2 << past_x1;
			ss2 >> past_x1_str;
			ss2.clear();
			ss2 << past_x2;
			ss2 >> past_x2_str;

		}
		
		if (decrypted_string.empty())
		{
			log_message("Cannot decrypt: " + deencrypt_input, LOG_TYPES::LOG_ERROR);
		}

		return decrypted_string;	
	}
	catch (std::invalid_argument e)
	{
		std::string errmsg = e.what();
		log_message("Decryptor error: " + errmsg, LOG_TYPES::LOG_ERROR);
	}
	catch (std::out_of_range e)
	{
		std::string errmsg = e.what();
		log_message("Decryptor error: " + errmsg, LOG_TYPES::LOG_ERROR);
	}
	
    return "";
}