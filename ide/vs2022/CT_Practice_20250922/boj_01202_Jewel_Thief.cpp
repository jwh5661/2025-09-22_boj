// 2026-03-13 (±Ý)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k, idx = 0;
	cin >> n >> k;

	long long ans = 0;
	vector<pair<int, int>> jewel(n);
	vector<int> bag(k);
	priority_queue<int> pq;

	for (int i = 0; i < n; i++)
	{
		int m, v;
		cin >> m >> v;

		jewel[i] = { m, v };
	}

	for (int i = 0; i < k; i++)
		cin >> bag[i];

	sort(jewel.begin(), jewel.end());
	sort(bag.begin(), bag.end());

	for (int i = 0; i < k; i++)
	{
		while (idx < n && jewel[idx].first <= bag[i])
		{
			pq.push(jewel[idx].second);
			idx++;
		}

		if (!pq.empty())
		{
			ans += pq.top();
			pq.pop();
		}
	}
	
	cout << ans << '\n';
}