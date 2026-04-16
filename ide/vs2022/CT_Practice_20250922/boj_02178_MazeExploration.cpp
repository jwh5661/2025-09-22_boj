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

/*
* 2025-12-19 복귀 간단 복습
* 방문 처리 : bfs로 다음 장소의 값이 1일 때 + 방문하지 않았을 때만 큐에 넣음
* 거리 배열 : 방문 처리를 하면서 거리 배열을 최신화함. 
			  큐에서 목적지가 뽑혀나오면 그대로 종료.
*/

/*
* [ 백준 2178 ] 미로 탐색 ( S1 )
* - 훈련 날짜 : 2026-04-16 ( 목 )
* - 알고리즘 : 그래프 탐색 ( BFS )
* - 목적 : 가중치가 없는 2D 그리드 환경에서 최단 거리( Shortest Path ) 찾기
* - 엔진 실무 최적화 :
* 1. push 대신 emplace를 사용하여 임시 객체 생성 비용 제거
* 2. visited 배열을 단순히 bool이 아닌 int로 선언하여 방문 여부와 최단 거리를 동시에 추적
* 3. 2차원 배열 초기화 시 memset( -1 ) 활용 ( memset은 0, -1만 안전함 )
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int mx = 101;
int maze[mx][mx];
int visited[mx][mx];
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	memset(visited, -1, sizeof(visited));
	// fill(&visited[0][0], &visited[101][101], -1)은 왜 안될까? 
	// -> fill(&visited[0][0], &visited[0][0] + (mx * mx), -1);
	// 또는 fill(visited[0], visited[mx], -1);

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

// 2025-10-23 D+3 REVIEW

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
// 	vector<vector<int>> maze(n + 1, vector<int>(m + 1, 0));
// 	vector<vector<int>> visited(n + 1, vector<int>(m + 1, -1));
// 
// 	for (int i = 1; i <= n; i++)
// 	{
// 		string str;
// 		cin >> str;
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
// 		int cx = cur.first;
// 		int cy = cur.second;
// 		if (cur.first == n && cur.second == m)
// 			break;
// 
// 		for (int i = 0; i < 4; i++)
// 		{
// 			int nx = cx + dx[i];
// 			int ny = cy + dy[i];
// 
// 			if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
// 			if (maze[nx][ny] == 0) continue;
// 			if (visited[nx][ny] != -1) continue;
// 			q.emplace(nx, ny);
// 			visited[nx][ny] = visited[cx][cy] + 1;
// 		}
// 	}
// 
// 	cout << visited[n][m] << '\n';
// }

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