#include "BitcoinExchange.hpp"
bool checkFormat(const std::string& date);

BitcoinExchange::BitcoinExchange(const std::string &str)
{
    std::ifstream _CSVfile;
    std::ifstream _userFile;

    _CSVfile.open("data.csv");
    if (!_CSVfile.is_open())
        throw FileOpenException();

    std::string line;
    std::getline(_CSVfile, line); // Skip header
    while (std::getline(_CSVfile, line))
    {
        size_t comma_pos = line.find(',');
        if (comma_pos != std::string::npos)
        {
            std::string date = line.substr(0, comma_pos);
            float value = std::atof(line.substr(comma_pos + 1).c_str());
            _data[date] = value;
        }
    }
    _CSVfile.close();

    _userFile.open(str.c_str());
    if (!_userFile.is_open())
        throw FileOpenException();

    std::string user_line;
    std::getline(_userFile, user_line); // Skip header
    while (std::getline(_userFile, user_line))
    {
        _userData[user_line] = 0; // placeholder
    }
    _userFile.close();
}

BitcoinExchange::~BitcoinExchange()
{
	// Destructor
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	_data = other._data;
	_userData = other._userData;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		_data = other._data;
		_userData = other._userData;
	}
	return *this;
}

void BitcoinExchange::processExchange()
{
    std::map<std::string, float>::iterator it;
    for (it = _userData.begin(); it != _userData.end(); ++it)
    {
        std::string line = it->first;

        size_t pipe_pos = line.find('|');
        if (pipe_pos == std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = line.substr(0, pipe_pos);
        date.erase(0, date.find_first_not_of(" \t"));
        if (!date.empty())
            date.erase(date.find_last_not_of(" \t") + 1);

        if (checkFormat(date) == false)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string value_str = line.substr(pipe_pos + 1);
        value_str.erase(0, value_str.find_first_not_of(" \t"));
        if (!value_str.empty())
            value_str.erase(value_str.find_last_not_of(" \t") + 1);

        if (value_str.empty())
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        float user_value = std::atof(value_str.c_str());

        if (user_value < 0)
        {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        if (user_value > 1000)
        {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        // Find closest date in database
        std::map<std::string, float>::iterator data_it = _data.lower_bound(date);
        if (data_it == _data.end() || (data_it != _data.begin() && data_it->first != date))
        {
            if (data_it != _data.begin())
                --data_it;
            else
            {
                std::cout << "Error: no data available for date: " << date << std::endl;
                continue;
            }
        }

        float bitcoin_value = data_it->second;
        float result = user_value * bitcoin_value;

        std::cout << date << " => " << user_value << " = " << result << std::endl;
    }
}

bool checkFormat(const std::string& date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	std::string year_str = date.substr(0, 4);
	std::string month_str = date.substr(5, 2);
	std::string day_str = date.substr(8, 2);

	for (size_t i = 0; i < year_str.length(); ++i)
	{
		if (!isdigit(year_str[i]))
			return false;
	}
	for (size_t i = 0; i < month_str.length(); ++i)
	{
		if (!isdigit(month_str[i]))
			return false;
	}
	for (size_t i = 0; i < day_str.length(); ++i)
	{
		if (!isdigit(day_str[i]))
			return false;
	}

	int year = std::atoi(year_str.c_str());
	int month = std::atoi(month_str.c_str());
	int day = std::atoi(day_str.c_str());

	if (month < 1 || month > 12)
		return false;

	int days_in_month[] = {31, (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (day < 1 || day > days_in_month[month - 1])
		return false;

	return true;
}
