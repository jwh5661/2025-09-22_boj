/*
BOJ 1012 — 유기농 배추 (Organic Cabbage)
Topic: BFS | Grid | Connected-Components
Folder: graph/bfs

⏱ 시간복잡도: O(T * M * N)    // T: 테스트케이스, 격자 M×N 전수 + BFS
💾 공간복잡도: O(M * N)

📌 핵심 아이디어
- 격자에서 값 1(배추)의 연결 요소 개수를 세는 문제.
- 방문하지 않은 배추 칸을 만나면 BFS로 인접(상하좌우)한 배추를 모두 방문 처리하고 지렁이수 +1

⚠️ 주의할 점
- 입력이 (m, n, k) 순이고 좌표가 (x, y)로 들어오므로, 2차원 배열 인덱싱을 [x][y]로 맞춘 현재 코드처럼 **일관성**을 유지해야 함.
- 범위 체크 순서: 경계 -> 방문 여부 -> 배추 유무(0/1).
- 테스트케이스마다 `cabbage`와 `visited`를 **재할당**하여 초기화

✔️ 지문 힌트
- 연결 요소(connected components) 개수 = BFS/DFS를 시작한 횟수.

*/

// 2025-10-14 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>

#define X first
#define Y second

using namespace std;

void BFS(int x, int y);

vector<vector<int>> cabbage;
vector<vector<bool>> visited;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };
int n, m;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--)
	{
		int k, worm = 0;
		cin >> m >> n >> k;

		cabbage = vector<vector<int>>(m, vector<int>(n, 0));
		visited = vector<vector<bool>>(m, vector<bool>(n, false));

		for (int i = 0; i < k; i++)
		{
			int x, y;
			cin >> x >> y;
			cabbage[x][y] = 1;
		}

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (visited[i][j]) continue;
				if (cabbage[i][j] == 0) continue;
				worm++;
				BFS(i, j);
			}
		}

		cout << worm << '\n';
	}
}

void BFS(int x, int y)
{
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	visited[x][y] = true;

	while (!q.empty())
	{
		auto cur = q.front(); q.pop();
		
		for (int i = 0; i < 4; i++)
		{
			int nxt_x = cur.X + dx[i];
			int nxt_y = cur.Y + dy[i];

			if (nxt_x < 0 || nxt_x >= m || nxt_y < 0 || nxt_y >= n) continue;
			if (visited[nxt_x][nxt_y]) continue;
			if (cabbage[nxt_x][nxt_y] == 0) continue;
			q.push(make_pair(nxt_x, nxt_y));
			visited[nxt_x][nxt_y] = true;
		}
	}
}