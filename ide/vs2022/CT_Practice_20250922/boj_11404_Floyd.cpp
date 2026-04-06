// 2026-04-06 (¿ù)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<long long>> visited(n + 1, vector<long long>(n + 1, 1e9));

	for (int i = 1; i <= n; i++)
		visited[i][i] = 0;

	for (int i = 0; i < m; i++)
	{
		int dep, arr;
		long long cost;
		cin >> dep >> arr >> cost;

		visited[dep][arr] = min(visited[dep][arr], cost);
	}

	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (i == j) continue;
				visited[i][j] = min(visited[i][j], visited[i][k] + visited[k][j]);
			}
				
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (visited[i][j] == 1e9) cout << 0 << ' ';
			else cout << visited[i][j] << ' ';
		}
		cout << '\n';
	}
}