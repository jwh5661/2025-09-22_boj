// 2026-03-04 (¼ö)

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

	vector<int> coin(n);
	vector<long long> dp(k + 1, 0);
	for (int i = 0; i < n; i++)
		cin >> coin[i];

	sort(coin.begin(), coin.end());

	dp[0] = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = coin[i]; j <= k; j++)
		{
			dp[j] += dp[j - coin[i]];
		}
	}

	cout << dp[k] << '\n';
}