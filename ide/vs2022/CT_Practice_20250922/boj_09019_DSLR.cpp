/*
BOJ 9019 — DSLR (DSLR)
Topic: BFS / Shortest Path / Path Reconstruction
Folder: graph/bfs/

⏱ 시간복잡도: O(10000) (각 테스트 케이스마다 상태 최대 10000개)
💾 공간복잡도: O(10000)

📌 핵심 아이디어
- 0~9999를 정점으로 보고 DSLR 연산을 간선으로 두는 무가중치 최단거리 문제.
- BFS로 최단 경로를 찾고, visited에 (사용한 연산, 이전 숫자)를 저장해 경로를 역추적한다.

⚠️ 주의할 점
- S 연산: 0이면 9999, 그 외는 n-1 (1은 0이 되어야 함).
- 범위는 항상 0~9999 유지.
- 범위 체크/모듈 연산으로 배열 범위 밖 접근(out of bounds, 배열 범위 밖 접근) 방지.

✔️ 지문 힌트
- “최소 연산 횟수” → BFS
- “명령어 출력” → parent/operation 기록 후 역추적
*/

// 2026-02-25 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--)
	{
		int a, b;
		cin >> a >> b;

		vector<pair<char, int>> visited(10000, { '.', -1 });
		queue<int> q;
		q.emplace(a);
		visited[a] = { 'X', a };

		while (!q.empty())
		{
			int cur = q.front(); q.pop();
			//cout << cur << '\n';
			if (cur == b) break;

			for (int d = 0; d < 4; d++)
			{
				int next;
				switch (d)
				{
				case 0:
					next = (cur * 2) % 10000;
					break;
				case 1:
					if (cur == 0)
						next = 9999;
					else
						next = cur - 1;
					break;
				case 2:
					next = (cur % 1000) * 10 + (cur / 1000);
					break;
				case 3:
					next = (cur % 10) * 1000 + (cur / 10);
					break;
				}
				
				if (visited[next].second != -1) continue;

				switch (d)
				{
				case 0:
					visited[next].first = 'D';
					break;
				case 1:
					visited[next].first = 'S';
					break;
				case 2:
					visited[next].first = 'L';
					break;
				case 3:
					visited[next].first = 'R';
					break;
				}
				q.push(next);
				visited[next].second = cur;
			}
		}

		stack<char> stk;
		int i = b;
		while (i != a)
		{
			stk.push(visited[i].first);
			i = visited[i].second;
		}
		
		while (!stk.empty())
		{
			cout << stk.top();
			stk.pop();
		}
		cout << '\n';
	}
}