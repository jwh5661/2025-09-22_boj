// 2026-03-19 (¸ñ)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void backtrack(int idx, int depth, int m);

vector<pair<int, int>> house;
vector<pair<int, int>> chicken;
vector<int> path;
int house_num, chicken_num, ans = 1e9;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	house.reserve(2 * n);
	chicken.reserve(13);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int x;
			cin >> x;

			if (x == 2)
				chicken.emplace_back(i, j);
			else if (x == 1)
				house.emplace_back(i, j);
		}
	}

	house_num = (int)house.size();
	chicken_num = (int)chicken.size();
	path = vector<int>(m, -1);

	backtrack(0, 0, m);

	cout << ans << '\n';
}

void backtrack(int idx, int depth, int m)
{
	if (depth == m)
	{
		vector<int> dist(house_num, 1e9);
		int sum = 0;

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < house_num; j++)
			{
				dist[j] = min(dist[j], abs(chicken[path[i]].first - house[j].first)
					+ abs(chicken[path[i]].second - house[j].second));
			}
		}

		for (int d : dist)
			sum += d;

		ans = min(ans, sum);
		return;
	}

	for (int i = idx; i < chicken_num; i++)
	{
		path[depth] = i;

		backtrack(i + 1, depth + 1, m);

		path[depth] = -1;
	}
}