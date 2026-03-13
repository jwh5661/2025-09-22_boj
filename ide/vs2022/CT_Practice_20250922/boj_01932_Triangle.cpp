// 2026-03-13 (±Ý)

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

	vector<int> dp(n, 0);

	cin >> dp[0];
	for (int i = 1; i < n; i++)
	{
		int x, prev;
		cin >> x;

		prev = dp[0];
		dp[0] = dp[0] + x;

		for (int j = 1; j < i; j++)
		{
			cin >> x;

			int val = max(prev, dp[j]) + x;
			prev = dp[j];
			dp[j] = val;
		}

		cin >> x;
		dp[i] = prev + x;
	}

	cout << *max_element(dp.begin(), dp.end()) << '\n';
}