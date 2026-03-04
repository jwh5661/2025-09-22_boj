// 2026-03-03 (ȭ)

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
	priority_queue<int, vector<int>, greater<int>> pq;

	while (n--)
	{
		int x;
		cin >> x;

		if (x == 0)
		{
			if (pq.empty())
				cout << 0 << '\n';
			else
			{
				cout << pq.top() << '\n';
				pq.pop();
			}
		}
		else
			pq.push(x);
	}
}