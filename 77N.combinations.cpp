// Created: 2025-05-11
#include "MyUtils.h"

/*77. 组合
给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
你可以按 任何顺序 返回答案。
示例 1：
    输入：n = 4, k = 2
    输出：[[2,4],[3,4],[2,3],[1,2],[1,3],[1,4]]
示例 2：
    输入：n = 1, k = 1
    输出：[[1]]     */

class Solution1 {
public:
	vector<vector<int>> combine(int n, int k) {
		res.reserve(int(fa(n, k) / fa(k, 1)));
		dfs(1, n, k);
		return res;
	}

private:
	vector<vector<int>> res;
	vector<int> path;
	void dfs(int start, int n, int k) {
		if(k == 0) {
			res.push_back(path);
			return;
		}
		// 剪枝：i 最多到 n - k + 1，确保后面还够 k 个数选
		for(int i = start; i <= n - k + 1; ++i) {
			path.push_back(i);
			dfs(i + 1, n, k - 1);
			path.pop_back();
		}
	}
	double fa(size_t n, size_t k) {
		if(n <= k)
			return 1;
		return n * fa(n - 1, k);
	}
};

class Solution2 {
public:
	vector<vector<int>> combine(int n, int k) {
		dfs(1, n, k);
		return ans;
	}

private:
	vector<int> temp;
	vector<vector<int>> ans;
	void dfs(int cur, int n, int k) {
		// 剪枝：temp 长度加上区间 [cur, n] 的长度小于 k，不可能构造出长度为 k 的 temp
		if(temp.size() + (n - cur + 1) < k) {
			return;
		}
		// 记录合法的答案
		if(temp.size() == k) {
			ans.push_back(temp);
			return;
		}
		// 考虑选择当前位置
		temp.push_back(cur);
		dfs(cur + 1, n, k);
		temp.pop_back();
		// 考虑不选择当前位置
		dfs(cur + 1, n, k);
	}
};

class Solution3 {
public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> ans;
		size_t size = (fa(n, max(n - k, k)) / fa(min(n - k, k), 1));
		ans.reserve(size);
		vector<int> st(k);
		int top = 0, val = 1;
		while(top > 0 || top == 0 && val <= n) {
			if(val <= n && top < k) {
				st[top++] = val++;
				if(top == k)
					ans.push_back(st);
			} else
				val = st[--top] + 1;
		}
		return ans;
	}
	size_t fa(size_t n, size_t end) {
		if(n <= end)
			return 1;
		return n * fa(n - 1, end);
	}
};

int main() {
	Solution1 sol1;
}