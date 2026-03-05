// 2026-03-05 (¸ñ)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	
	vector<pair<int, int>> items(n);
	vector<int> dp(k + 1, 0);

	for (int i = 0; i < n; i++)
	{
		int w, v;
		cin >> w >> v;

		items[i] = { w, v };
	}

	for (int i = 0; i < n; i++)
	{
		int cw = items[i].first;
		int cv = items[i].second;

		for (int j = k; j >= cw; j--)
		{
			dp[j] = max(dp[j - cw] + cv, dp[j]);
		}
	}

	cout << dp[k] << '\n';
}