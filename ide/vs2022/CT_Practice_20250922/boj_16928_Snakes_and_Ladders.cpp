/*
BOJ 16928 — 뱀과 사다리 게임 (Snakes and Ladders)
Topic: graph | bfs | shortest_path
Folder: graph/bfs

⏱ 시간복잡도: O(V + E)  // V=100, E<=600 → 상수 시간
💾 공간복잡도: O(V)     // 배열/큐 크기 ~ 101

📌 핵심 아이디어
- 칸(1..100)을 정점으로 보고, 각 칸에서 주사위 1..6으로 이동 가능한 간선을 만든다.
- 이동한 칸이 뱀/사다리 시작점이면 즉시 도착점으로 "워프".
- BFS로 최소 주사위 굴림 수(거리)를 구한다. 큐에 넣을 때 거리 = 이전 + 1.

⚠️ 주의할 점
- 🔁 **점프 적용 → 방문 판정 순서가 중요**
  올바른 순서:
  if (next > game_size) continue;
  if (jump[next] != -1) next = jump[next];          // ❶ 점프 먼저 적용
  if (count[next] != -1 && count[next] <= count[cur] + 1) continue; // ❷ 방문/거리 체크
반대로 ❷를 먼저 두면(점프 전에 count[next]를 검사) **실제 상태(점프 후 칸)**를 검사/마킹하지 못해
같은 목적지 칸이 여러 경로로 반복 삽입됩니다. 특히 뱀·사다리가 사이클을 만들면
큐에 동일 상태가 계속 쌓이며 무한에 가까운 반복(사실상 무한루프처럼 보임)을 유발합니다.

BFS 특성상 첫 방문이 최단거리이므로 간단히 if (count[next] != -1) continue;로도 충분합니다.

시작을 0에서 두고 1..6으로 진입해도 결과는 동일(현재 코드처럼 동작 OK).

✔️ 지문 힌트

“도착 즉시 재배치(워프)”로 구현하면 간선 전개가 단순해집니다.

BFS의 레벨이 곧 굴림 횟수이므로, 100에 처음 도달했을 때의 거리가 정답입니다.
*/

// 2026-02-05 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	const int game_size = 100;

	vector<int> jump(game_size + 1, -1);
	vector<int> count(game_size + 1, -1);
	queue<int> q;

	for (int i = 0; i < n; i++)
	{
		int dep, arr;
		cin >> dep >> arr;

		jump[dep] = arr;
	}

	for (int i = 0; i < m; i++)
	{
		int dep, arr;
		cin >> dep >> arr;

		jump[dep] = arr;
	}

	q.push(1);
	count[1] = 0;
	
	while (!q.empty())
	{
		auto cur = q.front(); q.pop();
		if (cur == game_size) break;

		for (int i = 1; i <= 6; i++)
		{
			int next = cur + i;

			if (next > game_size) continue;
			if (jump[next] != -1) next = jump[next];
			if (count[next] != -1 && count[next] <= count[cur] + 1) continue;

			q.push(next);
			count[next] = count[cur] + 1;
		}
	}

	cout << count[game_size] << '\n';
}