// 2026-03-26 (¸ñ)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool FindCount(long long x);

vector<long long> location;
int n, c;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> c;

	long long start = 0, end = -1;
	location.assign(n, 0);

	for (int i = 0; i < n; i++)
	{
		cin >> location[i];

		end = max(end, location[i]);
	}

	sort(location.begin(), location.end());

	while (start < end)
	{
		long long mid = (start + end + 1) / 2;
		if (FindCount(mid)) start = mid;
		else end = mid - 1;
	}

	cout << start << '\n';
}

bool FindCount(long long x)
{
	long long cur = 1;
	int idx = 0;
	for (int i = 1; i < n; i++)
	{
		if (location[i] - location[idx] >= x)
		{
			cur++;
			idx = i;
		}
	}

	return cur >= c;
}