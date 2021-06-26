#include <iostream>
#include <fstream>
#include <list>
#include <functional>
#include <algorithm>
#include <future>
#include <filesystem>
#include<map>
#include<thread>

class Communicate {
private:
	std::string _folder;
	std::list<std::string > _users;
	std::map<std::string, std::future<void>> activeThread;


	std::list<std::string> GetNewUsers() {
		for (auto& entry : std::filesystem::directory_iterator(_folder)) {
			if (std::find(_users.begin(), _users.end(), entry.path().generic_string()) == _users.end()) {

				_users.push_back(entry.path().generic_string());
				std::future<void> f = std::async(std::launch::async, &Communicate::fileReader, this, entry.path().generic_string());
				activeThread.insert(std::pair<std::string, std::future<void>>(entry.path().generic_string(), std::move(f)));
			}
		}
		return _users;
	}

	std::list<std::string> DeleteUserFromList() {
		std::list <std::string> temp;
		std::list <std::list<std::string>::iterator> delUsers;
		for (auto& entry : std::filesystem::directory_iterator(_folder))
			temp.push_back(entry.path().generic_string());
		for (auto it = _users.begin(); it != _users.end(); it++) {
			if (std::find(temp.begin(), temp.end(), *it) == temp.end()) {
				activeThread.erase(*it);
				delUsers.push_back(it);
			}
		}
		for (auto& item : delUsers) {
			_users.erase(item);
		}
		return _users;
	}

	void fileReader(const std::string& fileName) {
		for (;;) {
			std::ifstream read(fileName);
			if (!read.is_open())break;
			std::string s;
			read >> s;
			if (s != "DONE") {
				std::this_thread::sleep_for(std::chrono::seconds(2));
				std::cout << fileName << ": " << s << std::endl;
				std::ofstream wr(fileName);
				wr << "DONE";
				wr.close();
			}
		}
	}
public:
	Communicate(const std::string& path) :_folder(path) {

	}

	void Check() {
		for (;;) {
			GetNewUsers();
			auto users = DeleteUserFromList();
			std::this_thread::sleep_for(std::chrono::seconds(3));
			if (users.empty())break;
		}
	}

	~Communicate() {
		for (auto& Item : activeThread) {
			Item.second.wait();
		}
	}
};

int main() {
	Communicate com("D:\\folderUsers");
	com.Check();

	return 0;
}