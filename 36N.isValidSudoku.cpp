#include "MyUtils.h"
#include <chrono>
using namespace std::chrono;

// Solution0-2的方法一样，只是比较不同的容器的差别
// Solution3-4的方法更好

class Solution {
public:
	bool isValidSudoku(vector<vector<char>> &board) {
		for(int i = 0; i < 9; i++) {
			vector<bool> set(10, 0);
			for(int j = 0; j < 9; j++) {
				if(board[i][j] != '.') {
					if(set[board[i][j] - '0']) {
						return false;
					}
					set[board[i][j] - '0'] = true;
				}
			}
		} //逐行
		for(int i = 0; i < 9; i++) {
			vector<bool> set(10, 0);
			for(int j = 0; j < 9; j++) {
				if(board[j][i] != '.') {
					if(set[board[j][i] - '0']) {
						return false;
					}
					set[board[j][i] - '0'] = true;
				}
			}
		} //逐列
		for(int m = 0; m < 3; m++) {
			for(int n = 0; n < 3; n++) {
				vector<bool> set(10, 0);
				// 左上角坐标为 (3 * m, 3 * n)
				for(int i = 0; i < 3; i++) {
					for(int j = 0; j < 3; j++) {
						if(board[3 * m + i][3 * n + j] != '.') {
							if(set[board[3 * m + i][3 * n + j] - '0']) {
								return false;
							}
							set[board[3 * m + i][3 * n + j] - '0'] = true;
						}
					}
				}
			}
		}
		return true;
	}
};

class Solution0 {
public:
	bool isValidSudoku(vector<vector<char>> &board) {
		for(int i = 0; i < 9; i++) {
			array<bool, 10> set; //不涉及封装，比vector要快
			set.fill(false);
			for(int j = 0; j < 9; j++) {
				if(board[i][j] != '.') {
					if(set[board[i][j] - '0']) {
						return false;
					}
					set[board[i][j] - '0'] = true;
				}
			}
		} //逐行
		for(int i = 0; i < 9; i++) {
			array<bool, 10> set; //不涉及封装，比vector要快
			set.fill(false);
			for(int j = 0; j < 9; j++) {
				if(board[j][i] != '.') {
					if(set[board[j][i] - '0']) {
						return false;
					}
					set[board[j][i] - '0'] = true;
				}
			}
		} //逐列
		for(int m = 0; m < 3; m++) {
			for(int n = 0; n < 3; n++) {
				array<bool, 10> set; //不涉及封装，比vector要快
				set.fill(false);
				// 左上角坐标为 (3 * m, 3 * n)
				for(int i = 0; i < 3; i++) {
					for(int j = 0; j < 3; j++) {
						if(board[3 * m + i][3 * n + j] != '.') {
							if(set[board[3 * m + i][3 * n + j] - '0']) {
								return false;
							}
							set[board[3 * m + i][3 * n + j] - '0'] = true;
						}
					}
				}
			}
		}
		return true;
	}
};

class Solution1 {
public:
	bool isValidSudoku(vector<vector<char>> &board) {
		for(int i = 0; i < 9; i++) {
			auto set = make_unique<bool[]>(10); //不涉及封装，比vector要快
			for(int j = 0; j < 9; j++) {
				if(board[i][j] != '.') {
					if(set[board[i][j] - '0']) {
						return false;
					}
					set[board[i][j] - '0'] = true;
				}
			}
		} //逐行
		for(int i = 0; i < 9; i++) {
			auto set = make_unique<bool[]>(10);
			for(int j = 0; j < 9; j++) {
				if(board[j][i] != '.') {
					if(set[board[j][i] - '0']) {
						return false;
					}
					set[board[j][i] - '0'] = true;
				}
			}
		} //逐列
		for(int m = 0; m < 3; m++) {
			for(int n = 0; n < 3; n++) {
				auto set = make_unique<bool[]>(10);
				// 左上角坐标为 (3 * m, 3 * n)
				for(int i = 0; i < 3; i++) {
					for(int j = 0; j < 3; j++) {
						if(board[3 * m + i][3 * n + j] != '.') {
							if(set[board[3 * m + i][3 * n + j] - '0']) {
								return false;
							}
							set[board[3 * m + i][3 * n + j] - '0'] = true;
						}
					}
				}
			}
		}
		return true;
	}
};

