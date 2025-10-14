/*
BOJ 2606 — 바이러스 (Virus)
Topic: BFS | Graph | Adjacency List
Folder: graph/bfs

⏱ 시간복잡도: O(V + E)
💾 공간복잡도: O(V + E)

📌 핵심 아이디어
- 무방향 그래프에서 1번 정점부터 BFS로 방문을 확장.
- 새로 방문되는 정점마다 카운트를 +1 하여 "1 제외 감염 수"를 계산.

⚠️ 주의할 점
- 정점이 1부터 시작하므로 배열 크기는 v+1로 생성.
- 간선은 양방향으로 추가해야 함
- 큐에 넣을 때 바로 visited 표시해 중복 삽입 방지.

*/

// 2025-10-14 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int v, e;
	cin >> v >> e;

	vector<vector<int>> con_list(v + 1);
	vector<bool> visited(v + 1, false);
	queue<int> q;
	int cnt = 0;

	for (int i = 0; i < e; i++)
	{
		int dep, arr;
		cin >> dep >> arr;
		con_list[dep].push_back(arr);
		con_list[arr].push_back(dep);
	}

	q.push(1);
	visited[1] = true;

	while (!q.empty())
	{
		int cur = q.front(); q.pop();
		for (int i : con_list[cur])
		{
			if (visited[i]) continue;
			q.push(i);
			visited[i] = true;
			cnt++;
		}
	}

	cout << cnt << '\n';
}