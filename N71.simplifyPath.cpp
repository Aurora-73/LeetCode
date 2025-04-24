#include "MyUtils.h"

class Solution {
public:
	string simplifyPath(string path) {
		int n = path.size();
		stack<string> s;
		int i = 0;
		while(i < n) {
			while(i < n && path[i] == '/')
				i++;
			if(i >= n)
				break;
			int j = i;
			while(j < n && path[j] != '/')
				j++;
			string now = path.substr(i, j - i);
			if(now == "..") {
				if(!s.empty())
					s.pop();
			} else if(now != ".") {
				s.push(now);
			}
			while(j < n && path[j] == '/') {
				j++;
			}
			i = j;
		}
		string res;
		while(!s.empty()) {
			res = string("/") + s.top() + res;
			s.pop();
		}
		return res.size() ? res : "/";
	}
};

class Solution1 {
public:
	string simplifyPath(string path) {
		deque<string> dq;
		int n = path.size();
		int i = 0;
		while(i < n) {
			while(i < n && path[i] == '/') {
				i++;
			}
			if(i >= n) {
				break;
			}
			int j = i;
			while(j < n && path[j] != '/') {
				j++;
			}
			string dir = path.substr(i, j - i);
			i = j;
			if(dir == "..") {
				if(!dq.empty()) {
					dq.pop_back();
				}
			} else if(dir != ".") {
				dq.push_back(dir);
			}
		}
		string res;
		for(const string &s : dq) {
			res += "/" + s; // 直接顺序拼接
		}
		return res.empty() ? "/" : res;
	}
};

int main() {
	Solution1 sol;
	string path = "/home/";
	std::cout << sol.simplifyPath(path) << std::endl; // 修复这里
	path = "/home//foo/";
	std::cout << sol.simplifyPath(path) << std::endl; // 修复这里
	path = "/home/user/Documents/../Pictures";
	std::cout << sol.simplifyPath(path) << std::endl; // 修复这里
	path = "/.../a/../b/c/../d/./";
	std::cout << sol.simplifyPath(path) << std::endl; // 修复这里
}