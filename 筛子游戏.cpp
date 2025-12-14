// Created: 2025-07-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

vector<double> get_probability(int dice) {
	const int faces = 6;
	vector<double> vec(31, 0.0);
	vector<vector<long long>> ways(dice + 1, vector<long long>(dice * faces + 1, 0));

	for(int f = 1; f <= faces; ++f) {
		ways[1][f] = 1;
	}

	for(int d = 2; d <= dice; ++d) {
		for(int s = d; s <= d * faces; ++s) {
			long long count = 0;
			for(int f = 1; f <= faces; ++f) {
				if(s - f >= (d - 1) && s - f <= (d - 1) * faces) {
					count += ways[d - 1][s - f];
				}
			}
			ways[d][s] = count;
		}
	}

	long long total = 1;
	for(int i = 0; i < dice; ++i) total *= faces;

	for(int s = 5; s <= 30; ++s) {
		vec[s] = static_cast<double>(ways[dice][s]) / static_cast<double>(total);
	}

	return vec;
}

int main() {
	vector<int> money = { 350,
		50,
		350,
		20,
		100,
		30,
		500,
		20,
		400,
		20,
		350,
		20,
		188,
		-50,
		350,
		20,
		100,
		0,
		20,
		30,
		1000,
		30,
		350,
		20,
		30,
		20 };
	vector<int> step = { 14,
		15,
		12,
		11,
		10,
		19,
		20,
		7,
		22,
		30,
		24,
		29,
		26,
		27,
		28,
		25,
		5,
		23,
		6,
		21,
		8,
		9,
		18,
		17,
		16,
		13 };

	vector<double> probability = get_probability(5);
	array<int, 31> cnt;

	// 第一行：点数
	cout << setw(7) << "点数:   ";
	for(int s = 5; s <= 30; ++s) {
		cout << setw(7) << s; // 右对齐，宽度 10
	}
	cout << endl;

	// 第二行：概率（科学计数法）
	cout << setw(7) << "概率‰   ";
	for(int s = 5; s < 31; ++s) {
		cout << setw(7) << setprecision(4) << probability[s] * 1000;
	}
	cout << endl;

	// 计算右转收益
	cnt.fill(0);
	for(int i = 0; i < 26; ++i) {
		cnt[step[i]] = money[(step[i] + i - 1) % 26];
	}

	cout << setw(7) << "右转收益";
	for(int s = 5; s < 31; ++s) {
		cout << setw(7) << cnt[s];
	}
	cout << endl;

	double sum_right = 0;
	for(int i = 5; i < 31; ++i) {
		sum_right += cnt[i] * probability[i];
	}

	// 计算左转收益
	cnt.fill(0);
	for(int i = 0; i < 26; ++i) {
		cnt[step[i]] = money[(i - step[i] + 1 + 26 + 26) % 26];
	}
	cout << setw(7) << "左转收益";
	for(int s = 5; s < 31; ++s) {
		cout << setw(7) << cnt[s];
	}
	cout << endl;

	double sum_left = 0;
	for(int i = 5; i < 31; ++i) {
		sum_left += cnt[i] * probability[i];
		//cout << i << " " << cnt[i] << endl;
	}
	cout << endl;
	cout << "右转数学期望: " << sum_left << endl;
	cout << "左转数学期望: " << sum_right << endl;

	cout << endl;
	cout << "10元5次期望: " << (sum_left + sum_right) / 2 * 5 - 10 << endl;
	cout << "20元12次期望: " << (sum_left + sum_right) / 2 * 12 - 20 << endl;
}