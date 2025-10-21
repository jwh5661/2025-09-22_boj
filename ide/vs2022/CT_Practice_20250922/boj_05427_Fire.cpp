/*
BOJ 5427 — 불 (Fire) 방법 A (단일 큐: 불 먼저, 그다음 사람)
주제: BFS | Multi-source | Simulation
폴더: graph/bfs/combined

⏱ 시간복잡도: O(H*W)
💾 공간복잡도: O(H*W)

📌 핵심 아이디어
- 초기 큐에 모든 불(*)을 먼저 넣고, 이후 사람(@)을 넣어 **각 시각마다 불 확산->사람 이동** 순서가 유지되게 한다.
- 불이 확산될 때 즉시 격자에 '*'을 찍어 "동시 도착 시 불 우선" 규칙을 암묵적으로 반영한다.
- 사람이 가장자리를 벗어나는 순간 탈출, 그 시점까지의 이동 횟수가 정답.

⚠️ 주의할 점
- **순서 의존성**: 같은 시간대에서도 큐 순서에 따라 결과가 달라질 수 있어 로직이 민감함.
- **방문/중복 탐색**: 사람 이동에 방문 체크(거리 테이블)가 필요. 미흡하면 중복 enq 발생.
- **시작점 검증**: '@'가 없을 가능성 방어. 기본 좌표(0, 0)을 쓰지 않기.

🔧 개선 사항 (Improvement)
- 사람 이동용 `dist[h][w]`를 두어 재방문 방지 및 가독성 향상.
- 불/사람을 한 큐에 섞더라도, 레벨(큐 크기) 단위로 **불 레벨 전부 처리 -> 사람 레벨 전부 처리**를 명시적으로 구현하면 안정성 증가.
- 격자를 문자로 덮어쓰기보다, 별도의 상태/시간 배열을 병행해 디버깅 용이성 확보.

✔️ 문제 힌트 (Problem Hint)
- "동시에 번진다"= 멀티소스 출발. 불을 한꺼번에 큐에 넣어 퍼뜨리는 발상.
- "동시 도착 시 불 우선" 규칙을 구현해야 함(사람이 들어가려는 칸이 같은 시각에 불이면 불이 이김).
- 탈출 조건은 **격자 밖**으로 한 칸 나가는 순간.

*/

// 2025-10-21 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--)
	{
		int w, h, stx = -1, sty = -1;
		bool found = false;
		cin >> w >> h;

		vector<vector<char>> building(h, vector<char>(w));
		vector<vector<int>> time(h, vector<int>(w, -1));
		queue<tuple<char, int, int>> q;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				cin >> building[i][j];
				if (building[i][j] == '*')
					q.emplace(building[i][j], i, j);
				else if (building[i][j] == '@')
				{
					stx = i; sty = j;
				}
			}
		}

		if (stx == -1 || sty == -1)
		{
			cout << "IMPOSSIBLE\n";
			continue;
		}

		q.emplace(building[stx][sty], stx, sty);
		time[stx][sty] = 0;

		while (!found && !q.empty())
		{
			auto cur = q.front(); q.pop();
			int cx = get<1>(cur);
			int cy = get<2>(cur);

			for (int i = 0; i < 4; i++)
			{
				char c = get<0>(cur);
				int nx = cx + dx[i];
				int ny = cy + dy[i];

				if (c == '*')
				{
					if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
					if (building[nx][ny] == '#' || building[nx][ny] == '*') continue;
				}
				else if (c == '@')
				{
					if (nx < 0 || nx >= h || ny < 0 || ny >= w)
					{
						cout << time[cx][cy] + 1 << '\n';
						found = true;
						break;
					}
					if (building[nx][ny] == '#' || building[nx][ny] == '*') continue;
					if (time[nx][ny] != -1) continue;
					time[nx][ny] = time[cx][cy] + 1;
				}

				q.emplace(c, nx, ny);
				building[nx][ny] = c;
			}
		}

		if (!found)
			cout << "IMPOSSIBLE" << '\n';
	}
}