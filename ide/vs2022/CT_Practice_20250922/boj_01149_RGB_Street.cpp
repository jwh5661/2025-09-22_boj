// 2026-03-06 (±Ý)

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

	const int num_color = 3, MAX = 1e9;
	vector<vector<int>> cost(n, vector<int>(num_color));
	vector<vector<int>> dp(2, vector<int>(num_color, MAX));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < num_color; j++)
			cin >> cost[i][j];
	}

	dp[1][0] = cost[0][0];
	dp[1][1] = cost[0][1];
	dp[1][2] = cost[0][2];
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < num_color; j++)
			swap(dp[1][j], dp[0][j]);

		dp[1][0] = cost[i][0] + min(dp[0][1], dp[0][2]);
		dp[1][1] = cost[i][1] + min(dp[0][0], dp[0][2]);
		dp[1][2] = cost[i][2] + min(dp[0][0], dp[0][1]);
	}

	cout << min(min(dp[1][0], dp[1][1]), dp[1][2]) << '\n';
}