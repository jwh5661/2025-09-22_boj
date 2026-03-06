// 2026-03-06 (±Ý)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int k;
	cin >> k;

	while (k--)
	{
		int v, e;
		cin >> v >> e;

		vector<vector<int>> con_list(v + 1);
		vector<int> group(v + 1, -1);
		queue<int> q;

		for (int i = 0; i < e; i++)
		{
			int dep, arr;
			cin >> dep >> arr;

			con_list[dep].push_back(arr);
			con_list[arr].push_back(dep);
		}

		bool is_bipartite = true;
		for (int i = 1; i <= v; i++)
		{
			if (group[i] != -1) continue;
			q.push(i);
			group[i] = 0;

			while (!q.empty() && is_bipartite)
			{
				int cur = q.front(); q.pop();

				for (int next : con_list[cur])
				{
					if (group[next] == group[cur])
					{
						is_bipartite = false;
						break;
					}

					if (group[next] != -1) continue;
					q.push(next);
					
					if (group[cur] == 0)
						group[next] = 1;
					else
						group[next] = 0;
				}
			}
		}

		cout << (is_bipartite ? "YES" : "NO") << '\n';
	}
}