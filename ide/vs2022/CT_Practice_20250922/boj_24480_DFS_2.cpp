/*
BOJ 24480 — 알고리즘 수업: 깊이 우선 탐색 2 (DFS 2)
주제: DFS | Graph | Traversal
폴더: graph/dfs/

⏱ 시간복잡도: O(N + M) + 정렬 O(∑deg(v) log deg(v))
💾 공간복잡도: O(N + M)

📌 핵심 아이디어
- 인접 리스트를 내림차순으로 정렬한 뒤, DFS에서 "들어가는 순간" 방문 순서를 기록.
- 방문 못한 정점은 기본값 0으로 남아 출력 형식과 일치.

⚠️ 주의할 점
- 최악의 체인 그래프에서 재귀 깊이 초과 가능(환경마다 다름).
- ans는 1-based 정점을 0-based 인덱스에 기록하므로 `ans[node - 1]` 사용(이미 적용).

🔧 개선 사항 (Improvement)
- 내림차순 정렬로 24480 요구 만족.
- 재귀 대신 **반복 DFS(명시적 스택)**로 바꾸면 스택 오버플로 위험 제거.
- `con_list[i].shrink_to_fit()` 같은 미세 최적화는 선택 사항.
- 입력 큰 케이스 대비 가능하면 `cin.tie(nullptr);` 유지 + `cout` 버퍼링 최소화

✔️ 문제 힌트 (Problem Hint)
- "내림차순으로 방문" -> **인접 리스트를 내림차순 정렬** 후 DFS.
- "방문 순서 출력" -> **DFS 진입 시 카운터 증가** 방식이 가장 간단/안전.

*/

// 2025-11-05 ORIGINAL

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void DFS(int node);

vector<vector<int>> con_list;
vector<bool> visited;
vector<int> ans;
int cnt;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, r;
	cin >> n >> m >> r;

	con_list = vector<vector<int>>(n + 1);
	visited = vector<bool>(n + 1, false);
	ans = vector<int>(n, 0);

	for (int i = 0; i < m; i++)
	{
		int dep, arr;
		cin >> dep >> arr;

		con_list[dep].push_back(arr);
		con_list[arr].push_back(dep);
	}

	for (int i = 1; i <= n; i++)
		sort(con_list[i].begin(), con_list[i].end(), greater<int>());

	cnt = 1;
	DFS(r);

	for (int x : ans)
		cout << x << '\n';
}

void DFS(int node)
{
	visited[node] = true;
	ans[node - 1] = cnt++;

	for (int x : con_list[node])
	{
		if (visited[x]) continue;
		DFS(x);
	}
}