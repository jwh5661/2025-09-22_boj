# Baekjoon Review Notes

---

## 📅 2025-09-22
**BOJ 10809 - 알파벳 찾기**
**BOJ 2675 - 문자열 반복**
**BOJ 9251 - LCS**

### BOJ 10809 - 알파벳 찾기
- **Topic:** String | Implementation
- **Folder:** `string/impl/`
- **Time Complexity:** O(|S| + 26)
- **Space Complexity:** O(26)

- **Key Idea:** 
 - 배열을 -1로 초기화하고, 문자열을 순회하며 처음 등장한 위치만 기록.
 - 전체 알파벳 순서대로 결과를 출력.

- **Caution:**
 - 배열 크기 26 고정, 입력이 소문자라는 조건을 전제로 함.
 - fill을 사용한 -1 초기화는 안전.

- **Improvement:**
 - range-based for + 별도 인덱스 관리로 코드 단순화.
 - 출력 시 `ostringstream` / 조건부 콤마로 마지막 공백 처리 불필요.
 - `(int)s.size()` 캐스팅 대신 `size_t` / `auto` 사용 권장.

- **Problem Hint:**
 - "알파벳 소문자 a-z" -> 배열 크기 26 필요.
 - "처음 등장하는 위치" -> 값이 -1일 때만 갱신.

---

### BOJ 2675 - 문자열 반복
- **Topic:** String | Implementation
- **Folder:** `string/impl/`
- **Time Complexity:** O(n * |s|)  
- **Space Complexity:** O(|s| * n) (출력 크기에 비례)

- **Key Idea:**
 - 문자열의 각 문자를 n번 반복해 출력.
 - `string(count, char)` 생성자로 반복 문자열 생성 가능.

  **Caution:**
 - 출력 뒤 개행을 반드시 추가.
 - n이 커지면 string(n, c)가 큰 메모리를 할당하지만, 문제 제한에서 허용됨.

- **Improvement:** `string(count, char)` 같은 함수로 단순화 가능
 - 출력 버퍼에 `append(count, char)`해도 됨
 - 삼항연산자로 줄바꿈 할 때도 `cout` 해야 함
 - ✅ [추가] `ostringstream` 사용으로 출력 횟수를 줄여 성능 개선 가능.  
 - 🔄 [수정] `string(n, c)` 대신 단순 for 루프를 써도 동일, 가독성 차이 선택 가능.  

- **Problem Hint:**
 - "문자열의 각 문자를 반복해 출력" -> 문자 단위로 n번 반복 필요.
 - "테스트 케이스 T" -> 여러 케이스를 순차적으로 처리.

---

### BOJ 9251 - LCS
- **Topic:** DP | String DP | LCS
- **Folder:** `dp/lcs/`
- **Time Complexity:** O(N·M)
- **Space Complexity:** O(min(N, M))

- **Key Idea:**
 - LCS 점화식 기반 DP.
 - 메모리 최적화: 1D 배열 + `prev_diag`로 대각선 값 추적.
 
- **Caution:**
 - 문자열 복원 불가 (길이만 구함).
 - `prev_diag` 업데이트 순서 주의: tmp -> prev_diag 갱신.

- **Improvement:** 
 - 메모리 절약을 위해 2행만 사용 가능
 - dp를 일차원으로 하는 법
 길이가 긴 문자열을 s1, 짧은 문자열을 s2에 배치하고 작업
 길이가 짧은 문자열을 확인할 때 들어있는 `dp[j]`값은 이차원 벡터 dp로 표현하면 `dp[i-1][j]`와 같은 값이므로 문자를 비교하기 전에 따로 tmp에 저장했다가, 
 비교한 후 같으면 `prev_diag(dp[i-1][j-1])`값에 +1한 값을 `dp[j]`에 덮어씌우고, 
 다르다면 `dp[j-1]`은 `dp[i][j-1]`과 같고, `dp[j]`는 `d[i-1][j]`와 같으니 둘 중 큰 값을 `dp[j]`에 저장하면 된다. 
 그리고 `prev_diag`에 `tmp`를 저장하면 다음 `i`에서 이 값이 `dp[i-1][j-1]`값이 된다. 
 i가 증가할 때 마다 `dp[i-1][j-1]`값(특히 j = 0이 되므로)이 `0`이 되어야 하기 때문에 `i` 반복문 초반에 초기화를 시켜줘야 한다.
 - 복원까지 필요하다면 2D DP로 가야 함.
 - 변수명/주석을 더 직관적으로 작성하면 복습할 때 이해 빠름.

- **Problem Hint:** 
 - “공통 부분 수열의 최대 길이” → 전형적인 LCS DP
 - "길이만 출력" -> 복원 X
 - 문자열 길이 <= 1000 -> O(n*m) 충분

---

## 📅 2025-09-23
**BOJ 2941 - 크로아티아 알파벳**
**BOJ 1316 - 그룹 단어 체커**
**BOJ 1786 - 찾기**

### BOJ 2941 - 크로아티아 알파벳 (Croatian Alphabet)
- **Topic:** String | Pattern Matching | Parsing
- **Folder:** `string/impl/`
- **Time Complexity:** O(n)
- **Space Complexity:** O(1)

- **Key Idea:** 
 - 선형 스캔하면서 특수 3자 패턴 `"dz="` -> 특수 2자 패턴들 -> 일반 문자 순으로 우선 매칭
 - 매칭된 패턴 길이만큼 인덱스를 건너뛰며 `cnt++`

- **Caution*:**
 - `"dz="`를 `"z="`보다 먼저 검사(중복 방지).
 - 인덱스 경계 체크(`i+1`, `i+2`) 먼저 수행.
 - 분기에서 `i` 증가량(2 또는 1)을 정확히 반영.

- **Improvement:**
 - 가독성 향상을 위해 패턴 리스트 (`{"dz=","c=","c-","d-","lj","nj","s=","z="}`)를 우선순위 순으로 두고, `substr` 비교로 구현하면 조건식이 더 단순해짐.
 - 입력이 매우 길어질 경우엔 트라이(Trie)나 Aho-Corasick도 가능하지만 본 문제 규모에선 현재 방식이 최적.

- **Problem Hint:**
 - "특수 조합은 하나의 문자로 센다" -> 길이 카운트 시 패턴 우선 매칭 필요.
 - "dz=" 존재 -> 가장 긴 패턴부터 확인해야 정답.

---

### BOJ 1316 - 그룹 단어 체커 (Group Word Checker)
- **Topic:** String | Hashing/Counting | Implementation
- **Folder:** `string/impl/`
- **Time Complexity:** O(Σ|S|)
- **Space Complexity:** O(1)

- **Key Idea:** 
 - 직전 문자(prev)와 현재 문자가 다를 때만 방문 배열(seen[26]) 확인.
 - 이미 등장한 적 있는 문자가 다시 나오면 그룹 단어가 아님.
 - `prev = -1`로 초기화해 첫 문자도 예외 없이 동일 로직 처리.

- **Caution:**
 - seen, prev, is_group는 매 단어마다 반드시 초기화.
 - 배열 초기화는 `{}`로 하면 전부 false로 세팅됨 (C++ 표준 보장).
 - 입력 문자열은 최소 1자 이상이므로 `s[0]` 접근 문제는 없지만, prev 방식이 더 일반적임.

- **Improvement:** 
 - `vector<int>(26)` 대신 `bool seen[26]{}` + `int prev=-1`로 의미를 분명히.

- **Problem Hint:** 
 - "같은 문자는 연속해서 나타나야 함" -> 구간이 끊겼다가 재등장하면 그룹단어가 아님.

---

### BOJ 1786 - 찾기 (Finding)
- **Topic:** String, KMP, Patteren Matching
- **Folder:** `string/kmp/`
- **Time Complexity:** O(|T| + |P|)
- **Space Complexity:** O(|P|)

#### 1) 문제 요약
- 문자열 T(텍스트)에서 P(패턴)가 등장하는 모든 시작 위치(1-based)를 구하라.
- 공백 포함 가능하므로 `getline`으로 입력. 출력은 개수 + 위치들.

#### 2) 핵심 알고리즘 - KMP (Knuth-Morris-Pratt)
- **아이디어:** 패턴 P의 "접두사이자 접미사"의 최대 길이를 각 위치 i에 대해 전처리한 배열 **LPS**(또는 π, failure function)로 만든다.
- **효과:** 불일치가 발생했을 때, 텍스트 인덱스는 되돌리지 않고 **패턴 인덱스 j만** `LPS[j-1]`로 점프하여 이미 일치한 접두사 길이를 재사용한다.

#### 3) LPS(π) 배열 만들기 (전처리: O(|P|))
- 정의: `LPS[i] = P[0...i]`의 **진접두사=진접미사**의 최대 길이.
- 구성 절차(직관):
    1. `i`를 1부터 증가, `j`는 "현재까지 맞춘 접두사 길이".
    2. `P[i] == P[j]`면 `++j; LPS[i]=j`.
    3. 불일치면 `j = LPS[j-1]`로 물러나며 다시 비교. `j==0`이면 `LPS[i]=0`.
    **불변식:** 루프 내내 `j`는 `P[0...i]`의 접두사=접미사 일치 길이.

```cpp
vector<int> LPS(m, 0);
for (int i = 1, j = 0; i < m; i++)
{
    while (j > 0 && P[i] != P[j]) j = LPS[j - 1];
    if (P[i] == P[j]) LPS[i] = j++;
}
```

#### 4) 텍스트 탐색 (O(|T|))
- `j`는 현재까지 P와 일치한 길이(=다음에 비교할 패턴 인덱스).
- `T[i]`를 보며:
    - 불일치: `while (j>0 && T[i]!=P[j]) j = LPS[j-1];`
    - 일치: `if(T[i]==P[j]) j++;`
    - `j==m`(전체 패턴 매치) -> **매치 시작 인덱스 = i - m + 1** 저장. 이어서 `j = LPS[j - 1]`로 되돌려 **겹치는 매치**도 탐색.

```cpp
vector<int> pos;
for (int i = 0, j = 0; i < n; i++)
{
    while (j > 0 && T[i] != P[j]) j = LPS[j - 1];
    if (T[i] == P[j]) j++;
    if (j == m)
    {
        pos.push_back(i - m + 1);   // 0-based
        j = LPS[j - 1];             // 겹치는 패턴 허용
    }
}
```

#### 5) 왜 맞는가? (직관적 증명 스케치)
- `j`는 항상 "T의 접미사 == P의 접두사" 길이를 보존.
- 불일치 시 j = LPS[j-1]로 점프 -> **텍스트 인덱스 i는 그대로** 두며, 이미 검사한 부분을 재검사하지 않고 **가능한 최장 일치 상태**로 복원.
- 최소한 한 칸은 전지하거나 j가 줄어들기만 하므로 전체가 **선형시간**.

#### 6) 구현 디테일 & 실수 포인트
- **입력**: 공백 포함 -> `getline` 사용. 직진 입력에서 개행이 남아있다면 `getline` 전에 `cin.ignore()` 필요. (지금 코드는 첫 줄부터 `getline`이라 OK)
- **빈 패턴**: m==0 처리 필요(코드에 이미 반영).
- **출력 1-based**: 저장은 0-based로 해도, 출력 시 `+1`.
- **성능**: `pos.reserve(예상매치수)`는 미세 최적화. 최악 P(|T|) 매치 수일 수 있음(예: `T="aaaaa...", P="aaa"`).
- **길이 vs 인덱스 혼동 주의**: LPS 값과 j는 **"길이"**임. 길이가 j라면 최근 일치 구간의 마지막 인덱스는 j-1.
- **reserve 안전성**: 일반적으로 n < m일 경우 `(n - m + 1)`이 음수 -> size_t 변환 시 언더플로 위험
 - 하지만 본 문제 지문에서 **n >= m 보장**이 있으므로 현재 코드에선 안전.
 - 실무/범용 코드라면 `reserve(max(0, n-m+1))`처리 권장.

