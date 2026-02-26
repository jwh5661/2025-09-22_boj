/*
BOJ 9251 — LCS (Longest Common Subsequence)
Topic: DP | LCS | 문자열
Folder: dp/lcs/

⏱ 시간복잡도: O(n*m)
💾 공간복잡도: O(min(n,m))

📌 핵심 아이디어
- LCS 전형적인 DP: lcs[i][j] = (s1[i]==s2[j]) ? lcs[i-1][j-1]+1 : max(lcs[i-1][j], lcs[i][j-1])
- 메모리 최적화: 행 단위로만 필요하므로 1차원 배열 + prev_diag(대각선 값) 사용

⚠️ 주의할 점
- 문자열 복원은 불가 → 길이만 출력 가능
- prev_diag는 갱신 순서 주의 (tmp 저장 후 업데이트)

✔️ 지문 힌트
- "최장 공통 부분 수열의 길이" → 문자열 자체가 아닌 길이만 요구
- 문자열 길이 ≤ 1000 → O(n*m) DP 충분히 가능
*/

// 2026-02-26 D+14 REVIEW 간단 복습
// 역추적 과정이 없으므로 prev_diag로 대각선 값을 들고 1차원 dp를 수행
// j 루프로 들어갈 때 원래의 dp[j]에 대각선 값이 저장되어 있으므로
// 해당 값을 tmp에 미리 저장해두고 dp[j]에 새 값을 저장
// 그리고 나서 prev_diag에 tmp값을 저장한다

// 2026-02-04 D+3 REVIEW

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string str1, str2;
	cin >> str1 >> str2;

	int n = (int)str1.size(), m = (int)str2.size();

	if (n < m)
	{
		swap(str1, str2);
		swap(n, m);
	}

	vector<int> lcs(m + 1, 0);

	for (int i = 1; i <= n; i++)
	{
		int prev_diag = 0;
		for (int j = 1; j <= m; j++)
		{
			int temp = lcs[j];
			if (str1[i - 1] == str2[j - 1]) lcs[j] = prev_diag + 1;
			else lcs[j] = max(lcs[j], lcs[j - 1]);
			prev_diag = temp;
		}
	}

	cout << lcs[m] << '\n';
}

// 2026-01-30 Reboot

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <string>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string str1, str2;
// 	cin >> str1 >> str2;
// 
// 	int n = (int)str1.size(), m = (int)str2.size();
// 
// 	if (n < m)
// 	{
// 		swap(str1, str2);
// 		swap(n, m);
// 	}
// 
// 	vector<int> lcs(m + 1, 0);
// 
// 	for (int i = 1; i <= n; i++)
// 	{
// 		int prev_diag = 0;
// 		for (int j = 1; j <= m; j++)
// 		{
// 			int tmp = lcs[j];
// 			if (str1[i - 1] == str2[j - 1]) lcs[j] = prev_diag + 1;
// 			else lcs[j] = max(lcs[j], lcs[j - 1]);
// 			prev_diag = tmp;
// 		}
// 	}
// 
// 	cout << lcs[m] << '\n';
// }


// 2025-10-06 D+14 REVIEW

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <string>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string str1, str2;
// 	cin >> str1 >> str2;
// 	int n = (int)str1.size(), m = (int)str2.size();
// 
// 	if (n < m)
// 	{
// 		swap(str1, str2);
// 		swap(n, m);
// 	}
// 
// 	vector<int> lcs(m + 1, 0);
// 	for (int i = 1; i <= n; i++)	// 이건 j랑 맞추려고 1-base
// 	{
// 		int prev_diag = 0;
// 		for (int j = 1; j <= m; j++)	// j-1을 사용하니까 1-base
// 		{
// 			int tmp = lcs[j];
// 			if (str1[i - 1] == str2[j - 1]) lcs[j] = prev_diag + 1;
// 			else lcs[j] = max(lcs[j], lcs[j - 1]);
// 			prev_diag = tmp;
// 		}
// 	}
// 
// 	cout << lcs[m] << '\n';
// }

// 2025-09-25 D+3 REVIEW

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <string>
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
// 	if (n < m)
// 	{
// 		swap(s1, s2);
// 		swap(n, m);
// 	}
// 
// 	vector<int> lcs(m + 1, 0);
// 	for (int i = 1; i <= n; i++)
// 	{
// 		int prev_diag = 0;
// 		for (int j = 1; j <= m; j++)
// 		{
// 			int tmp = lcs[j];
// 			if (s1[i - 1] == s2[j - 1]) lcs[j] = prev_diag + 1;
// 			else lcs[j] = max(lcs[j], lcs[j - 1]);
// 			prev_diag = tmp;
// 		}
// 	}
// 
// 	cout << lcs[m] << "\n";
// }

// 2025-09-22 D+0 REVIEW

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <string>
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
// 	if (n < m)
// 	{
// 		swap(s1, s2);
// 		swap(n, m);
// 	}
// 	
// 	vector<int> dp(m + 1, 0);
// 	for (int i = 1; i <= n; i++)
// 	{
// 		int prev_diag = 0;
// 		for (int j = 1; j <= m; j++)
// 		{
// 			int tmp = dp[j];
// 			if (s1[i - 1] == s2[j - 1])
// 				dp[j] = prev_diag + 1;
// 			else
// 				dp[j] = max(dp[j - 1], dp[j]);
// 			prev_diag = tmp;
// 		}
// 	}
// 	cout << dp[m];
// }
// 
// 2025-09-22 ORIGINAL

// #include <iostream>
// #include <vector>
// #include <string>
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
// 	vector<vector<int>> v(n + 1, vector<int>(m + 1, 0));
// 
// 	for (int i = 1; i <= n; i++)
// 	{
// 		for (int j = 1; j <= m; j++)
// 		{
// 			if (s1[i - 1] == s2[j - 1]) v[i][j] = v[i - 1][j - 1] + 1;
// 			v[i][j] = max({ v[i][j], v[i][j - 1], v[i - 1][j] });
// 		}
// 	}
// 
// 	cout << v[n][m];
// }