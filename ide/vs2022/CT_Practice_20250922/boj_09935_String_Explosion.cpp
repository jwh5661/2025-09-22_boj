// 2026-03-27 (±Ý)

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string str, explode;
	cin >> str >> explode;

	string ans = "";
	int explode_size = (int)explode.size();

	for (int i = 0; i < (int)str.size(); i++)
	{
		ans += str[i];
		int ans_size = (int)ans.size();

		if (ans_size >= explode_size && ans[ans_size - 1] == explode[explode_size - 1])
		{
			bool can_explode = true;

			for (int j = 0; j < explode_size; j++)
			{
				if (ans[ans_size - explode_size + j] != explode[j])
				{
					can_explode = false;
					break;
				}
			}

			if (can_explode)
			{
				for (int j = 0; j < explode_size; j++)
					ans.pop_back();
			}
		}
	}

	if (!ans.empty())
		cout << ans << '\n';
	else
		cout << "FRULA" << '\n';
}