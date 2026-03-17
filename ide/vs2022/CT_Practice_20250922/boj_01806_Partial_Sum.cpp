// 2026-03-17 (ȭ)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, s, ans = 1e9;
	cin >> n >> s;

	vector<int> sum(n + 1, 0);

	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;

		sum[i] = sum[i - 1] + x;
	}

	int left = 0, right = 1;

	while ((left <= n && right <= n) && (left <= right))
	{
		if (sum[right] - sum[left] >= s)
		{
			ans = min(ans, right - left);
			left++;
		}
		else
			right++;
	}

	if (ans == 1e9)
		cout << 0 << '\n';
	else
		cout << ans << '\n';
}