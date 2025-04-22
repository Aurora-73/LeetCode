#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution1 {
public:
	int var[7] = {1000, 500, 100, 50, 10, 5, 1};
	char str[7] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
	string intToRoman(int num) {
		string roman;
		while(num > 0) {
			for(int i = 0; i < 7; i++) {
				while(num - var[i] >= 0) {
					num -= var[i];
					roman += str[i];
				}
				if(i < 6) {
					if(num + var[(i / 2 + 1) * 2] >= var[i]) {
						num += var[(i / 2 + 1) * 2] - var[i];
						roman += str[(i / 2 + 1) * 2];
						roman += str[i];
					}
				}
			}
		}
		return roman;
	}
};

class Solution2 {
public:
	int var[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
	string str[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	string intToRoman(int num) {
		string roman;
		while(num > 0) {
			for(int i = 0; i < 13; i++) {
				while(num - var[i] >= 0) {
					num -= var[i];
					roman += str[i];
				}
			}
		}
		return roman;
	}
};

int main() {
	Solution1 sol1;
	Solution2 sol2;
	int num = 1;
	while(num > 0 && num < 4000) {
		cout << "Enter a number 1 <= num <= 3999" << endl;
		cin >> num;
		cout << sol1.intToRoman(num) << " " << sol2.intToRoman(num) << endl;
	}
}
