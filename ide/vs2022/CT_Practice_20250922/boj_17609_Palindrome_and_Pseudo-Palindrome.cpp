/*
BOJ 17609 — 회문 (Palindrome / Pseudo-Palindrome)
Topic: String | Two Pointers
Folder: string/two-pointers/

⏱ 시간복잡도: O(n)   // 첫 불일치에서 최대 두 번의 구간 검사
💾 공간복잡도: O(1)

📌 핵심 아이디어
- 양끝 투 포인터로 비교하며 진행.
- 첫 불일치에서 두 경우 모두 검사:
  1) 왼쪽 문자 제거: 구간 [i+1, j]가 팰린드롬인지
  2) 오른쪽 문자 제거: 구간 [i, j-1]가 팰린드롬인지
- 둘 다 실패면 2, 하나라도 가능하면 1, 불일치가 한 번도 없으면 0.

⚠️ 주의할 점
- 보조 검사 루프에서 반드시 `{}`로 k++, l--를 함께 묶을 것.
- 첫 불일치에서 결과가 결정되면 바로 출력하고 종료(현재 코드는 break 후 바깥에서 0만 조건 출력 → OK).
- 길이 1, 이미 팰린드롬(0), 양쪽 모두 가능한 케이스(abca) 등의 엣지 확인.

✔️ 지문 힌트
- “최대 한 글자 삭제 허용” → 첫 불일치에서 양쪽 스킵을 각각 검증하면 충분.
*/

// 2025-10-20 D+14 REVIEW

#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(const string& og_str, int left, int right);

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--)
	{
		string str;
		cin >> str;

		bool is_pal = true;

		int i = 0, j = (int)str.size() - 1;
		while (i < j)
		{
			if (str[i] != str[j])
			{
				is_pal = false;

				if (isPalindrome(str, i + 1, j) || isPalindrome(str, i, j - 1))
				{
					cout << 1 << '\n';
					break;
				}
				else
				{
					cout << 2 << '\n';
					break;
				}
			}
			else
			{
				i++; j--;
			}
		}

		if (is_pal)
			cout << 0 << '\n';
	}
}

bool isPalindrome(const string& og_str, int left, int right)
{
	while (left < right)
	{
		if (og_str[left++] != og_str[right--]) return false;
	}
	return true;
}

// 2025-10-02 D+3 REVIEW

// #include <iostream>
// #include <string>
// 
// using namespace std;
// 
// bool isPalindrome(const string& og_str, int left, int right);
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int t;
// 	cin >> t;
// 
// 	while (t--)
// 	{
// 		string s;
// 		cin >> s;
// 
// 		int i = 0, j = (int)s.size() - 1;
// 		bool is_pal = true;
// 		while (i < j)
// 		{
// 			if (s[i] != s[j])
// 			{
// 				is_pal = false;
// 				if (isPalindrome(s, i + 1, j) || isPalindrome(s, i, j - 1))
// 				{
// 					cout << 1 << '\n';
// 					break;
// 				}
// 				else
// 				{
// 					cout << 2 << '\n';
// 					break;
// 				}
// 			}
// 			else
// 			{
// 				i++;
// 				j--;
// 			}
// 		}
// 
// 		if (is_pal)
// 			cout << 0 << '\n';
// 	}
// }
// 
// bool isPalindrome(const string& og_str, int left, int right)
// {
// 	while (left < right)
// 	{
// 		if (og_str[left++] != og_str[right--])
// 			return false;
// 	}
// 	return true;
// }

// 2025-09-29 D+0 REVIEW

// #include <iostream>
// #include <string>
// 
// using namespace std;
// 
// bool isPalindrome(const string& og_str, int left, int right);
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int t;
// 	cin >> t;
// 
// 	while (t--)
// 	{
// 		string s;
// 		cin >> s;
// 
// 		int n = (int)s.size(), i = 0, j = n - 1;
// 		bool is_pal = true;
// 		while (i < j)
// 		{
// 			if (s[i] == s[j])
// 			{
// 				i++;
// 				j--;
// 			}
// 			else
// 			{
// 				is_pal = false;
// 				if (isPalindrome(s, i + 1, j) || isPalindrome(s, i, j - 1))
// 				{
// 					cout << 1 << "\n";
// 					break;
// 				}
// 				else
// 				{
// 					cout << 2 << "\n";
// 					break;
// 				}
// 			}
// 		}
// 
// 		if (is_pal)
// 			cout << 0 << "\n";
// 	}
// }
// 
// bool isPalindrome(const string& og_str, int left, int right)
// {
// 	while (left < right)
// 		if (og_str[left++] != og_str[right--]) return false;
// 	return true;
// }


// 2025-09-29 ORIGINAL

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
// 	int t;
// 	cin >> t;
// 
// 	while (t--)
// 	{
// 		string s;
// 		cin >> s;
// 
// 		int n = (int)s.size();
// 		bool is_pal = true;
// 
// 		int i = 0, j = n - 1;
// 		while (i < j)
// 		{
// 			if (s[i] != s[j])
// 			{
// 				bool nor_string1 = false, nor_string2 = false;
// 				is_pal = false;
// 				int k = i + 1, l = j;
// 				while (k < l)
// 				{
// 					if (s[k] != s[l])
// 					{
// 						nor_string1 = true;
// 						break;
// 					}
// 					else
// 					{
// 						k++;
// 						l--;
// 					}
// 				}
// 
// 				k = i, l = j - 1;
// 				while (k < l)
// 				{
// 					if (s[k] != s[l])
// 					{
// 						nor_string2 = true;
// 						break;
// 					}
// 					else
// 					{
// 						k++;
// 						l--;
// 					}
// 				}
// 
// 				if (nor_string1 && nor_string2)
// 				{
// 					cout << 2 << "\n";
// 					break;
// 				}
// 				else
// 				{
// 					cout << 1 << "\n";
// 					break;
// 				}
// 			}
// 			else
// 			{
// 				i++;
// 				j--;
// 			}
// 		}
// 
// 		if (is_pal)
// 			cout << 0 << "\n";
// 	}
// }