// 2026-03-04 (¼ö)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int coin[101];
long long dp[10001];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	for (int i = 0; i < n; i++)
		cin >> coin[i];

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