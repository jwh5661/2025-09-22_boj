/*
BOJ 4991 — 로봇 청소기 (Robot Cleaner)
주제: BFS | 비트마스크 DP | 최단경로 전처리
폴더: dp/bitmask

⏱ 시간복잡도: O((W*H)*K + K^2 * 2^K)
💾 공간복잡도: O(W*H + K^2 + K*2^K)

📌 핵심 아이디어
- 시작점(o)과 먼지(*)들을 모아 크기 K+1의 리스트(special) 구성.
- 각 special에서 BFS → 모든 special까지의 최단거리 dist[i][j] 계산.
- dist에서 -1이 하나라도 있으면 불가능 → -1 출력.
- 가능한 경우, 상태(mask)와 현재 위치(u)로 정의된 DP:
  - dp[mask][u] = mask 상태(방문한 먼지 집합)로 u에 있을 때의 최소 이동.
  - 초기: dp[1<<(v-1)][v] = dist[0][v] (시작점 0에서 v로).
  - 전이: dp[nmask][v] = min(dp[nmask][v], dp[mask][u] + dist[u][v])

⚠️ 주의할 점
- BFS 방문배열은 매 출발점마다 새로 만들기.
- 입력이 (w,h) 순서이니 2차원 인덱싱(h행, w열) 주의.
- dist를 전부 채운 뒤 `can_reach`가 false면 DP 진행 없이 곧바로 -1 출력.

🔧 개선 사항 (Improvement)
- 루프 중단: dist[i][j] == -1을 발견하면 바로 바깥 i 루프까지 탈출하여 불필요한 BFS/DP를 건너뛰기.
- 인덱스/자료형 일관화: 비트마스크는 `int`(K≤10이면 안전)로 통일하면 불필요한 경고 감소.
- 입출력 최적화: 정답만 출력하고 불필요한 공백/개행 관리로 I/O 줄이기.

✔️ 문제 힌트 (Problem Hint)
- “장애물 있는 격자 최단 경로” → **각 특수 지점 쌍 최단거리**는 **BFS**로.
- “모든 먼지를 한 번씩” → **순회 경로 최소화** = **비트마스크 TSP DP**.
- “불가능한 경우 -1” → dist에 **-1 존재 여부**로 일찍 판정.
*/

// 2025-11-06 D+3 REVIEW

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int w, h;
	
	while (cin >> w >> h && (w != 0 || h != 0))
	{
		vector<vector<char>> room(h, vector<char>(w));
		vector<pair<int, int>> special(1);

		for (int i = 0; i < h; i++)
		{
			string str;
			cin >> str;

			for (int j = 0; j < w; j++)
			{
				room[i][j] = str[j];
				if (str[j] == 'o')
					special[0] = make_pair(i, j);
				else if (str[j] == '*')
					special.emplace_back(i, j);
			}
		}

		int special_size = (int)special.size();
		vector<vector<int>> dist(special_size, vector<int>(special_size, -1));
		bool can_reach = true;

		for (int i = 0; i < special_size; i++)
		{
			vector<vector<int>> visited(h, vector<int>(w, -1));
			queue<pair<int, int>> q;

			int special_x = special[i].first;
			int special_y = special[i].second;

			q.emplace(special_x, special_y);
			visited[special_x][special_y] = 0;
			dist[i][i] = 0;

			while (!q.empty())
			{
				auto cur = q.front(); q.pop();
				int cx = cur.first;
				int cy = cur.second;

				for (int i = 0; i < 4; i++)
				{
					int nx = cx + dx[i];
					int ny = cy + dy[i];

					if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
					if (room[nx][ny] == 'x') continue;
					if (visited[nx][ny] != -1) continue;

					q.emplace(nx, ny);
					visited[nx][ny] = visited[cx][cy] + 1;
				}
			}

			for (int j = 0; j < special_size; j++)
			{
				if (i == j) continue;
				int d = visited[special[j].first][special[j].second];
				if (d == -1)
				{
					can_reach = false;
					break;
				}
				dist[i][j] = d;
			}
		}

		if (!can_reach)
		{
			cout << -1 << '\n';
			continue;
		}
		else
		{
			int k = special_size - 1;
			int INF = 1000000000;
			size_t FULL = (size_t(1) << k) - 1;
			if (k == 0)
			{
				cout << 0 << '\n';
				continue;
			}

			vector<vector<int>> dp(size_t(1) << k, vector<int>(special_size, INF));

			for (int i = 1; i <= k; i++)
				dp[size_t(1) << (i - 1)][i] = dist[0][i];

			for (size_t mask = 0; mask <= FULL; mask++)
			{
				for (int i = 1; i <= k; i++)
				{
					if (dp[mask][i] == INF) continue;
					for (int j = 1; j <= k; j++)
					{
						size_t bit = size_t(1) << (j - 1);
						if (mask & bit) continue;
						size_t nmask = mask | bit;
						dp[nmask][j] = min(dp[nmask][j], dp[mask][i] + dist[i][j]);
					}
				}
			}

			int ans = INF;
			for (int i = 1; i <= k; i++)
				ans = min(ans, dp[FULL][i]);
			cout << (ans == INF ? -1 : ans) << '\n';
		}
	}
}

