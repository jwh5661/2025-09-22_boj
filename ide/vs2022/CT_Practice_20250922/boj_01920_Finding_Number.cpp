// 2026-01-28 ORIGINAL

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;

	cin >> n;
	vector<int> num = vector<int>(n);

	for (int i = 0; i < n; i++)
		cin >> num[i];

	sort(num.begin(), num.end());

	cin >> m;
	while (m--)
	{
		int target;
		cin >> target;
		if (binary_search(num.begin(), num.end(), target))
			cout << 1;
		else
			cout << 0;
		if (m != 0)
			cout << '\n';
	}
}