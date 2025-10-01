/*
BOJ 1213 — 팰린드롬 만들기 (Palindrome Making)
Topic: String | Counting | Greedy | Palindrome Construction
Folder: string/

⏱ 시간복잡도: O(|S| + Σ26) ≈ O(|S|)
💾 공간복잡도: O(1)         // 26개 카운트

📌 핵심 아이디어
- 알파벳 빈도를 세고, 홀수 빈도가 2개 이상이면 불가능 → "I'm Sorry Hansoo".
- 가능할 때: 앞 절반 = 각 문자 floor(cnt/2)개를 사전순으로 쌓기 → 가운데(odd 1개면 그 문자 1개) → 앞 절반의 역순.
- 이렇게 만들면 사전순 최소 팰린드롬.

⚠️ 주의할 점
- 입력이 **대문자**이므로 인덱싱은 `'A'` 기준.
- 사전순 최소를 위해 앞 절반은 **A→Z** 순으로, 뒷 절반은 **Z→A**로 채우기.
- 홀수 문자는 정확히 **한 글자**만 가운데에 올 수 있음.
- 두 번째 홀수 개 문자가 나오면 "I'm Sorry Hansoo" 출력.
- string.append(count, char)를 쓰면 같은 문자를 여러 번 추가할 때 효율적.
- `pal.reserve(n)`을 사용하면 메모리 재할당 방지 가능(미세 최적화).

✔️ 지문 힌트
-“팰린드롬을 만들 수 없을 때” → 실패 메시지 고정: `I'm Sorry Hansoo`
-“가능하면 아무거나”가 아니라 **사전순으로 가장 앞선** 팰린드롬을 요구.
- 입력은 대문자 알파벳만 -> 알파벳 크기 26.
*/

// 2025-09-28 D+3 REVIEW

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s, pal; cin >> s;
	int mid = -1, n = (int)s.size();
	vector<int> freq(26, 0);
	
	for (char c : s)
		freq[c - 'A']++;

	for (int i = 0; i < 26; i++)
	{
		if (mid == -1 && freq[i] % 2 != 0)
		{
			mid = i;
			freq[i]--;
		}
		else if (mid != -1 && freq[i] % 2 != 0)
		{
			cout << "I'm Sorry Hansoo\n";
			return 0;
		}
	}

	for (int i = 0; i < 26; i++)
	{
		int half = freq[i] / 2;
		pal.append(half, i + 'A');
		freq[i] = half;
	}

	if (mid != -1)
		pal += mid + 'A';

	for (int i = 25; i >= 0; i--)
		pal.append(freq[i], i + 'A');

	cout << pal << "\n";
}

// 2025-09-25 D+0 REVIEW

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
// 	string s, ans = "";
// 	cin >> s;
// 
// 	int n = (int)s.size(), mid = -1;
// 	const int mx = 26;
// 	vector<int> v(mx, 0);
// 	for (char c : s)
// 		v[c - 'A']++;
// 
// 	for (int i = 0; i < mx; i++)
// 	{
// 		if (mid == -1 && v[i] % 2 != 0)
// 		{
// 			mid = i;
// 			v[i]--;
// 		}
// 		else if (mid != -1 && v[i] % 2 != 0)
// 		{
// 			cout << "I'm Sorry Hansoo" << "\n";
// 			return 0;
// 		}
// 	}
// 
// 	for (int i = 0; i < mx; i++)
// 	{
// 		int tmp = v[i];
// 		while (v[i] > tmp / 2)
// 		{
// 			ans += i + 'A';
// 			v[i]--;
// 		}
// 	}
// 
// 	if (mid != -1)
// 		ans += mid + 'A';
// 
// 	for (int i = mx - 1; i >= 0; i--)
// 	{
// 		while (v[i]--)
// 			ans += i + 'A';
// 	}
// 
// 	cout << ans;
// }

// 2025-09-25 RECOMMENDED

// #include <bits/stdc++.h>
// using namespace std;
// 
// int main() {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string s;
// 	cin >> s;
// 
// 	constexpr int MX = 26;
// 	array<int, MX> cnt{};  // 0으로 자동 초기화
// 	for (char c : s) cnt[c - 'A']++;
// 
// 	int mid = -1;
// 	for (int i = 0; i < MX; i++) {
// 		if (cnt[i] % 2) {
// 			if (mid == -1) {
// 				mid = i;
// 				cnt[i]--;          // 가운데에 1개 배치 예정, 나머지는 짝수로
// 			}
// 			else {
// 				cout << "I'm Sorry Hansoo\n";
// 				return 0;
// 			}
// 		}
// 	}
// 
// 	string left;
// 	left.reserve(s.size() / 2);
// 	for (int i = 0; i < MX; i++) {
// 		int half = cnt[i] / 2;
// 		if (half) left.append(half, char('A' + i));
// 	}
// 
// 	string ans;
// 	ans.reserve(s.size());
// 	ans += left;
// 	if (mid != -1) ans.push_back(char('A' + mid));
// 	// 오른쪽 절반 = 왼쪽 절반의 역순
// 	for (auto it = left.rbegin(); it != left.rend(); ++it) ans.push_back(*it);
// 
// 	cout << ans << '\n';
// 	return 0;
// }

// 2025-09-25 ORIGINAL

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
// 	string s, ans = "";
// 	cin >> s;
// 
// 	vector<int> v(26, 0);
// 	int mid = -1;
// 
// 	for (int i = 0; i < (int)s.size(); i++)
// 	{
// 		int idx = s[i] - 'A';
// 		v[idx]++;
// 	}
// 
// 	for (int i = 0; i < 26; i++)
// 	{
// 		if (mid == -1 && v[i] % 2 != 0)
// 		{
// 			mid = i;
// 			v[i]--;
// 		}
// 		else if (mid != -1 && v[i] % 2 != 0)
// 		{
// 			cout << "I'm Sorry Hansoo";
// 			return 0;
// 		}
// 	}
// 
// 	for (int i = 0; i < 26; i++)
// 	{
// 		int j = v[i];
// 		while (v[i] > j / 2)
// 		{
// 			ans += i + 'A';
// 			v[i]--;
// 		}
// 	}
// 
// 	if (mid != -1)
// 		ans += mid + 'A';
// 
// 	for (int i = 25; i >= 0; i--)
// 	{
// 		while (v[i])
// 		{
// 			ans += i + 'A';
// 			v[i]--;
// 		}
// 	}
// 
// 	cout << ans;
// }