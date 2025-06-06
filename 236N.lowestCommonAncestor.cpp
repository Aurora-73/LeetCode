// Created: 2025-05-01
#include "MyTreeNode.h"
#include "MyUtils.hpp"
/*给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
 */
class Solution1 {
public:
	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
		if(!root || root == p || root == q) return root;
		TreeNode *l = lowestCommonAncestor(root->left, p, q);
		TreeNode *r = lowestCommonAncestor(root->right, p, q);
		if(l && r) {
			return root;
		}
		if(l || r) {
			return l ? l : r;
		}
		return nullptr;
	}
};

class Solution2 {
public:
	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
		count = 0;
		buildParentMap(root, nullptr, p, q);

		unordered_set<TreeNode *> ancestors;
		while(p) {
			ancestors.insert(p);
			p = parent[p];
		}

		while(q) {
			if(ancestors.count(q)) return q;
			q = parent[q];
		}

		return nullptr;
	}

private:
	unordered_map<TreeNode *, TreeNode *> parent;
	int count = 0;

	void buildParentMap(TreeNode *node, TreeNode *par, TreeNode *p, TreeNode *q) {
		if(!node || count == 2) return;
		count += (node == p || node == q);

		parent[node] = par;
		buildParentMap(node->left, node, p, q);
		buildParentMap(node->right, node, p, q);
	}
};

class Solution3 {
public:
	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
		vector<TreeNode *> path_p, path_q;
		getPath(root, p, path_p);
		getPath(root, q, path_q);
		// 比较路径
		int i = 0;
		while(i < path_p.size() && i < path_q.size() && path_p[i] == path_q[i]) {
			++i;
		}
		return path_p[i - 1];
	}

	// 使用非递归后序遍历记录到 target 的路径
	bool getPath(TreeNode *root, TreeNode *target, vector<TreeNode *> &path) {
		stack<TreeNode *> s;
		TreeNode *curr = root;
		TreeNode *lastVisited = nullptr;

		vector<TreeNode *> tempPath;

		while(curr || !s.empty()) {
			while(curr) {
				s.push(curr);
				tempPath.push_back(curr); // 入路径
				curr = curr->left;
			}
			TreeNode *node = s.top();
			if(node->right && node->right != lastVisited) {
				curr = node->right;
			} else {
				if(node == target) {
					path = tempPath;
					return true;
				}
				s.pop();
				tempPath.pop_back(); // 回溯时出路径
				lastVisited = node;
			}
		}
		return false;
	}
};

int main() { }