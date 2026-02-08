// Created: 2026-02-08
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给你一棵二叉树的根节点 root，返回树的 最大宽度。
树的 最大宽度 是所有层中最大的 宽度。
每一层的 宽度 被定义为该层最左和最右的非空节点（即，两个端点）之间的长度。将这个二叉树视作与满二叉树结构相同，
两端点间会出现一些延伸到这一层的 null 节点，这些 null 节点也计入长度。
题目数据保证答案将会在 32 位 带符号整数范围内。
示例 1：
	输入：root = {1,3,2,5,3,null,9}
	输出：4
	解释：最大宽度出现在树的第 3 层，宽度为 4 (5,3,null,9)。
示例 2：
	输入：root = {1,3,2,5,null,null,9,6,null,7}
	输出：7
	解释：最大宽度出现在树的第 4 层，宽度为 7 (6,null,null,null,null,null,7)。
示例 3：
	输入：root = {1,3,2,5}
	输出：2
	解释：最大宽度出现在树的第 2 层，宽度为 2 (3,2)。
提示：
	树中节点的数目范围是 {1, 3000}
	-100 <= Node.val <= 100 */

class Solution1 {
public:
	int widthOfBinaryTree(TreeNode *root) {
		begins.clear();
		if(!root) return 0;
		res = 1;
		dfs(root, 0, 0);
		return res;
	}

private:
	int res;
	vector<unsigned long long> begins;
	void dfs(TreeNode *root, int depth, unsigned long long id) {
		if(!root) return;
		if(begins.size() <= depth) {
			begins.push_back(id);
			// 因为是先左后右，只有第一次到深度 depth 的时候更新
		} else {
			res = max<int>(res, id - begins[depth] + 1ULL);
			// 因为初始化 res = 1 所以可以放到else里
		}

		dfs(root->left, depth + 1, id * 2ULL);
		dfs(root->right, depth + 1, id * 2ULL + 1ULL);
	}
}; // dfs

class Solution2 {
public:
	int widthOfBinaryTree(TreeNode *root) {
		if(!root) return 0;
		res = 1;
		begins.clear();
		dfs(root, 0, 0ULL);
		return res;
	}

private:
	int res;
	vector<unsigned long long> begins;

	void dfs(TreeNode *node, int depth, unsigned long long id) {
		if(!node) return;
		if(begins.size() <= depth) {
			begins.push_back(id);
		} else {
			res = max<int>(res, id - begins[depth] + 1ULL);
		}
		// 以本层基准归一化后再计算子节点索引，避免指数增长
		unsigned long long relative_id = id - begins[depth]; // 首次到达则为 0
		dfs(node->left, depth + 1, relative_id * 2ULL);
		dfs(node->right, depth + 1, relative_id * 2ULL + 1ULL);
	}
}; // bfs + 在同一层用最左节点的 id 做基准，传递相对索引（id - begins[depth]），这样每层 id 都被归一化，避免溢出

class Solution {
public:
	int widthOfBinaryTree(TreeNode *root) {
		if(!root) return 0;
		int res = 0;
		deque<pair<TreeNode *, unsigned long long>> q;
		q.emplace_back(root, 0ULL);

		while(!q.empty()) {
			int size = q.size();
			unsigned long long left_id = q.front().second;
			unsigned long long right_id = q.back().second;
			res = max(res, static_cast<int>(right_id - left_id + 1ULL));

			for(int i = 0; i < size; ++i) {
				auto [node, absolute_id] = q.front();
				q.pop_front();
				unsigned long long relative_id = absolute_id - left_id;
				// 以本层最左 id 归一化，避免 id 值指数增长或溢出
				if(node->left) q.emplace_back(node->left, relative_id * 2ULL);
				if(node->right) q.emplace_back(node->right, relative_id * 2ULL + 1ULL);
			}
		}
		return res;
	}
}; // 层次遍历

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 1, 3, 2, 5, 3, EMPTY_NODE, 9 });
	cout << sol.widthOfBinaryTree(root) << endl;

	root = createTree({ 1, 3, 2, 5, EMPTY_NODE, EMPTY_NODE, 9, 6, EMPTY_NODE, 7 });
	cout << sol.widthOfBinaryTree(root) << endl;

	root = createTree({ 1, 3, 2, 5 });
	cout << sol.widthOfBinaryTree(root) << endl;
}