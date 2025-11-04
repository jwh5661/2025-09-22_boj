/*
BOJ 7569 — 토마토 (3D BFS)
Topic: BFS | Graph | 3D Grid
Folder: graph/bfs

⏱ 시간복잡도: O(H*N*M)
💾 공간복잡도: O(H*N*M)

📌 핵심 아이디어
- 3차원 격자에서 익은 토마토(1)를 모두 큐에 넣고, 동시에 BFS를 시작한다(멀티 소스).
- 익지 않은 칸(0)만 전파 대상으로 사용하고, visited를 날짜(거리)로 사용.
- BFS 종료 후 visited가 -1로 남은 칸(처음 0이었으나 도달 못한 칸)이 있으면 -1, 아니면 최대값이 정답.

⚠️ 주의할 점
- 경계 체크: (0 <= x < H), (0 <= y < N), (0 <= z < M)
- 입력 -1(빈 칸)은 확산 대상이 아니므로 tomato[nx][ny][nz] != 0 조건으로 자연스럽게 스킵됨,
- 시작점(1)은 visited 기본값 0으로 충분(명시 초기화 없어도 OK).
- 최종 답은 visited의 최대값, 전부 1이면 0일이 나와야 정상.

✔️ 개선 포인트(선택)
- 가독성: 변수명을 Layer/row/col처럼 바꾸면 이해가 더 쉬움.
- 메모리: visited는 int로 충분, tomato는 int 유지. 필요시 `array<int,3>`로 방향 벡터를 묶어 표현 가능.

*/

// 2025-11-04 D+3 REVIEW

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

int dx[6] = { -1, 1, 0, 0, 0, 0 };
int dy[6] = { 0, 0, 0, 0, 1, -1 };
int dz[6] = { 0, 0, -1, 1, 0, 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int m, n, h, ans = -1;
	cin >> m >> n >> h;

	vector<vector<vector<int>>> tomato(h, vector<vector<int>>(n, vector<int>(m)));
	vector<vector<vector<int>>> visited(h, vector<vector<int>>(n, vector<int>(m, 0)));
	queue<tuple<int, int, int>> q;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < m; k++)
			{
				cin >> tomato[i][j][k];
				if (tomato[i][j][k] == 1)
					q.emplace(i, j, k);
				else if (tomato[i][j][k] == 0)
					visited[i][j][k] = -1;
			}
		}
	}

	while (!q.empty())
	{
		auto cur = q.front(); q.pop();
		int cx = get<0>(cur);
		int cy = get<1>(cur);
		int cz = get<2>(cur);

		for (int i = 0; i < 6; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			int nz = cz + dz[i];

			if (nx < 0 || nx >= h || ny < 0 || ny >= n || nz < 0 || nz >= m) continue;
			if (visited[nx][ny][nz] != -1) continue;

			q.emplace(nx, ny, nz);
			visited[nx][ny][nz] = visited[cx][cy][cz] + 1;
		}
	}

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < m; k++)
			{
				if (visited[i][j][k] == -1)
				{
					cout << -1 << '\n';
					return 0;
				}

				ans = max(visited[i][j][k], ans);
			}
		}
	}

	cout << ans << '\n';
}

// 2025-10-20 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <tuple>
// #include <algorithm>
// 
// using namespace std;
// 
// int dx[6] = { -1, 1, 0, 0, 0, 0 };
// int dy[6] = { 0, 0, 0, 0, 1, -1 };
// int dz[6] = { 0, 0, -1, 1, 0, 0 };
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int m, n, h;
// 	cin >> m >> n >> h;
// 
// 	vector<vector<vector<int>>> tomato(h, vector<vector<int>>(n, vector<int>(m, 0)));
// 	vector<vector<vector<int>>> visited(h, vector<vector<int>>(n, vector<int>(m, 0)));
// 	queue<tuple<int, int, int>> q;
// 	for (int i = 0; i < h; i++)
// 	{
// 		for (int j = 0; j < n; j++)
// 		{
// 			for (int k = 0; k < m; k++)
// 			{
// 				cin >> tomato[i][j][k];
// 				if (tomato[i][j][k] == 1)
// 					q.emplace(i, j, k);
// 				else if (tomato[i][j][k] == 0)
// 					visited[i][j][k] = -1;
// 			}
// 		}
// 	}
// 	
// 	while (!q.empty())
// 	{
// 		auto cur = q.front(); q.pop();
// 		int cx = get<0>(cur);
// 		int cy = get<1>(cur);
// 		int cz = get<2>(cur);
// 
// 		for (int i = 0; i < 6; i++)
// 		{
// 			int nx = cx + dx[i];
// 			int ny = cy + dy[i];
// 			int nz = cz + dz[i];
// 
// 			if (nx < 0 || nx >= h || ny < 0 || ny >= n || nz < 0 || nz >= m) continue;
// 			if (tomato[nx][ny][nz] != 0) continue;	// 없어도 되는데 의미를 명확하게 하기 위해 놔둠
// 			if (visited[nx][ny][nz] != -1) continue;
// 
// 			q.emplace(nx, ny, nz);
// 			visited[nx][ny][nz] = visited[cx][cy][cz] + 1;
// 		}
// 	}
// 
// 	int mx = -1;
// 	for (int i = 0; i < h; i++)
// 	{
// 		for (int j = 0; j < n; j++)
// 		{
// 			for (int k = 0; k < m; k++)
// 			{
// 				if (visited[i][j][k] == -1)
// 				{
// 					cout << -1 << '\n';
// 					return 0;
// 				}
// 				
// 				mx = max(mx, visited[i][j][k]);
// 			}
// 		}
// 	}
// 
// 	cout << mx << '\n';
// }