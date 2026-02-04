/*
BOJ 1316 — 그룹 단어 체커 (Group Word Checker)
Topic: String | Hashing/Counting | Implementation
Folder: string/impl

⏱ 시간복잡도: O(Σ|S|)
💾 공간복잡도: O(1) (알파벳 26개)

📌 핵심 아이디어
- 같은 문자는 반드시 연속 구간으로만 나타나야 함.
- 문자가 바뀔 때, 과거에 이미 등장한 적이 있으면 그룹 단어가 아님.
- prev = -1 로 초기화 → 첫 문자도 동일한 로직 안에서 처리 가능.

⚠️ 주의할 점
- seen, prev, is_group는 **단어마다 초기화**해야 함.
- 배열 초기화 시 반드시 0으로 세팅해야 함 → 초기화하지 않으면 쓰레기 값이 들어가 오답 발생.
- prev를 int로 두면 첫 문자에 대한 특수 처리 불필요.

📘 배열 초기화 규칙 (C++ 표준)
- `bool seen[26] = {false};`
  → seen[0] = false, 나머지도 **자동으로 0(false)** 로 채워짐.
- `bool seen[26] = {};`
  → 모든 원소가 false로 초기화됨 (가독성 ↑).
- 규칙: 배열 초기화 리스트에 값이 부족하면 **나머지는 전부 0으로 value-initialize** 된다.

✔️ 지문 힌트
- “같은 문자는 연속해서 나타나야 한다” → 구간이 끊겼다가 다시 등장하면 그룹 단어가 아님.

*/

// 2026-02-04 Reboot 간단 복습
// a-z까지 배열 만들고 본 알파벳은 true표시
// 만약 현재 알파벳이 이미 본 알파벳이면, 이전 알파벳을 확인
// 이전 알파벳이 같은 알파벳이면 진행, 아니면 다른 그룹임

// 2025-10-11 D+14 REVIEW

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
// 	int n, cnt = 0;
// 	cin >> n;
// 
// 	while (n--)
// 	{
// 		string str;
// 		cin >> str;
// 
// 		bool seen[26] = {}, is_group = true;
// 		int prev = -1;
// 		for (char c : str)
// 		{
// 			int idx = c - 'a';
// 			if (prev != idx && seen[idx])
// 			{
// 				is_group = false;
// 				break;
// 			}
// 			seen[idx] = true;	// 문제에서 소문자만 입력으로 나온다고 했으므로 크게 신경 안써도 될듯
// 			prev = idx;
// 		}
// 
// 		if (is_group)
// 			cnt++;
// 	}
// 
// 	cout << cnt << '\n';
// }

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
// 	int n, cnt = 0;
// 	cin >> n;
// 
// 	while (n--)
// 	{
// 		string s;
// 		cin >> s;
// 
// 		bool seen[26] = {}, is_group = true;
// 		int prev = -1;
// 		for (int i = 0; i < (int)s.size(); i++)
// 		{
// 			int idx = s[i] - 'a';
// 			if (prev != idx && seen[idx])
// 			{
// 				is_group = false;
// 				break;
// 			}
// 			seen[idx] = true;
// 			prev = idx;
// 		}
// 
// 		if (is_group) cnt++;
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
// 	int n, cnt = 0;
// 	cin >> n;
// 
// 	while (n--)
// 	{
// 		string s;
// 		cin >> s;
// 
// 		bool seen[26] = {};
// 		int prev = -1;
// 		bool is_group = true;
// 
// 		for (char c : s)
// 		{
// 			int idx = c - 'a';
// 			if (prev != idx)
// 			{
// 				if (seen[idx])
// 				{
// 					is_group = false;
// 					break;
// 				}
// 				else
// 					seen[idx] = true;
// 			}
// 			prev = idx;
// 		}
// 
// 		if (is_group)
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
// 	int n, cnt = 0;
// 	
// 	cin >> n;
// 
// 	while (n--)
// 	{
// 		string s;
// 		cin >> s;
// 
// 		vector<int> v(26, 0);
// 		bool is_group = true;
// 		int prev = -1;
// 
// 		for (char c : s)
// 		{
// 			int idx = c - 'a';
// 			if (prev != idx)
// 			{
// 				if (v[idx] != 0)
// 				{
// 					is_group = false;
// 					break;
// 				}
// 				else
// 					v[idx]++;
// 			}
// 			prev = idx;
// 		}
// 
// 		if (is_group)
// 			cnt++;
// 	}
// 
// 	cout << cnt;
// }