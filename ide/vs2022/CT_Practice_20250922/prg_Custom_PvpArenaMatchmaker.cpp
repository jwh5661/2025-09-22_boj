/*
 * [PRG_Mock_14] PvP 아레나 매치메이커 (Lv.3 수준)
 * - 훈련 날짜: 2026-06-26 (금)
 * - 알고리즘: Hash Map, Custom Hashing, Two-Sum Paradigm
 * - 목적: 구조체를 Key로 사용하는 해시맵을 구축하여, 20만 개의 스탯 데이터 중 합이 1000이 되는 고유한 쌍의 개수를 O(N)으로 도출
 * - 엔진 실무 최적화:
 * 1. Custom Functor Hashing : `size_t operator()(const Stats& s)`를 구현하고 비트 시프트와 `XOR`을 결합하여,
 3개의 int 변수를  충돌 없는 단일 해시값으로 압축
 * 2. Lookup-First 방어 로직 : 루프 내에서 타깃을 먼저 `find`하여 카운트한 뒤에 자기 자신을 등록함으로써,
 O(1) 매칭과 동시에 동일 쌍의 중복 카운팅을 원천 차단.
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

// =========================================================================
// [아키텍트 훈련 제출 구역]
// =========================================================================

struct Stats {
    int str, dex, intel;

    bool operator==(const Stats& other) const {
        return (str == other.str) && (dex == other.dex) && (intel == other.intel);
    }
};

struct HashStats {
    size_t operator()(const Stats& s) const {
        size_t h1 = hash<int>()(s.str);
        size_t h2 = hash<int>()(s.dex);
        size_t h3 = hash<int>()(s.intel);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

long long solution(const vector<Stats>& players) {
    unordered_map<Stats, int, HashStats> stat_count;
    long long total_pairs = 0;

    for (const auto& p : players)
    {
        Stats other;
        other.str = 1000 - p.str;
        other.dex = 1000 - p.dex;
        other.intel = 1000 - p.intel;

        if (stat_count.find(other) != stat_count.end())
            total_pairs += stat_count[other];

        stat_count[p]++;
    }

    return total_pairs;
}
// =========================================================================

int main() {
    // 5명의 플레이어 대기열
    vector<Stats> players = {
        {500, 500, 500}, // P1
        {500, 500, 500}, // P2
        {200, 800, 100}, // P3
        {800, 200, 900}, // P4
        {500, 500, 500}  // P5
    };

    /* * [시나리오 분석]
     * P1(500,500,500)의 퍼펙트 듀오: P2, P5
     * P2(500,500,500)의 퍼펙트 듀오: P1, P5
     * P3(200,800,100)의 퍼펙트 듀오: P4
     * P4(800,200,900)의 퍼펙트 듀오: P3
     * P5(500,500,500)의 퍼펙트 듀오: P1, P2
     * * 중복을 제외한 고유한 쌍(Pair):
     * (P1, P2), (P1, P5), (P2, P5), (P3, P4) = 총 4쌍
     */

    long long result = solution(players);

    cout << "========================================" << endl;
    cout << "[결성 가능한 퍼펙트 듀오의 수] : " << result << " (기대값: 4)" << endl;
    cout << "========================================" << endl;

    return 0;
}