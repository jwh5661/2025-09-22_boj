// 2026-03-17 (ȭ)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	for (int i = 0; i < n; i++)
	{
		int s, e;
		cin >> s >> e;

		pq.emplace(e, s);
	}

	int ans = 0, end_time = 0;
	while (!pq.empty())
	{
		auto cur = pq.top(); pq.pop();

		if (cur.second < end_time) continue;

		ans++;
		end_time = cur.first;
	}

	cout << ans << '\n';
}