#### 7) 대안/확장
- **Z-Algorithm**: 텍스트에 `P + '#' + T`를 이어 붙여 Z배열로 매치 위치 판정. 구현은 간단, 하지만 KMP와 성능 동급.
- **경로 복원이 필요한 문제**(여기선 불필요): 없음. KMP는 위치만 알면 충분.

#### 8) 예제 워크스루(요약)
- `T = "ABABABA", P = "ABA"`
- `LPS = [0,0,1]`
- 탐색 중 두 번 매치 후 `j = LPS[j-1]`로 1로 되돌려 **겹치는 매치**를 이어서 탐색 -> 위치: 0, 2, 4 (0-based)

---

## 📅 2025-09-24
**BOJ 2577 - 숫자의 개수**
**BOJ 4344 - 평균은 넘겠지**
**BOJ 12015 - 가장 긴 증가하는 부분 수열 2**

### BOJ 2577 - 숫자의 개수 (Number of Occurrences)
- **Topic:** Implementation | String Conversion | Frequency Counting
- **Folder:** `impl/`
- **Time Complexity:** O(log(val))
- **Space Complexity:** O(1)

- **Key Idea:**
 - 세 수의 곱을 구한 뒤 문자열로 반환.
 - 각 문자 `c`에서 `c - '0'`으로 인덱스를 구해 freq[10] 배열에 카운트.
 - 결과를 0~9 순서로 출력.

 - **Caution:**
  - 문제 조건: A, B, C <= 1000 -> 최댓값 10^9 -> int로 충분.
  - 문자열 변환 대신 수학적으로 자리수를 직접 세는 방법도 가능.
  - freq 배열은 반드시 초기화.

- **Improvement:**
 - 지금 문제 조건에서는 int로 충분 -> long long 필요 없음
 - 다른 환경/확장 문제라면 long long 고려.

- **Problem Hint:**
 - 세 수의 곱의 각 자리수를 카운트.
 - "0~9까지 각 숫자가 몇 번 쓰였는가" 그래도 출력.

---

### BOJ 4344 - 평균은 넘겠지 (Above Average)
- **Topic:** Implementation | Arithmetic | Output Formatting
- **Folder:** `impl/`
- **Time Complexity:** O(N)
- **Space Complexity:** O(N)

- **Key Idea (중요):** 
 - '평균 **초과**' 판정은 정수 나눗셈으로 정확히 가능.
 - 평균 = k + frac, `sum/n`은 k(내림) → `i > 평균` ⇔ `i ≥ k+1` ⇔ `i > sum/n`
 - 따라서 `if (i > sum / n)`은 논리적으로 맞음(부동소수 비교 불필요)
 - 비율 = (cnt/n) x 100.
 - 소수점 셋째 자리까지 출력 -> `fixed << setprecision(3)` + `%`.

- **Caution:**
 - 평균 계산 시 int 나눗셈 사용 -> avg가 내림 처리됨.
    -> 문제 조건에선 정답에 영향 없지만, 더 엄밀히 하려면 double avg = sum / (double)n.
 - 출력은 반드시 반올림 처리, setprecision과 fixed를 동시에 사용해야 함.
 - 출력 끝의 `%`를 반드시 붙여야 함.

- **Improvement:** 
 - `fixed << setprecision(3)`로 자동 반올림 -> `round` 불필요. `setprecision`함수는 `#include <iomanip>`에 존재.
 - sum도 long long으로 두면 점수가 많을 때 안전(문제 제한에서는 int로 충분).

- **Problem Hint:**
 - "평균 초과 비율"만 구한다 -> 평균과 같거나 작은 학생은 제외.
 - 출력은 % 기호 포함.

---

### BOJ 12015 - 가장 긴 증가하는 부분 수열 2 (Longest Increasing Subsequence 2)
- **Topic:** DP | Binary Search | LIS
- **Folder:** `dp/lis/`
- **Time Complexity:** O(N log N)
- **Space Complexity:** O(N)

- **Key Idea:** 
 - 길이별 최소 꼬리값 유지 + `lower_bound` 교체.
 - 배열 크기가 LIS 길이.
 - LIS 배열 = "해당 길이를 가지는 LIS의 ㅊ최적 꼬리값".
 - 원소 x 처리:
  - x > LIS.back() -> push_back
  - else -> `*lower_bound(LIS.begin(), LIS.end(), x) = x

- **Caution:**
 - strictly increasing 조건이므로 lower_bound 사용.
 - upper_bound를 쓰면 "같은 값 포함"으로 잘못된 결과 나옴.
 - LIS 수열 자체를 출력하는 문제면 추적 배열을 따로 관리해야 함.

- **Improvement:** 
 - 입력 스트리밍 처리로 메모리 절약 가능(`vector<int> a` 불필요).
 - n이 매우 큰 경우 reserve(n)으로 메모리 재할당 방지 가능(미세 최적화).
 - 값 범위가 작으면 세그먼트 트리/펜윅트리로도 O(N log N) 풀이 가능.

- **Problem Hint:**
 - "길이만 구한다" -> 수열 복원 필요 없음.
 - n ≤ 1,000,000 규모로 O(N^2) 불가 -> 이분 탐색 유도.

---

## 📅 2025-09-25
**BOJ 2947 - 나무 조각**
**BOJ 1213 - 팰린드롬 만들기**
**BOJ 9252 - LCS 2**

### BOJ 2947 - 나무 조각 (Wooden Pieces)
- **Topic:** Implementation | Simulation | Bubble sort (adjacent swap printing)
- **Folder:** `impl/simulation/`
- **Time Complexity:** O(n^2) (n=5 -> 상수라 사실상 매우 작음)
- **Space Complexity:** O(1)

- **Key Idea:**
 - 인접한 두 원소를 비교하고, 앞이 더 크면 swap.
 - swap 발생 시 배열 상태를 즉시 출력
 - 전체가 정렬될 때 까지 반복.

- **Caution:**
 - 스왑이 없으면 출력하지 않음(불필요 출력 금지).
 - 출력 형식: 숫자 사이 공백, 스왑 1회마다 개행.
 - 같은 패스에서 여러 번 스왑이 가능하니, 스왑 직후 바로 출력하는 위치가 맞아야 함.

- **Improvement:**
 - 범위 기반 for에서 루프 변수명이 바깥 루프의 `i`와 겹치므로 `x`같은 이름을 쓰면 가독성↑ 
 - 마지막 원소 뒤 공백 제거하는 출력 포맷도 고려 가능.
 - `return 0;` 명시적 종료 추가하면 더 깔끔.
 - 미세 최적화로는 바깥 루프에서 "이번 패스에 스왑 발생 여부 플래그"로 종료 해도 되지만, N=5라 현재 방식이 가장 간단·안전.

- **Problem Hint:**
 - 입력은 항상 1..5의 순열 -> 스왑 횟수 최대 10회 정도.
 - "스왑이 일어날 때만" 출력하는 것이 핵심.

---

### BOJ 1213 - 팰린드롬 만들기 (Make Palindrome)
- **Topic:** String | Counting | Palindrome Construction
- **Folder:** `string/impl/`
- **Time Complexity:** O(n + 26)
- **Space Complexity:** O(26)

- **Key Idea:**
 - 빈도 배열을 만들고, 홀스 빈도 문자가 2개 이상이면 불가능.
 - 홀수 문자가 1개면 그 문자를 가운데에 1개 배치하고 나머지는 짝수로 맞춤.
 - 짝수 개수의 절반을 사전순(오름차순)으로 앞 절반에 쌓고, 남은 절반을 역순(내림차순)으로 붙여 팰린드롬 완성

- **Caution:**
 - 가운데 문자를 하나 할당하면 freq를 1 줄여서 양쪽 대칭이 맞게 해야 함.
 - 불가능할 때 출력은 반드시 `"I'm Sorry Hansoo\n"`.
 - 문제에서 "사전순" 조건이 있으므로 반드시 A->Z 순으로 왼쪽 절반을 만들어야 함.

- **Improvement:**
 - 절반을 만드는 루프: `while`로 1개씩 감소시키는 대신 `ans.append(cnt/2, ch)`가 간결·빠름.
 - 출력 끝에 `'\n'` 추가(일관된 포맷).
 - 변수 네이밍: `v` -> `cnt`, `mx` -> `MX` 등 의미 드러내기.
 - `pal.reserve(n)`으로 메모리 최적화 가능.
 - `vector<int>` 대신 `array<int, 26>`이나 고정 배열 사용 시 약간 빠를 수 있음.
 
- **Problem Hint:**
 - 팰린드롬은 가운데를 기준으로 좌우 빈도 대칭이 필요 -> 홀수 문자는 최대 1개.
 - 사전순 요구 없음(유효한 팰린드롬이면 정답).

---

### BOJ 9252 - LCS 2 (Longest Common Subsequence with reconstruction)
- **Topic:** String | DP | LCS
- **Folder:** `dp/lcs/`
- **Time Complexity:** O(n*m)
- **Space Complexity:** O(n*m)

- **Key Idea:**
 - 표준 LCS DP(2차원 DP)로 길이를 구한 뒤, 끝에서 시작해 역추적하며 일치 문자를 모은다.
 - 뒤에서 앞으로 쌓이므로 최종 문자열은 `reverse`로 뒤집어 출력.

- **Caution:**
 - **길이 0일 때 문자열 줄 출력 금지**(빈 줄 X).
 - 인덱스 오프셋(s1[i-1], s2[j-1]) 헷갈리지 않기.
 - tie-break는 임의 허용이지만, 일관되게 유지.

- **Improvement:**
 - 필수 : `reverse(ans.begin(), ans.end());` 후 출력
 - `ans.reserve(lcs[n][m])`로 재할당 감소.
 - tie 시 방향 규칙 고정(`>=`로 위 우선 등)하면 결과가 안정적.
 - 메모리 절약이 필요하다면 1D DP + parent(방향) 기록으로 복원 또는 경로만 저장하는 방식 고려.
 - 입출력 많은 경우 `'\n'` 사용 유지.

- **Problem Hint:**
 - 9251(길이)와 달리 9252는 **문자열 복원**이 요구됨 -> parent 테이블 또는 역추적 로직 필수.
 - "임의의 LCS" 허용 -> 복원 경로는 한 가지면 충분.
 - 길이가 0이면 문자열 출력 생략.

---

## 📅 2025-09-26
**BOJ 5430 - AC**
**BOJ 1966 - 프린터 큐**
**BOJ 10986 - 나머지 합**

### BOJ 5430 - AC (수열 뒤집기/삭제)
- **Topic:** Implementation | Deque Simulation | Two-Pointer | String Parsing
- **Folder:** `impl/simulation/`
- **Time Complexity:** O(|p| + n)
- **Space Complexity:** O(n)

- **Key Idea:**
 - 입력 배열을 문자열에서 숫자 누적 파싱으로 복원.
 - `R`은 불리언 토글만, `D`는 left/right 포인터만 이동 -> 실제 reverse/pop 없음.
 - 최종 구간을 토글 상태에 따라 정/역순으로 출력.

- **Caution:**
 - 빈 배열 입력 시에도 올바르게 파싱 후 처리 (`[]`).
 - 구분자(,) 출력 위치 조건: 마지막 원소 뒤엔 붙이지 않음.

- **Improvement:**
 - 파싱 루프 종료 후 `if (in_num) num.push_back(val);` 추가 시 형식 변동에도 견고. ']'로 끝나지 않고 숫자로 끝나는 입력일 때를 말하는 것 같음. 이 문제에서는 안나옴.
 - `num.reserve(n)`로 재할당 최소화(미세 최적화).
 - 출력 시 콤마는 인덱스로 제어(조건 연산자/if로 첫 요소 제외 후 콤마).
 - 출력 부분을 람다 함수나 `ostringstream`로 모듈화하면 코드가 더 깔끔해짐.
  - 람다 함수 -> `auto printRange = [&](int a, int b, int step) {...};`

- **Problem Hint:**
 - 빈 배열(`[]`)과 `D` 초과 호출이 핵심 코너케이스.
 - reverse를 실제로 하지 말고 인덱스로만 처리해야 시간 초과를 피함.

---

### BOJ 1966 - 프린터 큐 (Printer Queue)
- **Topic:** Queue | Counting | Simulation
- **Folder:** `queue/simulation/`
- **Time Complexity:** O(O * P) (P=10 -> 상수), 사실상 O(N)
- **Space Complexity:** O(N)

- **Key Idea:**
 - 큐는 `(원래 인덱스, 중요도)`로 구성해 목표 문서를 식별.
 - 중요도 카운트 배열로 "더 높은 중요도 존재 여부"를 빠르게 확인.
 - 더 높은 게 있으면 회전, 아니면 출력 확정. 출력 시에만 `cnt++`

- **Caution:**
 - prio 감소는 **실제 출력이 일어났을 때만** 수행(현재 코드 OK).
 - mx_prio는 `while (prio[mx_prio]==0) mx_prio--;`로 항상 최신화.
 - 입력 우선순위가 0은 주어지지 않지만, prio 배열은 편의상 크기 10 사용.

- **Improvement:**
 - 현재 최대 중요도를 가리키는 포인터(예: `curMax`)를 유지하면 매 스텝 9칸 확인도 생략가능. 카운트가 0이면 `curMax--`로 갱신.
 - `queue<pair<int, int>>` 대신 `struct Doc{int idx, prio;};`로 의미를 드러내면 가독성↑
 - I/O 많을 때는 `'\n'` 사용 유지(이미 잘 되어 있음).
 - `cnt` 의미 주석("누적 인쇄 개수") 추가하면 흐름 파악이 빨라짐.
 - `emplace` / `{i, p}` 초기화로 간결화.
 - (선택) 케이스별 초기화 의도를 드러내는 `priority.assign(10,0)` 사용.

- **Problem Hint:** 
 - "같은 중요도"는 입력 순서(FIFO)가 유지돼야 함 -> 큐로 자연스레 보장.
 - 정답은 "내 목표 문서가 **몇 번째로 인쇄되는가**"에 해당하는 `cnt`.
 - 최대 우선순위만 보면 되므로 우선순위 큐 없이도 **빈도표 + 큐**로 해결 가능.

---

### BOJ 10986 - 나머지 합 (Remainder Sum)
- **Topic:** Prefix Sum | Counting | Combinatorics
- **Folder:** `prefix/counting/`
- **Time Complexity:** O(n + m)
- **Space Complexity:** O(m)

- **Key Idea:**
 - prefix 누적합의 나머지를 관리.
 - num[0] = 1로 시작 -> [0..i] 구간 자동 포함.
 - 매 스텝마다 cnt += num[res]; num[res]++ 로 동일 나머지 쌍 개수를 누적.

 **Caution:**
  - `cnt`와 `num`은 반드시 **long long** -> 조합 수가 최대 nC2 크기.
  - 변수 이름 `val`은 실제로 입력값이 아니라 누적 나머지를 담고 있어서 혼동 우려 -> `res`같은 이름으로 바꾸는 게 가독성에 좋음.
  - 입력이 크더라도 `(res + x)%m` 계산은 오버플로우 걱정 없음 (x ≤ 10^9, res < m).
  - `num[0] = 1` 초기화 없으면 `[0..i]` 구간이 누락됨 -> 실수 주의.
 
- **Improvement:**
 - 변수 네이밍: prev/res 대신 cur 등 일관성 있는 이름으로 단순화.
 - 코드 가독성을 위해 "누적 나머지" 변수 하나만 사용.
 - 입출력 많을 땐 `'\n'` 유지(이미 적용). 필요 시 `cout.tie(nullptr)`도 고려(미세).

- **Problem Hint:**
 - 같은 나머지끼리 짝을 지으면 그 차가 m의 배수.
 - 조합 공식을 따로 돌릴 필요 없이 루프에서 점진적으로 처리 가능.

---

## 📅 2025-09-29
**BOJ 9086 - 문자열**
**BOJ 1543 - 문서 검색**
**BOJ 17609 - 회문**

### BOJ 9086 - 문자열 (String)
- **Topic:** String | Implementation
- **Folder:** `string/impl/`
- **Time Complexity:** O(|s|)
- **Space Complexity:** O(1)

- **Key Idea:**
 - 문자열의 맨 앞(`s.front()`)와 맨 뒤(`s.back()`)를 출력.
 - 문자열 길이가 1이면 같은 문자가 두 번 출력됨.

- **Caution:**
 - `s.front()`와 `s.back()`은 내부적으로 첫/마지막 원소 참조.
 - 문자열이 비어있을 수 없으므로(문제 보장), 접근 안전.
 - 문자열 길이가 큰 경우에도 시간복잡도는 입력 읽기 O(|s|)가 전부.

- **Improvement:**
 - C++11 이전이라면 `s[0]`과 `s[s.size()-1]`로 처리.
 - 입출력 속도가 문제될 정도는 아니지만, `ios::sync_with_stdio(false)`와 `cin.tie(nullptr)`는 유지.

- **Problem Hint:**
 - 문자열 길이에 관계없이 앞뒤 문자만 출력하면 된다.

---

### BOJ 1543 - 문서 검색 (Document Search)
- **Topic:** String | Scanning | Non-overlapping Match
- **Folder:** `string/two-pointers/`
- **Time Complexity:** O(N*M)
- **Space Complexity:** O(1)

- **Key Idea:**
 - 텍스트 T에서 패턴 P를 왼쪽부터 탐색.
 - 인덱스 `i`만 관리하면서 `t.substr(i, m) == p`를 검사.
 - 일치 시 `cnt++`, `i += m`로 건너뛰기(겹침 금지).
 - 불일치 시 `i++`로 한 칸 전진.
 - `substr` 비교 또는 `find` 활용으로 구현 가능.

- **Caution:**
 - 겹침을 허용하지 않으므로 매치 직후 `i`를 **m만큼** 이동해야 함.
 - `substr(i,m)는 뒤에 남은 길이가 m보다 작아도 안전하지만, 불필요한 문자열 객체 생성이 발생 -> 성능 이슈.
 - `find` 반복문은 반드시 `(pos = t.find(p,pos))`처럼 대입식을 써야 올바른 위치로 전진 가능.
 - 입력은 `getline`으로 두 줄을 바로 받으므로 추가 `ignore()` 불필요(선행 `>>`가 없다는 전제에서).

