// 2026-03-23 (¿ù)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool can_horizontal(vector<vector<int>>& map, int x, int y);
bool can_vertical(vector<vector<int>>& map, int x, int y);
bool can_diagonal(vector<vector<int>>& map, int x, int y);

struct Pipe {
	int state, x, y;

	Pipe(int nstate, int nx, int ny)
		:state(nstate), x(nx), y(ny) {
	};
};

int horizontal[2][2] = { {0, 1}, {1, 1} };
int vertical[2][2] = { {1, 0}, {1, 1} };
int diagonal[3][2] = { {0, 1}, {1, 0}, {1, 1} };
int element_size[3] = { 2, 2, 3 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<vector<int>> map(n + 1, vector<int>(n + 1, 1));
	vector<vector<int>> cnt(n + 1, vector<int>(n + 1, 0));
	queue<Pipe> q;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cin >> map[i][j];
	}

	cnt[1][1] = 1;
	cnt[1][2] = 1;
	q.emplace(0, 1, 2);

	while (!q.empty())
	{
		auto cur = q.front(); q.pop();

		switch (cur.state)
		{
		case 0:
		{
			for (int i = 0; i < element_size[cur.state]; i++)
			{
				int nstate = -1;
				int nx = cur.x + horizontal[i][0];
				int ny = cur.y + horizontal[i][1];

				if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;
				if (i == 0)
				{
					if (!can_horizontal(map, cur.x, cur.y)) continue;
					nstate = 0;
				}
				else
				{
					if (!can_diagonal(map, cur.x, cur.y)) continue;
					nstate = 2;
				}

				cnt[nx][ny]++;
				q.emplace(nstate, nx, ny);
			}
			break;
		}
		case 1:
		{
			for (int i = 0; i < element_size[cur.state]; i++)
			{
				int nstate = -1;
				int nx = cur.x + vertical[i][0];
				int ny = cur.y + vertical[i][1];

				if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;
				if (i == 0)
				{
					if (!can_vertical(map, cur.x, cur.y)) continue;
					nstate = 1;
				}
				else
				{
					if (!can_diagonal(map, cur.x, cur.y)) continue;
					nstate = 2;
				}

				cnt[nx][ny]++;
				q.emplace(nstate, nx, ny);
			}
			break;
		}
		case 2:
		{
			for (int i = 0; i < element_size[cur.state]; i++)
			{
				int nstate = -1;
				int nx = cur.x + diagonal[i][0];
				int ny = cur.y + diagonal[i][1];

				if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;
				if (i == 0)
				{
					if (!can_horizontal(map, cur.x, cur.y)) continue;
					nstate = i;
					
				}
				else if (i == 1)
				{
					if (!can_vertical(map, cur.x, cur.y)) continue;
					nstate = 1;
				}
				else
				{
					if (!can_diagonal(map, cur.x, cur.y)) continue;
					nstate = 2;
				}

				cnt[nx][ny]++;
				q.emplace(nstate, nx, ny);
			}
			break;
		}
		}
	}

	cout << cnt[n][n] << '\n';
}

bool can_horizontal(vector<vector<int>>& map, int x, int y)
{
	if (map[x + diagonal[0][0]][y + diagonal[0][1]] != 0)
		return false;
	return true;
}

bool can_vertical(vector<vector<int>>& map, int x, int y)
{
	if (map[x + diagonal[1][0]][y + diagonal[1][1]] != 0)
		return false;
	return true;
}

bool can_diagonal(vector<vector<int>>& map, int x, int y)
{
	if (map[x + diagonal[0][0]][y + diagonal[0][1]] != 0
		|| map[x + diagonal[1][0]][y + diagonal[1][1]] != 0
		|| map[x + diagonal[2][0]][y + diagonal[2][1]] != 0
		)
		return false;
	return true;
}