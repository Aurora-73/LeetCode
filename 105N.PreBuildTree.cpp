// Created: 2025-04-30
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/* 105. 从前序与中序遍历序列构造二叉树
给定两个整数数组 preorder 和 inorder，其中 preorder 是二叉树的先序遍历，
 inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。
示例 1:
	输入: preorder = {3,9,20,15,7}, inorder = {9,3,15,20,7}
	输出: {3,9,20,null,null,15,7}
示例 2:
	输入: preorder = {-1}, inorder = {-1}
	输出: {-1} */

class Solution1 {
public:
	TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
		if(!preorder.size()) return nullptr;
		std::vector<int>::iterator prebegin = preorder.begin();
		return buildTreeIter(inorder.begin(), inorder.end(), prebegin, preorder.end());
	}
	TreeNode *buildTreeIter(std::vector<int>::iterator inbegin,
	    std::vector<int>::iterator inend,
	    std::vector<int>::iterator &prebegin,
	    std::vector<int>::iterator preend) {
		if(prebegin == preend || inbegin == inend) {
			return nullptr;
		}
		auto it = find(inbegin, inend, *prebegin); // 不能使用 lowwer_bound 因为数组不一定有序
		if(it == inend) {
			return nullptr;
		}
		TreeNode *now = new TreeNode(*prebegin);
		prebegin++;
		now->left = buildTreeIter(inbegin, it, prebegin, preend);
		now->right = buildTreeIter(it + 1, inend, prebegin, preend);
		return now;
	}
};

class Solution {
public:
	TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
		if(preorder.empty()) return nullptr;
		inorder_map.clear();

		// 建立哈希表加速查找
		for(auto it = inorder.begin(); it != inorder.end(); ++it) {
			inorder_map[*it] = it;
		}

		auto prebegin = preorder.begin();
		return buildTreeIter(inorder.begin(), inorder.end(), prebegin, preorder.end());
	}

private:
	unordered_map<int, vector<int>::iterator> inorder_map;

	TreeNode *buildTreeIter(std::vector<int>::iterator inbegin,
	    std::vector<int>::iterator inend,
	    std::vector<int>::iterator &prebegin,
	    std::vector<int>::iterator preend) {
		if(prebegin == preend || inbegin == inend) {
			return nullptr;
		}

		auto it = inorder_map[*prebegin]; // 用 map 查找代替 find()
		TreeNode *now = new TreeNode(*prebegin);
		++prebegin;

		now->left = buildTreeIter(inbegin, it, prebegin, preend);
		now->right = buildTreeIter(it + 1, inend, prebegin, preend);
		return now;
	}
};

template <typename Iterator>
class GenericTreeBuilder {
	using ValueType = typename std::iterator_traits<Iterator>::value_type;
	using MapType = std::unordered_map<ValueType, Iterator>;

public:
	template <typename Container>
	TreeNode *buildTree(Container &preorder, Container &inorder) {
		if(preorder.empty()) return nullptr;

		// 构建值到中序迭代器的映射
		inorder_map.clear();
		for(auto it = inorder.begin(); it != inorder.end(); ++it) {
			inorder_map[*it] = it;
		}

		auto prebegin = preorder.begin();
		return buildTreeIter(inorder.begin(), inorder.end(), prebegin, preorder.end());
	}

private:
	MapType inorder_map;

	TreeNode *buildTreeIter(Iterator inbegin, Iterator inend, Iterator &prebegin, Iterator preend) {
		if(prebegin == preend || inbegin == inend) {
			return nullptr;
		}

		auto it = inorder_map[*prebegin]; // 从哈希表中快速查找
		TreeNode *node = new TreeNode(*prebegin);
		++prebegin;

		node->left = buildTreeIter(inbegin, it, prebegin, preend);
		node->right = buildTreeIter(std::next(it), inend, prebegin, preend);
		return node;
	}
};

// 缺少 方法二：迭代

int main() {
	Solution sol;
	vector<int> preorder, inorder;
	preorder = { 3, 9, 20, 15, 7 }, inorder = { 9, 3, 15, 20, 7 };
	cout << sol.buildTree(preorder, inorder) << endl;

	preorder = { -1 }, inorder = { -1 };
	cout << sol.buildTree(preorder, inorder) << endl;
}
