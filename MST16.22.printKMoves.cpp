// Created: 2026-01-04
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 一只蚂蚁坐在由白色和黑色方格构成的无限网格上。
开始时，网格全白，蚂蚁面向右侧。每行走一步，蚂蚁执行以下操作。
(1) 如果在白色方格上，则翻转方格的颜色，向右(顺时针)转 90 度，并向前移动一个单位。
(2) 如果在黑色方格上，则翻转方格的颜色，向左(逆时针方向)转 90 度，并向前移动一个单位。
编写程序来模拟蚂蚁执行的前 K 个动作，并返回最终的网格。
网格由数组表示，每个元素是一个字符串，代表网格中的一行，黑色方格由"X"表示，白色方格由"_"表示，
蚂蚁所在的位置由"L", "U", "R", "D"表示，分别表示蚂蚁左、上、右、下 的朝向。只需要返回能够包含蚂蚁走过的所有方格的最小矩形。
示例 1：
	输入：0
	输出：{"R"}
示例 2：
	输入：2
	输出：
	{
	 "_X",
	 "LX"
	}
示例 3：
	输入：5
	输出：
	{
	 "_U",
	 "X_",
	 "XX"
	}
	说明：
	K <= 100000 */

class Solution {
public:
	vector<string> printKMoves(int K) {
		unordered_map<pair<int, int>, bool, pairHash> color_map; // 颜色用布尔表示，白色是0，黑色是1
		int i = 0, j = 0, direct = 0, max_i = 0, max_j = 0, min_i = 0, min_j = 0;
		array<char, 4> dir2char { 'R', 'D', 'L', 'U' };
		while(K--) {
			bool &curr_color = color_map[{ i, j }]; // 同时完成三件事：hash查找 不存在就插入 修改
			if(!curr_color) {                       // 先旋转后移动
				direct = (direct + 1) % 4;
			} else {
				direct = (direct - 1 + 4) % 4; // 注意负数要 + 4
			}
			curr_color = !curr_color;
			switch(direct) {
			case 0: ++j; break;
			case 1: ++i; break;
			case 2: --j; break;
			case 3: --i; break;
			default: throw std::runtime_error("Error!");
			}
			max_i = max(i, max_i), max_j = max(j, max_j);
			min_i = min(i, min_i), min_j = min(j, min_j);
		}

		int m = max_i - min_i + 1, n = max_j - min_j + 1;
		vector<string> res(m, string(n, '_')); // 矩形
		for(auto [pa, bcolor] : color_map) {
			if(bcolor) {
				int ii = pa.first - min_i, jj = pa.second - min_j;
				res[ii][jj] = 'X';
			}
		}
		res[i - min_i][j - min_j] = dir2char[direct];
		return res;
	}

private:
	struct pairHash {
		uint64_t operator()(const pair<int, int> &p) const noexcept {
			return ((uint64_t)p.first << 32) ^ (uint64_t)p.second;
		}
	};
};

class Solution1 {
	// 把 point 放在前面，方便在成员函数中使用
	struct point {
		int i, j;
		void moveOneStep(int dir) {
			switch(dir) {
			case 0: ++j; break; // R
			case 1: ++i; break; // D
			case 2: --j; break; // L
			case 3: --i; break; // U
			}
		}
		bool operator==(const point &other) const noexcept {
			return i == other.i && j == other.j;
		}
		struct Hash {
			uint64_t operator()(const point &p) const noexcept {
				// 更严谨的打包：先转换为 uint32_t，再拼接到 uint64_t
				return ((uint64_t)p.i << 32) | (uint64_t)p.j;
			}
		};
	};

public:
	vector<string> printKMoves(int K) {
		unordered_map<point, bool, point::Hash> color_map;
		if(K > 0) color_map.reserve(min<int>(K * 2, 200000)); // 适度 reserve，减少 rehash
		//unordered_map::reserve 不是在给“元素个数”留空间，而是在给 bucket 数量 留空间。

		point pos { 0, 0 };
		int direct = 0; // 0 = R,  1 = D,  2 = L,  3 = U
		int max_i = 0, max_j = 0, min_i = 0, min_j = 0;

		while(K--) {
			bool &curr_color = color_map[pos]; // 若不存在则插入，默认 false(白)
			if(!curr_color) {
				direct = (direct + 1) % 4; // 右转
			} else {
				direct = (direct + 3) % 4; // 左转
			}
			curr_color = !curr_color; // 翻转颜色
			pos.moveOneStep(direct);  // 前进一步

			max_i = max(max_i, pos.i), max_j = max(max_j, pos.j);
			min_i = min(min_i, pos.i), min_j = min(min_j, pos.j);
		}

		int m = max_i - min_i + 1, n = max_j - min_j + 1;
		vector<string> res(m, string(n, '_'));

		for(const auto &[piter, bcolor] : color_map) {
			if(bcolor) { // 黑格
				int ii = piter.i - min_i;
				int jj = piter.j - min_j;
				res[ii][jj] = 'X';
			}
		}

		res[pos.i - min_i][pos.j - min_j] = array<char, 4> { 'R', 'D', 'L', 'U' }[direct];
		return res;
	}
};

int main() {
	Solution sol;
	int K = 100000;
	cout << sol.printKMoves(K) << endl;

	K = 0;
	cout << sol.printKMoves(K) << endl;

	K = 2;
	cout << sol.printKMoves(K) << endl;

	K = 5;
	cout << sol.printKMoves(K) << endl;
}