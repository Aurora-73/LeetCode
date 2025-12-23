// Created: 2025-12-23
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 字符串轮转。
给定两个字符串s1和s2，请编写代码检查s2是否为s1旋转而成
（比如，waterbottle是erbottlewat旋转后的字符串）。
示例 1：
	 输入：s1 = "waterbottle", s2 = "erbottlewat"
	 输出：True
示例 2：
	 输入：s1 = "aa", s2 = "aba"
	 输出：False
提示：
	字符串长度在{0, 100000}范围内。
	说明:
	你能只调用一次检查子串的方法吗？ */

class Solution1 {
public:
	bool isFlipedString(const string &s1, const string &s2) {
		if(s1.size() != s2.size()) return false;
		int n = s1.size();
		if(n == 0) return true;
		for(int i = 0; i < n; ++i) {
			if(s1[i] == s2[0]) {
				int j;
				for(j = 0; j < n; ++j) {
					if(s1[(i + j) % n] != s2[j]) {
						break;
					}
				}
				if(j == n) return true;
			}
		}
		return false;
	}
};

class Solution2 {
public:
	bool isFlipedString(const string &s1, const string &s2) {
		if(s1.size() != s2.size()) return false;
		return (s1 + s1).find(s2) != string::npos;
	}
}; // 如果s1 = xy，s2 = yx；则s1s2 = xyxy，其中一定包含s2
// 由于find是库函数，用的是KMP算法，因此时间复杂度平均为O(n)

class Solution {
public:
	bool isFlipedString(const string &s1, const string &s2) {
		if(s1.size() != s2.size()) return false;
		return DoubleFind(s1, s2);
	}

private:
	bool DoubleFind(const string &text, const string &pattern) {
		int text_len = text.size();
		int pat_len = pattern.size();
		if(pat_len == 0) return true;

		vector<int> lps(pat_len, 0);
		for(int i = 1, matched = 0; i < pat_len; ++i) {
			while(matched > 0 && pattern[i] != pattern[matched]) {
				matched = lps[matched - 1];
			}
			if(pattern[i] == pattern[matched]) {
				++matched;
			}
			lps[i] = matched;
		}
		int total = text_len * 2;
		for(int i = 0, matched = 0; i < total; ++i) {
			int idx = (i < text_len) ? i : (i - text_len);
			while(matched > 0 && text[idx] != pattern[matched]) {
				matched = lps[matched - 1];
			}
			if(text[idx] == pattern[matched]) {
				++matched;
			}
			if(matched == pat_len) {
				return true;
			}
		}
		return false;
	}
};

// int main() {
// 	Solution sol;
// 	string s1, s2;
// 	s1 = "waterbottle", s2 = "erbottlewat";
// 	cout << sol.isFlipedString(s1, s2) << endl;

// 	s1 = "aa", s2 = "aba";
// 	cout << sol.isFlipedString(s1, s2) << endl;
// }

using namespace std;
using namespace std::chrono;
// -------------------- 随机与测试用例生成 --------------------
static std::mt19937_64 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());

// 生成长度为 len 的随机小写字母字符串
string gen_random_string(int len, const string &alphabet) {
	string s;
	s.resize(len);
	uniform_int_distribution<int> dist(0, (int)alphabet.size() - 1);
	for(int i = 0; i < len; ++i) s[i] = alphabet[dist(rng)];
	return s;
}

// 将 s 按位置 rot 旋转（s.substr(rot) + s.substr(0, rot)）
string rotate_string(const string &s, int rot) {
	int n = s.size();
	if(n == 0) return s;
	rot %= n;
	if(rot < 0) rot += n;
	return s.substr(rot) + s.substr(0, rot);
}

// 随机把 s 中 pos 位置替换为与原字符不同的随机字符（alphabet 中）
void mutate_char_at(string &s, int pos, const string &alphabet) {
	if(s.empty()) return;
	char oldc = s[pos];
	char newc = oldc;
	uniform_int_distribution<int> dist(0, (int)alphabet.size() - 1);
	while(newc == oldc) newc = alphabet[dist(rng)];
	s[pos] = newc;
}

