// 2026-03-12 (¸ñ)

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

	long long ans = 0;
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;

		pq.push(x);
	}

	while (!pq.empty())
	{
		int cur = pq.top(); pq.pop();

		if (pq.empty())
		{
			cout << ans << '\n';
			return 0;
		}

		int val = cur + pq.top(); pq.pop();

		ans += val;
		pq.push(val);
	}
}