/*
BOJ 13913 — 숨바꼭질 4 (Hide and Seek 4)
Topic: BFS / Path Reconstruction
Folder: graph/bfs/

⏱ 시간복잡도: O(MAX) (MAX≈100001)
💾 공간복잡도: O(MAX)

📌 핵심 아이디어
- 위치(0~100000)를 정점으로 보고 (x-1, x+1, 2x) 이동을 간선으로 두는 무가중치 최단거리 문제.
- BFS로 최단거리(dist)와 이전 위치(parent)를 저장한다.
- 목적지 k에서 parent를 따라가며 경로를 역추적하고, 스택으로 뒤집어 출력한다.

⚠️ 주의할 점
- “최단 시간(이동 횟수)”도 반드시 출력해야 함.
- 범위 체크로 배열 범위 밖 접근(out of bounds, 배열 범위 밖 접근) 방지.
- 경로 복원 시 입력 변수(k)를 직접 변경하면 헷갈릴 수 있어 별도 변수 권장.

✔️ 지문 힌트
- 최단 거리 + 경로 출력 → BFS + parent 역추적.
*/

// 2026-02-28 D+3 REVIEW

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	const int mx_loc = 100000;
	vector<int> visited(mx_loc + 1, -1);
	vector<int> path(mx_loc + 1, -1);
	queue<int> q;

	int n, k;
	cin >> n >> k;

	q.push(n);
	visited[n] = 0;

	while (!q.empty())
	{
		int cur = q.front(); q.pop();
		if (cur == k) break;

		for (int next : {cur - 1, cur + 1, 2 * cur})
		{
			if (next < 0 || next > mx_loc) continue;
			if (visited[next] != -1) continue;

			q.push(next);
			visited[next] = visited[cur] + 1;
			path[next] = cur;
		}
	}

	cout << visited[k] << '\n';

	stack<int> stk;
	int i = k;
	while (i != -1)
	{
		stk.push(i);
		i = path[i];
	}

	while (!stk.empty())
	{
		cout << stk.top() << ' ';
		stk.pop();
	}
	cout << '\n';
}

// 2026-02-24 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <stack>
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
// 	const int mx_location = 100001;
// 	vector<pair<int, int>> location(mx_location);
// 	queue<int> q;
// 	for (int i = 0; i < mx_location; i++)
// 		location[i] = make_pair(-1, -1);
// 
// 	location[n].first = 0;
// 	q.push(n);
// 
// 	while (!q.empty())
// 	{
// 		int cur = q.front(); q.pop();
// 
// 		if (cur == k) break;
// 
// 		for (int next : {cur - 1, cur + 1, 2 * cur})
// 		{
// 			if (next < 0 || next >= mx_location) continue;
// 			if (location[next].first != -1) continue;
// 
// 			q.push(next);
// 			location[next].first = location[cur].first + 1;
// 			location[next].second = cur;
// 		}
// 	}
// 
// 	cout << location[k].first << '\n';
// 
// 	stack<int> ans;
// 	ans.push(k);
// 	while (location[k].second != -1)
// 	{
// 		ans.push(location[k].second);
// 		k = location[k].second;
// 	}
// 	
// 
// 	while (!ans.empty())
// 	{
// 		cout << ans.top() << ' ';
// 		ans.pop();
// 	}
// 		
// 	cout << '\n';
// }