// -------------------- 测试主流程 --------------------
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// ============== 可配置参数 ==============
	const int NUM_TESTS = 50000;        // 测试用例总数（生成这么多对字符串）
	const int LEN = 200;                // 每个字符串长度（也可随机化）
	const double MISMATCH_RATIO = 0.20; // 多少比例的用例应被篡改为不匹配（0.0 - 1.0）
	const int NUM_WORST_CASES = 200;    // 插入多少最坏情况（大量相同字符）
	const string ALPHABET = "abcdefghijklmnopqrstuvwxyz"; // 可调整字符集
	const unsigned SEED = (unsigned)chrono::steady_clock::now().time_since_epoch().count();
	// =======================================

	cout << "配置: NUM_TESTS=" << NUM_TESTS << ", LEN=" << LEN
	     << ", MISMATCH_RATIO=" << MISMATCH_RATIO << ", NUM_WORST_CASES=" << NUM_WORST_CASES
	     << ", SEED=" << SEED << "\n\n";

	// 用确定种子便于复现（若想随机化，注释下一行）
	rng.seed(SEED);

	vector<pair<string, string>> tests;
	tests.reserve(NUM_TESTS + NUM_WORST_CASES);

	// 1) 生成随机旋转匹配 / 按比例做不匹配修改
	uniform_int_distribution<int> rot_dist(0, LEN - 1);
	uniform_real_distribution<double> prob(0.0, 1.0);
	uniform_int_distribution<int> pos_dist(0, LEN - 1);

	for(int t = 0; t < NUM_TESTS; ++t) {
		string s1 = gen_random_string(LEN, ALPHABET);
		int rot = rot_dist(rng);
		string s2 = rotate_string(s1, rot);

		// 按概率把 s2 改成不匹配（修改 1-3 个随机位置）
		if(prob(rng) < MISMATCH_RATIO) {
			int changes = 1 + (rng() % 3); // 1 到 3 个字符被改动
			for(int c = 0; c < changes; ++c) {
				int p = pos_dist(rng);
				mutate_char_at(s2, p, ALPHABET);
			}
		}
		tests.emplace_back(move(s1), move(s2));
	}

	// 2) 插入一些“最坏情况”：全部 'a' 的字符串（暴力法会退化）
	for(int i = 0; i < NUM_WORST_CASES; ++i) {
		string s1(LEN, 'a');
		// 大部分为匹配：旋转不会改变内容（仍然全是 'a'）
		string s2 = rotate_string(s1, i % LEN);
		// 但我们也插入一些确实不匹配的：把最后一个字符改为 'b'
		if(i % 3 == 0) s2[LEN - 1] = 'b';
		tests.emplace_back(move(s1), move(s2));
	}

	cout << "测试用例总数: " << tests.size() << "\n";

	Solution1 sol1;
	Solution2 sol2;

	// ---------- 测试 Solution1 ----------
	auto t0 = high_resolution_clock::now();
	size_t true_count1 = 0;
	vector<char> results1(tests.size());
	for(size_t i = 0; i < tests.size(); ++i) {
		const string &a = tests[i].first;
		const string &b = tests[i].second;
		bool res = sol1.isFlipedString(a, b);
		results1[i] = res ? 1 : 0;
		if(res) ++true_count1;
	}
	auto t1 = high_resolution_clock::now();
	double dur1 = duration_cast<duration<double, milli>>(t1 - t0).count();

	// ---------- 测试 Solution2 ----------
	auto t2 = high_resolution_clock::now();
	size_t true_count2 = 0;
	vector<char> results2(tests.size());
	for(size_t i = 0; i < tests.size(); ++i) {
		const string &a = tests[i].first;
		const string &b = tests[i].second;
		bool res = sol2.isFlipedString(a, b);
		results2[i] = res ? 1 : 0;
		if(res) ++true_count2;
	}
	auto t3 = high_resolution_clock::now();
	double dur2 = duration_cast<duration<double, milli>>(t3 - t2).count();

	// 校验两个实现的结果是否一致
	size_t mismatch_count = 0;
	for(size_t i = 0; i < tests.size(); ++i) {
		if(results1[i] != results2[i]) ++mismatch_count;
	}

	cout << fixed;
	cout << "Solution1 (暴力) : 总耗时 = " << dur1 << " ms, 平均每次 = " << (dur1 / tests.size())
	     << " ms, 返回 true 的数量 = " << true_count1 << "\n";
	cout << "Solution2 (s1+s1): 总耗时 = " << dur2 << " ms, 平均每次 = " << (dur2 / tests.size())
	     << " ms, 返回 true 的数量 = " << true_count2 << "\n";

	if(mismatch_count == 0) {
		cout << "两者返回一致 (所有用例结果相同)\n";
	} else {
		cout << "警告：两者返回不一致，数量 = " << mismatch_count << "\n";
		// 如有不一致，可打印部分案例进行排查
		for(size_t i = 0, printed = 0; i < tests.size() && printed < 10; ++i) {
			if(results1[i] != results2[i]) {
				cout << "例子 " << i << " : len=" << tests[i].first.size() << ", s1[:8]='"
				     << tests[i].first.substr(0, min(8, (int)tests[i].first.size())) << "'"
				     << ", s2[:8]='"
				     << tests[i].second.substr(0, min(8, (int)tests[i].second.size())) << "'\n";
				++printed;
			}
		}
	}

	cout << "\n提示：要调整压力测试参数，请修改程序顶部的 NUM_TESTS / LEN / MISMATCH_RATIO / "
	        "NUM_WORST_CASES，然后重新编译运行。\n";
	return 0;
}