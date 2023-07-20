#include <iostream>
#include "logger.h"

void Logger::writer(size_t thWID, std::string const &log)
{
	shMtx_.lock();
	logFile_.open(fileName_, std::ios::app);
	logFile_ << log << std::endl;
	logFile_.close();
	std::cout << "Поток #" << thWID << " записал лог: " << log << std::endl;
	shMtx_.unlock();
}

void Logger::reader(size_t thRID, size_t strID)
{
	shMtx_.lock();
	logFile_.open(fileName_, std::ios::in);
	std::string str;
	size_t counter = 1;
	while (!logFile_.eof())
	{
		getline(logFile_, str);
		if (strID == counter)
			break;
		++counter;
	}
	logFile_.close();
	if (!str.empty())
		std::cout << "Поток #" << thRID << " считал строку #" << strID << " :" << str << std::endl;
	else
		std::cout << "Поток #" << thRID << " не нашел в файле строку #" << strID << std::endl;
	shMtx_.unlock();
}

Logger::Logger(std::string const &fileName): fileName_(fileName)
{
	logFile_.open(fileName, std::ios::out | std::ios::in );
	if (!logFile_.is_open())
	{
		logFile_.open(fileName, std::ios::out | std::ios::in | std::ios::trunc);
		if (!logFile_.is_open())
			std::cout << "Невозможно открыть или создать файл " << fileName
				<< std::endl;
	}
	logFile_.close();
}

Logger::~Logger()
{
	logFile_.close();
}

void Logger::setInfo(size_t thWID, std::string const &log)
{
	writer(thWID, log);
}

void Logger::getInfo(size_t thRID, size_t strID)
{
	reader(thRID, strID);
}
