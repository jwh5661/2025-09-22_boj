// 2026-03-07 (≈‰)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<int> num;
	num.reserve(n);

	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;

		if (num.empty() || num.back() < x) num.push_back(x);
		else *lower_bound(num.begin(), num.end(), x) = x;
	}

	cout << (int)num.size() << '\n';
}