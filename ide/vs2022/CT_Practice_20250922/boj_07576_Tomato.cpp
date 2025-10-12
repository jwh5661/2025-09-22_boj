/*
BOJ 7576 — 토마토 (Tomato)
Topic: BFS | Multi-Source | Grid
Folder: graph/bfs

⏱ 시간복잡도: O(N*M)
💾 공간복잡도: O(N*M)

📌 핵심 아이디어
- 값이 1인 칸들을 모두 시작점으로 하는 **멀티 소스 BFS**.
- 4방향으로 익음 전파: 인점 0을 `현재값 + 1`로 갱신하여 "며칠째"를 겨자에 직접 기록.
- BFS 종료 후 격제에 0이 남아있으면 -1, 아니면 최대값에서 1을 빼서 총 일수 출력.

⚠️ 주의할 점
- 입력 시 1을 발견하면 즉시 큐에 삽입(여러 시작점 동시 확산).
- 방문배열 없이 `tomato[nx][ny] != 0` 여부로 방문/상태를 판정.
- 전부 -1(빈 칸)만 있는 경우 대비: 최댓값 기준을 1로 두고 `mx - 1`을 출력하면 0이 된다.

✔️ 지문 힌트
- "하루에 한 칸/레벨씩 확산"은 BFS 레벨 순회로 자연스럽게 모델링된다.

*/

// 2025-10-12 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>

#define X first
#define Y second

using namespace std;

// 상하좌우
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int m, n;
	cin >> m >> n;

	vector<vector<int>> tomato(n, vector<int>(m, 0));
	queue<pair<int, int>> q;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> tomato[i][j];
			if (tomato[i][j] == 1)
				q.push(make_pair(i, j));
		}
	}

	while (!q.empty())
	{
		auto cur = q.front(); q.pop();
		int cur_x = cur.X;
		int cur_y = cur.Y;

		for (int i = 0; i < 4; i++)
		{
			int nxt_x = cur_x + dx[i];
			int nxt_y = cur_y + dy[i];

			if (nxt_x < 0 || nxt_x >= n || nxt_y < 0 || nxt_y >= m) continue;
			if (tomato[nxt_x][nxt_y] != 0) continue;
			tomato[nxt_x][nxt_y] = tomato[cur_x][cur_y] + 1;
			q.push(make_pair(nxt_x, nxt_y));
		}
	}

	int mx = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (tomato[i][j] == 0)
			{
				cout << -1 << '\n';
				return 0;
			}

			if (tomato[i][j] > mx) mx = tomato[i][j];
		}
	}

	cout << mx - 1 << '\n';
}