class Solution2 {
public:
	bool isValidSudoku(vector<vector<char>> &board) {
		for(int i = 0; i < 9; i++) {
			bitset<10> set;
			for(int j = 0; j < 9; j++) {
				if(board[i][j] != '.') {
					int num = board[i][j] - '0';
					if(set[num]) {
						return false;
					}
					set[num] = true;
				}
			}
		} // 检查行

		for(int i = 0; i < 9; i++) {
			bitset<10> set;
			for(int j = 0; j < 9; j++) {
				if(board[j][i] != '.') {
					int num = board[j][i] - '0';
					if(set[num]) {
						return false;
					}
					set[num] = true;
				}
			}
		} // 检查列

		for(int m = 0; m < 3; m++) {
			for(int n = 0; n < 3; n++) {
				bitset<10> set;
				for(int i = 0; i < 3; i++) {
					for(int j = 0; j < 3; j++) {
						char c = board[3 * m + i][3 * n + j];
						if(c != '.') {
							int num = c - '0';
							if(set[num]) {
								return false;
							}
							set[num] = true;
						}
					}
				}
			}
		} // 检查 3x3 宫格
		return true;
	}
};

class Solution3 {
public:
	bool isValidSudoku(vector<vector<char>> &board) {
		//使用位运算加速
		vector<int> rows(9);
		vector<int> cols(9);
		vector<int> block(9);

		for(int i = 0; i < 9; ++i) {
			for(int j = 0; j < 9; ++j) {
				if(board[i][j] == '.')
					continue;
				int x = board[i][j] - '0';
				if(rows[i] >> x & 1 || cols[j] >> x & 1 || block[(i / 3) * 3 + j / 3] >> x & 1) {
					return false;
				}
				//加入
				rows[i] |= 1 << x;
				cols[j] |= 1 << x;
				block[(i / 3) * 3 + j / 3] |= 1 << x;
			}
		}
		return true;
	}
};

class Solution4 {
public:
	bool isValidSudoku(vector<vector<char>> &board) {
		// 使用 bitset 模拟集合
		array<bitset<10>, 9> rows;
		array<bitset<10>, 9> cols;
		array<bitset<10>, 9> block;

		for(int i = 0; i < 9; ++i) {
			for(int j = 0; j < 9; ++j) {
				if(board[i][j] == '.')
					continue;
				int x = board[i][j] - '0';
				if(rows[i][x] || cols[j][x] || block[(i / 3) * 3 + j / 3][x]) {
					return false;
				}
				rows[i].set(x);
				cols[j].set(x);
				block[(i / 3) * 3 + j / 3].set(x);
			}
		}
		return true;
	}
};

int main() {
	vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
	                              {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
	                              {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
	                              {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
	                              {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
	                              {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
	                              {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
	                              {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
	                              {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

	const int iterations = 100000;

	{
		Solution sol;
		auto start = high_resolution_clock::now();
		for(int i = 0; i < iterations; ++i)
			sol.isValidSudoku(board);
		auto end = high_resolution_clock::now();
		cout << "Solution (vector<bool>): " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
	}

	{
		Solution0 sol;
		auto start = high_resolution_clock::now();
		for(int i = 0; i < iterations; ++i)
			sol.isValidSudoku(board);
		auto end = high_resolution_clock::now();
		cout << "Solution0 (array<bool, 10>): " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
	}

	{
		Solution1 sol;
		auto start = high_resolution_clock::now();
		for(int i = 0; i < iterations; ++i)
			sol.isValidSudoku(board);
		auto end = high_resolution_clock::now();
		cout << "Solution1 (unique_ptr<bool[]>): " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
	}

	{
		Solution2 sol;
		auto start = high_resolution_clock::now();
		for(int i = 0; i < iterations; ++i)
			sol.isValidSudoku(board);
		auto end = high_resolution_clock::now();
		cout << "Solution2 (bitset): " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
	}

	{
		Solution3 sol;
		auto start = high_resolution_clock::now();
		for(int i = 0; i < iterations; ++i)
			sol.isValidSudoku(board);
		auto end = high_resolution_clock::now();
		cout << "Solution3 (bitwise int): " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
	}

	{
		Solution4 sol;
		auto start = high_resolution_clock::now();
		for(int i = 0; i < iterations; ++i)
			sol.isValidSudoku(board);
		auto end = high_resolution_clock::now();
		cout << "Solution4 (bitwise int): " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
	}

	return 0;
}