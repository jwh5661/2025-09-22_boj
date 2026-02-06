/*
BOJ 4344 — 평균은 넘겠지 (Above Average)
Topic: Implementation | Arithmetic | Output Formatting
Folder: impl/

⏱ 시간복잡도: O(N) ( 학생 수 만큼 순회 )
💾 공간복잡도: O(N)  ( 점수 저장 벡터 )

📌 핵심 아이디어
- 평균을 구한 뒤, 평균 '초과'인 학생 비율을 출력(소수점 셋째 자리).
- 비율 = (평균 초과 학생 수) / (전체 학생 수) * 100
- 출력은 소숫점 셋째 자리 까지, 뒤에 "%"를 붙임.

⚠️ 주의할 점
- '평균 초과(>)' 판정은 정수 나눗셈으로도 정확함:
  - 실제 평균 = sum/n = k + frac, 정수 나눗셈 sum/n은 k(내림)
  - i > 평균  ⇔ i ≥ k+1  ⇔ i > (sum/n)
  - 따라서 if (i > sum / n) 은 논리적으로 올바름(부동소수 사용 불필요)
- 다만 비율 출력은 부동소수 필요 → (cnt * 100.0) / n
- 형식: fixed + setprecision(3)로 자동 반올림, 'xxx.xxx%'

✔️ 지문 힌트
- "평균을 넘는 학생들의 비율" -> 평균보다 **큰** 점수만 카운트.
- 출력 예시가 3자리 고정 소수점 + '%'. -> round/truncate가 아니라 **반올림**.
*/

// 2026-02-06 Reboot 간단 복습 완료

// 2025-09-27 D+3 REVIEW

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int c;
	cin >> c;

	while (c--)
	{
		int n, sum = 0, cnt = 0;
		cin >> n;

		vector<int> score(n, 0);
		for (int i = 0; i < n; i++)
		{
			cin >> score[i];
			sum += score[i];
		}

		int avg = sum / n;
		
		for (int i = 0; i < n; i++)
		{
			if (score[i] > avg)
				cnt++;
		}

		cout << fixed << setprecision(3) << (cnt * 100.0) / n << "%\n";
	}
}

// 2025-09-24 D+0 REVIEW

// #include <iostream>
// #include <string>
// #include <vector>
// #include <iomanip>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int c;
// 	cin >> c;
// 
// 	while (c--)
// 	{
// 		int n, sum = 0, cnt = 0;
// 		cin >> n;
// 
// 		vector<int> v(n, 0);
// 
// 		for (int i = 0; i < n; i++)
// 		{
// 			cin >> v[i];
// 			sum += v[i];
// 		}
// 
// 		for (int i : v)
// 		{
// 			if (i > sum / n)
// 				cnt++;
// 		}
// 
// 		cout << fixed << setprecision(3) << (cnt * 100.0) / n << "%\n";
// 	}
// }

// 2025-09-24 ORIGINAL

// #include <iostream>
// #include <string>
// #include <vector>
// #include <iomanip>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	int c;
// 	cin >> c;
// 
// 	while (c--)
// 	{
// 		int num, cnt = 0;
// 		cin >> num;
// 		double avg = 0.0;
// 		vector<int> v(num, 0);
// 		for (int i = 0; i < num; i++)
// 		{
// 			cin >> v[i];
// 			avg += v[i];
// 		}
// 		avg /= (double)num;
// 
// 		for (int i = 0; i < num; i++)
// 		{
// 			if (v[i] > avg)
// 				cnt++;
// 		}
// 		cout << fixed << setprecision(3) << (cnt * 100.0) / num << "%" << "\n";
// 	}
// }