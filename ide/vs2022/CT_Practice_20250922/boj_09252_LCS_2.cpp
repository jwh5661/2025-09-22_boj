/*
BOJ 9252 — LCS 2
Topic: DP | LCS | Reconstruction
Folder: dp/lcs/

⏱ 시간복잡도: O(n·m)
💾 공간복잡도: O(n·m)

📌 핵심 아이디어
- 2D DP: lcs[i][j] = LCS( s1[0..i-1], s2[0..j-1] ) 길이.
- 복원: i=n, j=m에서 시작해
  - s1[i-1]==s2[j-1] → 문자를 답에 push_back하고 i--, j--.
  - 아니면 lcs[i][j-1]와 lcs[i-1][j] 중 큰 쪽으로 이동(같으면 한쪽을 선택).

⚠️ 주의할 점
- 인덱싱: 비교 시 s1[i-1], s2[j-1]로 접근.
- 출력 규칙(중요): LCS 길이가 0이면 **두 번째 줄(문자열)을 출력하지 않음**.
- 복원 시 tie-break는 임의 선택 가능(문제는 임의의 LCS 허용). 현재 코드는 j-1을 우선(>=)으로 택함.
- 메모리 O(n·m). 길이가 매우 크다면 복원용 parent만 저장하거나 경로 압축 기법 고려.

✔️ 지문 힌트
- 첫 줄: LCS 길이
- 둘째 줄: LCS 문자열(길이>0일 때만)
*/

// 2026-02-26 D+3 REIVEW 간단 복습
// 2차원 dp로 점화식 만들기
// 문자가 달랐을 경우 두 문자열 중 하나의 문자를 뺐을 때 까지의 결과의 최댓값을 dp에 저장
// 백트래킹은 맨 뒤 문자부터 같을 경우 정답 string에 넣고
// 다를 경우 dp값이 더 큰 쪽으로 i와 j를 변화해가면서 얻을 수 있음
// 마지막에 정답 string을 reverse 해주면 됨

// 2026-02-23 Reboot

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string str1, str2;
	cin >> str1 >> str2;

	int n = (int)str1.size(), m = (int)str2.size();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (str1[i - 1] == str2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
		}
	}

	cout << dp[n][m] << '\n';

	int i = n, j = m;
	string ans = "";
	while (i > 0 && j > 0)
	{
		if (str1[i - 1] == str2[j - 1])
		{
			ans += str1[i - 1];
			i--;
			j--;
		}
		else
		{
			if (dp[i][j - 1] >= dp[i - 1][j])
				j--;
			else
				i--;
		}
	}
	reverse(ans.begin(), ans.end());
	cout << ans << '\n';
}

// 2025-10-13 D+14 REVIEW

// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string str1, str2, ans;
// 	cin >> str1 >> str2;
// 
// 	int n = static_cast<int>(str1.size()), m = static_cast<int>(str2.size());
// 	vector<vector<int>> lcs(n + 1, vector<int>(m + 1));
// 	for (int i = 1; i <= n; i++)
// 	{
// 		for (int j = 1; j <= m; j++)
// 		{
// 			if (str1[i - 1] == str2[j - 1])
// 				lcs[i][j] = lcs[i - 1][j - 1] + 1;
// 			else
// 				lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
// 		}
// 	}
// 
// 	cout << lcs[n][m] << '\n';
// 
// 	int i = n, j = m;
// 	while (i > 0 && j > 0)	// 둘 중 하나가 0이 되면 강제 종료
// 	{
// 		if (str1[i - 1] == str2[j - 1])
// 		{
// 			ans += str1[i - 1];
// 			i--; j--;
// 		}
// 		else
// 		{
// 			if (lcs[i - 1][j] <= lcs[i][j - 1])
// 				j--;
// 			else
// 				i--;
// 		}
// 	}
// 
// 	reverse(ans.begin(), ans.end());
// 	cout << ans << '\n';
// }

// 2025-09-28 D+3 REVIEW

// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string s1, s2;
// 	cin >> s1 >> s2;
// 
// 	int n = (int)s1.size(), m = (int)s2.size();
// 
// 	vector<vector<int>> lcs(n + 1, vector<int>(m + 1, 0));
// 	for (int i = 1; i <= n; i++)
// 	{
// 		for (int j = 1; j <= m; j++)
// 		{
// 			if (s1[i - 1] == s2[j - 1]) lcs[i][j] = lcs[i - 1][j - 1] + 1;	// 비교할 때 s1과 s2는 index에 -1 해야 함
// 			else lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
// 		}
// 	}
// 
// 	string ans;
// 	int i = n, j = m;
// 	while (i > 0 && j > 0)
// 	{
// 		if (s1[i - 1] == s2[j - 1])	// 마찬가지
// 		{
// 			ans.push_back(s1[i - 1]);
// 			i--;
// 			j--;
// 		}
// 		else
// 		{
// 			if (lcs[i][j - 1] >= lcs[i - 1][j]) j--;
// 			else i--;
// 		}
// 	}
// 	reverse(ans.begin(), ans.end());
// 	cout << lcs[n][m] << "\n";
// 	if (lcs[n][m] > 0) cout << ans << "\n";
// }

// 2025-09-25 D+0 REVIEW

// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string s1, s2;
// 	cin >> s1 >> s2;
// 	int n = (int)s1.size(), m = (int)s2.size();
// 
// 	string ans = "";
// 	vector<vector<int>> lcs(n + 1, vector<int>(m + 1, 0));
// 
// 	for (int i = 1; i <= n; i++)
// 	{
// 		for (int j = 1; j <= m; j++)
// 		{
// 			if (s1[i - 1] == s2[j - 1]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
// 			else lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
// 		}
// 	}
// 
// 	ans.reserve(lcs[n][m]);
// 	int i = n, j = m;
// 	while (i > 0 && j > 0)
// 	{
// 		if (s1[i-1] == s2[j-1])
// 		{
// 			ans.push_back(s1[i - 1]);
// 			i--; j--;
// 		}
// 		else
// 		{
// 			if (lcs[i - 1][j] > lcs[i][j - 1]) i--;
// 			else j--;
// 		}
// 	}
// 	reverse(ans.begin(), ans.end());
// 
// 	cout << lcs[n][m] << "\n";
// 	if (!ans.empty()) cout << ans << "\n";
// }

// 2025-09-25 ORIGINAL

// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string s1, s2;
// 	cin >> s1 >> s2;
// 	int n = (int)s1.size(), m = (int)s2.size();
// 
// 	vector<vector<int>> lcs(n + 1, vector<int>(m + 1, 0));
// 	
// 	for (int i = 1; i <= n; i++)
// 	{
// 		for (int j = 1; j <= m; j++)
// 		{
// 			if (s1[i - 1] == s2[j - 1]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
// 			else lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
// 		}
// 	}
// 
// 	int i = n, j = m;
// 	string ans;
// 	while (i > 0 && j > 0)
// 	{
// 		if (s1[i - 1] == s2[j - 1])
// 		{
// 			ans.push_back(s1[i - 1]);
// 			i--;  j--;
// 		}
// 		else
// 		{
// 			if (lcs[i][j - 1] > lcs[i - 1][j]) j--;
// 			else i--;
// 		}
// 	}
// 	reverse(ans.begin(), ans.end());
// 
// 	cout << lcs[n][m] << "\n";
// 	if(!ans.empty()) cout << ans << "\n";
// }