#include <bits/stdc++.h>
#include "json.hpp"
using json = nlohmann::json;
using ll = long long;
using i128 = __int128_t;

i128 base_to_i128(const std::string& s, int base) {
    i128 res = 0;
    for (char c : s) {
        int d = 0;
        if (isdigit(c)) d = c - '0';
        else if (isalpha(c)) d = tolower(c) - 'a' + 10;
        else continue;
        if (d >= base) throw std::invalid_argument("digit too large");
        res = res * base + d;
    }
    return res;
}

i128 lagrange0(const std::vector<std::pair<i128,i128>>& P) {
    int k = P.size();
    i128 res = 0;
    for (int i = 0; i < k; i++) {
        i128 xi = P[i].first, yi = P[i].second;
        i128 num = 1, den = 1;
        for (int j = 0; j < k; j++) {
            if (i == j) continue;
            i128 xj = P[j].first;
            num *= -xj;
            den *= (xi - xj);
        }
        res += yi * (num / den);
    }
    return res;
}

std::string i128_to_str(i128 x) {
    if (x == 0) return "0";
    bool neg = (x < 0);
    if (neg) x = -x;
    std::string s;
    while (x > 0) {
        s.push_back(char('0' + (x % 10)));
        x /= 10;
    }
    if (neg) s.push_back('-');
    std::reverse(s.begin(), s.end());
    return s;
}

void solve(const std::string& fname) {
    std::ifstream f(fname);
    json j; f >> j;
    int n = j[" keys"]["n"];
    int k = j[" keys"]["k"];
    std::vector<std::pair<i128,i128>> pts;
    for (auto& item : j.items()) {
        if (item.key() == " keys") continue;
        i128 x = std::stoll(item.key());
        int base = std::stoi(item.value()["base"].get<std::string>());
        std::string vs = item.value()["value"];
        try {
            i128 y = base_to_i128(vs, base);
            pts.push_back({x, y});
        } catch (...) { }
    }
    std::map<i128,int> count;
    int m = pts.size();
    for (int mask = 0; mask < (1<<m); mask++) {
        if (__builtin_popcount(mask) != k) continue;
        std::vector<std::pair<i128,i128>> sel;
        for (int i = 0; i < m; i++)
            if (mask & (1<<i)) sel.push_back(pts[i]);
        try {
            i128 s = lagrange0(sel);
            if (s > 0) count[s]++;
        } catch (...) {}
    }
    // pick the most frequent positive secret
    i128 best = 0; int bestc = 0;
    for (auto &pr : count)
        if (pr.second > bestc) { best = pr.first; bestc = pr.second; }
    std::cout << fname << " secret = " << i128_to_str(best) << "\n";
}

int main(){
    solve("testcase1.json");
    solve("testcase2.json");
    return 0;
}
