/*
BOJ 5430 — AC (수열 뒤집기/삭제)
Topic: Implementation | Deque Simulation | Two-Pointer | String Parsing
Folder: impl/simulation/

⏱ 시간복잡도: O(|p| + n)      // 실제 reverse 없이 포인터만 이동
💾 공간복잡도: O(n)

📌 핵심 아이디어
- 입력 배열은 문자열에서 숫자 토큰을 누적 파싱해 vector<int>로 복원.
- R은 불리언 토글만, D는 좌/우 포인터(left/right)만 이동(컨테이너 조작 X).
- 최종 출력에서 토글 상태에 따라 [L..R] 또는 [R..L]로 출력.

⚠️ 주의할 점
- 파싱 루프 종료 후 `if (in_num) num.push_back(val);` 처리 → 입력 포맷 변동에도 견고 (원래 코드에는 없음). 
- 숫자 파싱 조건은 반드시 ('0' <= c && c <= '9').
- 파싱 시 숫자가 두 자리 이상일 수 있으므로 `val = val*10 + (c - '0') 누적.
- n=0일 경우 -> 빈 배열 처리 주의(`[]` 출력).
- D가 남았는데 구간이 비면(error) 즉시 "error" 출력 후 케이스 스킵.
- 각 테스트 케이스마다 개행 출력.
- 출력 시 인덱스 경계 맞추기: 구분자(,)는 마지막 원소 뒤에 붙이지 않음.

✔️ 지문 힌트
- reverse를 실제로 수행하면 TLE; 인덱스만 움직이는 게 핵심.
*/

// 2025-09-29 D+3 REVIEW

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--)
	{
		string p, num_string;
		int n, val = 0;
		cin >> p >> n >> num_string;

		vector<int> num;
		num.reserve(n);
		bool in_num = false, is_reversed = false, is_error = false;
		for (char c : num_string)
		{
			if ('0' <= c && c <= '9')
			{
				in_num = true;
				val = val * 10 + (c - '0');
			}
			else
			{
				if (in_num)
				{
					in_num = false;
					num.push_back(val);
					val = 0;
				}
			}
		}

		int l = 0, r = n - 1;
		for (char c : p)
		{
			if (c == 'R')
				is_reversed = !is_reversed;
			else
			{
				if (l > r)
				{
					is_error = true;
					break;
				}
				else
				{
					if (!is_reversed) l++;
					else r--;
				}
			}
		}

		if (is_error)
		{
			cout << "error\n";
			continue;
		}
		
		cout << "[";
		if (!is_reversed)
		{
			for (int i = l; i <= r; i++)
				cout << num[i] << (i == r ? "" : ",");
		}
		else
		{
			for (int i = r; i >= l; i--)
				cout << num[i] << (i == l ? "" : ",");
		}
		cout << "]\n";
	}
}

// 2025-09-26 D+0 REVIEW

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
// 		string p, num_string;
// 		int n, val = 0;
// 		bool in_num = false, is_reversed = false, is_error = false;;
// 		cin >> p >> n >> num_string;
// 
// 		vector<int> num;
// 		num.reserve(n);
// 		for (char c : num_string)
// 		{
// 			if ('0' <= c && c <= '9')
// 			{
// 				in_num = true;
// 				val = val * 10 + (c - '0');
// 			}
// 			else
// 			{
// 				if (in_num)
// 				{
// 					in_num = false;
// 					num.push_back(val);
// 					val = 0;
// 				}
// 			}
// 		}
// 
// 		int left = 0, right = n - 1;
// 		for (char c : p)
// 		{
// 			if (c == 'R')
// 				is_reversed = !is_reversed;
// 			else if (c == 'D')
// 			{
// 				if (left <= right)
// 				{
// 					if (is_reversed) right--;
// 					else left++;
// 				}
// 				else
// 				{
// 					is_error = true;
// 					break;
// 				}
// 			}
// 		}
// 
// 		if (is_error)
// 		{
// 			cout << "error\n";
// 			continue;
// 		}
// 			
// 		cout << "[";
// 		if (!is_reversed)
// 		{
// 			for(int i = left; i <= right; i++)
// 				cout << num[i] << (i == right ? "" : ",");
// 		}
// 		else
// 		{
// 			for (int i = right; i >= left; i--)
// 				cout << num[i] << (i == left ? "" : ",");
// 		}
// 		cout << "]\n";
// 	}
// }

// 2025-09-26 ORIGINAL

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
// 		string p, input_num;
// 		int n;
// 		cin >> p >> n >> input_num;
// 
// 		int left = 0, right = n - 1, val = 0;
// 		bool is_reversed = false, is_error = false, in_num = false;
// 
// 		vector<int> num;
// 		num.reserve(n);
// 		
// 		for (char c : input_num)
// 		{
// 			if ('0' <= c && c <= '9')
// 			{
// 				val = val * 10 + (c - '0');
// 				in_num = true;
// 			}
// 			else
// 			{
// 				if (in_num)
// 				{
// 					in_num = false;
// 					num.push_back(val);
// 					val = 0;
// 				}
// 			}
// 		}
// 
// 		for (char c : p)
// 		{
// 			if (c == 'R')
// 				is_reversed = !is_reversed;
// 			else if (c == 'D')
// 			{
// 				if (left <= right)
// 				{
// 					if(is_reversed)
// 						right--;
// 					else
// 						left++;
// 				}
// 				else
// 				{
// 					is_error = true;
// 					break;
// 				}
// 			}
// 		}
// 
// 		if (is_error)
// 		{
// 			cout << "error\n";
// 			continue;
// 		}
// 
// 		cout << "[";
// 		if (left <= right)
// 		{
// 			if (is_reversed)
// 			{
// 				for (int i = right; i >= left; i--)
// 					cout << num[i] << (i == left ? "" : ",");
// 			}
// 			else
// 			{
// 				for (int i = left; i <= right; i++)
// 					cout << num[i] << (i == right ? "" : ",");
// 			}
// 		}
// 		cout << "]\n";
// 	}
// }