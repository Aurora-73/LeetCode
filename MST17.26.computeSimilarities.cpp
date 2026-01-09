// Created: 2026-01-09
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 两个(具有不同单词的)文档的交集(intersection)中元素的个数除以并集(union)中元素的个数，就是这两个文档的相似度。
例如，{1, 5, 3} 和 {1, 7, 2, 3} 的相似度是 0.4，其中，交集的元素有 2 个，并集的元素有 5 个。给定一系列的长篇文档，每个文档元素各不相同，并与一个 ID 相关联。它们的相似度非常“稀疏”，
也就是说任选 2 个文档，相似度都很接近 0。请设计一个算法返回每对文档的 ID 及其相似度。只需输出相似度大于 0 的组合。请忽略空文档。为简单起见，可以假定每个文档由一个含有不同整数的数组表示。
输入为一个二维数组 docs，docs{i}表示id 为 i 的文档。返回一个数组，其中每个元素是一个字符串，代表每对相似度大于 0 的文档，
其格式为 {id1},{id2}: {similarity}，其中 id1 为两个文档中较小的 id，similarity 为相似度，精确到小数点后 4 位。以任意顺序返回数组均可。
示例:
输入: 
{
 {14, 15, 100, 9, 3},
 {32, 1, 9, 3, 5},
 {15, 29, 2, 6, 8, 7},
 {7, 10}
}
输出:
{
 "0,1: 0.2500",
 "0,2: 0.1000",
 "2,3: 0.1429"
}
提示：
	docs.length <= 500
	docs{i}.length <= 500 */

class Solution1 {
public:
	vector<string> computeSimilarities(vector<vector<int>> &docs) {
		int n = docs.size();
		unordered_map<int, vector<int>> havesId;
		vector<vector<int>> sameCnt(n, vector<int>(n, 0));
		for(int i = 0; i < n; ++i) {
			for(auto val : docs[i]) {
				auto &ids = havesId[val];
				for(auto id : ids) {
					++sameCnt[id][i];
				}
				ids.push_back(i);
			}
		}
		vector<string> res;
		for(int i = 0; i < n; ++i) {
			for(int j = i + 1; j < n; ++j) {
				if(sameCnt[i][j]) {
					double val
					    = 1.0 * sameCnt[i][j] / (docs[i].size() + docs[j].size() - sameCnt[i][j]);
					res.emplace_back(
					    to_string(i) + "," + to_string(j) + ": " + to_string_fixed(val));
				}
			}
		}
		return res;
	}

private:
	std::string to_string_fixed(double val, int precision = 4) {
		double factor = std::pow(10, precision);
		double rounded = std::round(val * factor) / factor;
		std::string s = std::to_string(rounded);
		auto pos = s.find('.');
		if(pos != std::string::npos) {
			s = s.substr(0, pos + 1 + precision);
		}
		return s;
	}
}; // 直接用邻接矩阵

class Solution {
public:
	vector<string> computeSimilarities(vector<vector<int>> &docs) {
		int n = docs.size();
		unordered_map<int, vector<int>> havesId;
		unordered_map<pair<int, int>, int, HashPair> sameCnt;
		for(int i = 0; i < n; ++i) {
			for(auto val : docs[i]) {
				auto &ids = havesId[val];
				for(auto id : ids) {
					++sameCnt[{ id, i }];
				}
				ids.push_back(i);
			}
		}
		vector<string> res;
		char temp[256];
		for(auto &[ij, cnt] : sameCnt) {
			double sim = 1.0 * cnt / (docs[ij.first].size() + docs[ij.second].size() - cnt);
			res.emplace_back(format_pair(ij.first, ij.second, sim));
		}
		return res;
	}

private:
	string format_pair(int i, int j, double sim) {
		ostringstream oss;
		oss << i << "," << j << ": " << fixed << setprecision(4) << (sim + 1e-9);
		return oss.str();
	}
	struct HashPair {
		size_t operator()(const pair<int, int> &pa) const noexcept {
			return (size_t)pa.first << 32 | (size_t)pa.second;
		}
	};
}; // 注意到是稀疏矩阵

int main() {
	Solution sol;
	vector<vector<int>> docs;
	docs = { { 14, 15, 100, 9, 3 }, { 32, 1, 9, 3, 5 }, { 15, 29, 2, 6, 8, 7 }, { 7, 10 } };
	cout << sol.computeSimilarities(docs) << endl;
}