- **Improvement:**
 - `substr` 생성 비용을 줄이려면 수동 비교:

  ``` cpp
  bool ok = true;
  for (int k = 0; k < m; k++) if (t[i+k] != p[k]) { ok = false; break; }
  if(ok) { cnt++; i += m; } else i++;
  ```

 - 또는 `string::npos; pos += p.size()) cnt - 또는 `string::find`를 이용해 더 간결하게:

  ``` cpp
  for (size_t pos = 0; (pos = t.find(p, pos)) != string::npos; pos += p.size()) cnt++;
  ```

 (자동으로 겹치지 않게 `pos += p.size()`로 전진)
 - 입출력 최적화는 이미 적용되어 있음.

- **Problem Hint:**
 - "겹치지 않게" 세는 케이스: `t="aaaa"`, `p="aa"` -> 답은 2 (인덱스 0, 2).

---

### BOJ 17609 - 회문 (Palindrome / Pseudo-Palindrome)
- **Topic:** String | Two Pointers
- **Folder:** `string/two-pointers/`
- **Time Complexity:** O(n)
- **Space Complexity:** O(1)

- **Key Idea:**
 - 투 포인터로 진행하다가 첫 불일치에서만 분기.
 - `[i+1, j]` 또는 `[i, j-1]` 중 하나라도 팰린드롬이면 1, 둘 다 아니면 2.
 - 끝까지 불일치가 없으면 0.

- **Caution:**
 - 보조 검사에서 `else k++; l--;`처럼 중괄호 없이 쓰면 `l--`가 항상 실행되는 버그 발생 -> 반드시 블록으로 묶기(지금 코드는 수정 OK).
 - 첫 불일치에서 이미 답이 정해지므로 **즉시 출력 후 종료**하면 깔끔함(현재는 break 후 `is_pal`로 0만 체크 -> 동작상 문제 없음).
 - 인덱스 범위는 `[i+1, j]`, `[i, j-1]`로 정확히 설정(현재 코드 OK).
 - 길이 0/1도 정상 동작해야 함(현재 로직은 `while (i < j)`라 안전).

- **Improvement:**
 - 의미 명확성을 위해 보조 함수를 쓰면 가독성↑:
  ```cpp
  bool isPal(const string& s, int l, int r)
  {
    while(l < r) if (s[l++] != s[r--]) return false;
    return  true;
  }
  // if (!isPal(s, i+1, j) && !isPal(s, i, j-1)) cout << 2; else cout << 1;
  ```
 - 사용하지 않는 변수(`cnt`)는 제거.
 - 보조 함수를 `const string&`로 받도록 수정(`const`로 불변성 명확).
 - 네이밍 일관화(`isPalindrome`)로 가독성 향상.

- **Problem Hint:**
 - "최대 한 글자 삭제 허용" -> "첫 번째 불일치"만 잘 처리하면 된다 -> 이후는 결과가 고정.

---

## 📅 2025-09-30
**BOJ 11654 - 아스키 코드**
**BOJ 5525 - IOIOI**
**BOJ 16916 - 부분 문자열**

### BOJ 11654 - 아스키 코드 (ASCII Code)
- **Topic:** Implementation | ASCII | Type Casting
- **Folder:** `impl/type-casting`
- **Time Complexity:** O(1)
- **Space Complexity:** O(1)

- **Key Idea:**
 - 문자 하나를 입력받아 정수형으로 캐스팅해 ASCII 값을 출력한다.

- **Caution:**
 - `cin >> c`는 공백/개행을 무시하므로 공백 문자를 다뤄야 하는 변형 문제에서는 `cin.get(c)` 사용.
 - 일부 환경에서 `char`가 signed일 수 있어 확장 아스키(>127) 입력 시 음수가 나올 수 있음.
 - 출력 시 `endl` 대신 `"\n"` 사용이 성능상 유리.

- **Improvement:**
 - 입출력 실패 대비 `if(!(cin>>c)) return 0;` 체크.
 - 확장 입력 대비 `static_cast<int>(static_cast<unsigned char>(c))`로 승격해 음수 가능성 제거.

- **Problem Hint:**
 - 입력은 정확히 한 글자이며 공백은 주어지지 않는다.

---

### BOJ 5525 - IOIOI (IOIOI)
- **Topic:** String | Pattern Counting
- **Folder:** `string/kmp/`
- **Time Complexity:** O(M)
- **Space Complexity:** O(1)

- **Key Idea:**
 - 본문을 한 번 순회하며 `"IOI"`를 찾을 때마다 `streak++`
 - `sterak >= n`일 때마다 `cnt++` -> 겹침 패턴 자동 반영

- **Caution:**
 - 경계: `i + 1 < m`에서만 3글자 접근
 - 전진 규칙: 매칭 `i += 2`, 불일치 `i++`

- **Improvement:**
 - 입력 `m` 대신 `s.size()` 사용 권장(안정성)
 - 루프 조건을 의도대로 표현해 가독성↑

- **Problem Hint:**
 - 연속 `"IOI"` 길이가 `k`이면, 해당 구간 기여는 `max(0, k - n + 1)`

---

### BOJ 16916 - 부분 문자열 (Substring)
- **Topic:** String | KMP
- **Folder:** `string/kmp/`
- **Time Complexity:** O(N + M)
- **Space Complexity:** O(M)

- **Key Idea:**
 - 패턴 P의 LPS(π)로 접두/접미 정보를 선계산.
 - 본문 T를 순회하며 불일치 시 `j = lps[j-1]`로 **같은 i에서 재비교** -> 텍스트는 한 번씩만 읽음.
 - 일치 시 `++j`, `j==M`이면 존재(1) 출력 후 종료.

- **Caution:**
 - `while(j>0 && t[i]!=p[j]) j = lps[j-1];`를 **비교 전에** 실행해 i를 증가시키지 않고 j만 조정.
 - 매치 분기에서 `j++` 누락 금지(전진 정지/미탐 발생).
 - LPS 구축도 동일 원리: 불일치마다 while로 j를 당겨 O(M) 유지.
 - 나이브/`find` 반복은 데이터에 따라 TLE 가능.

- **Improvement:**
 - 배열명 `lps` 사용 등 의미 있는 네이밍.
 - 조기 매칭 시 `cout << 1 << '\n'; return 0;`로 정상 종료 일관화.
 - I/O는 `'\n'` 사용으로 불필요한 flush 방지.

- **Problem Hint:**
 - 존재 여부만 판단하면 되므로 첫 매칭을 찾는 즉시 종료 가능.
 - KMP 골격: **buildLPS -> scan** (불일치 while 백트랙, 일치 시 j++).

---

## 📅 2025-10-01
**BOJ 10828 - 스택**
**BOJ 4949 - 균형잡힌 세상**
**BOJ 17298 - 오큰수**

### BOJ 10828 - 스택 (Stack)
- **Topic:** Stack | Implementation
- **Folder:** `stack/basic/`
- **Time Complexity:** O(Q)
- **Space Complexity:** O(Q)

- **Key Idea:**
 - `vector<int>`로 스택 기능을 직접 매핑하고, 각 명령에 맞는 값을 즉시 출력.
 - 빈 스택 예외 처리를 명확히 분기(pop/top = -1, empty = 1/0).

- **Caution:**
 - 출력 개수/순서가 스펙과 정확히 일치해야 함(특히 push는 출력 없음).
 - `size()`는 정수로 출력, `\n`로 개행(endl 금지).

- **Improvement:**
 - **[현재 코드에 존재하지만 성능상 더 나은 대안]** `"\n"` 대신 `'\n'`로 통일하면 미세하게 가벼움.
 - **[현재 코드에 없음 / 선택]** 매우 큰 출력에서 누적 버퍼(예: 문자열에 모아 한 번에 출력) 사용 시 I/O 마진이 조금 더 넉넉해짐(이 문제에선 필수 아님).

- **Problem Hint:**
 - 각 연산은 암묵적 O(1) amortized이며, `reserve(Q)`로 재할당을 줄여 안정적인 수행 보장.

---

### BOJ 4949 - 균형잡힌 세상 (Balanced World)
- **Topic:** Stack | Parsing
- **Folder:** `stack/brackets/`
- **Time Complexity:** O(L) per line
- **Space Complexity:** O(L)

- **Key Idea:**
 - 한 줄씩 읽어 괄호만 대상으로 스택 검사: 여는 괄호 push, 닫는 괄호는 empty 체크 -> 종류 매칭 후 pop.
 - 라인 종료 시 `is_balanced && stack.empty()`이면 "yes", 아니면 "no".

- **Caution:**
 - 입력 종료 라인은 `"."` 단독이어야 하며 출력 없음.
 - 닫는 괄호에서 언더플로 방지(먼저 empty 확인).

- **Improvement:**
 - **[현재 코드에 존재]** 기능은 충분히 정답. 가독성을 위해 `stack<char>`로 바꾸는 대안이 좋다.
 - **[현재 코드에 존재]** `"\n"` 대신 `'\n'` 사용은 미세 최적화(필수 아님).
 - **[현재 코드에 없음]** 라인 내 `'.'`을 만나면 즉시 순회 중단하는 조기 종료(마이크로 최적화).

- **Problem Hint:**
 - 입력은 **여러 줄**이고, 각 줄마다 **독립적으로** 균형을 판단한다.
 - **괄호 외 문자는 전부 무시**한다(공백, 알파벳, 마침표 포함).
 - **종료 조건**: 한 줄이 **정확히 `"."`**일 때 전체 입력을 끝낸다(출력 없음).
 - **즉시 실패 규칙**: 닫는 괄호를 만났는데 스택이 비어 있거나 종류가 다르면 그 줄은ㅇ `no`.
 - **최종 조건**: 줄을 다 돈 뒤 스택이 **비어 있어야** `yes` (열린 괄호가 남아 있으면 `no`).

---

### BOJ 17298 - 오큰수 (Next Greater Element)
- **Topic:** Stack | Monotonic Stack
- **Folder:** `stack/monotonic/`
- **Time Complexity:** O(N)
- **Space Complexity:** O(N)

- **Key Idea:**
 - 왼->오로 보며 인덱스 스택을 유지(값은 내림 단조).
 - 매 i에서 `while stack not empty and A[i] > A[stack.top]`:
  - `ans[stack.top] = A[i]` 후 pop
 - 그 뒤 i를 push. 끝나면 남은 인덱스는 이미 `-1`

- **Caution:**
 - **동등값은 미포함** -> 비교는 `>` 사용.
 - 스택에는 **인덱스** 저장(중복값 처리가 간단).

- **Improvement:**
 - 출력이 매우 크면 `ostringstream` 등으로 **뻐퍼링 출력** 후 한 번에 찍어 I/O 오버헤드 감소.
 - 오른쪽->왼쪽 변형도 가능(스택에는 "현재보다 큰 후보"만 유지) - 학습용으로 패턴 대비에 유용.

- **Problem Hint:**
 - "다음/이전 + 큰/작은 + 가장 가까운" 형태가 보이면 단조 스택을 떠올리기.
 - 각 인덱스는 최대 **1 push + 1 pop**만 수행 -> O(N) 직관 확보.
 - 엣지 케이스:
  - 내림차순: 전부 `-1`
  - 동일값 나열: 전부 `-1`
  - 오름차순: 각 원소의 오큰수는 바로 다음 원소

---

## 📅 2025-10-02
**BOJ 9012 - 괄호**
**BOJ 2504 - 괄호의 값**
**BOJ 1935 - 후위 표기식2**

### BOJ 9012 - 괄호 (Parentheses)
- **Topic:** Stack | Parsing
- **Folder:** `stack/brackets/`
- **Time Complexity:** O(L) per test case
- **Space Complexity:** O(L) (stack), O(1) (counter alternative)

- **Key Idea:**
 - `'('`는 push, `')'`는 스택 비었는지/짝 일치 확인 후 pop.
 - 라인 종료 시 스택이 비어 있어야 YES.

- **Caution:**
 - 케이스마다 스택/플래그 초기화.
 - 중간에 빈 스택에서 `')'`가 나오면 즉시 NO.

- **Improvement:**
 - 스택 대신 **balance 정수**(증감만)로 판정 가능 -> 메모리/상수항 절약.

- **Problem Hint:**
 - "중간 음수 금지, 최종 합 0"이 VPS의 본질.
 - 테스트: `()()`->YES, `(()`->NO, `())`->NO, `((()))`->YES.

---

### BOJ 2504 - 괄호의 값 (Value of Brackets)
- **Topic:** Stack | Parsing | Evaluation
- **Folder:** `stack/evaluation/`
- **Time Complexity:** O(L)
- **Space Complexity:** O(L)

- **Key Idea:** 
 - 스택은 괄호 짝만 검증, 값 계산은 `mul`(중첩 계수)과 `val`로 분리.
 - 여는 괄호에서 `mul`을 곱하고, 닫는 괄호에서 **바로 닫힘이면 `val += mul`**후 **반드시 `mul`을 되돌림**
 
- **Caution:**
 - 진행 중 불일치(스택 비었거나 종류 불일치) 시 즉시 `0`.
 - 종료 시 스택이 비어 있어야 정답, 아니면 `0`.
 - 플래그는 여는 순간 `true`, 닫는 순간 사용 후 `false`로 명확히 관리.

- **Improvement:**
 - 가독성: 닫힘 처리에서 `pop -> (필요 시) val += mul -> mul 되돌리기` 순서로 정리하면 읽기 수월.
 - 입력 길이가 매우 클 수 있으면 `mul/val`을 `long long`로 여유 있게 잡는 선택 가능.
 
- **Problem Hint:**
 - 규칙 요약: `()`=2, `[]`= 3, 인접은 합, 중첩은 곱.
 - 불변식: **여는 때 x / 닫는 때 (바로 닫힘이면 +) -> /**.
 - 체크 케이스: `([])=6`, `()[[]]=11`, `[]()=5`, `[()[[]]]=33`.

---

### BOJ 1935 - 후위 표기식2 (Postfix Evaluation 2)
- **Topic:** Stack | Postfix Evaluation
- **Folder:** `stack/postfix/`
- **Time Complexity:** O(L)
- **Space Complexity:** O(N)

- **Key Idea:**
 - `A..Z`를 입력한 값 배열에 매핑하고, 후위식을 순회하며 숫자 스택으로 평가.
 - 연산자에서는 스택에서 두 값을 꺼내 `좌항 op 우항` 순서로 계산 후 다시 push.
 - 마지막에 스택에 남는 하나의 값이 결과 -> `fixed`, `setprecision(2)`로 출력.

- **Caution:**
 - pop 순서 주의: `tmp1 = top()`(우항) -> pop -> `tmp2 = top()`(좌항) -> pop -> `tmp2 op tmp1`.
 - 출력 포맷 오차 방지: `fixed << setprecision(2)`.
 - 입력이 정상이라면 스택 최종 크기는 1이어야 한다.

- **Improvement:**
 - 연산자 처리 전에 **스택 크기 >= 2**인지 한 번에 검사하면 가독성↑.
 - `case '/'`에서 불필요한 캐스팅 제거 가능(이미 double).
 - (선택) 종료 전 스택 크기 확인으로 방어적 체크 추가.

- **Problem Hint:**
 - 후위식은 스택으로 자연스럽게 평가된다 - 피연산자 push, 연산자면 두 개 pop하여 계산.
 - 테스트 예: `AB+C*`는 `(A+B)*C`와 동일하게 계산되어야 한다.

---

## 📅 2025-10-03
**BOJ 10773 - 제로**
**BOJ 11866 - 요세푸스 문제 0**
**BOJ 15828 - Router**

### BOJ 10773 - 제로
- **Topic:** Stack | Implementation
- **Folder:** `stack/basic/`
- **Time Complexity:** O(K)
- **Space Complexity:** O(K)

- **Key Idea:**
 - 값이 0이면 최근 값을 취소(pop), 그 외엔 push하여 전체 과정을 스택으로 시뮬레이션.
 - 최종적으로 스택에 남은 값들의 합을 출력.

- **Caution:**
 - 합과 스택 원소는 `long long`으로 처리해 오버플로 여유 확보.
 - (방어) `pop`전 `empty()` 체크를 넣으면 안정성 증가. (문제에서는 무조건 있다고 하니 상관 없을듯)

- **Improvement:**
 - 입력 처리 중에 `sum`을 동시 갱신하면 마지막 합산 루프 제거 가능.

- **Problem Hint:**
 - "되돌리기/취소" 동작은 스택 패턴의 신호. push/pop으로 그대로 구현하면 된다.

---

### BOJ 11866 - 요세푸스 문제 0 (Josephus Problem 0)
- **Topic:** Queue | Simulation
- **Folder:** `queue/josephus/`
- **Time Complexity:** O(N*K)
- **Space Complexity:** O(N)

- **Key Idea:**
 - 1..N을 큐에 넣고, `cur`로 K를 세며 K번째마다 `pop`하여 결과에 저장.
 - K가 아닐 때는 `front`를 `push`로 뒤로 보내어 원형을 시뮬레이션.

- **Caution:**
 - 출력 형식: `"<a, b, c>"` (마지막 원소 뒤엔 콤마 없음, 개행 추가 권장).
 - `cur`는 K에 도달하면 0으로 리셋하여 다시 카운트.

- **Improvement:**
 - `josephus.reserve(n)`으로 재할당 최소화.
 - 대체 표현: 반복 내부에서 `k-1`회 회전 후 즉시 pop -> 가독성↑.

- **Problem Hint:**
 - "원형 + K번째 제거"는 큐로 자연스럽게 풀린다.
 - 검증 예: `n=7, k=3 -> <3, 6, 2, 7, 5, 1, 4>`.

---

### BOJ 15828 - Router
- **Topic:** Queue | Simulation
- **Folder:** `queue/simulation/`
- **Time Complexity:** O(M)
- **Space Complexity:** O(N)

- **Key Idea:**
 - 입력 스트림을 읽으며 `-1`이면 종료, `0`이면 비어있지 않을 때 pop, 양수면 `size < N`일 때만 push.
 - 종료 후 큐가 비어 있으면 `"empty"`, 아니면 front부터 공백으로 구분해 출력.

- **Caution:**
 - 버퍼가 꽉 찼을 때의 패킷은 **드롭**.
 - 빈 큐에서의 pop 요청(0)은 **무시**.
 - 스트림 기반 루프로 입력 끝/종료 토큰 처리.

- **Improvement:**
- `(int)q.size()` 캐스팅 제거 -> `q.size() < n`.
- 출력 마지막에 `'\n'` 추가.

- **Problem Hint:**
 - "고정 크기 버퍼" 시뮬레이션 문제: 큐 연ㄴ산(push/pop)과 드롭 규칙만 정확히 지키면 된다.

---

## 📅 2025-10-05
**BOJ 1874 - 스택 수열**
**BOJ 1406 - 에디터**

### BOJ 1874 - 스택 수열 (Stack Sequence)
- **Topic:** Stack | Simulation | Invariant-Driven
- **Folder:** `stack/sequence`
- **Time Complexity:** O(N)
- **Space Complexity:** O(N)

- **Key Idea:**
 - **사후조건 우선**: 각 입력 `val` 처리 후에는 `stk.top() == val`이어야 pop이 가능하고, 아니면 불가능.
 - 이를 보장하려면 **단조 변수 `j`를 `val`까지 밀어넣는 것**이 전부다 -> `while (j <= val) push(j++);`.
 - 이렇게 하면 스택 상태(비었는지/작은지) 같은 부수 분기에 의존하지 않아 **검증이 쉬워지고** 반례 설계가 간단해진다.

- **Caution:**
 - `j`는 1..N에서 **단조 증가**하고, **중복 push불가**.
 - `j > val`인데 `top != val`이면 더 이상 push할 수 없으니 **즉시 "NO"**.
 - 로그는 `2*N` 길이까지 커질 수 있으므로 `vector<char>`에 기록 후 한 번에 출력.

- **Improvement:**
 - `v.reserve(2*N);`로 로그 벡터 재할당 최소화.
 - 디버깅시 `assert(1 <= j && j <= n + 1);` 같은 **단조성 어서션**을 두면 오류 위치가 바로 드러난다.
 - 입력을 처리하며 **최소 반례**를 빠르게 만들기: `n=1, seq=1` 완전 오름/완전 내림, 불가능 수열 `1 2 5 3 4`.

- **Problem Hint:**
 - 이 문제의 본질은 **"단조 증가하는 j를 어디까지 밀어야 하는가"**를 결정하는 것.
 - 루프는 항상 **사후조건에서 역추적**하여 설계: "끝나고 `top=val`이 되도록 `j`를 `val`까지".

---

### BOJ 1406 - 에디터 (Editor)
- **Topic:** Stack | Two-Stacks | Simulation
- **Folder:** `stack/editor`
- **Time Complexity:** O(N + M)
- **Space Complexity:** O(N + M)

- **Key Idea:**
 - 커서 기준 **두 스택(left/right)** 로 분리해 커서 이동과 편집 연산을 모두 O(1)로 처리.
 - `L`-> left->right, `D` -> right->left, `B` -> left pop, `P x` -> left push.
 - 출력은 최종적으로 left를 right로 옮긴 뒤 right를 순서대로 출력.

- **Caution:**
 - 각 연산 전 대상 스택 **empty 체크** vlftn (L/D/B).
 - 대량 출력 시 중간 flush 없이 마지막에 한 번에 출력.

- **Improvement:**
 - 가독성: `stk1/stk2` 대신 `left/right` 네이밍.
 - 상수항 최적화: `std::stack<char>` 대신 `vector<char>`로 직접 push_back/pop_back 사용 가능.

- **Problem Hint:**
 - 에디터 커서 문제는 **두 스택**이 정석. 이동 연산을 push/pop 전환으로 치환하면 구현이 단순해진다.

---

## 📅 2025-10-06
**BOJ 10845 - 큐**
**BOJ 1021 - 회전하는 큐**
**BOJ 13335 - 트럭**

### BOJ 10845 - 큐 (Queue)
- **Topic:** Queue | Implementation
- **Folder:** `queue/basic/`
- **Time Complexity:** O(M)
- **Space Complexity:** O(N)

- **Key Idea:**
 - 명령을 읽어 `std::queue<int>`에 그대로 매핑하여 시뮬레이션
 - 빈 큐 예외(pop/front/back)만 정확히 처리하면 나머지는 단순 출력.

- **Caution:**
 - `pop/front/back`에서 빈 큐면 `-1`.
 - `size`는 필요시 `static_cast<int>(q.size())`로 명시적 정수 출력.
 - 출력마다 `'\n'`로 개행.

- **Improvement:**
 - `empty`는 `cout << (q.empty() ? 1 : 0 ) << '\n';`로 간결화 가눙

- **Problem Hint:**
 - 큐 연산 정의 그대로 구현하는 구현력 체크 문제.
 - 표준 컨테이너 사용에 익숙해지는 데 적합

---

### BOJ 1021 - 회전하는 큐 (Rotating Queue)
- **Topic:** Deque | Simulation | Rotation
- **Folder:** `deque/rotation`
- **Time Complexity:** O(N*M)
- **Space Complexity:** O(N)

- **Key Idea:**
 - 매 타깃마다 덱에서 위치 `idx`를 구해 **왼쪽 거리 `idx`**와 **오른쪽 거리 `size-idx`**를 비교, 더 짧은 방향으로만 회전.
 - `front == target`가 되면 `pop_front`로 제거하고, 회전 횟수를 누적.

- **Caution:**
 - 인덱스 탐색은 매칭 즉시 `break`로 종료.
 - 동일 거리일 때의 정책(왼쪽/오른쪽)을 코드 전반에 일관되게 유지.
 - 회전 루프는 방향을 정한 뒤 **그 방향만** 수행(중간에 재계산 불필요).

- **Improvement:**
 - 인덱스 탐색을 `auto it = find(dq.begin(), dq.end(), target); idx = it - dq.begin();`로 간결화.
 - 동일 거리 정책을 왼쪽 우선으로 바꾸려면 `if(idx <= size-idx)` 사용.

- **Problem Hint:**
 - 원형 데크에서의 최단 이동 문제는 결국 **두 거리 비교**다: `idx` vs `size-idx`.
 - 회전 연산은 덱의 양끝 연산으로 O(1)에 구현된다.

---

### BOJ 13335 - 트럭 (Trucks)
- **Topic:** Queue | Simulation | Sliding Window
- **Folder:** `queue/simulation`
- **Time Complexity:** O(N + T)
- **Space Complexity:** O(w)

- **Key Idea:**
 - 다리를 길이 `w`의 큐로 모델링해, 매 틱마다 한 칸씩 전진시킨다.
 - 다리 하중을 `cur_weight`로 관리하고, 꽉 찼을 때 먼저 내린 뒤 새 트럭을 올릴지를 판단.
 - 못 올리면 `0`을 넣어 **시간만 경과**시키고, 모든 트럭을 올린 후 `+w`로 마지막 이동 보정.

- **Caution:**
 - 업데이트 순서: **내리기 -> 올리기/0 -> 시간증가**.
 - 합계 자료형은 입력 범위에 따라 `int`로 충분하지만, 습관적으로 `long long`을 사용할 수도 있다.

- **Improvement:**
 - 따로 없음

- **Problem Hint:**
 - 다리 = 고정 길이 큐, 하중 = 큐 원소 합. 이 두 상태만 올바르게 유지하면 정답이 자연스럽게 나온다.

---

## 📅 2025-10-08
**BOJ 2164 - 카드2**
**BOJ 7562 - 나이트의 이동**
**BOJ 2346 - 풍선 터뜨리기**

### BOJ 2164 - 카드2 (Card 2)
- **Topic:** Queue | Simulation
- **Folder:** `queue/basic/`
- **Time Complexity:** O(N)
- **Space Complexity:** O(N)

- **Key Idea:**
 - 큐에 1..N을 넣고, `pop`으로 맨 위 카드를 버린 뒤 `front`를 `push`로 맨 아래로 이동.
 - 카드가 하나 남을 때까지 반복 후 남은 값을 출력.

- **Caution:**
 - 루프는 `q.size() > 1` 조건으로 유지.
 - 출력은 개행 포함, 빠른 I/O 설정 유지.

- **Improvement:**
 - 수학적 풀이로 O(1)도 가능(최대 2의 거듭제곱 활용) - 학습용 참고.

- **Problem Hint:**
 - "버리고 하나 뒤로"는 큐 그 자체. 구현은 `pop -> push(front) -> pop`의 반복으로 충분.

---

### BOJ 7562 - 나이트의 이동 (Knight Moves)
- **Topic:** BFS | Grid | Knight
- **Folder:** `graph/bfs/`
- **Time Complexity:** O(L^2)
- **Space Complexity:** O(L^2)

- **Key Idea:**
 - 나이트의 8개 이동을 간선으로 모델링하고 BFS로 최단 거리 계산.
 - 시작점을 `0`으로 두고, 유효 범위이면서 미방문인 칸을 `현재+1`로 갱신하며 큐에 넣는다.
 - 목표 지점에 도달한 순간의 거리(dist)가 정답.

- **Caution:**
 - 매 테스트마다 `visited`를 `-1`로 재초기화.
 - 좌표 범위와 미방문 체크 순서를 지켜서 불필요한 enqueue 방지.
 - 현재 코드는 목표에서 `break` 후 `visited[end_x][end_y]`를 출력하는데, **발견 즉시 출력 후 테스트 루프 종료** 형태로 바꾸면 플로우가 더 직관적.

- **Improvement:**
 - `make_pair` 대신 `q.emplace(nx, ny)` 사용으로 미세한 효율/가독성 향상.
 - `#define X/Y` 매크로 대신 `first/second` 사용하면 매크로 충돌 리스크 감소.
 - (선택) 1차원 dist(`vector<int> dist(L*L, -1)`)로 캐시 지역성 개선 가능.

