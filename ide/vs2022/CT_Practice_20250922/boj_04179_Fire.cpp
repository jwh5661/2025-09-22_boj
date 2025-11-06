/*
BOJ 4179 — 불! (Fire)
주제: BFS | Multi-source | Grid | Escape
폴더: graph/bfs/multisource

⏱ 시간복잡도: O(R*C)
💾 공간복잡도: O(R*C)

📌 핵심 아이디어
- 모든 불의 시작점을 멀티소스로 BFS 하여 fire[r][c]에 “불 도착 시간”을 채운다(도달 불가: -1).
- 지훈은 BFS로 이동하되, 다음 칸으로의 시간 nt가 불 도착 시간보다 엄격히 작아야(nt < fire[nx][ny]) 진입 가능.
- 격자 밖으로 나가는 순간이 탈출이므로, 경계 밖으로 나가면 즉시 답을 출력한다.

⚠️ 주의할 점
- 벽('#')은 불/지훈 모두 진입 금지.
- 불이 도달하지 않는 칸(fire == -1)은 지훈이 자유롭게 통과 가능.
- 방문 배열은 지훈용(visited)을 별도로 두어 재방문을 막고, 불과 혼동하지 않는다.

🔧 개선 사항 (Improvement)
- 메모리 최적화: 시간 범위가 작다면 fire/visited를 `short`로 낮출 수 있음.
- 시작이 가장자리인 경우: 현재 로직도 다음 스텝에 1로 처리되지만, 초기 상태에서 가장자리면 바로 1을 출력하는 조기 종료를 추가해도 됨.
- 코드 가독성: `pair<int,int>` 대신 좌표 구조체를 써 필드명을 명확히 하거나, 방향 배열을 한 배열로 묶어 반복 실수를 줄일 수 있음.

✔️ 문제 힌트 (Problem Hint)
- “불은 동시에 번진다” → 모든 불을 **멀티소스 BFS**로 한 번에 퍼뜨린다.
- “동시에 도착하면 불이 이긴다” → **지훈도착시간 < 불도착시간** 조건으로만 진입.
- “탈출”은 **격자 밖으로 한 칸 나간 순간**이다.
*/

// 2025-11-06 D+3 REVIEW

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int r, c;
	cin >> r >> c;

	vector<vector<char>> maze(r, vector<char>(c, '.'));
	vector<vector<int>> fire(r, vector<int>(c, -1));
	vector<vector<int>> person(r, vector<int>(c, -1));
	queue<pair<int, int>> fire_q;
	queue<pair<int, int>> person_q;

	for (int i = 0; i < r; i++)
	{
		string str;
		cin >> str;

		for (int j = 0; j < c; j++)
		{
			maze[i][j] = str[j];
			if (str[j] == 'J')
			{
				person_q.emplace(i, j);
				person[i][j] = 0;
			}
			else if (str[j] == 'F')
			{
				fire_q.emplace(i, j);
				fire[i][j] = 0;
			}
		}
	}

	while (!fire_q.empty())
	{
		auto cur = fire_q.front(); fire_q.pop();
		int cx = cur.first;
		int cy = cur.second;

		for (int i = 0; i < 4; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
			if (maze[nx][ny] == '#') continue;
			if (fire[nx][ny] != -1) continue;

			fire_q.emplace(nx, ny);
			fire[nx][ny] = fire[cx][cy] + 1;
		}
	}

	while (!person_q.empty())
	{
		auto cur = person_q.front(); person_q.pop();
		int cx = cur.first;
		int cy = cur.second;

		for (int i = 0; i < 4; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			int t = person[cx][cy] + 1;

			if (nx < 0 || nx >= r || ny < 0 || ny >= c)
			{
				cout << t << '\n';
				return 0;
			}
			if (maze[nx][ny] == '#') continue;
			if (person[nx][ny] != -1) continue;
			if (fire[nx][ny] != -1 && fire[nx][ny] <= t) continue;

			person_q.emplace(nx, ny);
			person[nx][ny] = person[cx][cy] + 1;
		}
	}

	cout << "IMPOSSIBLE\n";
}

// 2025-10-30 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <string>
// 
// using namespace std;
// 
// int dx[4] = { 0, 0, -1, 1 };
// int dy[4] = { -1, 1, 0, 0 };
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int r, c;
// 	cin >> r >> c;
// 
// 	vector<vector<char>> maze(r, vector<char>(c, 0));
// 	vector<vector<int>> fire(r, vector<int>(c, -1));
// 	vector<vector<int>> visited(r, vector<int>(c, -1));
// 
// 	queue<pair<int, int>> fire_q;
// 	queue<pair<int, int>> jihoon_q;
// 
// 	for (int i = 0; i < r; i++)
// 	{
// 		string str;
// 		cin >> str;
// 
// 		for (int j = 0; j < c; j++) 
// 		{
// 			maze[i][j] = str[j];
// 			if (str[j] == 'J')
// 			{
// 				jihoon_q.emplace(i, j);
// 				visited[i][j] = 0;
// 			}
// 			else if (str[j] == 'F')
// 			{
// 				fire_q.emplace(i, j);
// 				fire[i][j] = 0;
// 			}
// 		}
// 	}
// 
// 
// 	while (!fire_q.empty())
// 	{
// 		auto cur = fire_q.front(); fire_q.pop();
// 		int cx = cur.first;
// 		int cy = cur.second;
// 
// 		for (int i = 0; i < 4; i++)
// 		{
// 			int nx = cx + dx[i];
// 			int ny = cy + dy[i];
// 
// 			if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
// 			if (maze[nx][ny] == '#') continue;
// 			if (fire[nx][ny] != -1) continue;
// 			fire_q.emplace(nx, ny);
// 			fire[nx][ny] = fire[cx][cy] + 1;
// 		}
// 	}
// 
// 	while (!jihoon_q.empty())
// 	{
// 		auto cur = jihoon_q.front(); jihoon_q.pop();
// 		int cx = cur.first;
// 		int cy = cur.second;
// 
// 		for (int i = 0; i < 4; i++)
// 		{
// 			int nx = cx + dx[i];
// 			int ny = cy + dy[i];
// 
// 			if (nx < 0 || nx >= r || ny < 0 || ny >= c)
// 			{
// 				cout << visited[cx][cy] + 1 << '\n';
// 				return 0;
// 			}
// 			if (maze[nx][ny] == '#') continue;
// 			if (visited[nx][ny] != -1) continue;
// 			int nt = visited[cx][cy] + 1;
// 			if (fire[nx][ny] != -1 && fire[nx][ny] <= nt) continue;
// 			jihoon_q.emplace(nx, ny);
// 			visited[nx][ny] = nt;
// 		}
// 	}
// 
// 	cout << "IMPOSSIBLE\n";
// }