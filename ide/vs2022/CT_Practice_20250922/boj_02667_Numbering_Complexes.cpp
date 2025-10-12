/*
BOJ 2667 — 단지번호붙이기 (Numbering Complexes)
Topic: BFS | Grid | Connected-Components
Folder: graph/bfs

⏱ 시간복잡도: O(N^2)
💾 공간복잡도: O(N^2)

📌 핵심 아이디어
- NxN 격자에서 값 1의 연겨 요소를 4방향(BFS)으로 탐색하여 각 단지의 크기를 센다.
- 방문 배열로 재방문을 막고, 시작 지점 발견 시 단지 크기 1로 시작해 인접 1들을 큐로 확장하며 누적

⚠️ 주의할 점
- 매크로 `#define X first;`/`#define Y second;`의 세미콜론 제거(또는 매크로 없이 first/second 사용).
- 시작 셀은 BFS 호출 전에 방문 처리되어야 하며(지금처럼 main에서 처리하거나 BFS 입구에서 처리), 경계/값/방문 순서로 체크.

✔️ 지문 힌트
- 각 미방문 1에서 시작해 BFS/DFS로 연결된 1을 모두 방문 -> 단지 크기 기록.
- 모든 단지 크기를 오름차순 정렬해 계수와 함께 출력.

*/

// 2025-10-12 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

#define X first
#define Y second

using namespace std;

void BFS(int x, int y);

vector<vector<int>> map;
vector<vector<bool>> visited;
vector<int> complex_size;
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int n;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;

	map = vector<vector<int>>(n, vector<int>(n, 0));
	visited = vector<vector<bool>>(n, vector<bool>(n, false));

	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;

		for (int j = 0; j < n; j++)
			map[i][j] = str[j] - '0';
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (visited[i][j]) continue;
			visited[i][j] = true;
			if (map[i][j] == 0) continue;
			complex_size.push_back(1);
			BFS(i, j);
		}
	}

	sort(complex_size.begin(), complex_size.end());
	cout << complex_size.size() << '\n';
	for (int i : complex_size)
		cout << i << '\n';
}

void BFS(int x, int y)
{
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));

	while (!q.empty())
	{
		int cur_x = q.front().X;
		int cur_y = q.front().Y;
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int nxt_x = cur_x + dx[i];
			int nxt_y = cur_y + dy[i];
			if (nxt_x < 0 || nxt_x >= n || nxt_y < 0 || nxt_y >= n) continue;
			if (map[nxt_x][nxt_y] == 0) continue;
			if (visited[nxt_x][nxt_y]) continue;
			visited[nxt_x][nxt_y] = true;
			q.push(make_pair(nxt_x, nxt_y));
			*(complex_size.end() - 1) += 1;
		}
	}
}