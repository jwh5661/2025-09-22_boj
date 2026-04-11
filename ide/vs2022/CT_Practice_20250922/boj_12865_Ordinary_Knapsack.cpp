// 2026-03-05 (¸ñ)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dp[100001];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	for (int i = 0; i < n; i++)
	{
		int w, v;
		cin >> w >> v;

		for (int j = k; j >= w; j--)
		{
			dp[j] = max(dp[j - w] + v, dp[j]);
		}
	}

	cout << dp[k] << '\n';
}