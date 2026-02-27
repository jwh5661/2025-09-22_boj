/*
BOJ 13549 — 숨바꼭질 3 (Hide and Seek 3)
Topic: Shortest Path / 0-1 BFS (or Dijkstra)
Folder: shortest_path/01bfs

⏱ 시간복잡도: O(V log V)  (현재 코드: 다익스트라, V≈100001)
💾 공간복잡도: O(V)

📌 핵심 아이디어
- 위치 x를 정점으로 보고, 이동은 3가지:
  1) x -> 2x (비용 0)
  2) x -> x-1 (비용 1)
  3) x -> x+1 (비용 1)
- 비용이 0/1뿐이라 최단거리 문제이며, 다익스트라로 해결 가능.

⚠️ 주의할 점
- 범위: 0 ~ 100000을 벗어나면 안 됨 (배열 범위 밖 접근(out of bounds, 배열 범위 밖 접근) 방지).
- 우선순위 큐에는 같은 정점이 여러 번 들어갈 수 있으니,
  pop한 거리 d가 dist[x]와 다르면 건너뛰는 체크를 넣으면 더 빠르고 안전함.

✔️ 지문 힌트
- 순간이동은 시간이 0 → 일반 BFS가 아니라 0-1 BFS/다익스트라.
*/

// 2026-02-27 D+3 REIVEW

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	const int mx_loc = 100000;
	vector<int> dist(mx_loc + 1, 1e9);
	deque<int> dq;

	dist[n] = 0;
	dq.emplace_front(n);

	while (!dq.empty())
	{
		auto cur = dq.front(); dq.pop_front();
		int d = dist[cur];

		if (cur == k) break;

		int nx = 2 * cur;
		if (nx <= mx_loc && dist[nx] > d)
		{
			dq.push_front(nx);
			dist[nx] = d;
		}

		nx = cur - 1;
		if (nx >= 0 && dist[nx] > d + 1)
		{
			dq.push_back(nx);
			dist[nx] = d + 1;
		}

		nx = cur + 1;
		if (nx <= mx_loc && dist[nx] > d + 1)
		{
			dq.push_back(nx);
			dist[nx] = d + 1;
		}
	}

	cout << dist[k] << '\n';
}

// 2026-02-23 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <queue>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, k;
// 	cin >> n >> k;
// 
// 	const int mx_dist = 100000;
// 	vector<int> visited(mx_dist + 1, 1e9);
// 
// 	priority_queue
// 		<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;
// 
// 	pq.emplace(0, n);
// 	visited[n] = 0;
// 
// 	while (!pq.empty())
// 	{
// 		auto cur = pq.top(); pq.pop();
// 		int d = cur.first;
// 		int x = cur.second;
// 
// 		if (d != visited[x]) continue;	// 오래된 데이터 제거
// 		if (x == k) break;
// 
// 		for (int next : {x - 1, x + 1, 2 * x})
// 		{
// 			if (next < 0 || next > mx_dist) continue;
// 			int nd = d;
// 			if (next != 2 * x)
// 				nd++;
// 			if (visited[next] <= nd) continue;
// 			pq.emplace(nd, next);
// 			visited[next] = nd;
// 		}
// 	}
// 
// 	cout << visited[k] << '\n';
// }