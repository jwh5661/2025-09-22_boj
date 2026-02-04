/*
BOJ 3184 — 양 (Sheep)
Topic: graph | bfs | connected_component
Folder: graph/bfs

⏱ 시간복잡도: O(R*C)
💾 공간복잡도: O(R*C)

📌 핵심 아이디어
- 격자를 연결 요소 단위로 BFS.
- 각 영역에서 'o'(양)·'v'(늑대) 개수를 세고, 양 > 늑대면 양만 생존, 아니면 늑대만 생존.

⚠️ 주의할 점
- 시작 칸도 반드시 카운트.
- 방문 체크는 큐에 넣을 때 즉시(중복 방지).
- 벽('#')은 애초에 방문 불가 처리(visited=1 또는 바로 continue).

✔️ 지문 힌트
- 울타리로 둘러싸인 “같은 영역” 단위로만 비교한다.
- 영역마다 결과를 누적: 양이 많으면 늑대 0, 반대면 양 0.
*/

// 2026-02-04 D+3 REVIEW

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int BFS(int x, int y);

int r, c;
int dx[4] = { 0, 0, -1 ,1 };
int dy[4] = { 1, -1, 0, 0 };
vector<vector<char>> farm;
vector<vector<int>> visited;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int sheep_cnt = 0, wolf_cnt = 0;
	cin >> r >> c;

	farm = vector<vector<char>>(r, vector<char>(c));
	visited = vector<vector<int>>(r, vector<int>(c, -1));

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			cin >> farm[i][j];

			if (farm[i][j] == '#')
				visited[i][j] = 0;
		}
	}

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (visited[i][j] != -1) continue;
			int result = BFS(i, j);

			if (result > 0)
				sheep_cnt += result;
			else
				wolf_cnt -= result;
		}
	}

	cout << sheep_cnt << ' ' << wolf_cnt << '\n';
}

int BFS(int x, int y)
{
	queue<pair<int, int>> q;
	q.emplace(x, y);
	visited[x][y] = 0;
	int sheep = 0, wolf = 0;

	if (farm[x][y] == 'o') sheep++;
	else if (farm[x][y] == 'v') wolf++;

	while (!q.empty())
	{
		auto cur = q.front(); q.pop();
		int cx = cur.first;
		int cy = cur.second;

		for (int i = 0; i < 4; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
			if (visited[nx][ny] != -1) continue;

			q.emplace(nx, ny);
			visited[nx][ny] = 0;

			if (farm[nx][ny] == 'o') sheep++;
			else if (farm[nx][ny] == 'v') wolf++;
		}
	}

	return sheep > wolf ? sheep : -wolf;
}

// 2026-02-02 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <queue>
// 
// using namespace std;
// 
// int BFS(int x, int y);
// 
// int r, c;
// int dx[4] = { 0, 0, -1 ,1 };
// int dy[4] = { 1, -1, 0, 0 };
// vector<vector<char>> farm;
// vector<vector<int>> visited;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int sheep = 0, wolf = 0;
// 	cin >> r >> c;
// 
// 	farm = vector<vector<char>>(r, vector<char>(c, 0));
// 	visited = vector<vector<int>>(r, vector<int>(c, -1));
// 
// 	for (int i = 0; i < r; i++)
// 	{
// 		for (int j = 0; j < c; j++)
// 		{
// 			cin >> farm[i][j];
// 
// 			if (farm[i][j] == '#')
// 				visited[i][j] = 1;
// 				
// 		}
// 	}
// 
// 	for (int i = 0; i < r; i++)
// 	{
// 		for (int j = 0; j < c; j++)
// 		{
// 			if (visited[i][j] != -1) continue;
// 			int result = BFS(i, j);
// 
// 			if (result > 0)
// 				sheep += result;
// 			else
// 				wolf -= result;
// 		}
// 	}
// 
// 	cout << sheep << ' ' << wolf << '\n';
// }
// 
// int BFS(int x, int y)
// {
// 	queue<pair<int, int>> q;
// 	int temp_sheep = 0, temp_wolf = 0;
// 	q.emplace(x, y);
// 	visited[x][y] = 1;
// 
// 	if (farm[x][y] == 'o')
// 		temp_sheep++;
// 	else if (farm[x][y] == 'v')
// 		temp_wolf++;
// 
// 	while (!q.empty())
// 	{
// 		auto cur = q.front(); q.pop();
// 		int cx = cur.first;
// 		int cy = cur.second;
// 
// 		for (int i = 0; i < 4; i++)
// 		{
// 			int nx = cx + dx[i];
// 			int ny = cy + dy[i];
// 
// 			if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
// 			if (visited[nx][ny] != -1) continue;
// 
// 			q.emplace(nx, ny);
// 			visited[nx][ny] = 1;
// 
// 			if (farm[nx][ny] == 'o')
// 				temp_sheep++;
// 			else if (farm[nx][ny] == 'v')
// 				temp_wolf++;
// 		}
// 	}
// 
// 	if (temp_sheep > temp_wolf)
// 		return temp_sheep;
// 	else
// 		return -temp_wolf;
// }