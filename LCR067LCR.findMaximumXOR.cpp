// Created: 2025-12-15
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个整数数组 nums，返回 nums{i} XOR nums{j} 的最大运算结果，其中 0 ≤ i ≤ j < n。
示例 1：
	输入：nums = {3,10,5,25,2,8}
	输出：28
	解释：最大运算结果是 5 XOR 25 = 28.
示例 2：
	输入：nums = {0}
	输出：0
示例 3：
	输入：nums = {2,4}
	输出：6
示例 4：
	输入：nums = {8,10,2}
	输出：10
示例 5：
	输入：nums = {14,70,53,83,49,91,36,80,92,51,66,70}
	输出：127
提示：
	1 <= nums.length <= 2 * 10^5
	0 <= nums{i} <= 2^31 - 1
	进阶：你可以在 O(n) 的时间解决这个问题吗？ */

class Solution1 {
public:
	int findMaximumXOR(vector<int> &nums) {
		if(nums.empty()) return 0;
		int max_val = 0, highBit = 1, res = 0, n = nums.size();
		for(int num : nums) max_val = max(max_val, num);
		while(max_val != 1) {
			max_val >>= 1;
			highBit <<= 1;
		} // 注意不是max_val > 0，因为highBit <= max_val;
		Trie *root = new Trie();
		insert(root, nums.front(), highBit);
		for(int i = 1; i < n; ++i) {
			int val = check(root, nums[i], highBit);
			res = max(val, res);
			insert(root, nums[i], highBit);
		}
		return res;
	}

private:
	struct Trie {
		Trie *zero, *one;
		Trie() : zero { nullptr }, one { nullptr } { }
	};
	void insert(Trie *root, int num, int highBit) {
		while(highBit > 0) {
			if(highBit & num) {
				if(!root->one) {
					root->one = new Trie;
				}
				root = root->one;
				highBit >>= 1;
			} else {
				if(!root->zero) {
					root->zero = new Trie;
				}
				root = root->zero;
				highBit >>= 1;
			}
		}
	}
	int check(Trie *root, int num, int highBit) {
		int res = 0;
		while(highBit > 0) {
			if(highBit & num) {
				if(root->zero) {
					root = root->zero;
					res |= highBit;
				} else {
					root = root->one;
				}
				highBit >>= 1;
			} else {
				if(root->one) {
					root = root->one;
					res |= highBit;
				} else {
					root = root->zero;
				}
				highBit >>= 1;
			}
		}
		return res;
	}
};
// 使用字典树保存已经遍历过的元素的位，对于一个新的数，在树中寻找与它异或值最大的结果，注意不是先全部插入树然后异或，而是边插入边异或，注意插入首个元素前不能异或，会空指针

class Solution {
public:
	int findMaximumXOR(vector<int> &nums) {
		int max_val = 0, highBit = 1, res = 0, n = nums.size();
		for(int num : nums) max_val = max(max_val, num);
		while(max_val != 1) {
			max_val >>= 1;
			highBit <<= 1;
		}
		unique_ptr<Trie> root = make_unique<Trie>();
		insert(root.get(), nums.front(), highBit);
		for(int i = 1; i < n; ++i) {
			int val = check(root.get(), nums[i], highBit);
			res = max(val, res);
			insert(root.get(), nums[i], highBit);
		}
		return res;
	}

private:
	struct Trie {
		unique_ptr<Trie> zero, one;
		Trie() : zero { nullptr }, one { nullptr } { }
	};
	void insert(Trie *root, int num, int highBit) {
		while(highBit > 0) {
			if(highBit & num) {
				if(!root->one) {
					root->one.reset(new Trie);
				}
				root = (root->one).get();
			} else {
				if(!root->zero) {
					root->zero.reset(new Trie);
				}
				root = (root->zero).get();
			}
			highBit >>= 1;
		}
	}
	int check(Trie *root, int num, int highBit) {
		int res = 0;
		while(highBit > 0) {
			if(highBit & num) {
				if(root->zero) {
					root = root->zero.get();
					res |= highBit;
				} else {
					root = root->one.get();
				}
			} else {
				if(root->one) {
					root = root->one.get();
					res |= highBit;
				} else {
					root = root->zero.get();
				}
			}
			highBit >>= 1;
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 2147483647, 2147483646, 2147483645 };
	cout << sol.findMaximumXOR(nums) << endl;
	nums = { 3, 10, 5, 25, 2, 8 };
	cout << sol.findMaximumXOR(nums) << endl;
	return 0;
}