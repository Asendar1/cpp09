#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <exception>
#include <string>
#include <cstdlib>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _data;
		std::map<std::string, float> _userData;

	public:
		BitcoinExchange(const std::string &str);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);

		void processExchange();

		class FileOpenException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return "Error: could not open file.";
				}
		};
		class InvalidDataException : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return "Error: invalid data.";
				}
		};
};
