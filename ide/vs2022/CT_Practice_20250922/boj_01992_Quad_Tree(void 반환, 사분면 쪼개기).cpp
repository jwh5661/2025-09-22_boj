// 2026-04-13 (월)

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve(int y, int x, int size);

int n;
int video_data[65][65];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < n; j++)
			video_data[i][j] = str[j] - '0';
	}

	solve(0, 0, n);
}

void solve(int y, int x, int size)
{
	bool is_same = true;
	int mark = video_data[y][x];

	// 여기서 i < y;랑 j < x가 아니라 i < y + size;랑 j < x + size; 였음 -> 거의 30분동안 찾음
	for (int i = y; i < y + size; i++)
	{
		for (int j = x; j < x + size; j++)
		{
			if (video_data[i][j] != mark)
			{
				is_same = false;
				break;
			}
		}

		if (!is_same)
			break;
	}

	if (is_same)
	{
		cout << mark;
	}
	else
	{
		int half = size / 2;

		cout << '(';
		solve(y, x, half);
		solve(y, x + half, half);
		solve(y + half, x, half);
		solve(y + half, x + half, half);
		cout << ')';
	}
}