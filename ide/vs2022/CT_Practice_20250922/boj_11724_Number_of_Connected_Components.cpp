// 2025-10-15 ORIGINAL
/*
BOJ 11724 — 연결 요소의 개수 (Number of Connected Components)
Topic: BFS | Graph | Connected-Components
Folder: graph/bfs

⏱ 시간복잡도: O(N + M)
💾 공간복잡도: O(N + M)

📌 핵심 아이디어
- 무방향 그래프에서 아직 방문하지 않은 정점 i마다 BFS를 1회 실행 -> 실행 횟수가 곧 연결 요소 개수.
- 큐에 넣을 때 즉시 visited=true로 표시하여 중복 삽입 방지.

⚠️ 주의할 점
- 정점 번호가 1..N이므로 배열 크기를 N+1로 생성
- 간선은 양방향으로 추가
- 입력 M=0(모두 고립) 같은 케이스도 `cnt++`로 올바르게 처리됨.

✔️ 개선 여지(선택)
- `q.emplace(node);` 등 emplace 계열로 미세 상수항 개선.
- 대량 입력에서 출력 하나뿐이라 I/O 최적화는 이미 충분.

*/

// 2025-10-27 D+3 REVIEW

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void BFS(int node);

vector<vector<int>> con_list;
vector<bool> visited;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, cnt = 0;
	cin >> n >> m;

	con_list = vector<vector<int>>(n + 1);
	visited = vector<bool>(n + 1, false);

	for (int i = 0; i < m; i++)
	{
		int dep, arr;
		cin >> dep >> arr;
		con_list[dep].push_back(arr);
		con_list[arr].push_back(dep);
	}

	for (int i = 1; i <= n; i++)
	{
		if (visited[i]) continue;
		cnt++;
		BFS(i);
	}

	cout << cnt << '\n';
}

void BFS(int node)
{
	queue<int> q;
	q.push(node);
	visited[node] = true;

	while (!q.empty())
	{
		int cur = q.front(); q.pop();

		for (int next : con_list[cur])
		{
			if (visited[next]) continue;
			q.push(next);
			visited[next] = true;
		}
	}
}

// 2025-10-15 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <queue>
// 
// using namespace std;
// 
// void BFS(int node);
// 
// vector<vector<int>> con_list;
// vector<bool> visited;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, m, cnt = 0;
// 	cin >> n >> m;
// 
// 	con_list = vector<vector<int>>(n + 1);
// 	visited = vector<bool>(n + 1, false);
// 
// 	for (int i = 0; i < m; i++)
// 	{
// 		int dep, arr;
// 		cin >> dep >> arr;
// 
// 		con_list[dep].push_back(arr);
// 		con_list[arr].push_back(dep);
// 	}
// 
// 	for (int i = 1; i <= n; i++)
// 	{
// 		if (visited[i]) continue;
// 		cnt++;
// 		BFS(i);
// 	}
// 
// 	cout << cnt << '\n';
// }
// 
// void BFS(int node)
// {
// 	queue<int> q;
// 	q.push(node);
// 	visited[node] = true;
// 
// 	while (!q.empty())
// 	{
// 		int cur = q.front(); q.pop();
// 
// 		for (int i : con_list[cur])
// 		{
// 			if (visited[i]) continue;
// 			q.push(i);
// 			visited[i] = true;
// 		}
// 	}
// }