// 2026-04-01 (¼ö)

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

struct Minsik {
	int x, y, keys;
	
	Minsik(int nx, int ny, int nkeys)
		: x(nx), y(ny), keys(nkeys) {
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<char>> maze(n, vector<char>(m));
	vector<vector<vector<int>>> visited(n, vector<vector<int>>(m, vector<int>(64, -1)));
	queue<Minsik> q;

	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;

		for (int j = 0; j < m; j++)
		{
			maze[i][j] = str[j];

			if (maze[i][j] == '0')
			{
				q.emplace(i, j, 0);
				visited[i][j][0] = 0;
				maze[i][j] = '.';
			}
		}
	}

	while (!q.empty())
	{
		auto cur = q.front(); q.pop();
		int cx = cur.x;
		int cy = cur.y;
		int ckeys = cur.keys;

		for (int d = 0; d < 4; d++)
		{
			int nx = cx + dx[d];
			int ny = cy + dy[d];
			int nkeys = ckeys;
			
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

			if (maze[nx][ny] == '#')
				continue;
			else if (maze[nx][ny] >= 'A' && maze[nx][ny] <= 'F')
			{
				if (!(nkeys & (1 << maze[nx][ny] - 'A'))) continue;
			}
			else if (maze[nx][ny] >= 'a' && maze[nx][ny] <= 'f')
			{
				nkeys = nkeys | (1 << maze[nx][ny] - 'a');
			}
			else if (maze[nx][ny] == '1')
			{
				cout << visited[cx][cy][ckeys] + 1 << '\n';
				return 0;
			}

			if (visited[nx][ny][nkeys] != -1) continue;

			q.emplace(nx, ny, nkeys);
			visited[nx][ny][nkeys] = visited[cx][cy][ckeys] + 1;
		}
	}

	cout << -1 << '\n';
}