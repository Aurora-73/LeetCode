// Created: 2025-06-28
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 156. 序列化与反序列化二叉树
序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，
同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。
请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，
你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
提示: 输入输出格式与 LeetCode 目前使用的方式一致，
	详情请参阅LeetCode 序列化二叉树的格式。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。
示例 1：
	输入：root = {1,2,3,null,null,4,5}
	输出：{1,2,3,null,null,4,5}
示例 2：
	输入：root = {}
	输出：{}
示例 3：
	输入：root = {1}
	输出：{1}
示例 4：
	输入：root = {1,2}
	输出：{1,2}
提示：
	树中结点数在范围 {0, 10^4} 内
	-1000 <= Node.val <= 1000 */

class Codec1 {
public:
	string serialize(TreeNode *root) {
		string res;
		preOrderSer(root, res);
		return res;
	}

	TreeNode *deserialize(const string &data) {
		stringstream ss(data);
		return preOrderDeSer(ss);
	}

private:
	void preOrderSer(TreeNode *root, string &res) {
		if(!root) {
			res.append(",");
			return;
		}
		res.append(to_string(root->val));
		res.push_back(',');
		preOrderSer(root->left, res);
		preOrderSer(root->right, res);
	}

	TreeNode *preOrderDeSer(stringstream &ss) {
		if(ss.eof()) return nullptr;
		if(ss.peek() == ',') {
			ss.ignore(1);
			return nullptr;
		}
		TreeNode *now = new TreeNode;
		ss >> now->val;
		ss.ignore(1);
		now->left = preOrderDeSer(ss);
		now->right = preOrderDeSer(ss);
		return now;
	}
};

class Codec {
public:
	string serialize(TreeNode *root) {
		string res;
		preOrderSer(root, res);
		return res;
	}

	TreeNode *deserialize(string data) {
		string_view sv(data);
		return preOrderDeSer(sv);
	}

private:
	void preOrderSer(TreeNode *root, string &res) {
		if(!root) {
			res.append(",");
			return;
		}
		res.append(to_string(root->val));
		res.push_back(',');
		preOrderSer(root->left, res);
		preOrderSer(root->right, res);
	}

	TreeNode *preOrderDeSer(string_view &sv) {
		if(sv.empty()) return nullptr;

		if(sv[0] == ',') {
			sv.remove_prefix(1);
			return nullptr;
		}

		// 找到下一个逗号的位置
		int comma_pos = 0;
		while(sv[comma_pos] != ',') ++comma_pos;

		TreeNode *now = new TreeNode;
		// 使用 from_chars 直接从 string_view 提取 int
		std::from_chars(sv.data(), sv.data() + comma_pos, now->val);
		sv.remove_prefix(comma_pos + 1); // 移除已处理的部分（包括逗号）

		now->left = preOrderDeSer(sv);
		now->right = preOrderDeSer(sv);
		return now;
	}
};

// 序列化方案：空节点不加元素，节点之间用','隔开

int main() {
	Codec coder;
	TreeNode *root = createTree({ -1, -2, 3, EMPTY_NODE, EMPTY_NODE, -4, 5 });
	cout << root << endl;
	string ser = coder.serialize(root);
	cout << ser << endl;
	TreeNode *root2 = coder.deserialize(ser);
	cout << root2 << endl;
}