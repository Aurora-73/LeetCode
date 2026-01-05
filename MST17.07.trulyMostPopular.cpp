// Created: 2026-01-05
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 每年，政府都会公布一万个最常见的婴儿名字和它们出现的频率，也就是同名婴儿的数量。
有些名字有多种拼法，例如，John 和 Jon 本质上是相同的名字，但被当成了两个名字公布出来。给定两个列表，一个是名字及对应的频率，另一个是本质相同的名字对。
设计一个算法打印出每个真实名字的实际频率。注意，如果 John 和 Jon 是相同的，并且 Jon 和 Johnny 相同，则 John 与 Johnny 也相同，即它们有传递和对称性。
在结果列表中，选择 字典序最小 的名字作为真实名字。
示例：
输入：names = {"John(15)","Jon(12)","Chris(13)","Kris(4)","Christopher(19)"}, synonyms = {"(Jon,John)","(John,Johnny)","(Chris,Kris)","(Chris,Christopher)"}
输出：{"John(27)","Chris(36)"}
提示：
	names.length <= 100000 */

class Solution {
public:
	vector<string> trulyMostPopular(const vector<string> &names, const vector<string> &synonyms) {
		int nn = names.size();
		frequence.reserve(nn);
		for(auto &name : names) {
			name2map(name);
		}
		parent = vector<int>(nn, -1);
		for(auto &syn : synonyms) {
			Union(syn2pair(syn));
		}
		for(int i = 0; i < nn; ++i) {
			if(parent[i] != -1) {
				frequence[Find(i)] += frequence[i];
			}
		} // 不用处理后面加的，因为频率全是0
		vector<string> res;
		for(unsigned i = 0; i < pure_names.size(); ++i) {
			if(parent[i] == -1) {
				res.emplace_back(pure_names[i]);
				res.back() += "(" + to_string(frequence[i]) + ")";
			}
		}
		return res;
	}

private:
	vector<int> parent;
	vector<int> frequence;
	vector<string_view> pure_names;
	unordered_map<string_view, int> name2Id;
	void name2map(const string &name) {
		unsigned end = 0, n = name.size(), freq = 0;
		while(name[end] != '(') ++end;
		for(unsigned i = end + 1; name[i] != ')'; ++i) {
			freq = freq * 10 + name[i] - '0';
		}
		pure_names.emplace_back(name.data(), end);
		name2Id[pure_names.back()] = frequence.size();
		frequence.push_back(freq);
	} // 处理name，实现名称、id、频率的映射，然后将纯名字放入pure_names
	pair<int, int> syn2pair(const string &syn) {
		size_t combo = 0;
		while(syn[combo] != ',') ++combo;
		string_view sv[2] { { syn.data() + 1, combo - 1 },
			{ syn.data() + combo + 1, syn.size() - combo - 2 } };
		unordered_map<string_view, int>::iterator it[2] { name2Id.find(sv[0]),
			name2Id.find(sv[1]) };
		int id[2] { -1, -1 };
		for(int i = 0; i < 2; ++i) {
			if(it[i] == name2Id.end()) {
				id[i] = pure_names.size();
				name2Id[sv[i]] = id[i];
				pure_names.emplace_back(sv[i]);
				frequence.push_back(0);
				parent.push_back(-1);
			} else {
				id[i] = it[i]->second;
			}
		}
		return { id[0], id[1] };
	} // 将synonyms切分为两个name，然后在name2freqAndId查找这两个的id，如果不存在则新建到pure_name
	int Find(int id) {
		if(parent[id] == -1) return id;
		return parent[id] = Find(parent[id]);
	}
	void Union(pair<int, int> ab) {
		int pa = Find(ab.first), pb = Find(ab.second);
		if(pa != pb) {
			if(pure_names[pa] > pure_names[pb]) {
				parent[pa] = pb;
				parent[ab.first] = pb;
			} else {
				parent[pb] = pa;
				parent[ab.second] = pa;
			}
		}
	} // 这里要将字典序小的作为父节点
};

int main() {
	Solution sol;
	vector<string> names, synonyms;
	names = { "John(15)", "Jon(12)", "Chris(13)", "Kris(4)", "Christopher(19)" },
	synonyms = { "(Jon,John)", "(John,Johnny)", "(Chris,Kris)", "(Chris,Christopher)" };
	cout << sol.trulyMostPopular(names, synonyms) << endl;
}