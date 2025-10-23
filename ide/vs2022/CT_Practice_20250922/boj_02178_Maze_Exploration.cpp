/*
BOJ 2178 — 미로 탐색 (Maze Exploration)
Topic: BFS | Grid | Shortest-Path
Folder: graph/bfs

⏱ 시간복잡도: O(N*M)
💾 공간복잡도: O(N*M)

📌 핵심 아이디어
- 시작 (1,1)에서 4방향 BFS로 전파하며, 방문 배열에 "거리(칸 수)"를 저장./
- 이동 가능 조건: 범위 내 && 길(maze==1) && 미방문(visited==-1).
- BFS 종료 후 visited[N][M]이 최단 경로 길이.

⚠️ 주의할 점
- 입력을 문자로 받아 `'0'/'1'` -> 0/1로 변환(현재처럼 `- '0'`).
- 시작 칸이 1이 아닌 입력은 보통 주어지지 않지만, 방어적으로 체크해도 좋음.
- 1-based 인덱싱을 쓰므로 경계식과 초기화(visited[1][1]=1)를 일관되게 유지.

✔️ 지문 힌트
- 가중치가 동일(모두 1)이므로 다익스트라가 아닌 **BFS**로 최단 거리 계산이 가능.

*/

// 2025-10-23 D+3 REVIEW

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> maze(n + 1, vector<int>(m + 1, 0));
	vector<vector<int>> visited(n + 1, vector<int>(m + 1, -1));

	for (int i = 1; i <= n; i++)
	{
		string str;
		cin >> str;
		for (int j = 1; j <= m; j++)
			maze[i][j] = str[j - 1] - '0';
	}

	queue<pair<int, int>> q;
	q.emplace(1, 1);
	visited[1][1] = 1;

	while (!q.empty())
	{
		auto cur = q.front(); q.pop();
		int cx = cur.first;
		int cy = cur.second;
		if (cur.first == n && cur.second == m)
			break;

		for (int i = 0; i < 4; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
			if (maze[nx][ny] == 0) continue;
			if (visited[nx][ny] != -1) continue;
			q.emplace(nx, ny);
			visited[nx][ny] = visited[cx][cy] + 1;
		}
	}

	cout << visited[n][m] << '\n';
}

// 2025-10-15 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <string>
// #include <queue>
// 
// using namespace std;
// 
// int dx[4] = { 0, 0, -1, 1 };
// int dy[4] = { 1, -1, 0, 0 };
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, m;
// 	cin >> n >> m;
// 
// 	vector<vector<char>> maze(n + 1, vector<char>(m + 1, 0));
// 	vector<vector<int>> visited(n + 1, vector<int>(m + 1, -1));
// 
// 	for (int i = 1; i <= n; i++)
// 	{
// 		string str;
// 		cin >> str;
// 
// 		for (int j = 1; j <= m; j++)
// 			maze[i][j] = str[j - 1] - '0';
// 	}
// 
// 	queue<pair<int, int>> q;
// 	q.emplace(1, 1);
// 	visited[1][1] = 1;
// 
// 	while (!q.empty())
// 	{
// 		auto cur = q.front(); q.pop();
// 
// 		for (int i = 0; i < 4; i++)
// 		{
// 			int nxt_x = cur.first + dx[i];
// 			int nxt_y = cur.second + dy[i];
// 
// 			if (nxt_x <= 0 || nxt_x > n || nxt_y <= 0 || nxt_y > m) continue;
// 			if (maze[nxt_x][nxt_y] == 0) continue;
// 			if (visited[nxt_x][nxt_y] != -1) continue;
// 			
// 			q.emplace(nxt_x, nxt_y);
// 			visited[nxt_x][nxt_y] = visited[cur.first][cur.second] + 1;
// 		}
// 	}
// 
// 	cout << visited[n][m] << '\n';
// }