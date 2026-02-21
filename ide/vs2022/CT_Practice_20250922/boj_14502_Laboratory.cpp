/*
BOJ 14502 — 연구소 (Laboratory)
Topic: Brute Force / BFS
Folder: graph/bfs

⏱ 시간복잡도: O(C(E,3) * N*M)   (E=빈 칸 수, N,M ≤ 8)
💾 공간복잡도: O(N*M)

📌 핵심 아이디어
- 빈 칸(0) 중 3개를 골라 벽(1)을 세우는 모든 경우(조합)를 탐색한다.
- 각 경우마다 바이러스(2)를 BFS로 확산시켜 감염되는 빈 칸 수를 세고,
  안전 영역 = (빈 칸 수 - 3) - (감염된 빈 칸 수) 의 최댓값을 갱신한다.
- visited는 스탬프(stamp) 방식으로 재사용해 매 케이스마다 재할당 비용을 줄인다.
  (visited[x][y] == stamp 이면 현재 케이스에서 방문한 칸)

⚠️ 주의할 점
- 입력 루프에서 열은 반드시 j < m (실수하면 out of bounds=배열 범위 밖 접근 위험).
- 벽을 세운 칸은 다음 케이스를 위해 반드시 원복해야 한다.
- 스탬프 방식에서 visited에 true(1) 같은 값을 넣으면 다음 stamp에서 방문 체크가 깨질 수 있으니
  반드시 visited[x][y] = stamp 로 기록한다.
- 가지치기: BFS 중 safe_zone이 이미 mx 이하로 내려가면 더 진행해도 이길 수 없으므로 중단 가능.

✔️ 지문 힌트
- N, M이 최대 8이라 완전탐색(벽 3개) + BFS 확산이 정석.
*/

// 2026-02-21 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, blank_cnt = 0, mx = 0;
	cin >> n >> m;

	vector<vector<int>> lab(n, vector<int>(m));
	vector<pair<int, int>> virus;
	vector<pair<int, int>> blank;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> lab[i][j];
			if (lab[i][j] == 2)
				virus.emplace_back(i, j);
			else if (lab[i][j] == 0)
				blank.emplace_back(i, j);
		}
	}

	blank_cnt = (int)blank.size();
	vector<vector<int>> visited(n, vector<int>(m, 0));
	int stamp = 0;

	for (int i = 0; i < blank_cnt; i++)
	{
		int wall1_x = blank[i].first;
		int wall1_y = blank[i].second;
		lab[wall1_x][wall1_y] = 1;

		for (int j = i + 1; j < blank_cnt; j++)
		{
			int wall2_x = blank[j].first;
			int wall2_y = blank[j].second;
			lab[wall2_x][wall2_y] = 1;

			for (int k = j + 1; k < blank_cnt; k++)
			{
				int wall3_x = blank[k].first;
				int wall3_y = blank[k].second;
				lab[wall3_x][wall3_y] = 1;

				int safe_zone = blank_cnt - 3;
				queue<pair<int, int>> q;
				stamp++;

				for (auto origin : virus)
				{
					int ox = origin.first;
					int oy = origin.second;
					q.emplace(ox, oy);
					visited[ox][oy] = stamp;
				}

				bool stop = false;
				while (!q.empty() && !stop)
				{
					auto cur = q.front(); q.pop();
					int cx = cur.first;
					int cy = cur.second;

					for (int d = 0; d < 4; d++)
					{
						int nx = cx + dx[d];
						int ny = cy + dy[d];

						if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
						if (visited[nx][ny] == stamp) continue;
						if (lab[nx][ny] != 0) continue;

						q.emplace(nx, ny);
						visited[nx][ny] = stamp;
						safe_zone--;
						if (safe_zone <= mx)
						{
							stop = true;
							break;
						}
					}
				}

				mx = max(mx, safe_zone);

				lab[wall3_x][wall3_y] = 0;
			}
			lab[wall2_x][wall2_y] = 0;
		}
		lab[wall1_x][wall1_y] = 0;
	}

	cout << mx << '\n';
}