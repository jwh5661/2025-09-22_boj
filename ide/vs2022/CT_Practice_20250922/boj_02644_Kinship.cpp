/*
BOJ 2644 — 촌수계산 (Kinship)
Topic: graph | bfs
Folder: graph/bfs

⏱ 시간복잡도: O(N+M)
💾 공간복잡도: O(N+M)

📌 핵심 아이디어
- 무가중치 그래프에서 두 사람 사이 촌수 = 최단거리.
- dist(=visited)를 -1로 초기화하고 시작 정점 거리 0.
- BFS로 최초 방문 시 dist[next] = dist[cur] + 1.
- 목적지에 도달하면 조기 종료, dist[target2] 출력(미도달 시 -1).

⚠️ 주의할 점
- dist 배열 이름을 visited 대신 dist로 쓰면 의미가 명확.
- 입력이 1-indexed이므로 배열 크기를 n+1로 생성(이미 OK).
- 그래프가 비연결일 수 있으므로 -1 처리 필수.

✔️ 지문 힌트
- DFS도 가능하지만, 최단거리 보장은 BFS가 간단/명확.
*/

// 2026-01-30 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, target1, target2, m;
	cin >> n >> target1 >> target2 >> m;

	vector<vector<int>> family(n + 1);
	vector<int> visited(n + 1, -1);

	while (m--)
	{
		int dep, arr;
		cin >> dep >> arr;

		family[dep].push_back(arr);
		family[arr].push_back(dep);
	}

	queue<int> q;
	q.push(target1);
	visited[target1] = 0;

	while (!q.empty())
	{
		int cur = q.front(); q.pop();
		if (cur == target2) break;
		for (int next : family[cur])
		{
			if (visited[next] != -1) continue;
			q.push(next);
			visited[next] = visited[cur] + 1;
		}
	}

	cout << visited[target2] << '\n';
}