#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution {
public:
	bool isPalindrome(string s) {
		auto ischar = [](int c) { return (c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a'); };
		auto isdige = [](int c) { return c <= '9' && c >= '0'; };
		int i = 0, j = s.length() - 1;
		while(i < j) {
			while(i < j && !ischar(s[i]) && !isdige(s[i]))
				i++;
			while(i < j && !ischar(s[j]) && !isdige(s[j]))
				j--;
			if(i >= j)
				break;
			if(s[i] != s[j] && !(max(s[j], s[i]) - min(s[j], s[i]) == 'a' - 'A' && ischar(s[i]) && ischar(s[j]))) {
				return false;
			}
			i++;
			j--;
		}
		return true;
	}
};

int main() {
	Solution sol;
	string s;
	// cin >> s;
	cout << sol.isPalindrome("0P");
}