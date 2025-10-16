/*
BOJ 1987 — 알파벳 (Alphabet)
Topic: DFS | Backtracking | Grid
Folder: graph/dfs

⏱ 시간복잡도: O(R*C*min(26, R*C))   // 분기 최대 4, 문자 26개가 상한
💾 공간복잡도: O(R*C + 26)

📌 핵심 아이디어
- 현재 칸 문자 사용 여부를 기록하며 4방향으로 DFS 백트래킹.
- 다음 칸 문자가 이미 사용된 알파벳이면 진행 중단.
- 재귀 복귀 시 사용 표시를 해제해 다른 경로 탐색 보장.
- 상한 가지치기: 최대 길이 26에 도달하면 더 탐색하지 않음.

⚠️ 주의할 점
- 이 문제는 "문자 중복 금지"만 요구하므로 `visited` 없이도 `is_used`만으로 충분.
- 인덱싱 1-based를 쓰고 있으니 경계식과 입력 파싱에서 일관성 유지.

✔️ 개선 여지
- 성능/간결성: `visited` 제거(문자 중복만 막으면 됨).
- 상한 가지치기: `if (mx == 26) return;`로 최적 상한 도달 시 조기 종료.
- 미세 가독성: 진입 직후 `mx = max(mx, depth);`로도 동일 동작(현재는 재귀 이후 갱신).

*/

// 2025-10-15 ORIGINAL

#include <iostream>
#include <vector>

using namespace std;

void Solve(int x, int y);

vector<vector<char>> board;
vector<bool> is_used;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };
int r, c, mx, depth;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> r >> c;
	mx = -1;
	depth = 0;

	board = vector<vector<char>>(r + 1, vector<char>(c + 1));
	is_used = vector<bool>(26, false);

	for (int i = 1; i <= r; i++)
	{
		string str;
		cin >> str;
		for (int j = 1; j <= c; j++)
			board[i][j] = str[j - 1];
	}

	Solve(1, 1);

	cout << mx << '\n';
}

void Solve(int x, int y)
{
	if (mx == 26) return;
	int idx = board[x][y] - 'A';
	is_used[idx] = true;
	depth++;
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx <= 0 || nx > r || ny <= 0 || ny > c) continue;
		int nidx = board[nx][ny] - 'A';
		if (is_used[nidx]) continue;
		Solve(nx, ny);
	}
	is_used[idx] = false;
	if (mx < depth) mx = depth;
	depth--;
}