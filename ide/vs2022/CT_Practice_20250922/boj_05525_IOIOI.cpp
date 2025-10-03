/*
BOJ 5525 - IOIOI (IOIOI)
Topic : String | Pattern Counting
Folder : string/kmp/

⏱ 시간복잡도: O(M)
💾 공간복잡도: O(1)

📌 핵심 아이디어
- 문자열을 한 번 순회하며 "IOI"를 찾을 때마다 streak++.
- streak >= n일 때마다 cnt++ -> 겹치는 경우도 자연스럽게 카운트.

⚠️ 주의할 점
- 인덱스 경계: i + 1 < m 일 때만 s[i-1], s[i], s[i+1] 접근.
- 전진 규칙: 매칭 시 i += 2, 불일치 시 i++.

✔️ 지문 힌트
 - Pn = I (OI)^n -> 결국 "IOI"가 연속 몇 번 등장하는지에 달려 있음.
*/

// 2025-10-03 D+3 REVIEW

#include <iostream>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, cnt = 0, streak = 0;
	string str;
	cin >> n >> m >> str;

	for (int i = 1; i < m - 1;)
	{
		if (str[i - 1] == 'I' && str[i] == 'O' && str[i + 1] == 'I')
		{
			streak++;
			if (streak >= n)
				cnt++;
			i += 2;
		}
		else
		{
			streak = 0;
			i++;
		}
	}

	cout << cnt << '\n';
}

// 2025-09-30 D+0 REVIEW

// #include <iostream>
// #include <string>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int n, m, streak = 0, cnt = 0;
// 	string s;
// 	cin >> n >> m >> s;
// 	
// 	for (int i = 1; i < m - 1;)
// 	{
// 		if (s[i - 1] == 'I' && s[i] == 'O' && s[i + 1] == 'I')
// 		{
// 			streak++;
// 			if (streak >= n)
// 				cnt++;
// 			i += 2;
// 		}
// 		else
// 		{
// 			streak = 0;
// 			i++;
// 		}
// 	}
// 
// 	cout << cnt << '\n';
// }

// 2025-09-30 ORIGINAL

// #include <iostream>
// #include <string>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string s;
// 	int n, m, cnt = 0, streak = 0;
// 	cin >> n >> m >> s;
// 
// 	for (int i = 1; i < m - 1;)
// 	{
// 		if (s[i - 1] == 'I' && s[i] == 'O' && s[i + 1] == 'I')
// 		{
// 			streak++;
// 			if (streak >= n)
// 				cnt++;
// 			i += 2;
// 		}
// 		else
// 		{
// 			streak = 0;
// 			i++;
// 		}
// 	}
// 	cout << cnt << "\n";
// }