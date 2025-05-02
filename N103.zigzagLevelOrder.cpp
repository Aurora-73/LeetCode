// Created: 2025-04-30
#include "MyUtils.h"
#include "MyTreeNode.h"

/*103. 二叉树的锯齿形层序遍历
给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。
（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。*/
class Solution1 {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
		if(!root)
			return {}; // 很重要
		deque<TreeNode *> q;
		vector<vector<int>> res;
		q.push_back(root);
		bool left2right = true;
		while(!q.empty()) {
			int size = q.size();
			res.push_back({});
			if(left2right) {
				for(int i = 0; i < size; i++) {
					TreeNode *now = q.front();
					q.pop_front();
					if(now->left) {
						q.push_back(now->left);
					}
					if(now->right) {
						q.push_back(now->right);
					}
					res.back().push_back(now->val);
				}
			} else {
				for(int i = 0; i < size; i++) {
					TreeNode *now = q.back();
					q.pop_back();
					if(now->right) {
						q.push_front(now->right);
					}
					if(now->left) {
						q.push_front(now->left);
					} // 逆序时应该先右后左
					res.back().push_back(now->val);
				}
			}
			left2right = !left2right;
		}
		return res;
	}
};

class Solution2 {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
		vector<vector<int>> ans;
		if(!root) {
			return ans;
		}

		queue<TreeNode *> nodeQueue; // 还是用普通的层序遍历的顺序
		nodeQueue.push(root);
		bool isOrderLeft = true;

		while(!nodeQueue.empty()) {
			deque<int> levelList; // 每一层的结果保存用deque
			int size = nodeQueue.size();
			for(int i = 0; i < size; ++i) {
				auto node = nodeQueue.front();
				nodeQueue.pop();
				if(isOrderLeft) {
					levelList.push_back(node->val);
				} else {
					levelList.push_front(node->val);
				}
				if(node->left) {
					nodeQueue.push(node->left);
				}
				if(node->right) {
					nodeQueue.push(node->right);
				}
			}
			ans.emplace_back(vector<int>{levelList.begin(), levelList.end()});
			isOrderLeft = !isOrderLeft;
		}

		return ans;
	}
};

int main() {
	auto tree = createTree({1, 2, 3, 4, 5, -1, 7});
	Solution1 sol1;
	cout << sol1.zigzagLevelOrder(tree) << endl;
	Solution2 sol2;
	cout << sol2.zigzagLevelOrder(tree) << endl;
}