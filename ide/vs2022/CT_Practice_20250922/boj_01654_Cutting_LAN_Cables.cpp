// 2026-03-16 (¿ù)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int k, n;
	cin >> k >> n;

	long long ans = 0;
	vector<long long> cable(k);
	long long left = 1, right = 0;

	for (int i = 0; i < k; i++)
	{
		cin >> cable[i];
		
		if (right < cable[i])
			right = cable[i];
	}
	
	while (left <= right)
	{
		long long count = 0;
		long long mid = (left + right) / 2;

		for (int i = 0; i < k; i++)
			count += cable[i] / mid;

		if (count >= n)
		{
			left = mid + 1;
			ans = mid;
		}
		else
			right = mid - 1;
	}

	cout << ans << '\n';
}