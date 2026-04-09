// 2026-04-08 (¼ö)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--)
	{
		int n, k;
		cin >> n >> k;

		vector<vector<int>> con_list(n + 1);
		vector<int> construct_time(n + 1, -1);
		vector<int> final_time(n + 1, 0);
		vector<int> freq(n + 1, 0);
		queue<int> q;

		for (int i = 1; i <= n; i++)
			cin >> construct_time[i];

		for (int i = 0; i < k; i++)
		{
			int b1, b2;
			cin >> b1 >> b2;

			con_list[b1].push_back(b2);
			freq[b2]++;
		}

		for (int i = 1; i <= n; i++)
		{
			if (freq[i] == 0)
				q.push(i);
		}

		int target;
		cin >> target;

		while (!q.empty())
		{
			int cur = q.front(); q.pop();
			final_time[cur] += construct_time[cur];

			if (cur == target) break;

			for (int building : con_list[cur])
			{
				freq[building]--;
				final_time[building] = max(final_time[building], final_time[cur]);

				if (freq[building] == 0)
					q.push(building);
			}
		}

		cout << final_time[target] << '\n';
	}
}