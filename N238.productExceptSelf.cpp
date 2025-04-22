#include <vector>
#include <iostream>
using std::vector;

class Solution {
public:
	vector<int> productExceptSelf(vector<int> &nums) {
		int n = nums.size();
		vector<int> pre(n), suf(n);
		pre[0] = 1;
		suf[n - 1] = 1;
		for(int i = 1; i < n; i++) {
			pre[i] = pre[i - 1] * nums[i - 1];
			suf[n - 1 - i] = suf[n - i] * nums[n - i];
		}
		for(int i = 0; i < n; i++) {
			pre[i] *= suf[i];
		}
		return pre;
	} // ����ǰ׺��׺��������������
	vector<int> productExceptSelf1(vector<int> &nums) {
		int n = nums.size();
		int pre = 1, suf = 1;
		vector<int> res(n, 1);
		for(int i = 1; i < n; i++) {
			pre *= nums[i - 1];
			suf *= nums[n - i];
			res[i] *= pre;
			res[n - i - 1] *= suf;
		}
		return res;
	} // ������ֵ�ֱ��ʾǰ��׺����ÿ����һ�����˵���Ӧ����Ҫ�Ľ���У��ȳɺ���
	vector<int> productExceptSelf2(vector<int> &nums) {
		int n = nums.size();
		int L = 1, R = 1;
		vector<int> res(n, 1);
		for(int i = 0; i < n; i++) {
			res[i] *= L;
			res[n - i - 1] *= R;
			L *= nums[i];
			R *= nums[n - 1 - i];
		}
		return res;
	} // ͬ�ϣ��������ú��
};

int main() {
	vector<int> nums = {2, 3, 4, 5};
	Solution sol;
	auto sol_vec = sol.productExceptSelf1(nums);
	for(int i : sol_vec) {
		std::cout << i << " ";
	}
}