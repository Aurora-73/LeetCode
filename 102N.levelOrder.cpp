// Created: 2025-04-30
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/* 给你二叉树的根节点 root，返回其节点值的 层序遍历。
 （即逐层地，从左到右访问所有节点）。
示例 1：
	输入：root = {3,9,20,null,null,15,7}
	输出：{{3},{9,20},{15,7}}
示例 2：
	输入：root = {1}
	输出：{{1}}
示例 3：
	输入：root = {}
	输出：{}
提示：
	树中节点数目在范围 {0, 2000} 内
	-1000 <= Node.val <= 1000 */

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode *root) {
		vector<vector<int>> res;
		queue<TreeNode *> que;
		que.push(root);
		while(!que.empty()) {
			int size = que.size();
			res.emplace_back();
			for(int i = 0; i < size; ++i) {
				TreeNode *curr = que.front();
				res.back().push_back(curr->val);
				que.pop();
				if(curr->left) que.push(curr->left);
				if(curr->right) que.push(curr->right);
			}
		}
		return res;
	}
};

int main() {
	TreeNode *tree = createTree({ 1, 2, 3, 4, 5, EMPTY_NODE, 7 });
	Solution sol;
	cout << sol.levelOrder(tree) << endl;
}