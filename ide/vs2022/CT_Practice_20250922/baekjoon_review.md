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
- **Folder:** `string/lcs/`
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
**BOK 17609 - 회문**

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

### BOJ 10828 - 스택 (Stack)
- **Topic:** Stack | Implementation
- **Folder:** `stack/basic`
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
- **Folder:** `stack/brackets`
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
- **Folder:** `stack/monotonic`
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
