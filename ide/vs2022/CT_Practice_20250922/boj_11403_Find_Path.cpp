/*
BOJ 11403 — 경로 찾기 (Find Path)
주제: Graph | Transitive Closure | Floyd–Warshall
폴더: graph/floyd

⏱ 시간복잡도: O(N^3)   (N ≤ 100이므로 충분)
💾 공간복잡도: O(N^2)

📌 핵심 아이디어
- 간선 인접행렬 A에서, 어떤 정점 k를 중간에 거치면 i->j 경로가 성립: A[i][j] |= (A[i][k] & A[k][j]).
- k를 바깥 루프로 두는 Warshall 순서(k, i, j)로 모든 경유 정점을 차례로 반영하면 전이 폐쇄가 완성됨.

⚠️ 주의할 점
- 대각 원소(i==j)는 자기 자신으로 가는 경로가 **사이클이 존재할 때만** 1이 된다(문제 정의상 OK).
- 출력 포맷: 각 행마다 공백으로 구분, 줄 끝 개행 필요(지금 구현대로면 정답).

🔧 개선 사항 (Improvement)
- (현재 코드에 존재) `k->i->j` 순서의 Warshall 전개.
- (현재 코드에 존재) 이미 1인 경우 `continue`로 가지치기.
- (현재 코드에 없음) 분기 제거 버전: `con_arr[i][j] |= (con_arr[i][k] & con_arr[k][j]);` 로 쓰면 분기 예측 부담↓, 구현 간결.
- (현재 코드에 없음) `bitset<100>`로 각 행을 비트셋으로 두고 `if (A[i][k]) row[i] |= row[k];`를 쓰면 상수배 속도 향상.
- (현재 코드에 없음) 간선이 희소하면 정점마다 **BFS/DFS N번**으로도 풀이 가능(O(N·(N+M))), 다만 N=100에선 O(N^3)와 큰 차이 없음.

✔️ 문제 힌트 (Problem Hint)
- “경로가 존재하는가?” = “중간 정점을 하나씩 허용했을 때 도달 가능한가?” -> **Floyd–Warshall의 전이 폐쇄**.
- 행렬 기반이면 **k를 경유점으로 두고** A[i][j] 갱신을 반복하면 된다.
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

	vector<vector<int>> con_arr(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> con_arr[i][j];
	}

	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (con_arr[i][j]) continue;
				if (con_arr[i][k] == 1 && con_arr[k][j] == 1)
					con_arr[i][j] = 1;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << con_arr[i][j] << " ";
		cout << '\n';
	}
}