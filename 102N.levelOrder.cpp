// Created: 2025-04-30
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/*  */
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode *root) {
		if(!root) return {}; // 很重要
		queue<TreeNode *> q;
		vector<vector<int>> res;
		q.push(root);
		while(!q.empty()) {
			int size = q.size();
			res.push_back({});
			for(int i = 0; i < size; i++) {
				TreeNode *now = q.front();
				q.pop();
				if(now->left) {
					q.push(now->left);
				}
				if(now->right) {
					q.push(now->right);
				}
				res.back().push_back(now->val);
			}
		}
		return res;
	}
};

int main() {
	auto tree = createTree({ 1, 2, 3, 4, 5, -1, 7 });
	Solution sol;
	cout << sol.levelOrder(tree) << endl;
}