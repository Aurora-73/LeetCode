// Created: 2025-04-30
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/* 给你二叉树的根节点 root，返回其节点值的 锯齿形层序遍历。
（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
示例 1：
	输入：root = {3,9,20,null,null,15,7}
	输出：{{3},{20,9},{15,7}}
示例 2：
	输入：root = {1}
	输出：{{1}}
示例 3：
	输入：root = {}
	输出：{}
提示：
	树中节点数目在范围 {0, 2000} 内
	-100 <= Node.val <= 100 */

class Solution1 {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
		if(!root) return {}; // 很重要
		deque<TreeNode *> deq;
		vector<vector<int>> res;
		deq.push_back(root);
		bool left2right = true;
		while(!deq.empty()) {
			int size = deq.size();
			vector<int> &back = res.emplace_back();
			if(left2right) {
				for(int i = 0; i < size; i++) {
					TreeNode *now = deq.front();
					deq.pop_front();
					if(now->left) deq.push_back(now->left);
					if(now->right) deq.push_back(now->right);
					back.push_back(now->val);
				}
			} else {
				for(int i = 0; i < size; i++) {
					TreeNode *now = deq.back();
					deq.pop_back();
					if(now->right) deq.push_front(now->right);
					if(now->left) deq.push_front(now->left);
					// 逆序时应该先右后左
					back.push_back(now->val);
				}
			}
			left2right = !left2right;
		}
		return res;
	}
}; // 直接按照Z字形遍历，在每一层处理完之后，都保证 deq 中保存的 “下一层节点” 是按 “从左到右” 的顺序排列的

class Solution2 {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
		vector<vector<int>> res;
		if(!root) return res;

		queue<TreeNode *> que; // 还是用普通的层序遍历的顺序
		que.push(root);
		bool left2right = true;

		while(!que.empty()) {
			int size = que.size();
			vector<int> temp; // 每一层的结果保存用deque
			temp.reserve(size);
			for(int i = 0; i < size; ++i) {
				TreeNode *node = que.front();
				que.pop();
				temp.push_back(node->val);
				if(node->left) que.push(node->left);
				if(node->right) que.push(node->right);
			}
			if(left2right)
				res.emplace_back(temp.begin(), temp.end());
			else
				res.emplace_back(temp.rbegin(), temp.rend());
			left2right = !left2right;
		}
		return res;
	}
}; // 不真的进行Z字形遍历，只是对结果数组进行翻转

class Solution {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
		if(!root) return {};
		vector<vector<int>> res;
		queue<TreeNode *> que;
		que.push(root);
		bool left2right = true;
		while(!que.empty()) {
			int size = que.size();
			vector<int> &back = res.emplace_back(size);
			for(int i = 0; i < size; ++i) {
				TreeNode *curr = que.front();
				que.pop();
				if(left2right) {
					back[i] = curr->val;
				} else {
					back[size - i - 1] = curr->val;
				}
				if(curr->left) que.push(curr->left);
				if(curr->right) que.push(curr->right);
			}
			left2right ^= 1;
		}
		return res;
	}
}; // 不真的进行Z字形遍历，只是对结果数组进行翻转

int main() {
	TreeNode *tree = createTree({ 1, 2, 3, 4, 5, EMPTY_NODE, 7 });
	Solution1 sol1;
	cout << sol1.zigzagLevelOrder(tree) << endl;
	Solution2 sol2;
	cout << sol2.zigzagLevelOrder(tree) << endl;
}