// 2025-10-30 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <string>
// #include <algorithm>
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
// 	int w, h;
// 	
// 	while (cin >> w >> h && (w != 0 && h != 0))
// 	{
// 		vector<vector<char>> room(h, vector<char>(w, 0));
// 		vector<pair<int, int>> special(1);
// 
// 		for (int i = 0; i < h; i++)
// 		{
// 			string str;
// 			cin >> str;
// 
// 			for (int j = 0; j < w; j++)
// 			{
// 				room[i][j] = str[j];
// 				if (str[j] == '*')
// 					special.push_back(make_pair(i, j));
// 				else if (str[j] == 'o')
// 					special[0] = make_pair(i, j);
// 			}
// 		}
// 
// 		int num = static_cast<int>(special.size());
// 		vector<vector<int>> dist(num, vector<int>(num, -1));
// 		bool can_reach = true;
// 		for (int i = 0; i < num; i++)
// 		{
// 			vector<vector<int>> time(h, vector<int>(w, -1));
// 			queue<pair<int, int>> q;
// 			q.emplace(special[i].first, special[i].second);
// 			time[special[i].first][special[i].second] = 0;
// 
// 			while (!q.empty())
// 			{
// 				auto cur = q.front(); q.pop();
// 				int cx = cur.first;
// 				int cy = cur.second;
// 
// 				for (int j = 0; j < 4; j++)
// 				{
// 					int nx = cx + dx[j];
// 					int ny = cy + dy[j];
// 
// 					if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
// 					if (room[nx][ny] == 'x') continue;
// 					if (time[nx][ny] != -1) continue;
// 					q.emplace(nx, ny);
// 					time[nx][ny] = time[cx][cy] + 1;
// 				}
// 			}
// 
// 			for (int j = 0; j < num; j++)
// 			{
// 				if (i == j)
// 				{
// 					dist[i][j] = 0;
// 					continue;
// 				}
// 				auto target = special[j];
// 				dist[i][j] = time[target.first][target.second];
// 				if (dist[i][j] == -1)
// 				{
// 					can_reach = false;
// 					break;
// 				}
// 			}
// 		}
// 
// 		if (!can_reach)
// 		{
// 			cout << -1 << '\n';
// 			continue;
// 		}
// 		else
// 		{
// 			const int k = num - 1;
// 			const int INF = 1000000000;
// 			if (k == 0)
// 			{
// 				cout << 0 << '\n';
// 				continue;
// 			}
// 
// 			const size_t FULL = (size_t(1) << k) - 1;
// 
// 			vector<vector<int>> dp((size_t(1) << k), vector<int>(num, INF));	// 산술 오버플로라고 나옴. 결과가 예상값이 아닐 수 있다고 함 왜?
// 			for (int v = 1; v <= k; v++)
// 				dp[size_t(1) << (v - 1)][v] = dist[0][v];	// 산술 오버플로라고 나옴. 결과가 예상값이 아닐 수 있다고 함 하위 식은 더 광범위한 형식에 할당되기 전에 오버플로 될 수 있다고 함 왜?
// 
// 			for (size_t mask = 0; mask <= FULL; mask++)
// 			{
// 				for (int u = 1; u <= k; u++)
// 				{
// 					if (dp[mask][u] == INF) continue;
// 					for (int v = 1; v <= k; v++)
// 					{
// 						size_t bit = size_t(1) << (v - 1);
// 						if (mask & bit) continue;
// 						if (dist[u][v] == -1) continue;	// 이건 어차피 위에서 검사하는 데 없어도 되는거 아닌가?
// 						size_t nmask = mask | bit;
// 						dp[nmask][v] = min(dp[nmask][v], dp[mask][u] + dist[u][v]);
// 					}
// 				}
// 			}
// 
// 			int ans = INF;
// 			for (int u = 1; u <= k; u++) ans = min(ans, dp[FULL][u]);
// 			cout << (ans == INF ? -1 : ans) << '\n';
// 		}
// 	}
// }