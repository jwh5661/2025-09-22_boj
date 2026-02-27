/*
BOJ 1525 — 퍼즐 (Puzzle)
Topic: BFS / State Space Search
Folder: bfs/graph/state/

⏱ 시간복잡도: O(9!)  (상태 ≤ 362880, 각 상태에서 최대 4개 전이)
💾 공간복잡도: O(9!)

📌 핵심 아이디어
- 3x3 퍼즐 상태를 길이 9 문자열로 표현한다(예: "123456780", 0은 빈칸).
- 빈칸(0)의 위치를 찾아 상/하/좌/우로 swap하여 다음 상태를 만든다.
- BFS로 목표 상태 "123456780"까지의 최단 이동 횟수를 구한다.
- 방문 여부와 거리는 unordered_map에 저장한다.

⚠️ 주의할 점
- 입력은 9개를 모두 읽어 문자열 길이가 9가 되어야 한다.
- 범위 체크로 배열 범위 밖 접근(out of bounds, 배열 범위 밖 접근) 방지.

✔️ 지문 힌트
- “최소 이동” → BFS
- 상태 수가 제한적(9!) → 해시로 방문 체크
*/

// 2026-02-27 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int dr[4] = { 0, 0, -1, 1 };
int dc[4] = { -1, 1, 0, 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	queue<string> q;
	unordered_map<string, int> m;
	m.reserve(400000);
	string start = "", end = "123456780";

	for (int i = 0; i < 9; i++)
	{
		int num;
		cin >> num;
		start += num + '0';
	}

	q.push(start);
	m[start] = 0;

	while (!q.empty())
	{
		string cur = q.front(); q.pop();
		int cnt = m[cur];
		if (cur == end)
		{
			cout << m[cur] << '\n';
			return 0;
		}

		int idx = cur.find('0');
		int r = idx / 3, c = idx % 3;

		for (int i = 0; i < 4; i++)
		{
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (nr < 0 || nr >= 3 || nc < 0 || nc >= 3) continue;

			swap(cur[idx], cur[nr * 3 + nc]);

			if (m.find(cur) == m.end())
			{
				q.push(cur);
				m[cur] = cnt + 1;
			}

			swap(cur[idx], cur[nr * 3 + nc]);
		}
	}

	cout << -1 << '\n';
}