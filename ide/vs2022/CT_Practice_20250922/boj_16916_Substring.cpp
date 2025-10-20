/*
BOJ 16916 — 부분 문자열 (Substring)
Topic: String | KMP
Folder: string/kmp

⏱ 시간복잡도: O(N+M)
💾 공간복잡도: O(M)

📌 핵심 아이디어
- 패턴 P의 LPS(=π)의 배열을 만든 뒤, 본문 T를 선형 스캔한다.
- 탐색 중 불일치가 나올 때는 i(텍스트 인덱스)는 고정한 채 while로 j를 lps[j-1]로 줄이며 같은 T[i]를 더 짧은 덥두어와 재비교한다(선형 보장).
- 일치하면 j++ 하고, j==M(패턴 길이)이 되면 매칭 성공.

⚠️ 주의할 점
- 왜 `while (j>0 && t[i] != p[j]) j = lps[j-1];`를 먼저 하나?
	-> KMP 불변식(`p[0..j-1]` ≡ `t[0..i-1]`의 접미사)을 유지하며, 같은 i에서 맞을 수 있는 최장 후보로 j를 줄여 재비교해야 텍스트 문자를 버리지 않고 O(N+M) 보장.
- 매칭 분기에서 `++j`를 반드시 해줘야 함(전진 누락 방지) -> 그 후 `j==M` 체크.
- LPS 구축도 불일치 시 while로 j를 당겨서 O(M)에 만든다.
- 출력은 존재 여부만(있으면 1, 없으면 0), 조기 종료 시 `return 0;`로 정상 종료.

✔️ 지문 힌트
- 나이브/`string::find` 반복은 최약 O(N*M). KMP/Z/해시 중 KMP가 구현 안정적.
- 최악 예시 T="aaaa...a", P="aaaab"에서도 KMP는 선형.
*/

//2025-10-20 D+14 REVIEW

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s, p;
	cin >> s >> p;

	int n = (int)s.size(), m = (int)p.size();

	if (n < m)
	{
		cout << 0 << '\n';
		return 0;
	}

	vector<int> lps(m, 0);
	for (int i = 1; i < m; i++)
	{
		int j = lps[i - 1];
		while (j > 0 && p[i] != p[j]) j = lps[j - 1];
		if (p[i] == p[j]) j++;
		lps[i] = j;
	}

	for (int i = 0, j = 0; i < n; i++)
	{
		while (j > 0 && s[i] != p[j]) j = lps[j - 1];
		if (s[i] == p[j])
		{
			j++;
			if (j == m)
			{
				cout << 1 << '\n';
				return 0;
			}
		}
	}

	cout << 0 << '\n';
}

//2025-10-03 D+3 REVIEW

// #include <iostream>
// #include <string>
// #include <vector>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string s, p;
// 	cin >> s >> p;
// 
// 	int n = (int)s.size(), m = (int)p.size();
// 
// 	if (n < m)
// 	{
// 		cout << 0 << '\n';
// 		return 0;
// 	}
// 
// 	vector<int> lis(m, 0);
// 	for (int i = 1; i < m; i++)
// 	{
// 		int j = lis[i - 1];
// 		while (j > 0 && p[i] != p[j]) j = lis[j - 1];
// 		if (p[i] == p[j]) j++;
// 		lis[i] = j;
// 	}
// 
// 	for (int i = 0, j = 0; i < n; i++)
// 	{
// 		while (j > 0 && s[i] != p[j]) j = lis[j - 1];
// 		if (s[i] == p[j])
// 		{
// 			j++;
// 			if (j == m)
// 			{
// 				cout << 1 << '\n';
// 				return 0;
// 			}
// 		}
// 	}
// 
// 	cout << 0 << '\n';
// }

// 2025-10-03 D+3 REVIEW
// boyer_moore_search 연습. 시간 복잡도 O(N * M)

// #include <iostream>
// #include <string>
// #include <functional>
// #include <algorithm>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string t, p;
// 	cin >> t >> p;
// 
// 	auto srch = boyer_moore_searcher(p.begin(), p.end());
// 	auto it = search(t.begin(), t.end(), srch);
// 	bool found = (it != t.end());
// 	if (found)
// 		cout << 1 << '\n';
// 	else
// 		cout << 0 << '\n';
// }

// 2025-09-30 D+0 REVIEW

// #include <iostream>
// #include <string>
// #include <vector>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string t, p;
// 	cin >> t >> p;
// 
// 	int n = (int)t.size(), m = (int)p.size();
// 
// 	if (n < m)
// 	{
// 		cout << 0 << '\n';
// 		return 0;
// 	}
// 
// 	vector<int> lis(m, 0);
// 	for (int i = 1; i < m; i++)
// 	{
// 		int j = lis[i - 1];
// 		while (j > 0 && p[i] != p[j]) j = lis[j - 1];
// 		if (p[i] == p[j]) j++;
// 		lis[i] = j;
// 	}
// 
// 	for (int i = 0, j = 0; i < n; i++)
// 	{
// 		while (j > 0 && t[i] != p[j]) j = lis[j - 1];
// 		if (t[i] == p[j])
// 		{
// 			j++;
// 			if (j == m)
// 			{
// 				cout << 1 << '\n';
// 				return 0;
// 			}
// 		}
// 	}
// 
// 	cout << 0 << '\n';
// }

// 2025-09-30 ORIGINAL

// #include <iostream>
// #include <string>
// #include <vector>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string t, p;
// 	cin >> t >> p;
// 
// 	int n = (int)t.size(), m = (int)p.size();
// 	if (n < m)
// 	{
// 		cout << 0 << "\n";
// 		return 0;
// 	}
// 
// 	vector<int> kmp(m, 0);
// 	for (int i = 1; i < m; i++)
// 	{
// 		int j = kmp[i - 1];
// 		while (j > 0 && p[i] != p[j]) j = kmp[j - 1];
// 		if (p[i] == p[j]) j++;
// 		kmp[i] = j;
// 	}
// 
// 	for (int i = 0, j = 0; i < n; i++)
// 	{
// 		while (j > 0 && t[i] != p[j]) j = kmp[j - 1];
// 		if (t[i] == p[j])
// 		{
// 			j++;
// 			if (j == m)
// 			{
// 				cout << 1 << "\n";
// 				return 0;
// 			}
// 		}
// 	}
// 	cout << 0 << "\n";
// }