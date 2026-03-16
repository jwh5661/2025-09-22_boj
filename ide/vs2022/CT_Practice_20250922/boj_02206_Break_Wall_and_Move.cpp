// 2026-03-16 (¿ù)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
	int x, y, broken;

	Node(int nx, int ny, int nbroken)
		: x(nx), y(ny), broken(nbroken) {
	};
};

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> map(n + 1, vector<int>(m + 1, 0));
	vector<vector<vector<int>>> visited(
		n + 1, vector<vector<int>>(m + 1, vector<int>(2, -1))
	);
	queue<Node> q;

	for (int i = 1; i <= n; i++)
	{
		string str;
		cin >> str;

		for (int j = 1; j <= m; j++)
			map[i][j] = str[j - 1] - '0';
	}
	
	q.emplace(1, 1, 0);
	visited[1][1][0] = 1;

	while (!q.empty())
	{
		Node cur = q.front(); q.pop();
		int cx = cur.x;
		int cy = cur.y;
		int cbroken = cur.broken;

		if (cx == n && cy == m) break;

		for (int d = 0; d < 4; d++)
		{
			int nx = cx + dx[d];
			int ny = cy + dy[d];
			int nbroken = cbroken;

			if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
			if (map[nx][ny] == 1)
			{
				if (nbroken == 1) continue;
				else nbroken++;
			}
			if (visited[nx][ny][nbroken] != -1) continue;

			q.emplace(nx, ny, nbroken);
			visited[nx][ny][nbroken] = visited[cx][cy][cbroken] + 1;
		}
	}

	cout << max(visited[n][m][0], visited[n][m][1]) << '\n';
}