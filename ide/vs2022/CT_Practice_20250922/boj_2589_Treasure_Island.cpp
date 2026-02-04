/*
BOJ 2589 — 보물섬 (Treasure Island)
Topic: BFS | Graph | Grid
Folder: graph/bfs

⏱ 시간복잡도: O((N*M) * (N*M))   // 각 육지에서 BFS
💾 공간복잡도: O(N*M)

📌 핵심 아이디어
- 지도에서 'L'(육지)인 칸마다 BFS를 수행해, 그 출발점에서의 **최장 최단거리**를 구함.
- 모든 시작점에 대해 최대값을 갱신 -> 전체 지도에서 가장 먼 두 육지 사이의 거리.

⚠️ 주의할 점
- 시작점이 고립된 육지라도 최단거리는 0이므로, `BFS`와 `ans`는 0으로 시작.
- 경계/방문 체크 순서와 조건: 범위 -> 육지 여부 -> 미방문(`visited == -1`) 순으로 안전하게 필터.
- 입력은 'W/L' 문자이므로 내부 맵은 불리언/char로도 충분(현재 int도 OK).

*/

// 2026-02-04 Reboot 간단 복습
// 
// 모든 땅인 지역에서 BFS 진행
// BFS 함수에 리턴값을 int로 지정하고, 해당 위치에서 가장 많이 걸린 시간을 리턴
// 리턴값을 받으면 바로 최댓값과 비교하여 최댓값 결정 후 출력


// 2025-11-04 D+3 REVIEW

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int BFS(int x, int y);

vector<vector<int>> treasure;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };
int n, m;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int mx = 0;
	cin >> n >> m;

	treasure = vector<vector<int>>(n, vector<int>(m, 0));

	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < m; j++)
		{
			if (str[j] == 'L')
				treasure[i][j] = 1;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (treasure[i][j] != 1) continue;
			mx = max(mx, BFS(i, j));
		}
	}

	cout << mx << '\n';
}

int BFS(int x, int y)
{
	queue<pair<int, int>> q;
	vector<vector<int>> visited(n, vector<int>(m, -1));
	int ret = 0;
	q.emplace(x, y);
	visited[x][y] = 0;

	while (!q.empty())
	{
		auto cur = q.front(); q.pop();
		int cx = cur.first;
		int cy = cur.second;

		for (int i = 0; i < 4; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (treasure[nx][ny] == 0) continue;
			if (visited[nx][ny] != -1) continue;

			q.emplace(nx, ny);
			visited[nx][ny] = visited[cx][cy] + 1;
			ret = max(ret, visited[nx][ny]);
		}
	}

	return ret;
}

// 2025-10-20 ORIGINAL

// #include <iostream>
// #include <string>
// #include <vector>
// #include <queue>
// 
// using namespace std;
// 
// int BFS(int x, int y);
// 
// vector<vector<int>> treasure;
// int dx[4] = { 0, 0, -1, 1 };
// int dy[4] = { -1, 1, 0, 0 };
// int n, m;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int mx_val = -1;
// 	cin >> n >> m;
// 
// 	treasure = vector<vector<int>>(n, vector<int>(m, 0));
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		string str;
// 		cin >> str;
// 		for (int j = 0; j < m; j++)
// 		{
// 			if (str[j] == 'L')
// 				treasure[i][j] = 1;
// 		}
// 	}
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		for (int j = 0; j < m; j++)
// 		{
// 			if (treasure[i][j] == 0) continue;
// 			mx_val = max(mx_val, BFS(i, j));
// 		}
// 	}
// 
// 	cout << mx_val << '\n';
// }
// 
// int BFS(int x, int y)
// {
// 	queue<pair<int, int>> q;
// 	vector<vector<int>> visited(n, vector<int>(m, -1));
// 	int ans = 0;
// 
// 	q.emplace(x, y);
// 	visited[x][y] = 0;
// 
// 	while (!q.empty())
// 	{
// 		auto cur = q.front(); q.pop();
// 
// 		for (int i = 0; i < 4; i++)
// 		{
// 			int nx = cur.first + dx[i];
// 			int ny = cur.second + dy[i];
// 
// 			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
// 			if (treasure[nx][ny] == 0) continue;
// 			if (visited[nx][ny] != -1) continue;
// 
// 			q.emplace(nx, ny);
// 			visited[nx][ny] = visited[cur.first][cur.second] + 1;
// 			ans = max(ans, visited[nx][ny]);
// 		}
// 	}
// 
// 	return ans;
// }