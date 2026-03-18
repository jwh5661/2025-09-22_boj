// 2026-03-18 (¼ö)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct CompareAbs {
	bool operator() (const int& a, const int& b) const
	{
		if (abs(a) == abs(b))
			return a > b;
		else
			return abs(a) > abs(b);
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	priority_queue<int, vector<int>, CompareAbs> pq;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
			
		if (x != 0)
			pq.push(x);
		else if (pq.empty())
			cout << 0 << '\n';
		else
		{
			cout << pq.top() << '\n';
			pq.pop();
		}
	}
}