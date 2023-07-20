#include <vector>
#include "logger.h"

auto main(void) -> int
{
	system("chcp 1251");
	system("cls");
	Logger logger("./log.txt");
	std::vector<std::string> logs;
	std::vector<std::thread> th {};
	srand((unsigned int) time(NULL));
	size_t userSenderNumb = 0, userRecipientNumb = 0, logNumb = 0;
	for (auto i = 0; i < 10; i++)
	{
		userSenderNumb = static_cast<size_t>(rand() % 10) + 1;
		userRecipientNumb = static_cast<size_t>(rand() % 10) + 1;
		logs.push_back("User" + std::to_string(userSenderNumb) + " to User" 
			+ std::to_string(userRecipientNumb) + " : Привет, потоки!");
	}
	for (auto i = 0; i < logs.size() * 2; i += 2)
	{
		th.push_back(std::thread(&Logger::setInfo, &logger, i + 1, 
			std::ref(logs[i / 2])));
		logNumb = static_cast<size_t>(rand() % 100) + 1;
		th.push_back(std::thread(&Logger::getInfo, &logger, i + 2, logNumb));
	}
	for (auto &th : th)
		th.join();
	return 0;
}