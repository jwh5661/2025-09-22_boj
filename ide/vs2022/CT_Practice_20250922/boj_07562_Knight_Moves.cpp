/*
BOJ 7562 — 나이트의 이동 (Knight Moves)
Topic: BFS | Grid | Knight
Folder: graph/bfs

⏱ 시간복잡도: O(L^2)    // 보드 한 변 L, 각 칸 최대 8간선
💾 공간복잡도: O(L^2)

📌 핵심 아이디어
- 체스판의 각 칸을 정점으로 보고, 나이트의 8가지 점프를 간선으로 하여 BFS로 최단 이동 횟수를 구한다.
- 시작 칸 dist = 0을 큐에 넣고, 범위 내 & 미방문 칸만 dist = 부모 + 1로 갱신하면서 확장한다.
- 목표 칸을 꺼내는 순간의 dist가 곧 정답.

⚠️ 주의할 점
- 테스트 케이스마다 visited(dist)를 -1로 초기화.
- 범위 체크 -> 미방문 체크 -> dist 갱신 -> enqueue 순서 유지.
- 시작 == 목표일 때는 0이 정답(현재 로직도 자연스럽게 처리됨).
- (선택) 목표를 큐에서 꺼낸 순간 바로 출력하고 해당 테스트 루프를 종료하면 더 명확하다.

✔️ 지문 힌트
- 격자 최단 거리는 BFS가 정석. 나이트 이동 오프셋(+-1/+-2 조합)만 정확히 구현하면 된다.

*/

// 2025-10-08 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>

#define X first
#define Y second

using namespace std;

int dx[8] = {-2, -1, 1, 2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--)
	{
		int i, st_x, st_y, end_x, end_y;
		cin >> i >> st_x >> st_y >> end_x >> end_y;
		vector<vector<int>> visited = vector<vector<int>>(i, vector<int>(i, -1));

		queue<pair<int, int>> q;
		q.push(make_pair(st_x, st_y));
		visited[st_x][st_y] = 0;

		while (!q.empty())
		{
			auto cur = q.front();
			int cur_x = cur.X, cur_y = cur.Y;
			if (cur_x == end_x && cur_y == end_y) break;
			q.pop();

			for(int j = 0; j < 8; j++)
			{
				int new_x = cur_x + dx[j];
				int new_y = cur_y + dy[j];

				if (new_x < 0 || new_x >= i || new_y < 0 || new_y >= i) continue;
				if (visited[new_x][new_y] != -1) continue;
				visited[new_x][new_y] = visited[cur_x][cur_y] + 1;
				q.push(make_pair(new_x, new_y));
			}
		}

		if (!q.empty())
			cout << visited[end_x][end_y] << '\n';
		else
			cout << 0 << '\n';
	}
}