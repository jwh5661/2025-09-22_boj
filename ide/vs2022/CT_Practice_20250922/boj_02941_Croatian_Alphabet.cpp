/*
BOJ 2941 — 크로아티아 알파벳 (Croatian Alphabet)
Topic: String | Implementation
Folder: string/

⏱ 시간복잡도: O(|S|)
💾 공간복잡도: O(1)

📌 핵심 아이디어
- 특수 패턴을 일반 문자보다 먼저/우선적으로 매칭해 길이를 1로 카운트.
- 가장 긴 패턴인 "dz="를 먼저 확인해 "z="와의 중복 매칭을 방지.
- 매칭되면 i를 패턴 길이만큼 건너뛰며 cnt++.

⚠️ 주의할 점
- `&&` vs `||` 연산자 우선순위 때문에 i+1 < n 검사가 일부 패턴에 적용되지 않을 수 있음 → 전체를 괄호로 묶어야 안전.
- 사용하지 않는 `#include <vector>` 제거 가능.
- else 분기에서 ++cnt를 확실하게 넣어주기.
- "dz="를 항상 "z="보다 **먼저** 체크해야 이중 카운트가 안 생김.
- 인덱스 범위(i+1, i+2) 체크를 먼저 해서 out-of-range 방지.
- 연속 패턴이 이어질 수 있으니 while/for에서 i 증가를 패턴 길이에 맞춰 정확히 처리.

✔️ 지문 힌트
- `"c=","c-","dz=","d-","lj","nj","s=","z="` → 이들 조합은 각각 **하나의 문자**로 취급.
- 문자열 길이 제한이 작아(≤100) 선형 스캔으로 충분.

*/

// 2025-10-11 D+14 REVIEW

#include <iostream>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string str;
	cin >> str;
	int n = (int)str.size(), cnt = 0;

	for (int i = 0; i < n; i++)
	{
		if (i + 2 < n && str[i] == 'd' && str[i + 1] == 'z' && str[i + 2] == '=')
		{
			cnt++;
			i += 2;
		}
		else if (i + 1 < n &&
			(
				(str[i] == 'c' && (str[i + 1] == '=' || str[i + 1] == '-')) ||
				(str[i] == 'd' && str[i + 1] == '-') ||
				(str[i] == 'l' && str[i + 1] == 'j') ||
				(str[i] == 'n' && str[i + 1] == 'j') ||
				(str[i] == 's' && str[i + 1] == '=') ||
				(str[i] == 'z' && str[i + 1] == '=')))
		{
			cnt++;
			i++;
		}
		else
			cnt++;
	}
	cout << cnt << '\n';
}

// 2025-09-26 D+3 REVIEW

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
// 	cin >> s;
// 
// 	int cnt = 0, n = (int)s.size();
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		if (i + 2 < n && s[i] == 'd' && s[i + 1] == 'z' && s[i + 2] == '=')
// 		{
// 			cnt++;
// 			i += 2;
// 		}
// 
// 		else if (i + 1 < n &&
// 			(
// 				(s[i] == 'c' && (s[i + 1] == '=' || s[i + 1] == '-')) ||
// 				(s[i] == 'd' && s[i + 1] == '-') ||
// 				(s[i] == 'l' && s[i + 1] == 'j') ||
// 				(s[i] == 'n' && s[i + 1] == 'j') ||
// 				(s[i] == 's' && s[i + 1] == '=') ||
// 				(s[i] == 'z' && s[i + 1] == '=')
// 				))
// 		{
// 			cnt++;
// 			i++;
// 		}
// 		else
// 			cnt++;
// 	}
// 	cout << cnt << "\n";
// }

// 2025-09-23 D+0 REVIEW

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
// 	cin >> s;
// 
// 	int n = (int)s.size(), cnt = 0;
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		if (i + 2 < n && s[i] == 'd' && s[i + 1] == 'z' && s[i + 2] == '=')
// 		{
// 			cnt++;
// 			i += 2;
// 		}
// 		else if (i + 1 < n && (
// 			(s[i] == 'c' && (s[i + 1] == '=' || s[i + 1] == '-')) ||
// 			(s[i] == 'd' && s[i + 1] == '-') || 
// 			(s[i] == 'l' && s[i + 1] == 'j') ||
// 			(s[i] == 'n' && s[i + 1] == 'j') || 
// 			(s[i] == 's' && s[i + 1] == '=') ||
// 			(s[i] == 'z' && s[i + 1] == '=')
// 			))
// 		{
// 			cnt++;
// 			i++;
// 		}
// 		else
// 			cnt++;
// 	}
// 	cout << cnt;
// }

// 2025-09-23 ORIGINAL

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
// 	string s;
// 	cin >> s;
// 
// 	int cnt = 0, t = (int)s.size();
// 
// 	for (int i = 0; i < t; i++)
// 	{
// 		if (i < t - 2 && s.substr(i, 3) == "dz=")
// 		{
// 			cnt++;
// 			i += 2;
// 		}
// 		else if (i < t - 1)
// 		{
// 			string s2 = s.substr(i, 2);
// 			if (s2 == "c=" || s2 == "c-" ||
// 				s2 == "d-" || s2 == "lj" ||
// 				s2 == "nj" || s2 == "s=" ||
// 				s2 == "z=")
// 			{
// 				cnt++;
// 				i++;
// 			}
// 			else
// 				cnt++;
// 		}
// 		else
// 			cnt++;
// 	}
// 	cout << cnt;
// }