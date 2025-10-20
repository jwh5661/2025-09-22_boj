// 2025-10-20 ORIGINAL

/*
BOJ 1520 — 내리막 길
주제: DFS | DP(메모이제이션) | DAG
폴더: dp/graph

⏱ 시간복잡도: O(M * N)
💾 공간복잡도: O(M * N)

📌 핵심 아이디어
- 높이가 반드시 내려가므로 그래프는 사이클이 없는 DAG.
- DFS(x, y)가 (x, y)에서 도착지까지의 "경로 수"를 반환하도록 만들고, 한 번 계산한 값은 dp[x][y]에 저장해 재사용한다(메모이제이션).

⚠️ 주의할 점
- visited 사용 금지: 같은 칸을 다른 경로가 공유할 수 있으므로 막으면 오답 위험.
- 기저 조건: (m-1, n-1) 도착 시 1 반환, 진행 불가면 0 누적.
- 전이 조건은 엄격히 감소: map[nx][ny] < map[x][y] 인 칸으로만 이동.

🔧 개선 사항 (Improvement)
- 경로 수가 커질 수 있으니 dp 자료형을 long long으로 올리는 방안 고려.
- 방향 배열을 int d[4][2] = {{0,1},{0,-1},{-1,0},{1,0}}; 형태로 묶어 인덱스 실수 감소.
- 경계/전이 체크를 헬퍼 함수로 분리해 가독성 향상, 컴파일 최적화(-O2) 권장(-O2는 g++/clang++의 최적화 옵션).

✔️ 문제 힌트 (Problem Hint)
- "내리막만 이동" -> DAG에서의 경로 수 세기 문제.
- Top-Down Dp 패턴: dp[x][y] = Σdp[nx][ny] (단, h[nx][ny] < h[x][y]).
- 한 번 계산한 칸은 다시 풀지 않는다(메모이제이션으로 중복 제거).

*/

#include <iostream>
#include <vector>

using namespace std;

int DFS(int x, int y);

vector<vector<int>> travel_map;
vector<vector<int>> dp;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };
int m, n;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> m >> n;

	travel_map = vector<vector<int>>(m, vector<int>(n, 0));
	dp = vector<vector<int>>(m, vector<int>(n, -1));

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> travel_map[i][j];
	}

	cout << DFS(0, 0) << '\n';
}

int DFS(int x, int y)
{
	if (dp[x][y] != -1) return dp[x][y];

	if (x == m - 1 && y == n - 1)
	{
		return 1;
	}

	int sum = 0;
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
		if (travel_map[x][y] <= travel_map[nx][ny]) continue;

		sum += DFS(nx, ny);
	}

	return dp[x][y] = sum;
}