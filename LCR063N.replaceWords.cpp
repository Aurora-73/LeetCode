// Created: 2025-12-10
#include "MyUtils.hpp"
#include <string_view>
// #ifdef MY_UTILS_H

/* 在英语中，有一个叫做词根(root) 的概念，
它可以跟着其他一些词组成另一个较长的单词——我们称这个词为继承词(successor)。
例如，词根an，跟随着单词other(其他)，可以形成新的单词another(另一个)。
现在，给定一个由许多词根组成的词典和一个句子，需要将句子中的所有继承词用词根替换掉。
如果继承词有许多可以形成它的词根，则用最短的词根替换它。
需要输出替换之后的句子。
示例 1：
	输入：dictionary = {"cat","bat","rat"}, sentence = "the cattle was rattled by the battery"
	输出："the cat was rat by the bat"
示例 2：
	输入：dictionary = {"a","b","c"}, sentence = "aadsfasf absbs bbab cadsfafs"
	输出："a a b c"
示例 3：
	输入：dictionary = {"a", "aa", "aaa", "aaaa"}, sentence = "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa"
	输出："a a a a a a a a bbb baba a"
示例 4：
	输入：dictionary = {"catt","cat","bat","rat"}, sentence = "the cattle was rattled by the battery"
	输出："the cat was rat by the bat"
	示例 5：
	输入：dictionary = {"ac","ab"}, sentence = "it is abnormal that this solution is accepted"
	输出："it is ab that this solution is ac"
提示：
	1 <= dictionary.length<= 1000
	1 <= dictionary{i}.length <= 100
	dictionary{i}仅由小写字母组成。
	1 <= sentence.length <= 10^6
	sentence仅由小写字母和空格组成。
	sentence 中单词的总量在范围 {1, 1000} 内。
	sentence 中每个单词的长度在范围 {1, 1000} 内。
	sentence 中单词之间由一个空格隔开。
	sentence没有前导或尾随空格。  */

class Solution {
public:
	string replaceWords(vector<string> &dictionary, string sentence) {
		TrieNode *root = new TrieNode;
		for(auto &str : dictionary) {
			insert(str, root);
		}
		string res = "";
		int beg = 0;
		for(int i = 0; i < sentence.size(); ++i) {
			if(sentence[i] != ' ') {
				continue;
			}
			res += find_succ(string_view(sentence.data() + beg, i - beg), root);
			res += " ";
			beg = i + 1;
		}
		res += find_succ(string_view(sentence.data() + beg, sentence.size() - beg), root);
		return res;
	}

private:
	struct TrieNode {
		bool isEnd = false;
		array<TrieNode *, 26> child { nullptr };
	};
	void insert(string &str, TrieNode *root) {
		for(auto c : str) {
			if(root->isEnd) {
				return; // 仅保留最短前缀
			}
			int id = c - 'a';
			if(!root->child[id]) {
				root->child[id] = new TrieNode;
			}
			root = root->child[id];
		}
		root->isEnd = true;
	}
	string_view find_succ(const string_view &sv, TrieNode *root) {
		for(int i = 0; i < sv.size(); ++i) {
			if(!root) {
				return sv;
			}
			if(root->isEnd) {
				return string_view(sv.begin(), sv.begin() + i);
			}
			root = root->child[sv[i] - 'a'];
		}
		return sv;
	}
};

int main() {
	Solution sol;
	vector<string> dictionary;
	string sentence;
	dictionary = { "cat", "bat", "rat" }, sentence = "the cattle was rattled by the battery";
	cout << sol.replaceWords(dictionary, sentence) << endl;
	dictionary = { "a", "b", "c" }, sentence = "aadsfasf absbs bbab cadsfafs";
	cout << sol.replaceWords(dictionary, sentence) << endl;
	dictionary = { "a", "aa", "aaa", "aaaa" },
	sentence = "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa";
	cout << sol.replaceWords(dictionary, sentence) << endl;
}