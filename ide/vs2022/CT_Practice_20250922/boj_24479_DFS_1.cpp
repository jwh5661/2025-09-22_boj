/*
BOJ 24479 — 알고리즘 수업: 깊이 우선 탐색 1 (DFS 1)
주제: DFS | Graph | Traversal
폴더: graph/dfs/basic

⏱ 시간복잡도: O(N + M) + 정렬 O(∑ deg(v) log deg(v)) ≈ O(N + M log M)
💾 공간복잡도: O(N + M)

📌 핵심 아이디어
- 인접 리스트를 정점별 오름차순으로 정렬하여 DFS 방문 순서를 결정.
- 방문 배열로 재방문을 차단하고, 방문 순서를 out[node]에 1부터 증가하며 기록.
- 시작 정점 r에서 도달하지 못한 정점은 out[i]가 0으로 남아 문제 요구와 일치.

⚠️ 주의할 점
- 입력이 많아 I/O 최적화 필수(이미 적용).
- 그래프가 긴 체인 형태일 때 재귀 깊이(Stack) 초과 위험(C++ 환경마다 다름).

🔧 개선 사항 (Improvement)
- (🟥 현재 코드에 없음) **반복 DFS(명시적 스택)**로 바꾸면 재귀 스택 오버플로를 방지할 수 있음.
- (🟩 현재 코드에 존재) **인접 리스트 정렬**로 방문 순서 보장.
- (🟩 현재 코드에 존재) **도달 못한 정점 0 출력**: out의 기본값 0 유지로 충족.
- (🟩 현재 코드에 존재) **1-based 인덱스 관리**로 입력/출력 일치.
- (🟥 현재 코드에 없음) `con_list.reserve(n+1);` 같은 상위 벡터 사전 예약은 미미하지만 재할당을 약간 줄일 수 있음.

✔️ 문제 힌트 (Problem Hint)
- “오름차순으로 방문” → **인접 리스트 정렬 후 DFS**.
- “방문 순서 출력” → **들어가는 시점에 순서 번호 증가**.
- “미도달은 0” → **초기값 0 유지**.
*/

// 2025-10-31 ORIGINAL

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void DFS(int node);

vector<vector<int>> con_list;
vector<bool> visited;
vector<int> out;
int n, m, order;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int r;
	cin >> n >> m >> r;

	con_list = vector<vector<int>>(n + 1);
	visited = vector<bool>(n + 1, false);
	out = vector<int>(n + 1, 0);
	order = 1;

	for (int i = 1; i <= m; i++)
	{
		int dep, arr;
		cin >> dep >> arr;

		con_list[dep].push_back(arr);
		con_list[arr].push_back(dep);
	}

	for (int i = 1; i <= n; i++)
		sort(con_list[i].begin(), con_list[i].end());

	DFS(r);

	for (int i = 1; i <= n; i++)
		cout << out[i] << '\n';
}

void DFS(int node)
{
	visited[node] = true;
	out[node] = order++;
	for (int next : con_list[node])
	{
		if (visited[next]) continue;
		DFS(next);
	}
}