#pragma once
#include <string>
#include <fstream>
#include <shared_mutex>

class Logger
{
	std::fstream logFile_;
	std::string fileName_;
	std::shared_mutex shMtx_;
	void writer(size_t thWID, std::string const &log);
	void reader(size_t thRID, size_t strID);
public:
	Logger(std::string const &fileName);
	~Logger();
	void setInfo(size_t thWID, std::string const &log);
	void getInfo(size_t thRID, size_t strID);
};