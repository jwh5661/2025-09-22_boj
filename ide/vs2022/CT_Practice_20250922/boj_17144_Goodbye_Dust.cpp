// 2026-03-24 (ȭ)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void Purifier_Operation(int dir, int order[]);

vector<vector<int>> room;
vector<vector<int>> add_dust;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };
int upper_order[4] = { 2, 1, 3, 0 };
int lower_order[4] = { 3, 1, 2, 0 };
int R, C, T;
int upper_purifier_x, upper_purifier_y;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int ans = 0;

	cin >> R >> C >> T;

	upper_purifier_x = -1;
	upper_purifier_y = 0;
	room = vector<vector<int>>(R, vector<int>(C, 0));
	add_dust = vector<vector<int>>(R, vector<int>(C, 0));
	queue<pair<int, int>> q;

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> room[i][j];

			if (room[i][j] == -1 && upper_purifier_x == -1)
				upper_purifier_x = i;
			else if (room[i][j] != 0 && room[i][j] >= 5)
				q.emplace(i, j);
		}
	}

	while (T--)
	{
		add_dust.assign(R, vector<int>(C, 0));
		int q_size = (int)q.size();

		while (q_size--)
		{
			auto cur = q.front(); q.pop();
			int cx = cur.first;
			int cy = cur.second;

			for (int d = 0; d < 4; d++)
			{
				int nx = cx + dx[d];
				int ny = cy + dy[d];
				int ndust = room[cx][cy] / 5;

				if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
				if (room[nx][ny] == -1) continue;

				add_dust[cx][cy] -= ndust;
				add_dust[nx][ny] += ndust;
			}
		}

		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
				room[i][j] += add_dust[i][j];
		}

		Purifier_Operation(0, upper_order);
		Purifier_Operation(1, lower_order);

		int tmp_ans = 0;
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				if (room[i][j] != -1)
					tmp_ans += room[i][j];

				if (room[i][j] >= 5)
					q.emplace(i, j);
			}
		}
		ans = tmp_ans;
	}

	cout << ans << '\n';
}

void Purifier_Operation(int dir, int order[])
{
	int rotate_x = upper_purifier_x - 1;
	if (dir == 1)
		rotate_x += 3;
	int rotate_y = upper_purifier_y;

	for (int i = 0; i < 4; i++)
	{
		while ((rotate_x + dx[order[i]] >= 0
			&& rotate_x + dx[order[i]] < R
			&& rotate_y + dy[order[i]] >= 0
			&& rotate_y + dy[order[i]] < C)
			&& room[rotate_x + dx[order[i]]][rotate_y + dy[order[i]]] != -1)
		{
			if (i == 2)
			{
				if (dir == 0 && rotate_x == upper_purifier_x)
					break;
				else if (dir == 1 && rotate_x == upper_purifier_x + 1)
					break;
			}
			room[rotate_x][rotate_y] = room[rotate_x + dx[order[i]]][rotate_y + dy[order[i]]];

			rotate_x += dx[order[i]];
			rotate_y += dy[order[i]];
		}
	}

	if (dir == 0)
		room[upper_purifier_x][upper_purifier_y + 1] = 0;
	else
		room[upper_purifier_x + 1][upper_purifier_y + 1] = 0;
}