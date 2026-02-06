/*
BOJ 16236 — 아기 상어 (Baby Shark)
Topic: graph | bfs | simulation
Folder: graph/bfs

⏱ 시간복잡도: O(K * N^2)      // K=먹은 횟수(최대 N^2), 라운드당 BFS O(N^2)
💾 공간복잡도: O(N^2)

📌 핵심 아이디어
- 매 라운드 BFS로 현재 크기에서 이동 가능한 칸들 탐색.
- 먹을 수 있는 물고기(0 < size < shark_size) 중 **최단 거리**를 고르고, 동거리면 **행↑ → 열↑**로 선택.
- 선택된 물고기까지의 거리만큼 시간 누적 후, 위치 이동·먹은 수 증가·크기 갱신(먹은 수 == 크기일 때 +1).

⚠️ 주의할 점
- 시작 칸의 9는 **즉시 0으로 변경**(장애물 방지) — 코드에 반영됨.
- BFS에서 먹잇감 최초 거리 `dist`를 정한 뒤, `t[nx][ny] > dist`는 **확장 중단**(현재 코드: `if (dist != -1 && dist < t[nx][ny]) continue;`로 OK).
- 먹기/이동 조건 구분:
  - 이동: `fish[nx][ny] <= cur_size`
  - 먹기: `fish[nx][ny] != 0 && fish[nx][ny] < cur_size`
- 동거리 후보는 `vector<pair<int,int>>`로 모아 **정렬(행,열 오름차순)** 후 선택 — 정석.

✔️ 지문 힌트
- “가장 가까운 물고기”는 BFS로만 정확하게 판별 가능, 동거리 타이브레이크는 (행,열) 오름차순으로 처리.
- 더 이상 먹을 수 없으면 종료.

*/

// 2026-02-06 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, start_x = 0, start_y = 0, cur_size = 2, ate = 0, cur_time = 0;
	cin >> n;

	vector<vector<int>> fish(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> fish[i][j];

			if (fish[i][j] == 9)
			{
				start_x = i;
				start_y = j;
				fish[i][j] = 0;
			}
		}
	}

	while (true)
	{
		vector<vector<int>> t(n, vector<int>(n, -1));
		vector<pair<int, int>> tmp;
		queue<pair<int, int>> q;
		int dist = -1;

		q.emplace(start_x, start_y);
		t[start_x][start_y] = 0;

		while (!q.empty())
		{
			auto cur = q.front(); q.pop();
			int cx = cur.first;
			int cy = cur.second;
			
			for (int i = 0; i < 4; i++)
			{
				int nx = cx + dx[i];
				int ny = cy + dy[i];
				
				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (t[nx][ny] != -1) continue;
				if (fish[nx][ny] > cur_size) continue;

				t[nx][ny] = t[cx][cy] + 1;

				if (dist != -1 && dist < t[nx][ny]) continue;

				if (fish[nx][ny] != 0 && fish[nx][ny] < cur_size)
				{
					if (dist == -1) 
						dist = t[nx][ny];

					if (dist == t[nx][ny])
						tmp.emplace_back(nx, ny);
				}

				q.emplace(nx, ny);
			}
		}

		if (dist != -1)
		{
			sort(tmp.begin(), tmp.end());
			start_x = tmp[0].first;
			start_y = tmp[0].second;

			cur_time += t[start_x][start_y];
			ate++;
			fish[start_x][start_y] = 0;

			if (ate == cur_size)
			{
				cur_size++;
				ate = 0;
			}
		}
		else
			break;
	}

	cout << cur_time << '\n';
}