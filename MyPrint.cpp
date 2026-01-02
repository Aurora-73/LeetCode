// Created: 2026-01-01
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

// 练习，参数包
void printhelp(ostringstream &oss, const string &str, size_t i) {
	while(i < str.size()) oss << str[i++];
}

template <typename T, typename... Args>
void printhelp(ostringstream &oss, const string &str, size_t i, T value, Args... args) {
	while(i < str.size() && str[i] != '%') oss << str[i++];
	if(i < str.size()) {
		oss << value;
		printhelp(oss, str, i + 1, args...);
	}
}

template <typename... Args>
void print(const string &str, Args... args) {
	ostringstream oss;
	printhelp(oss, str, 0, args...);
	cout << oss.str() << endl;
}

int main() {
	print("get a val");
	print("get val %", 0);
	print("a=% b=% c=%", 1, 2, 3);

	std::cout << std::format("get a val") << std::endl;
	std::cout << std::format("get val {}", 0) << std::endl;
	std::cout << std::format("a={} b={} c={}", 1, 2, 3) << std::endl;
}