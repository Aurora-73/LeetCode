// Created: 2025-04-30
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/*106. 从中序与后序遍历序列构造二叉树
给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历， 
postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。*/

// 直接用反向迭代器
class Solution1 {
public:
	TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
		if(!postorder.size()) return nullptr;
		vector<int>::reverse_iterator postRbegin = postorder.rbegin();
		return buildTreeIter(inorder.begin(), inorder.end(), postRbegin, postorder.rend());
	}
	TreeNode *buildTreeIter(vector<int>::iterator inbegin,
	    vector<int>::iterator inend,
	    vector<int>::reverse_iterator &postRbegin,
	    vector<int>::reverse_iterator postRend) {
		if(inbegin == inend) {
			return nullptr;
		}
		auto it = find(inbegin, inend, *postRbegin);
		if(it == inend) {
			return nullptr;
		}
		TreeNode *now = new TreeNode(*postRbegin);
		postRbegin++;
		now->right = buildTreeIter(
		    it + 1, inend, postRbegin, postRend); // 先右后左，后序遍历根的左边是右子树
		now->left = buildTreeIter(inbegin, it, postRbegin, postRend);
		return now;
	}
};

class Solution2 {
public:
	TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
		if(postorder.empty()) return nullptr;
		inorder_map.clear();
		// 建立哈希表加速查找
		for(auto it = inorder.begin(); it != inorder.end(); ++it) {
			inorder_map[*it] = it;
		}
		std::vector<int>::reverse_iterator postRbegin = postorder.rbegin();
		return buildTreeIter(inorder.begin(), inorder.end(), postRbegin, postorder.rend());
	}

private:
	unordered_map<int, vector<int>::iterator> inorder_map;

	TreeNode *buildTreeIter(std::vector<int>::iterator inbegin,
	    std::vector<int>::iterator inend,
	    std::vector<int>::reverse_iterator &postRbegin,
	    std::vector<int>::reverse_iterator postRend) {
		if(inbegin == inend) {
			return nullptr;
		}
		auto it = inorder_map[*postRbegin]; // 用 map 查找代替 find()
		TreeNode *now = new TreeNode(*postRbegin);
		postRbegin++;
		now->right = buildTreeIter(it + 1, inend, postRbegin, postRend);
		now->left = buildTreeIter(inbegin, it, postRbegin, postRend);
		return now;
	}
};

int main() {
	Solution1 sol1;
	vector<int> inorder = { 9, 3, 15, 20, 7 };
	vector<int> postorder = { 9, 15, 7, 20, 3 };
	sol1.buildTree(inorder, postorder);
}
