/*
BOJ 14442 — 벽 부수고 이동하기 2 (Move and Break Walls 2)
Topic: BFS / Shortest Path (State BFS)
Folder: graph/bfs

⏱ 시간복잡도: O(N * M * K)
💾 공간복잡도: O(N * M * K)

📌 핵심 아이디어
- 상태를 (x, y, broken)으로 확장해서 BFS.
- 같은 칸이라도 부순 횟수(broken)가 다르면 이후 선택지가 달라서 별도 방문 처리 필요.

⚠️ 주의할 점
- visited 3번째 차원은 반드시 k+1 (0..k) 이어야 함. k=0도 고려.
- 목표 (n,m)에 최초 도달한 순간이 최단거리라 즉시 종료 가능.

✔️ 지문 힌트
- “최대 K개까지 벽을 부술 수 있다” → 부순 횟수가 상태(state).
*/

// 2026-02-10 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>

using namespace std;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, k;
	cin >> n >> m >> k;

	vector<vector<int>> map(n + 1, vector<int>(m + 1, 0));
	vector<vector<vector<bool>>> visited(n + 1, 
		vector<vector<bool>>(m + 1, 
			vector<bool>(k + 1, false)));
	queue<tuple<int, int, int>> q;

	for (int i = 1; i <= n; i++)
	{
		string str;
		cin >> str;
		for (int j = 1; j <= m; j++)
			map[i][j] = str[j - 1] - '0';
	}

	q.emplace(1, 1, 0);
	visited[1][1][0] = true;

	int steps = 1;
	while (!q.empty())
	{
		int step_size = (int)q.size();
		while (step_size--)
		{
			auto [cx, cy, broken] = q.front(); q.pop();

			if (cx == n && cy == m)
			{
				cout << steps << '\n';
				return 0;
			}

			for (int i = 0; i < 4; i++)
			{
				int nx = cx + dx[i];
				int ny = cy + dy[i];

				if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;

				int n_broken = broken;
				if (map[nx][ny] == 1)
				{
					if (broken == k) continue;
					n_broken++;
				}
				if (visited[nx][ny][n_broken]) continue;

				q.emplace(nx, ny, n_broken);
				visited[nx][ny][n_broken] = true;
			}
		}

		steps++;
	}

	cout << -1 << '\n';
}