// 2026-03-20 (±Ý)

#include <iostream>
#include <vector>

using namespace std;

int Find(int a);
void Union(int a, int b);

vector<int> parent;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, true_num;
	cin >> n >> m >> true_num;

	vector<int> true_people(true_num);
	vector<int> party(m);

	for (int i = 0; i < true_num; i++)
		cin >> true_people[i];

	parent = vector<int>(n + 1);

	for (int i = 1; i <= n; i++)
		parent[i] = i;

	int ans = 0;

	for (int i = 0; i < m; i++)
	{
		int people_num, first_person;
		cin >> people_num >> first_person;

		for (int j = 0; j < people_num - 1; j++)
		{
			int new_person;
			cin >> new_person;

			Union(first_person, new_person);
		}
		party[i] = first_person;
	}

	for (int p : party)
	{
		bool can_lie = true;
		for (int i = 0; i < true_num; i++)
		{
			if (Find(p) == Find(true_people[i]))
				can_lie = false;
		}

		if (can_lie)
		{
			ans++;
		}
	}

	cout << ans << '\n';
}

int Find(int a)
{
	if (a == parent[a])
		return a;
	else 
		return parent[a] = Find(parent[a]);
}

void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	parent[b] = a;
}