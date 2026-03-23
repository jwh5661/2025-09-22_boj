// 2026-03-21 (≈‰)

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	unordered_map<string, bool> um;
	vector<string> names;
	names.reserve(n + m);

	while (n--)
	{
		string name;
		cin >> name;

		um[name] = true;
	}

	while (m--)
	{
		string name;
		cin >> name;

		if (um.find(name) != um.end())
			names.push_back(name);
	}

	sort(names.begin(), names.end());

	cout << names.size() << '\n';
	for (string s : names)
		cout << s << '\n';
}