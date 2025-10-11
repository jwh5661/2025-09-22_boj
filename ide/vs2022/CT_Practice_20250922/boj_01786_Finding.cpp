/*
BOJ 1786 — 찾기 (Finding)
Topic: String | KMP (Prefix Function) | Pattern Matching
Folder: string/kmp/

⏱ 시간복잡도: O(|T| + |P|)
💾 공간복잡도: O(|P|)

📌 핵심 아이디어
- 패턴 P의 LPS(= π, prefix function)로 “접두사=접미사” 최대 길이를 전처리.
- 불일치 시 텍스트 인덱스는 되돌리지 않고, 패턴 인덱스 j만 LPS[j-1]로 점프.
- 매치 성공(j==m) 후에도 j를 LPS[j-1]로 되돌려 겹치는 매치까지 탐색.

⚠️ 주의할 점
- 이 파일이 **단독 실행**이면 getline 바로 사용해도 OK.
  다른 입력(>> 연산)과 섞을 땐, 직전 개행이 남아 t가 비게 될 수 있으니 `cin.ignore()`로 개행 제거 필요.
- 출력은 1-based 요구 → 내부 0-based 인덱스 저장 후 출력 시 `+1`.
- LPS 계산에서 `while (j>0 && p[i]!=p[j]) j=LPS[j-1];` 순서/조건 실수 주의.
- **길이 vs 인덱스 혼동 주의**: LPS 값과 j는 "길이". 길이가 j라면 최근 일치 구간의 마지막 인덱스는 j-1.
- **reserve 관련**: 일반적으로 n < m이면 (n-m+1)이 음수 → size_t 변환 시 언더플로 위험.

✔️ 지문 힌트
- “문자열 T에서 P가 나타나는 모든 위치” + “모든 발생” → 전형적인 KMP 패턴 매칭.
- 공백 포함 가능 → `getline`으로 전체 라인 입력.
*/

// 2025-10-11 D+14 REVIEW

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string t, p;
	getline(cin, t);
	getline(cin, p);

	int n = (int)t.size(), m = p.size();

	if (n < m)
	{
		cout << 0 << '\n';
		return 0;
	}

	vector<int> lps(m, 0), idx;
	idx.reserve(n - m + 1);
	for (int i = 1; i < m; i++)
	{
		int j = lps[i - 1];
		while (j > 0 && p[i] != p[j]) j = lps[j - 1];
		if (p[i] == p[j]) j++;
		lps[i] = j;
	}

	for (int i = 0, j = 0; i < n; i++)
	{
		while (j > 0 && t[i] != p[j]) j = lps[j - 1];
		if (t[i] == p[j])
			j++;
		if (j == m)
		{
			idx.push_back(i - m + 1);
			j = lps[j - 1];
		}
	}

	cout << idx.size() << '\n';
	for (int i : idx)
		cout << i + 1 << ' ';
	cout << '\n';
}

// 2025-09-26 D+3 REVIEW

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
// 	string s1, s2;
// 	getline(cin, s1);
// 	getline(cin, s2);
// 
// 	int n = (int)s1.size(), m = (int)s2.size();
// 
// 	if (m == 0)
// 	{
// 		cout << 0 << "\n";
// 		return 0;
// 	}
// 
// 	// if (n < m)
// 	// {
// 	// 	swap(s1, s2);
// 	// 	swap(n, m);
// 	// }
// 
// 	vector<int> v(m, 0), idx;
// 	idx.reserve(n - m + 1);
// 	for (int i = 1; i < m; i++)	// 0부터 시작하지 않는 이유 -> 여기서 j는 s2의 i까지 문자열이 있을 때, 지금까지의 가장 긴 접두사의 마지막 인덱스(=길이)를 뜻함
// 								// 문자열이 1개 밖에 없을 때에는 자기 자신만 있으므로 접두사/접미사가 나타날 수 없음
// 								// 그래서 v[0]은 무조건 0이고, 1부터 시작해서 v[i-1]과 비교하여 같은지 확인하면 된다.
// 	{
// 		int j = v[i - 1];
// 		while (j > 0 && s2[i] != s2[j]) j = v[j - 1];	// 같은 문자열인 p에서 비교하는 거니까 s2[i]와 s2[j]를 비교, 
// 														// 점프는 방금 확인한 문자앞까지 문자를 잘라서 
// 		if (s2[i] == s2[j]) j++;
// 		v[i] = j;
// 	}
// 
// 	for (int i = 0, j = 0; i < n; i++)
// 	{
// 		while (j > 0 && s1[i] != s2[j]) j = v[j - 1];
// 		if (s1[i] == s2[j]) j++;
// 		if (j == m)
// 		{
// 			idx.push_back(i - m + 1);
// 			j = v[j - 1];	// 이거 해야 다음 일치 찾을 때 미리 줄여놓을 수 있음
// 		}
// 	}
// 
// 	cout << (int)idx.size() << "\n";	// 새로 변수 만들지 말고 크기로 출력
// 	for (int i : idx)
// 		cout << i + 1 << " ";	// 1번 인덱스부터 시작이니까 출력에 + 1
// 	cout << "\n";
// }

// 2025-09-23 D+0 REVIEW

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
// 	getline(cin, t);
// 	getline(cin, p);
// 
// 	int n = (int)t.size();
// 	int m = (int)p.size();
// 
// 	if (m == 0)
// 	{
// 		cout << 0 << "\n";
// 		return 0;
// 	}
// 
// 	vector<int> LPS(m, 0);
// 
// 	for (int i = 1; i < m; i++)
// 	{
// 		int j = LPS[i - 1];
// 		while (j > 0 && p[i] != p[j]) j = LPS[j - 1];
// 		if (p[i] == p[j]) j++;
// 		LPS[i] = j;
// 	}
// 
// 	int j = 0;
// 	vector<int> ans;
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		while (j > 0 && t[i] != p[j]) j = LPS[j - 1];
// 		if (t[i] == p[j]) j++;
// 		if (j == m)
// 		{
// 			ans.push_back(i - m + 1);
// 			j = LPS[j - 1];
// 		}
// 	}
// 
// 	cout << (int)ans.size() << "\n";
// 	for (int i : ans)
// 		cout << i + 1 << " ";
// 	cout << "\n";
// }

// 2025-09-23 ORIGINAL

// #include <iostream>
// #include <string>
// #include <vector>
// 
// using namespace std;
// 
// 
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string t, p;
// 	getline(cin, t);
// 	getline(cin, p);
// 
// 	int n = (int)t.size(), m = (int)p.size();
// 	if (m == 0)
// 	{
// 		cout << 0 << "\n";
// 		return 0;
// 	}
// 	vector<int> v(m, 0);
// 	vector<int> ans;
// 
// 	for (int i = 1; i < m; i++)
// 	{
// 		int j = v[i - 1];
// 		while (j > 0 && p[i] != p[j])
// 			j = v[j - 1];
// 		if (p[i] == p[j])
// 			j++;
// 		v[i] = j;
// 	}
// 
// 	int j = 0;
// 
// 	for (int i = 0; i < n; i++)
// 	{
// 		while (j > 0 && t[i] != p[j]) j = v[j - 1];
// 		if (t[i] == p[j]) j++;
// 		if (j == m)
// 		{
// 			ans.push_back(i - m + 1);
// 			j = v[j - 1];
// 		}
// 	}
// 
// 	cout << (int)ans.size() << "\n";
// 	for (int i : ans)
// 		cout << i + 1 << " ";
// 	cout << "\n";
// }