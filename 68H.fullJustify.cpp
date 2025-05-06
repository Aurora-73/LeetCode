#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

/*
给定一个单词数组 words 和一个长度 maxWidth ，重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。
你应该使用 “贪心算法” 来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 ' ' 填充，使得每行恰好有 maxWidth 个字符。
要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。
文本的最后一行应为左对齐，且单词之间不插入额外的空格。
注意:
单词是指由非空格字符组成的字符序列。
每个单词的长度大于 0，小于等于 maxWidth。
输入单词数组 words 至少包含一个单词。
示例 1:
输入: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
输出:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]*/

class Solution {
public:
	vector<string> fullJustify(vector<string> &words, int maxWidth) {
		vector<string> result;
		for(int i = 0; i < words.size(); i++) {
			result.push_back("");
			int j, sumsize = -1;
			for(j = i; j < words.size(); j++) {
				if(sumsize + 1 + words[j].length() > maxWidth) {
					break;
				}
				sumsize += 1 + words[j].length();
			}
			if(j != words.size()) {
				int spacenum = maxWidth - sumsize, ave_space = 0, extra_space = 0, endspace = 0;
				if(j - i - 1 != 0) {
					ave_space = spacenum / (j - i - 1), extra_space = spacenum - ave_space * (j - i - 1);
				} else {
					endspace = spacenum;
				} // 如果只有一个单词，则直接补' '
				while(i < j) {
					result.back() += words[i];
					if(i < j - 1) {
						result.back() += ' ';
						if(extra_space > 0) {
							result.back() += ' ';
							extra_space--;
						}
						for(int k = 0; k < ave_space; k++) {
							result.back() += ' ';
						}
					} // 非最后一个单词要在后面补' '
					for(int k = 0; k < endspace; k++) {
						result.back() += ' ';
					} // 如果只有一个单词，则直接补' '
					i++;
				}
			} else {
				while(i < j) {
					result.back() += words[i];
					if(i < j - 1) {
						result.back() += ' ';
					}
					i++;
				}
				result.back().resize(maxWidth, ' ');
			} // 最后一行
			i--;
		}
		return result;
	}
};

int main() {
	Solution sol;
	vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};
	int maxWidth = 16;
	for(auto str : sol.fullJustify(words, maxWidth)) {
		cout << "|" << str << "|" << endl;
	};
}