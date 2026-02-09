/*
BOJ 16234 — 인구 이동 (Population Movement)
Topic: graph | bfs | simulation
Folder: graph/bfs

⏱ 시간복잡도: O(D * N^2)   // D: 진행 일수(반복 횟수)
💾 공간복잡도: O(N^2)

📌 핵심 아이디어
- 하루마다 방문배열 초기화 후, 모든 칸에서 BFS로 연합을 구성(L ≤ |diff| ≤ R).
- 연합의 칸 목록과 합계를 모아 평균(내림)을 구하고, 하루가 끝나면 연합별로 동시에 갱신.
- 연합이 모두 크기 1(=국경 개방 없음)이라면 종료. (unite_count == n*n)

⚠️ 주의할 점
- BFS 시작 시 **시작 칸을 반드시 연합 벡터에 포함**해야 평균 적용 누락이 없음. (지금 코드 OK)
- 하루가 끝난 뒤 `unite`를 재생성할 때 **`clear()`를 추가로 호출하지 말 것**(크기가 0으로 줄어 UB 위험).
  지금은 `unite = vector<vector<pair<int,int>>>(n * n);`까지만 하므로 OK.
- 차이 조건은 **L ≤ |pop[a]-pop[b]| ≤ R**이어야 함. (지금 코드: `if (diff < l || diff > r) continue;`로 정확)

✔️ 지문 힌트
- “연합 만들기 → 평균 일괄 적용”을 하루에 한 번만 수행하고, 다음 날을 새로 시작.
- 종료 조건은 “**그날** 연합 수가 n*n (모두 크기 1)”이면 중지.
*/

// 2026-02-06 ORIGINAL

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int BFS(int x, int y);

vector<vector<int>> population;
vector<vector<bool>> visited;
vector<vector<pair<int, int>>> unite;
vector<int> unite_population;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
int n, l, r, unite_count;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int result = 0;
	cin >> n >> l >> r;
	unite_count = 0;
	population = vector<vector<int>>(n, vector<int>(n, 0));
	visited = vector<vector<bool>>(n, vector<bool>(n, false));
	unite = vector<vector<pair<int, int>>>(n * n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> population[i][j];
	}
	
	while (true)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (visited[i][j]) continue;
				unite_population.push_back(BFS(i, j));
				unite_count++;
				//cout << 1;
			}
		}

		if (unite_count == n*n) break;

		for (int i = 0; i < unite_count; i++)
		{
			for (int j = 0; j < unite[i].size(); j++)
				population[unite[i][j].first][unite[i][j].second] = unite_population[i];
		}

		visited = vector<vector<bool>>(n, vector<bool>(n, false));
		unite = vector<vector<pair<int, int>>>(n * n);
		unite_count = 0;
		unite_population.clear();
		result++;
	}

	cout << result << '\n';
}

int BFS(int x, int y)
{
	queue<pair<int, int>> q;
	q.emplace(x, y);
	unite[unite_count].emplace_back(x, y);
	visited[x][y] = true;
	int result = population[x][y], count = 1;
	
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
			if (visited[nx][ny]) continue;
			int abs_value = abs(population[nx][ny] - population[cx][cy]);
			if (abs_value < l || abs_value > r) continue;

			q.emplace(nx, ny);
			visited[nx][ny] = true;
			unite[unite_count].emplace_back(nx, ny);
			result += population[nx][ny];
			count++;
		}
	}

	return result / count;
}