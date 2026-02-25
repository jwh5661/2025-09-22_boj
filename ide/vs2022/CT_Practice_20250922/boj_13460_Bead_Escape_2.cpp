/*
BOJ 13460 — 구슬 탈출 2 (Bead Escape 2)
Topic: BFS / Simulation / State Search
Folder: graph/bfs

⏱ 시간복잡도: O((N*M)^2 * 4 * max(N,M))  (상태 수 ≤ (N*M)^2, 한 번 기울일 때 굴리기 O(max))
💾 공간복잡도: O((N*M)^2)  (visited[rx][ry][bx][by] + 보드)

📌 핵심 아이디어
- 상태를 (빨강 위치 rx,ry / 파랑 위치 bx,by / 이동 횟수 cnt)로 잡고 BFS.
- 한 번 “기울이기”마다 두 구슬을 그 방향으로 벽(#) 또는 구멍(O) 전까지 굴린다.
- 파랑이 구멍에 빠지면 실패(버림), 빨강만 빠지면 성공.
- 둘이 같은 칸에 겹치면(충돌), 더 많이 이동한 구슬을 한 칸 뒤로 물려 겹침 해소.

⚠️ 주의할 점
- 굴릴 때 보드 밖으로 나가지 않게(배열 범위 밖 접근(out of bounds, 배열 범위 밖 접근) 방지) 보더가 #임을 전제로 함(지문 보장).
- 시작 상태도 visited 처리해야 중복 상태로 돌아오는 루프를 줄일 수 있음.
- 10회 초과는 실패(<=10만 허용).

✔️ 지문 힌트
- “최대 10번 기울이기” + “최소 횟수” → BFS가 정석.
*/

// 2026-02-25 D+3 REIVEW

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int Move(int& x, int& y, int dx, int dy);

vector<vector<char>> board;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };
int n, m;

struct State
{
	int rx, ry, bx, by, cnt;

	State(int nrx, int nry, int nbx, int nby, int ncnt)
		:rx(nrx), ry(nry), bx(nbx), by(nby), cnt(ncnt) {
	};
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int start_rx = 0, start_ry = 0, start_bx = 0, start_by = 0;
	cin >> n >> m;

	board = vector<vector<char>>(n, vector<char>(m));
	vector<bool> visited(n * m * n * m, false);
	queue<State> q;

	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < m; j++)
		{
			board[i][j] = str[j];

			if (board[i][j] == 'R')
			{
				start_rx = i; 
				start_ry = j;
				board[i][j] = '.';
			}
			else if (board[i][j] == 'B')
			{
				start_bx = i;
				start_by = j;
				board[i][j] = '.';
			}
		}
			
	}

	q.emplace(start_rx, start_ry, start_bx, start_by, 0);
	visited[start_rx * m * n * m + 
		start_ry * n * m + start_bx * m + start_by] = true;

	while (!q.empty())
	{
		State cur = q.front(); q.pop();

		if (cur.cnt >= 10) continue;

		for (int d = 0; d < 4; d++)
		{
			int nrx = cur.rx;
			int nry = cur.ry;
			int nbx = cur.bx;
			int nby = cur.by;
			int r_dist = 0, b_dist = 0;

			r_dist = Move(nrx, nry, dx[d], dy[d]);

			b_dist = Move(nbx, nby, dx[d], dy[d]);

			if (board[nbx + dx[d]][nby + dy[d]] == 'O') continue;

			if (board[nrx + dx[d]][nry + dy[d]] == 'O')
			{
				cout << cur.cnt + 1 << '\n';
				return 0;
			}

			if (nrx == nbx && nry == nby)
			{
				if (r_dist > b_dist)
				{
					nrx -= dx[d];
					nry -= dy[d];
				}
				else
				{
					nbx -= dx[d];
					nby -= dy[d];
				}
			}

			int idx = nrx * m * n * m + nry * n * m + nbx * m + nby;
			if (visited[idx]) continue;
			q.emplace(nrx, nry, nbx, nby, cur.cnt + 1);
			visited[idx] = true;
		}
	}

	cout << -1 << '\n';
}

int Move(int& x, int& y, int dx, int dy)
{
	int dist = 0;

	while (board[x + dx][y + dy] == '.')
	{
		x += dx;
		y += dy;
		dist++;
	}

	return dist;
}

// 2026-02-20 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <queue>
// 
// using namespace std;
// 
// struct State {
// 	int rx, ry, bx, by, cnt;
// 
// 	State(int nrx, int nry, int nbx, int nby, int ncnt)
// 		:rx(nrx), ry(nry), bx(nbx), by(nby), cnt(ncnt) {
// 	}
// };
// 
// bool visited[11][11][11][11];
// int dx[4] = { 0, 0, -1, 1 };
// int dy[4] = { -1, 1, 0, 0 };
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, m, start_rx = 0, start_ry = 0, start_bx = 0, start_by = 0;
// 	cin >> n >> m;
// 
// 	vector<vector<char>> board(n, vector<char>(m));
// 	queue<State> q;
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		string str;
// 		cin >> str;
// 		for (int j = 0; j < m; j++)
// 		{
// 			board[i][j] = str[j];
// 			if (board[i][j] == 'B')
// 			{
// 				start_bx = i;
// 				start_by = j;
// 			}
// 			else if (board[i][j] == 'R')
// 			{
// 				start_rx = i;
// 				start_ry = j;
// 			}
// 		}
// 	}
// 
// 	q.emplace(State(start_rx, start_ry, start_bx, start_by, 0));
// 	visited[start_rx][start_ry][start_bx][start_by] = true;
// 
// 	while (!q.empty())
// 	{
// 		State cur = q.front(); q.pop();
// 		int crx = cur.rx, cry = cur.ry, cbx = cur.bx, cby = cur.by, ccnt = cur.cnt;
// 
// 		if (ccnt >= 10) continue;
// 		for (int i = 0; i < 4; i++)
// 		{
// 			int nrx = crx + dx[i];
// 			int nry = cry + dy[i];
// 			int nbx = cbx + dx[i];
// 			int nby = cby + dy[i];
// 			int r_dist = 0, b_dist = 0;
// 			bool r_escape = false, b_escape = false;
// 
// 			while (board[nrx][nry] != '#' && board[nrx][nry] != 'O')
// 			{
// 				r_dist++;
// 				nrx += dx[i];
// 				nry += dy[i];
// 			}
// 
// 			while (board[nbx][nby] != '#' && board[nbx][nby] != 'O')
// 			{
// 				b_dist++;
// 				nbx += dx[i];
// 				nby += dy[i];
// 			}
// 
// 			if (board[nrx][nry] == 'O')
// 				r_escape = true;
// 
// 			if (board[nbx][nby] == 'O')
// 				b_escape = true;
// 
// 			if (b_escape) continue;
// 			if (r_escape)
// 			{
// 				cout << ccnt + 1 << '\n';
// 				return 0;
// 			}
// 			if (nrx == nbx && nry == nby)
// 			{
// 				if (r_dist < b_dist)
// 				{
// 					nbx -= dx[i];
// 					nby -= dy[i];
// 				}
// 				else
// 				{
// 					nrx -= dx[i];
// 					nry -= dy[i];
// 				}
// 			}
// 
// 			nrx -= dx[i];
// 			nry -= dy[i];
// 			nbx -= dx[i];
// 			nby -= dy[i];
// 
// 			if (visited[nrx][nry][nbx][nby]) continue;
// 			q.emplace(nrx, nry, nbx, nby, ccnt + 1);
// 			visited[nrx][nry][nbx][nby] = true;
// 		}
// 	}
// 
// 	cout << -1 << '\n';
// }