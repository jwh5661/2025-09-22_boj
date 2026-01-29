/*
BOJ 6118 — 숨바꼭질 (Hide and Seek)
Topic: graph | bfs
Folder: graph/bfs

⏱ 시간복잡도: O(N + M)
💾 공간복잡도: O(N + M)

📌 핵심 아이디어
- dist 배열 하나로 방문+최단거리 겸용(초기 -1). 시작점은 0.
- 무가중치 그래프이므로 BFS 최초 방문 거리가 최단거리.
- 탐색 후 dist를 스캔해 최대 거리(mx), 그 거리의 가장 작은 정점(idx), 개수(cnt) 산출.

⚠️ 주의할 점
- 비연결 그래프에서 미방문은 -1로 남지만, 최대 거리는 0 이상이므로 결과에 영향 없음.
- BFS 순서는 결과(idx) 결정에 영향 없음(우리가 dist를 스캔하며 ‘가장 작은 번호’를 선택).

✔️ 지문 힌트
- 추가 정렬 불필요. dist 한 번만 잘 채우면 됨.
*/

// 2026-01-29 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void BFS(int node);

vector<vector<int>> barn;
vector<int> visited;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	barn = vector<vector<int>>(n + 1);
	visited = vector<int>(n + 1, -1);

	while (m--)
	{
		int dep, arr;
		cin >> dep >> arr;

		barn[dep].push_back(arr);
		barn[arr].push_back(dep);
	}

	BFS(1);

	int mx = -1, idx = -1, cnt = 0;
	for (int i = 1; i <= n; i++) mx = max(mx, visited[i]);
	for (int i = 1; i <= n; i++)
	{
		if (visited[i] == mx)
		{
			if (idx == -1)
				idx = i;
			cnt++;
		}
	}

	cout << idx << ' ' << mx << ' ' << cnt << '\n';
}

void BFS(int node)
{
	queue<int> q;
	q.push(node);
	visited[node] = 0;

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (int next : barn[cur])
		{
			if (visited[next] != -1) continue;
			q.push(next);
			visited[next] = visited[cur] + 1;
		}
	}
}