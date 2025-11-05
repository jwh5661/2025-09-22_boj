/*
BOJ 2660 — 회장 뽑기 (Select the President)
주제: Graph | Floyd–Warshall | All-Pairs Shortest Path
폴더: graph/floyd

⏱ 시간복잡도: O(N^3) (N <= 50)
💾 공간복잡도: O(N^2)

📌 핵심 아이디어
- 모든 쌍 최단거리(Floyd–Warshall)로 각 정점 i의 excentricity = max_j dist[i][j] 계산.
- 가장 작은 excentricity 값을 회장 점수로, 해당 정점들을 후보로 출력.

⚠️ 주의할 점
- 도달 불가 상태는 반드시 INF로 두고, 시작 대각(dist[i][i])은 0으로 초기화.
- 인접행렬 기반이면 업데이트는 `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])` 형태로 분기 없이 처리.
- 출력 시 1..N 범위만 고려. 미사용 인덱스(0) 포함 금지.

🧩 문제 힌트 (Problem Hint)
- “가장 가까운 사람들과의 최대 거리” -> 정점의 **excentricity**.
- “회장 점수 = 최소 excentricity, 후보 = 그 값을 갖는 정점들”.

🔧 개선 사항 (Improvement)
- (현재 코드에 없음) 0/1을 “거리”처럼 쓰지 말고 **INF/0/1**로 명확히 표현.
- (현재 코드에 없음) `min` 갱신식으로 분기 제거해 간결/안전성 향상.
- (현재 코드에 존재) 입력은 무방향 그래프이므로 양방향 세팅 Ok.
*/

// 2025-11-05 ORIGINAL

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	const int mx_val = 1000000000;
	vector<vector<int>> con_arr(n + 1, vector<int>(n + 1, mx_val));

	int dep, arr;

	for (int i = 1; i <= n; i++)
		con_arr[i][i] = 0;

	while (cin >> dep >> arr && (dep != -1 || arr != -1))
	{
		con_arr[dep][arr] = 1;
		con_arr[arr][dep] = 1;
	}

	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (con_arr[i][k] < mx_val && con_arr[k][j] < mx_val)
					con_arr[i][j] = min(con_arr[i][j], con_arr[i][k] + con_arr[k][j]);
			}
		}
	}

	vector<int> score(n + 1);
	int min_val = mx_val;
	for (int i = 1; i <= n; i++)
	{
		score[i] = *max_element(con_arr[i].begin() + 1, con_arr[i].end());
		min_val = min(min_val, score[i]);
	}

	vector<int> ans;
	for (int i = 1; i <= n; i++)
	{
		if (score[i] == min_val)
			ans.push_back(i);
	}

	cout << min_val << " " << ans.size() << '\n';
	for (int x : ans)
		cout << x << " ";
	cout << '\n';
}