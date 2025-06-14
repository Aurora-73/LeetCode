#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

/* 罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。
	字符          数值
	I             1
	V             5
	X             10
	L             50
	C             100
	D             500
	M             1000
例如， 罗马数字 2 写做 II ，即为两个并列的 1 。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。
通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，
所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。
这个特殊的规则只适用于以下六种情况：
I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给定一个罗马数字，将其转换成整数。 */

class Solution {
public:
	unordered_map<char, int> oneChar;
	Solution() {
		oneChar['I'] = 1;
		oneChar['V'] = 5;
		oneChar['X'] = 10;
		oneChar['L'] = 50;
		oneChar['C'] = 100;
		oneChar['D'] = 500;
		oneChar['M'] = 1000;
	}
	int romanToInt(string s) {
		int sum = 0;
		for(int i = s.size() - 1; i >= 0; i--) {
			if(i < s.size() - 1 &&
			   (oneChar[s[i + 1]] == 5 * oneChar[s[i]] || oneChar[s[i + 1]] == 10 * oneChar[s[i]])) {
				sum -= oneChar[s[i]];
			} else {
				sum += oneChar[s[i]];
			}
		}
		return sum;
	}
};

int main() {
	Solution sol;
	cout << sol.romanToInt("MCMXCIV");
}