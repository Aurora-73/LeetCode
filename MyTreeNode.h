// MyTreeNode.h
#ifndef MY_TREENODE_H
#define MY_TREENODE_H

#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define EMPTY_NODE numeric_limits<int>::min() // 定义空节点构造时的值

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) { }
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) { }
};

/**
 * 根据层序数组创建二叉树（-1 表示空节点）
 * @param values 整数数组
 * @return 树的根节点
 */
TreeNode *createTree(const std::vector<int> &values);

/**
 * 输出二叉树（层序遍历）
 * @param os 输出流
 * @param root 根节点
 */
void printTreeFancy(TreeNode *node,
    std::ostream &os,
    const std::string &prefix,
    bool isLeft,
    const std::string &tag);

// 重载 << 运算符，打印带 l/r 标签的树
std::ostream &operator<<(std::ostream &os, TreeNode *root);

/**
 * 释放二叉树内存
 * @param root 根节点
 */
void deleteTree(TreeNode *root);

#endif // MY_TREENODE_H
