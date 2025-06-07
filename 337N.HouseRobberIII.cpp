// Created: 2025-06-07
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/* 337. 打家劫舍 III
小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。
除了 root 之外，每栋房子有且只有一个“父“房子与之相连。
一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 
如果 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。
给定二叉树的 root 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。
示例 1:
    输入: root = [3,2,3,null,3,null,1]
    输出: 7 
    解释: 小偷一晚能够盗取的最高金额 3 + 3 + 1 = 7
示例 2:
    输入: root = [3,4,5,1,3,null,1]
    输出: 9
    解释: 小偷一晚能够盗取的最高金额 4 + 5 = 9
提示：
    树的节点数在 [1, 104] 范围内
    0 <= Node.val <= 104*/

class Solution1 {
public:
	int rob(TreeNode *root) {
		get.clear();
		get[nullptr] = 0;
		notGet.clear();
		notGet[nullptr] = 0;
		return PostOrder(root);
	}

private:
	unordered_map<TreeNode *, int> get, notGet;
	int PostOrder(TreeNode *root) {
		if(!root) return 0;
		PostOrder(root->left);
		PostOrder(root->right);
		auto itg = get.insert({ root, 0 });
		auto itng = notGet.insert({ root, 0 });
		int gl = get[root->left], gr = get[root->right];
		int ngl = notGet[root->left], ngr = notGet[root->right];
		itg.first->second = root->val + ngl + ngr;
		itng.first->second = max(gl, ngl) + max(gr, ngr);
		return max(itg.first->second, itng.first->second);
	}
};

class Solution {
public:
	int rob(TreeNode *root) {
		auto res = PostOrder(root);
		return max(res.first, res.second);
	}

private:
	// 返回 {选当前节点的最大值, 不选当前节点的最大值}
	pair<int, int> PostOrder(TreeNode *node) {
		if(!node) return { 0, 0 };
		auto l = PostOrder(node->left);
		auto r = PostOrder(node->right);
		int get = node->val + l.second + r.second;
		int notGet = max(l.first, l.second) + max(r.first, r.second);
		return { get, notGet };
	}
};

int main() {
	Solution sol;
}