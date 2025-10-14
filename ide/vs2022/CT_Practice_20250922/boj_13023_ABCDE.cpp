/*
BOJ 13023 — ABCDE (ABCDE)
Topic: DFS | Backtracking | Graph
Folder: graph/dfs

⏱ 시간복잡도: O(V * (V + E))   // 각 정점을 시작으로 깊이 5까지 DFS
💾 공간복잡도: O(V + E)

📌 핵심 아이디어
- 무방향 그래프에서 임의 시작 정점부터 **단순 경로 길이 4(정점 5개)** 가 존재하는지 DFS로 탐색.
- 방문 체크로 사이클/재방문 방지, 재귀 복귀 시 **visited 복구 + depth 감소**로 백트래킹.
- `depth`를 **증가한 직후** `depth == 5`이면 `found = true`로 조기 종료.

⚠️ 주의할 점
- 성공 판정은 **depth++ 이후**에 수행(오프바이원 방지).
- 모든 재귀 프레임에서 `depth--`와 `visited[node]=false`를 **항상** 수행(복구 누락 금지).
- 시작 루프마다 `visited` 초기화.

✔️ 지문 힌트
- "ABCDE 친구 관계"는 **단순 경로 길이 4** 존재 여부와 동치 -> DFS 백트래킹이 정석.

*/

// 2025-10-14 ORIGINAL

#include <iostream>
#include <vector>

using namespace std;

void DFS(int node);

vector<vector<int>> con_list;
vector<bool> visited;
int depth;
bool found = false;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int v, e;
	cin >> v >> e;

	con_list.resize(v);
	visited = vector<bool>(v, false);

	for (int i = 0; i < e; i++)
	{
		int dep, arr;
		cin >> dep >> arr;
		con_list[dep].push_back(arr);
		con_list[arr].push_back(dep);
	}

	for (int i = 0; i < v; i++)
	{
		fill(visited.begin(), visited.end(), false);
		depth = 0;
		DFS(i);
		if (found)
		{
			cout << 1 << '\n';
			return 0;
		}
	}

	cout << 0 << '\n';
}

void DFS(int node)
{
	if (found) return;
	visited[node] = true;
	depth++;
	if (depth == 5)
	{
		found = true;
		depth--;
		visited[node] = false;
		return;
	}

	for (int i : con_list[node])
	{
		if (visited[i]) continue;
		DFS(i);
	}
	
	depth--;
	visited[node] = false;
}