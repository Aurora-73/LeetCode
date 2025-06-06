// Created: 2025-05-03
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/*1007. 行相等的最少多米诺旋转
在一排多米诺骨牌中，tops[i] 和 bottoms[i] 分别代表第 i 个多米诺骨牌的上半部分和下半部分。
（一个多米诺是两个从 1 到 6 的数字同列平铺形成的 —— 该平铺的每一半上都有一个数字。）
我们可以旋转第 i 张多米诺，使得 tops[i] 和 bottoms[i] 的值交换。
返回能使 tops 中所有值或者 bottoms 中所有值都相同的最小旋转次数。
如果无法做到，返回 -1.*/

class Solution1 {
public:
	int minDominoRotations(vector<int> &tops, vector<int> &bottoms) {
		array<int, 6> all { 0 }, up { 0 },
		    down { 0 }; // 必须同时记录上半和下半，因为两边反转的成本可能不一样
		for(int i = 0; i < tops.size(); i++) {
			up[tops[i] - 1]++;
			all[tops[i] - 1]++;
			down[bottoms[i] - 1]++;
			if(tops[i] != bottoms[i]) {
				all[bottoms[i] - 1]++;
			}
		}
		int can = -1;
		for(int i = 0; i < 6; i++) {
			if(all[i] >= tops.size()) {
				can = i;
				break;
			}
		}
		if(can == -1) return -1;
		int minval = min(
		    min(up[can], int(tops.size() - up[can])), min(down[can], int(tops.size() - down[can])));
		return minval;
	}
};

class Solution2 {
public:
	int minDominoRotations(vector<int> &tops, vector<int> &bottoms) {
		int Aup = 0, Adown = 0, Bup = 0, Bdown = 0,
		    n = tops.size(); // 必须同时记录上半和下半，因为两边反转的成本可能不一样
		bool a = true, b = true;
		for(int i = 0; i < n; i++) {
			Aup += tops[i] == tops[0];
			Adown += bottoms[i] == tops[0];
			Bup += tops[i] == bottoms[0];
			Bdown += bottoms[i] == bottoms[0];
			a &= tops[i] == tops[0] || bottoms[i] == tops[0];
			b &= tops[i] == bottoms[0] || bottoms[i] == bottoms[0];
			if(!a && !b) {
				return -1;
			} // 提前结束
		}
		if(a) {
			// return min(min(Aup, int(n - Aup)), min(Adowm, int(n - Adowm)));
			// 没必要算Aup和Adown，因为如果可行，那么Aup一定是大于n - Aup的
			return min(n - Aup, n - Adown);
		}
		if(b) {
			// return min(min(Bup, int(n - Bup)), min(Bdown, int(n - Bdown)));
			return min(n - Bup, n - Bdown);
		}
		return -1;
	}
}; // 可以放心的以A[0] 和 B[0] 为基准，因为如果存在一个可行值，那么在0这个位置也一定有值，就是A[0] 或 B[0]

class Solution3 {
public:
	int check(int x, vector<int> &A, vector<int> &B, int n) {
		int rotations_a = 0, rotations_b = 0;
		for(int i = 0; i < n; i++) {
			// rotations coudn't be done
			if(A[i] != x && B[i] != x) return -1;
			// A[i] != x and B[i] == x
			else if(A[i] != x)
				rotations_a++;
			// A[i] == x and B[i] != x
			else if(B[i] != x)
				rotations_b++;
		}
		// min number of rotations to have all
		// elements equal to x in A or B
		return min(rotations_a, rotations_b);
	}

	int minDominoRotations(vector<int> &A, vector<int> &B) {
		int n = A.size();
		int rotations = check(A[0], B, A, n);
		// If one could make all elements in A or B equal to A[0]
		if(rotations != -1 || A[0] == B[0]) return rotations;
		// If one could make all elements in A or B equal to B[0]
		else
			return check(B[0], B, A, n);
	}
};

int main() {
	Solution1 sol1;
	vector<int> tops, bottoms;
	tops = { 2, 1, 2, 4, 2, 2 };
	bottoms = { 5, 2, 6, 2, 3, 2 };
	tops = { 1, 2, 1, 1, 1, 2, 2, 2 };
	bottoms = { 2, 1, 2, 2, 2, 2, 2, 2 };
	cout << sol1.minDominoRotations(tops, bottoms);
}