- **Problem Hint:**
 - 나이트는 대각선/직선이 아닌 "L자" 이동. 8개 오프셋만 정확히 순회하면 BFS가 최단을 보장한다.

---

### BOJ 2346 — 풍선 터뜨리기 (Balloon Popping)
- **Topic:** Deque | Simulation | Rotation
- **Folder:** deque/rotation
- **Time Complexity:** O(N + K)  *(회전 합 K, 모듈러로 평균 감소)*
- **Space Complexity:** O(N)
- **Key Idea:**
  - 덱에서 현재 풍선을 꺼내 번호를 출력하고, 숫자 k에 따라 덱을 회전해 다음 타깃을 맨 앞으로 가져온다.
  - `k > 0` → `k-1`칸 왼쪽 회전, `k < 0` → `|k|`칸 오른쪽 회전.
- **Caution:**
  - `steps = abs(k) % size`로 줄이는 최적화 권장.
  - 마지막 하나 남을 때까지 처리 후, 마지막 번호를 출력.
- **Improvement:**
  - `emplace_back(i, val)` 사용으로 약간 간결.
  - 구조적 바인딩(`auto [idx,k] = dq.front();`)으로 가독성↑.
- **Problem Hint:**
  - 이 문제는 **덱 회전 시뮬레이션** 그 자체. 가운데 `erase`는 필요 없고, 양끝 연산으로 충분하다.

  ---

  ## 📅 2025-10-11
  **BOJ 18258 - 큐 2**
  **BOJ 1697 - 숨바꼭질**
  **BOJ 2812 - 크게 만들기**
  
  ### BOJ 18258 - 큐 2 (Queue 2)
  - **Topic:** Queue | Implementation | I/O
  - **Folder:** `queue/basic/`
  - **Time Complexity:** O(M)
  - **Space Complexity:** O(N)

  - **Key Idea:**
   - 명령어를 읽어 `std::queue<int>` 연산으로 그대로 매핑하여 수행한다.
   - 빈 큐 예외(pop/front/back)는 즉시 `-1`을 출력한다.
   - 빠른 입출력 설정으로 대량 명령에 대비한다.

  - **Caution:**
   - `size`는 정수 출력 기대에 맞춰 `static_cast<int>(q.size())`를 사용할 수 있다.
   - `'\n'` 사용으로 불필요한 flush 방지(`endl` 지양)

  - **Improvement:**
   - **출력 버퍼링**: 각 연산 결과를 문자열에 누적했다가 마지막에 한 번에 출력하면 상수항 감소.
   - **파싱 최소화(선택)**: 첫 글자 기준 분기(`'p'`->push/pop, `'s'`->size, `'e'`->empty, `'f'`->front, `'b'`->back)로 문자열 비교 비용 절감.
   - **커스텀 원형 큐(선택)**: 극단적 성능 추구 시 고정 배열 + head/tail로 직접 큐 구현.

  - **Problem Hint:**
   - 큐 연산 정의 그 자체를 구현하는 문제로, 예외 처리와 I/O만 정확히 하면 안정적으로 통과한다.
  
  ---
  
  ### BOJ 1697 - 숨바꼭질 (Hide and Seek)
  - **Topic:** BFS | Shortest Path | Graph
  - **Folder:** `graph/bfs/`
  - **Time Complexity:** O(MAX)
  - **Space Complexity:** O(MAX)

  - **Key Idea:**
   - 정점: 위치 0..MAX, 간선: `{x-1, x+1, 2*x}`.
   - BFS로 범위 내 미방문 이웃만 `dist = dist[cur] + 1`로 갱신.
   - 큐에서 **목표 k를 꺼낸 시점의 dist**가 곧 최소 시간.

  - **Caution:**
   - 경계 체크 순서 `if(nx < 0 || nx > MAX) continue;` -> `if (visited[nx] != -1) continue;`.
   - `visited`를 `-1`로 초기화해 거리/방문을 함께 관리.
   - 시작과 목표가 같으면 즉시 `0`.

  - **Improvement:**
   - `constexpr int MAX = 100000;`로 **상태공간을 100000에 고정**(메모리·탐색량 절감, 정답 불변).
   - 변수명 `dx` -> `nx`로 의미 명확화, 목표를 만난 즉시 `return 0;`로 종료하면 흐름 깔끔.

  - **Problem Hint:**
   - 무가중 최단 경로는 **BFS 정석**. 이웃 생성과 경계·방문 체크만 틀리지 않으면 항상 최단이 나온다.
  
  ---
  
  ### BOJ 2812 - 크게 만들기 (Make It Big)
  - **Topic:** Greedy | Monotonic Stack
  - **Folder:** `stack/monotonic/`
  - **Time Complexity:** O(N)
  - **Space Complexity:** O(N)

  - **Key Idea:**
   - 왼쪽부터 보며 스택 top보다 큰 숫자가 오면 가능할 때 pop해 **단조 감소 스택**을 유지.
   - 최종 길이는 `n-k`여야 하므로, 남은 문자 수로 길이를 채울 수 있는지 확인하며 pop/push를 결정.

  - **Caution:**
   - 현재 코드는 "남은자리 >= 필요자리" 검사를 통해 pop 허용 여부를 판단.
    - 대안: `k_rem`(남은 삭제 수)을 명시적으로 관리하면 구현이 간결해지고 검증이 쉬움.
   - 마지막 출력은 스택을 뒤집어 순서를 복원.
   
  - **Improvement:**
   - `stack<int>` 대신 `string`/`vector<char>` + `push_back/pop_back`를 쓰면 상수항 감소.
   - 역출력용 보조 스택 대신, 스택을 **벡터로 두고 뒤에서부터 출력**하거나 `string(result.rbegin(), result.rend())` 사용.
   - 조건식 간단화:
    `remain = n - (i + 1); need = (n - k) - (int)stk.size();`로 분리해 읽기 쉽게.

  - **Problem Hint:** 지문 키워드 → 접근법
   - "왼쪽에서부터 가능한 한 큰 수를 앞에 배치"는 전형적인 greedy.
   - **단조 감소 스택**을 떠올리면 구현이 한 줄로 정리된다.
  ---
  
  ## 📅 2025-10-12
  **BOJ 10866 - 덱**
  **BOJ 2667 - 단지 번호 붙이기**
  **BOJ 7576 - 토마토**
  
  ### BOJ 10866 - 덱 (Deque)
  - **Topic:** Deque | Implementation | I/O
  - **Folder:** `deque/basic/`
  - **Time Complexity:** O(M)
  - **Space Complexity:** O(N)

  - **Key Idea:**
   - 표준 `std::deque<int>`로 명령을 그대로 매핑해 처리.

  - **Caution:**
   - 빈 덱 예외(pop/front/back->-1)만 정확히 처리하면 안정적으로 통과.
   
  - **Improvement:**
   - 출력 누적(버퍼링)과 간단한 명령 파싱 최적화로 상수항을 줄일 수 있음.

  - **Problem Hint:**
   - 하라는 대로 하자.
  
  ---
  
  ### BOJ 2667 - 단지 번호 붙이기 (Numbering Complexes)
  - **Topic:** BFS | Grid | Connected-Components
  - **Folder:** `graph/bfs/`
  - **Time Complexity:** O(N^2)
  - **Space Complexity:** O(N^2)

  - **Key Idea:**
   - 격자를 순회하며 `visited[i][j]==false && map[i][j]==1`이면 새로운 단지 시작.
   - 큐에 시작 좌표를 넣고, 4방향 `(dx, dy)`로 범위·값·방문 체크 후 확장.
   - 확장할 때마다 현재 단지 크기 증가, 탐색 완료 후 벡터에 push.

  - **Caution:**
   - 매크로 `X/Y`는 세미콜론 제거 또는 사용하지 않고 `first/second` 사용.
   - 시작 셀 방문 처리 위치를 한 곳으로 일관되게 두기(현재는 main에서 처리 -> OK).

  - **Improvement:**
   - 가독성: `BFS`가 단지 크기를 `int`로 **반환**하게 하고, main에서 `size.push_back(bfs(i,j));` 형태로 수집하면 명료.
   - `auto cur = q.front(); q.pop();` 후 `cur.first/cur.second` 사용으로 `q.front()` 중복 접근 제거.
   - 전역 `map` 이름은 STL과 혼동될 수 있어 `grid` 등으로 변경 권장.

  - **Problem Hint:**
   - 전형적인 격자 연결 요소 문제. 4방향 BFS로 각 컴포넌트의 크기만 구해 오름차순 출력하면 된다.
  
  ---
  
  ### BOJ 7576 - 토마토 (Tomato)
  - **Topic:** BFS | Multi-Source | Grid
  - **Folder:** `graph/bfs/`
  - **Time Complexity:** O(N*M)
  - **Space Complexity:** O(N*M)

  - **Key Idea:**
   - 1(익은 토마토)들을 모두 큐에 담에ㅏ 시작하는 멀티 소스 BFS.
   - 인접 0을 `현재값+1`로 갱신해 각 칸에 "익은 날"을 저장.
   - 탐색 후 0이 남아 있으면 -1, 아니면 `max - 1`이 정답.

  - **Caution:**
   - 좌표 경계 -> 상태값(0/1/-1) -> 갱신 순서로 조건 체크.
   - 입력이 전부 -1일 수도 있으니 최댓값 초기값을 1로 두면 `mx-1=0`.
   - 큐 삽입은 `emplace` 사용 시 상수항 미세 개선 가능.

  - **Improvement:**
   - 매크로 대신 `first/second` 사용으로 가독성↑.
   - dx/dy 순서를 고정(상하좌우 등)해 디버깅 일관성 확보.
   - 매우 큰 I/O에서 출력 모으기(이 문제에선 출력이 1줄이라 필요 없음).

  - **Problem Hint:**
   - 시작점이 여러 개인 최단 거리 전파 문제는 **멀티 소스 BFS**로 풀면 깔끔하다.
  
  ---
  
  ## 📅 2025-10-14
  **BOJ 2606 - 바이러스**
  **BOJ 13023 - ABCDE**
  **BOJ 1012 - 유기농 배추**
  
  ### BOJ 2606 - 바이러스
  - **Topic:** BFS | Graph | Adjacency List
  - **Folder:** `graph/bfs/`
  - **Time Complexity:** O(V + E)
  - **Space Complexity:** O(V + E)

  - **Key Idea:**
   - 1번 정점에서 BFS 시작, 방문하지 않은 이웃만 큐에 넣으면서 방문 처리.
   - 방문되는 각 정점을 셀 때 1번 정점은 제외 -> 감염된 컴퓨터 수가 됨.

  - **Caution:**
   - 입력이 많은 편은 아니지만, 빠른 입출력 설정 유지.
   - 간선 중복 입력이 와도 visited 체크로 안전.

  - **Improvement (선택):**
   - DFS로도 동일한 정답 가능(스택/재귀)하지만 BFS가 직관적.

  - **Problem Hint:**
   - 하라는 대로 하자.
  
  ---
  
  ### BOJ 13023 - ABCDE (ABCDE)
  - **Topic:** DFS | Backtracking | Graph
  - **Folder:** `graph/dfs/`
  - **Time Complexity:** O(V * (V + E))
  - **Space Complexity:** O(V + E)

  - **Key Idea:**
   - 각 정점을 시작으로 DFS를 돌며 현재 경로 길이를 `depth`로 관리.
   - 재귀 진입 시 `visited[u]=true; depth++;` -> 직후 `depth==5`면 성공.
   - 모든 이웃 탐색 후 `depth--; visited[u]=false;`로 백트래킹.

  - **Caution:**
   - **오프바이원**: 성공 판정은 `depth` 증가 **이후**에 해야 함.
   - `visited` 복구 누락 시 다른 경로 차단 -> 오답.
   - 입력 인덱싱(0-based)과 인접 리스트 크기 일치 확인.

  - **Improvement:**
   - 전역 `depth` 대신 `DFS(u, d)`로 **깊이 인자화**하면 상태 관리가 명확.
   - 전역 `found`로 **가지치기**(`if (found) return;) 유지.

  - **Problem Hint:**
   - "연속한 5명"은 그래프의 **단순 경로** 문제. DFS로 경로를 뻗다가 길이 5가 되는 순간 멈추면 된다.
  
  ---
  
  ### BOJ 1012 - 유기농 배추 (Organic Cabbage)
  - **Topic:** BFS | Grid | Connected-Components
  - **Folder:** `graph/bfs/`
  - **Time Complexity:** O(T * M * N)
  - **Space Complexity:** O(M * N)

  - **Key Idea:**
   - 격자를 순회하며 `visited[x][y]==false && cabbage[x][y]==1`이면 BFS를 시작.
   - 큐에서 꺼낸 좌표의 4방향을 확인해 범위/방문/값 체크 후 확장.
   - BFS를 한 번 시작할 때마다 지렁이 수를 1 증가.

  - **Caution:**
   - 본 문제의 입력은 보통 `M(rkfh)=x`, `N(세로)=y`로 제공됨. 코드에서 1차원 인덱스를 x, 2차원을 y로 쓰고 있으므로 **dx, dy, 경계, 배열 차원**이 서로 맞물리는지 항상 점검.
   - 다중 테스트케이스에서 매번 초기화 필요.

  - **Improvement:**
   - `q.emplace(x, y);` 사용으로 미세 상수항 감소.
   - 매크로 대신 `cur.first/cur.second` 사용 시 가독성 향상.
   - 변수 명 `m, n` 대신 `cols, rows`처럼 의미를 드러내면 헷갈림 감소.

  - **Problem Hint:**
   - 하라는 대로 하자.
  
  ---
  
  ## 📅 2025-10-15
  **BOJ 2178 - 미로 탐색**
  **BOJ 11724 - 연결 요소의 개수**
  **BOJ 1987 - 알파벳**
  
  ### BOJ 2178 - 미로 탐색 (Maze Exploration)
  - **Topic:** BFS | Grid | Shortest-Path
  - **Folder:** `graph/bfs/`
  - **Time Complexity:** O(N*M)
  - **Space Complexity:** O(N*M)

  - **Key Idea:**
   - 큐에 (1,1)을 넣고, 4방향으로 확장하면서 `visited[nx][ny] = visited[cur]+1`.
   - 최종 `visited[N][M]`이 최소 이동 칸 수.

  - **Caution:**
   - 1-based 인덱스 사용 시 배열 크기를 `n+1, m+1`로 생성
   - `maze`를 `vector<string>`이나 `vector<vector<int>>`로 두면 의미가 더 명확

  - **Improvement:**
   - 조기 종료: `if (cur == make_pair(n,m)) break;`로 약간의 가지치기 가능.
   - 0-based로 바꾸면 인덱싱이 간단해지고 경계식도 직관적.
   - `q.emplace(nxt_x, nxt_y);` 사용으로 미세 상수항 개선.

  - **Problem Hint:**
   - 동일 가중치 격자 최단 경로 = **BFS**가 정답이다.
  
  ---
  
  ### BOJ 11724 - 연결 요소의 개수 (Number of Connected Components)
  - **Topic:** BFS | Graph | Connected-Components
  - **Folder:** `graph/bfs/`
  - **Time Complexity:** O(N + M)
  - **Space Complexity:** O(N + M)

  - **Key Idea:**
   - 1..N 순회하며 `visited[i]==false`면 `cnt++` 후 BFS로 해당 컴포넌트 전체 방문.
   - 큐에서 꺼낸 정점의 모든 이웃을 방문하지 않았을 때만 큐에 삽입.

  - **Caution:**
   - 1-based 인덱스와 배열 크기를 일관되게 유지.
   - 큐 삽입 시 바로 `visited=true` 처리해 중복 삽입 방지(현재 구현처럼).

  - **Improvement:**
   - `con_list[cur]` 순회에서 `const auto&` 사용 등 미세 가독성 향상 가능.
   - 간선 입력이 크지 않다면 추가 최적화는 불필요.

  - **Problem Hint:**
   - 하라는 대로 하자.
  
  ---
  
  ### BOJ 1987 - 알파벳 (Alphabet)
  - **Topic:** DFS | Backtracking | Grid
  - **Folder:** `graph/dfs/`
  - **Time Complexity:** O(R*C*min(26, R*C))
  - **Space Complexity:** O(26)

  - **Key Idea:**
   - `is_used[26]`로 알파벳 사용 여부만 관리하며 DFS 백트래킹.
   - 다음 칸의 알파벳이 사용 중이면 그 분기는 중단.
   - 경로 길이는 `depth`로 관리하고, 되돌아올 때 `mx = max(mx, depth)`.

  - **Caution:**
   - 1-based 인덱스 사용 시 경계 체크 일관 유지.
   - `mx == 26`이면 즉시 가지치기(현재 코드 구현됨).
   - `board`를 `vector<string>`(0-based)로 바꾸면 인덱싱이 간결하나, 현재도 일관적이면 문제 없음.

  - **Improvement:**
   - 미세 최적화: `mx = max(mx, depth);`를 **자식 호출 직후/루프 중간**에 배치해 조기 가지치기 조건(`if (mx==26)`)과 결합하면 평균 탐색량 감소.
   - 방향 배열을 `constexpr int dx[4]` 등으로 선언해 의도 명확화.

  - **Problem Hint:**
   - **상태는 "사용된 알파벳 집합"**이다 -> 격자 방문 여부보다 **알파벳 사용 여부**가 핵심.
   - 알파벳은 26개뿐 -> **최대 경로 길이는 26**이 상한. 여기에 도달하면 더 탐색할 필요 없음.
   - 다음 칸으로 갈 때는 **현재 사용 집합에 그 글자가 없는지만 체크**하면 된다.
   - 대안 관점: 상태를 `(x, y, mask)`로 볼 수 있어 DFS가 자연스럽다. (메모이제이션은 상태 수가 커서 기본 풀이에선 생략)
   - 그리디로는 해결 불가. **완전탐색+가지치기(백트래킹)**가 정석.

  ---

  ## 📅 2025-10-16
  **BOJ 3015 - 오아시스 재결합**
  **BOJ 6198 - 옥상 정원 꾸미기**
  **BOJ 1158 - 요세푸스 문제**
  
  ### BOJ 3015 - 오아시스 재결합 (Oasis Reunion)
  - **Topic:** Monotonic Stack | Stack | Counting
  - **Folder:** `stack/monotonic/`
  - **Time Complexity:** O(N)
  - **Space Complexity:** O(N)

  - **Key Idea:**
   - 스택을 키 내림차순으로 유지하며 `(height, count)`를 저장.
   - 새 키가 오면 더 작은 키 그룹을 모두 pop하면서 `+count`, 같은 키는 `+count` 후 병합.
   - 정리 후 스택이 남아 있으면 맨 위 큰 키와 `+1`.

  - **Caution:**
   - 정답형은 `long long`.
   - 같은 키 로직: `ans += top.count` -> `group += top.count` -> `pop()` 순으로 처리.
   - 시작값은 `0`; `n-1` 같은 사전 가산은 하지 않기.

  - **Improvement:**
   - 같은 키를 추가 할 때 그냥 스택으로 숫자를 넣는 게 아니라 스택을 pair로 선언해서 count를 올려준다는 발상을 해야 한다.

  - **Problem Hint:**
   - 쌍을 직접 세면 O(N^2).
   - **단조 스택**으로 "보이는 관계"를 한 번의 통과로 세어라:
    - 작으면 전부 보임 -> 그룹 수만큼 더함
    - 같으면 서로 전부 보임 -> 그룹 수만큼 더하고 병합
    - 크면 바로 한 명만 보임 -> +1
  
  ---
  
  ### BOJ 6198 - 옥상 정원 꾸미기 (Rooftop Garden)
  - **Topic:** Monotonic Stack | Stack | Greedy
  - **Folder:** `stack/monotonic/`
  - **Time Complexity:** O(N)
  - **Space Complexity:** O(N)

  - **Key Idea:**
   - 단조 감소 스택을 유지하며, 현재 높이 `h`보다 **작거나 같은** 높이는 팝.
   - 팝 이후 스 택에 남은 수(`stk.size()`)가 `h`를 볼 수 있는 **왼쪽 건물 수**이므로 누적.
   - 그 뒤 `h`를 스택에 푸시.

  - **Caution:**
   - 비교 연산은 `<=` (같은 높이도 시야 차단).
   - 누적 카운트는 `long long`.
   - 별도 마무리 합산 불필요(순회 중 모두 계산).

  - **Improvement:**
   - `build.reserve(n)`로 미세한 재할당 방지.

  - **Problem Hint:**
   - 한 빌딩에서 보이는 건물은 **왼쪽에 있는 자신보다 높은 건물들**뿐이다.
   - "보이는 쌍"을 직접 세지 말고, **오른쪽에서 등장할 때마다** 스택 크기만큼 한 번에 더하라.
  
  ---
  
  ### BOJ 1158 - 요세푸스 문제 (Josephus Problem)
  - **Topic:** Queue | Simulation
  - **Folder:** `queue/simulation/`
  - **Time Complexity:** O(N*K)
  - **Space Complexity:** O(N)

  - **Key Idea:**
   - 큐에 1..N을 넣고 `(K-1)`회 회전 + `K`번째 pop을 반복.

  - **Caution:**
   - 출력 형식의 쉼표/공백/괄호를 정확히 맞추기.

  - **Improvement:**
   - `int r = (k - 1) % q.size();`만큼만 회전해 불필요한 이동을 줄일 수 있음.
   - 결과를 `string out;`에 누적 후 한 번에 `cout << out;` 출력.

  - **Problem Hint:**
   - 하라는 대로 하자.
  
  ---
  
  ## 📅 2025-10-20
  **BOJ 7569 - 토마토**
  **BOJ 2589 - 보물섬**
  **BOJ 1520 - 내리막 길**
  
  ### BOJ 7569 - 토마토 (Tomato)
  - **Topic:** BFS | Graph | 3D Grid
  - **Folder:** `graph/bfs/`
  - **Time Complexity:** O(H*N*M)
  - **Space Complexity:** O(H*N*M)

  - **Key Idea:**
   - 익은 토마토를 멀티 소스로 큐에 넣고 6방향 BFS로 전파.
   - 익을 수 없는 칸은 visited가 -1로 남으므로 탐색 후 한 번에 판정.

  - **Caution:**
   - 경계: `0 <= x < H`, `0 <= y < N`, `0 <= z < M`.
   - 입력 시 0칸만 `visited = -1`로 초기화해 미방문 표시.
   - 이웃 확장 시 **값 필터**(`tomato[nx][ny][nz] == 0`)와 **상태 필터**(`visited[nx][ny][nz] == -1`)을 함께 적용.

  - **Improvement:**
   - 방향 벡터를 `int d[6][3] = {{-1,0,0}, {1,0,0}. {0,-1,0}, {0,1,0}, {0,0,-1},{0,0,1}};`로 묶어 인덱스 실수 감소.
   - `visited`를 `short`로 낮춰 메모리 절감(최대 일수 범위 확인 필수).
   - 의미 명확화를 위해 레벨별 루프(큐 크기 기준)로 하루 단위 증가를 명시적으로 구현.

  - **Problem Hint:**
   - "하루마다 익는다" -> **BFS 레벨**로 치환.
   - 출발점이 여러 개 -> **멀티 소스 BFS** 적용.
   - "모두 익는 최소 일수" = **최대 레벨**, 방문 불가가 있으면 `-1`.
  
  ---
  
  ### BOJ 2589 - 보물섬 (Treasure Island)
  - **Topic:** BFS | Graph | Grid
  - **Folder:** `graph/bfs/`
  - **Time Complexity:** O((N·M)·(N·M))
  - **Space Complexity:** O(N·M)

  - **Key Idea:**
   - 각 육지 칸을 시작점으로 **BFS**를 돌려 그 지점에서의 최장 최단거리를 구하고, 그들 중 **최댓값**을 출력한다.

  - **Caution:**
   - 고립된 육지의 경우도 거리는 **0** -> `ans = 0`으로 초기화(현재 코드 OK).
   - 방문 배열은 거리 기록용으로 `-1` 미방문, `0` 시작점, `+1`씩 증가 패턴 유지.
   - 경계 체크: `0 <= x < n`, `0 <= y < m`.

  - **Improvement:**
   - **컴포넌트 기반 2-BFS 최적화:** 각 연결 컴포넌트별로 임의의 육지에서 BFS->가장 먼 점 u 찾기, u에서 다시 BFS->지름(diameter). 모든 칸에서 BFS 하는 것보다 평균적으로 빠름.
   - **시작점 휴리스틱:** 바다에 인접한 육지(경계 육지)에서만 BFS 시작 -> 평균 시간 단축.
   - **메모리/가독성:** `vector<sring>`으로 지도를 보관하고 `visited`만 `vector<vector<int>>`로 유지.

  - **Problem Hint:**
   - 격자에서의 최단거리는 **BFS 레벨** = 거리.
   - "가장 먼 두 육지"는 한 지점에서의 **최장 최단거리**의 **최댓값**과 동일.
  
  ---
  
  ### BOJ 1520 - 내리막 길 (Downhill)
  - **Topic:** DFS | DP (Memoization) | DAG
  - **Folder:** `dp/graph/`
  - **Time Complexity:** O(M·N)
  - **Space Complexity:** O(M·N)

  - **Key Idea:**
   - 내리막 제약으로 DAG가 되므로, 각 칸에서 도착지까지의 **경로 수**를 DFS로 계산하고 `dp`에 캐시.

  - **Caution:**
   - `visited`는 사용하지 않는다(경로 공유를 막아 오답 유발).
   - 기저 및 전이 조건을 엄격히: `map[nx][ny] < map[x][y]`.

  - **Improvement:**
   - 경로 수가 커질 수 있으니 `vector<vector<long long>> dp` 고려.
   - 방향 배열을 `int d[4][2] = {{0,1},{0,-1},{-1,0},{1,0}};`로 묶어 실수 감소.
   - 큰 입력에서 최적화 플래그(-O2) 사용 권장.

  - **Problem Hint:**
   - "경로 수 세기"는 **Top-Down DP** 패턴: 한 번 푼 칸은 다시 풀지 않는다.
  
  ---
  
  ## 📅 2025-10-21
  **BOJ 6549 - 히스토그램에서 가장 큰 직사각형**
  **BOJ 11003 - 최솟값 찾기**
  **BOJ 5427 - 불**
  
  ### BOJ 6549 - 히스토그램에서 가장 큰 직사각형 (Largest Rectangle in a Histogram)
  - **Topic:** Stack | Monotonic Stack | Greedy
  - **Folder:** `stack/monotonic/`
  - **Time Complexity:** O(N)
  - **Space Complexity:** O(N)

  - **Key Idea:**
   - 인덱스 기반 **단조 증가 스택** 유지. 현재 높이가 감소하면 pop된 막대를 그 구간의 **최소 높이**로 보고 면적 계산.
   - 오른쪽 경계 = 현재 i(미포함), 왼쪽 경계 = pop 후 스택 top(없으면 -1).
    `width = i - (left + 1)`, `area = h[top] * width`.

  - **Caution:**
   - 면적은 반드시 `long long`.
   - 배열 끝에 **센티널 0**을 추가해 잔여 스택을 한 번에 정산.
   - 스택 비었을 때와 아닐 때의 **너비 분기**를 정확히 구현.

  - **Improvement:**
   - 타입 일관성: (A) 인덱스 `int` + `int N = (int)h.size();`, (B) 전부 `size_t` + 곱셈 직전 `width`만 `long long` 캐스팅.
   - `h.reserve(n + 1)`로 재할당 최소화, 미세 성능 향상.

  - **Problem Hint:**
   - 최대면적은 어떤 구간에서의 **최소 높이**로 결정되고, 그 최소가 바뀌는 순간이 **스택이 깨질 때**다.
   - 그래서 **감소하는 순간**에만 면적을 갱신하면 전체가 **선형 시간**으로 끝난다.
  
  ---
  
  ### BOJ 11003 - 최솟값 찾기 (Sliding Window Minimum)
  - **Topic:** Deque | Monotonic Queue | Sliding Window
  - **Folder:** `deque/monoqueue/`
  - **Time Complexity:** O(N)
  - **Space Complexity:** O(N)

  - **Key Idea:**
   - 인덱스 기반 **단조 증가 데크**를 유지하여 각 단계의 윈도우 최솟값을 `O(1)`에 얻는다.
   - 앞은 범위를 벗어나면 제거, 뒤는 현재 값 이상을 제거해 후보만 유지.

  - **Caution:**
   - 경계 체크는 `dq.front() <= i - L`로 명확히.
   - 대용량 입출력 최적화 유지, 마지막에 **개행 출력**.

  - **Improvement:**
   - 메모리 절약을 위해 결과를 **즉시 출력**(현재 방식) 유지.
   - 필요 시 출력 버퍼링으로 약간의 속도 향상 가능.

  - **Problem Hint:**
   - 슬라이딩 윈도우 최소/최대는 모노토닉 데크 패턴으로 각 원소가 **1번 들어가고 1번 나온다** -> 선형 시간.
  
  ---
  
  ### BOJ 5427 - 불 (Fire) - 방법 A: 단일 큐(불->사람 순)
  - **Topic:** BFS | Multi-source | Simulation
  - **Folder:** `graph/bfs/`
  - **Time Complexity:** O(H·W)
  - **Space Complexity:** O(H·W)

  - **Key Idea:**
   - 초기 큐에 `*`들을 먼저, 그다음 `@`을 넣어 매 시각 **불 먼저->사람** 순서 유지.
   - 불이 확산될 때 해당 칸을 즉시 `'*'`로 마킹해 동시 도착 시 불 우선 보장.

  - **Caution:**
   - 큐 처리 순서에 민감(동일 시각 섞임 주의).
   - 사람 쪽 방문/거리 테이블 필요. 시작점 부재 시 즉시 실패 처리.

  - **Improvement:**
   - 레벨 단위(큐 크기)로 "불 레벨 모두 ->  사람 레벨 모두" 처리 명시.
   - 문자 덮어쓰기 대신 `dist`/보조 배열로 판정 분리.
   
  - **Problem Hint:**
   - 멀티 소스 BFS, 동시 도착 시 불 우선, 경계 밖 탈출이 포인트.
  
  ---
  
  ## 📅 2025-10-30
  **BOJ 4179 - 불!**
  **BOJ 4991 - 로봇 청소기**

  ### BOJ 4179 - 불! (Fire)
  - **주제:** BFS | Multi-source | Grid | Escape  
  - **폴더:** `graph/bfs/`  
  - **시간복잡도:** O(R*C)  
  - **공간복잡도:** O(R*C)

  - **핵심 아이디어:**
    - 불 시간을 먼저 BFS로 전부 계산하고, 지훈은 그 시간표를 제약으로 BFS 이동.
    - 다음 칸으로의 `nt = visited[cx][cy] + 1`이 `fire[nx][ny]`보다 **작아야** 진입.

  - **주의할 점:**
    - 벽은 불/지훈 모두 금지, 불 미도달 칸은 자유롭게 이동 가능.
    - 경계 밖으로 나가면 즉시 `nt`를 출력하고 종료.

  - **개선 사항 (Improvement):**
    - `short`로 배열 축소 검토, 가장자리 시작 시 조기 종료, 좌표 구조체/방향 묶음으로 가독성↑.

  - **문제 힌트 (Problem Hint):**
    - 멀티소스 불 BFS → 사람 BFS(시간 비교) 순서가 정답의 핵심.
    - “동시 도착이면 불 우선”을 시간 비교로 반영해야 한다.

    ---

  ### BOJ 4991 — 로봇 청소기 (Robot Cleaner)
  - **주제:** BFS | 비트마스크 DP | 최단경로 전처리  
  - **폴더:** `dp/bitmask/`  
  - **시간복잡도:** O((W*H)*K + K^2 * 2^K)  
  - **공간복잡도:** O(W*H + K^2 + K*2^K)

  - **핵심 아이디어:**
    - 시작점과 먼지들을 모아 인덱싱하고, 각 지점에서 BFS로 서로 간 최단거리 행렬 `dist` 구성.
    - `dist`가 전부 유효하면 비트마스크 DP로 최소 이동거리 계산.

  - **주의할 점:**
    - `can_reach=false`가 되면 즉시 -1 출력(시간 아낌).
    - (w,h) 입력 순서에 따른 배열 크기/인덱스 주의.

  - **개선 사항 (Improvement):**
    - 비트마스크 자료형을 `int`로 통일(경고 감소, K≤10이므로 안전).
    - 바깥 루프까지 즉시 탈출하는 가드 추가.
    - DP 배열 초기화 시 INF를 `const int INF = 1e9;`로 두되, 덧셈 시 오버플로 여지 없음을 주석으로 명시.

  - **문제 힌트 (Problem Hint):**
    - “격자 최단거리”는 **BFS**, “모든 지점 방문 최소 비용”은 **비트마스크 DP**.
    - 시작점은 먼지 집합에 포함하지 않고, DP 초기화에서 시작점을 반영.

    ---

    ## 📅 2025-11-01
    **BOJ 24479 - 알고리즘 수업: 깊이 우선 탐색 1 (DFS 1)**
    
    ### BOJ 24479 — 알고리즘 수업: 깊이 우선 탐색 1 (DFS 1)
    - **주제:** DFS | Graph | Traversal  
    - **폴더:** `graph/dfs/`  
    - **시간복잡도:** O(N + M) + 정렬 O(∑deg·log deg)  
    - **공간복잡도:** O(N + M)

    - **핵심 아이디어:**
      - 인접 리스트를 오름차순 정렬 후 DFS로 방문하면서 out[node]에 순서를 기록.

    - **주의할 점:**
      - 입력 규모가 커서 재귀 깊이 한계에 걸릴 수 있음(환경 의존).

    - **개선 사항 (Improvement):**
      - 재귀 대신 **반복 DFS(스택)** 사용해 스택 오버플로 방지.
      - 정렬된 인접 리스트 사용으로 방문 순서 보장.

    - **문제 힌트 (Problem Hint):**
      - 오름차순 방문 요구 → **정렬 + DFS**가 정석.
      - 방문 순서 → **진입 시 카운터 증가**가 간단하고 안전.
    
    ---

    ## 📅 2025-11-05
    **BOJ 24480 - 알고리즘 수업: 깊이 우선 탐색 2**
    **BOJ 11403 - 경로 찾기**
    **BOJ 2660 - 회장 뽑기**

    ### BOJ 24480 - 알고리즘 수업: 깊이 우선 탐색 2 (DFS 2)
    - **Topic:** DFS  | Graph | Traversal
    - **Folder:** `graph/dfs/`
    - **Time Complexity:** O(N + M) + 정렬 O(∑deg log deg) 
    - **Space Complexity:** O(N + M)

    - **Key Idea:**
     - 인접 리스트 내림차순 정렬 -> DFS에서 진입 시점에 방문 순서 기록(1부터).

    - **Caution:**
     - 긴 체인 그래프에서 재귀 깊이 제한 주의.

    - **Improvement:**
     - 반복 DFS(스택)로 전환해 스택 오버플로 방지.
     - 출력은 `for (i=1..n) ans[i-1]` 형식 유지.

    - **Problem Hint:**
     - 24479는 오름차순, **24480은 내림차순** 정렬이 포인트.
     - 방문 순서는 **진입 시 카운트**가 자연스럽다.
    
    ---
    
    ### BOJ 11403 - 경로 찾기 (Find Path)
    - **Topic:** Graph | Transitive Closure | Floyd-Warshall
    - **Folder:** `graph/floyd/`
    - **Time Complexity:** O(N^3)
    - **Space Complexity:** O(N^2)

    - **Key Idea:**
     - `k`를 경유점으로 삼아 `A[i][j] |= (A[i][k] & A[k][j])`를 모든 `(i, j)`에 적용 -> 전이 폐쇄 완성.

    - **Caution:**
     - 자기 자신으로의 경로는 사이클이 있을 때만 1로 찍힘(문제 맞춤 동작).

    - **Improvement:**
     - (🟥 현재 코드에 없음) 분기 제거 한 줄 갱신식으로 단순화.
     - (🟥 현재 코드에 없음) `bitset` 행 연산으로 상수배 개선.
     - (🟩 현재 코드에 존재) 이미 1이면 건너뛰는 가지치기.

    - **Problem Hint:** 지문 키워드 → 접근법
     - "경로 존재 여부"는 **중간 정점 허용 여부**로 귀결 -> **Floyd-Warshall 전이 폐쇄**가 정석.
    ---
    
    ### BOJ 2660 - 회장 뽑기 (Select the President)
    - **Topic:** Graph | Floyd-Warshall | APSP
    - **Folder:** `graph/floyd/`
    - **Time Complexity:** O(N^3)
    - **Space Complexity:** O(N^2)

    - **Key Idea:**
     - Floyd-Warshall로 전쌍 최단거리 -> 각 정점의 최대거리(eccentricity) -> 최소값과 그 정점 출력

    - **Caution:**
     - 도달 불가는 **INF**, 자기 자신은 **0**으로 초기화해야 오답 방지.

    - **Improvement:**
     - 분기 제거 갱신식과 INF 초기화로 안정성 향상.

    - **Problem Hint:**
     - "회장 점수"는 그래프에서 **중심성(최대 거리의 최소화)** 개념.
    
    ---
    