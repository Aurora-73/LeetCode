// Created: 2025-05-03
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/*543. 二叉树的直径
给你一棵二叉树的根节点，返回该树的 直径 。
二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点 root 。
两节点之间路径的 长度 由它们之间边数表示。*/
class Solution1 {
public:
	int diameterOfBinaryTree(TreeNode *root) {
		maxsize = 0;
		dfs(root);
		return maxsize;
	}

private:
	int dfs(TreeNode *root) {
		if(!root) return 0;
		int l = dfs(root->left);
		int r = dfs(root->right);
		maxsize = max(maxsize, l + r); // 不要当前节点的父节点，自立为王
		// 不要+2，可以想想空节点
		return max(l, r) + 1; // 要当前节点的父节点，只能保留一个子树
	}
	int maxsize;
};

class Solution2 {
public:
	int diameterOfBinaryTree(TreeNode *root) {
		ans = 1;
		depth(root);
		return ans - 1;
	}

private:
	int depth(TreeNode *rt) {
		if(rt == NULL) {
			return 0; // 访问到空节点了，返回0
		}
		int L = depth(rt->left);   // 左儿子为根的子树的深度
		int R = depth(rt->right);  // 右儿子为根的子树的深度
		ans = max(ans, L + R + 1); // 计算d_node即L+R+1 并更新ans
		return max(L, R) + 1;      // 返回该节点为根的子树的深度
	}
	int ans; // 保存的是节点数，而非边长，节点数 = 边长 + 1
};

int main() {
	Solution1 sol1;
	Solution2 sol2;
	TreeNode *tree = createTree({ 1, 2, 3, 4, 5, EMPTY_NODE, 7 });
	cout << sol1.diameterOfBinaryTree(tree) << " " << sol2.diameterOfBinaryTree(tree) << endl;
}