// 2026-03-25 (수)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void FindTetromino(int x, int y, int depth, int sum);
void FindTShape(int x, int y);

vector<vector<int>> map;
vector<vector<bool>> visited;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int mx_val = -1;
int n, m;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;

	map.assign(n, vector<int>(m, 0));
	visited.assign(n, vector<bool>(m, false));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cin >> map[i][j];
	}

	// 테트로미노 놓기

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			FindTetromino(i, j, 1, 0);
			FindTShape(i, j);
		}
	}

	cout << mx_val << '\n';
}

void FindTetromino(int x, int y, int depth, int sum)
{
	if (depth == 4)
	{
		mx_val = max(sum + map[x][y], mx_val);
		return;
	}

	visited[x][y] = true;

	for (int d = 0; d < 4; d++)
	{
		int nx = x + dx[d];
		int ny = y + dy[d];

		if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
		if (visited[nx][ny]) continue;

		FindTetromino(nx, ny, depth + 1, sum + map[x][y]);
	}

	visited[x][y] = false;
}

void FindTShape(int x, int y)
{
	int cnt = 0;
	int sum = map[x][y];
	int sub_arr[4] = { 0, 0, 0, 0 };

	for (int d = 0; d < 4; d++)
	{
		int nx = x + dx[d];
		int ny = y + dy[d];

		if (nx < 0 || nx >= n || ny < 0 || ny >= m) 
		{
			cnt++;
			if (cnt == 2)
				return;
			continue;
		}

		sum += map[nx][ny];
		sub_arr[d] = map[nx][ny];
	}

	if (cnt == 1)
	{
		mx_val = max(sum, mx_val);
		return;
	}
	else
	{
		for (int i = 0; i < 4; i++)
			mx_val = max(sum - sub_arr[i], mx_val);
		return;
	}
}