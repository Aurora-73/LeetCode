// Created: 2025-05-18
#include "MyUtils.hpp"

/*  */

class Solution {
public:
	vector<int> plusOne(vector<int> &digits) {
		bool size_up = true;
		for(auto &x : digits) {
			if(x != 9) {
				size_up = false;
				break;
			}
		}
		if(size_up) {
			digits.resize(digits.size() + 1);
			for(int i = digits.size() - 2; i >= 0; --i) {
				digits[i + 1] = digits[i];
			}
			digits[0] = 0;
		}
		for(int i = digits.size() - 1; i >= 0; --i) {
			if(digits[i] == 9) {
				digits[i] = 0;
			} else {
				++digits[i];
				break;
			}
		}
		return digits;
	}
};

class Solution {
public:
	vector<int> plusOne(vector<int> &digits) {
		bool size_up = true;
		for(auto &x : digits) {
			if(x != 9) {
				size_up = false;
				break;
			}
		}
		if(size_up) {
			vector<int> res(digits.size() + 1, 0);
			res[0] = 1;
			return res;
		}
		for(int i = digits.size() - 1; i >= 0; --i) {
			if(digits[i] == 9) {
				digits[i] = 0;
			} else {
				++digits[i];
				break;
			}
		}
		return digits;
	}
};

int main() {
	Solution sol;
	vector<int> digits { 9, 8, 9, 9 };
	cout << sol.plusOne(digits);
}