#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    const int RANDOM = (long long)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) {
        return a * 31 + b;
    }
    int operator()(int x) const {
        return hash_f(x)^RANDOM;
    }
};

gp_hash_table<int, int, chash> mp[200005];

/*
https://codeforces.com/blog/entry/62393?fbclid=IwAR0jc-v18zfgraeAenjLpzyxiYnbKR18BU7msMnAPRVSovFq99HPO-kY3bI
*/ 


struct CustomHash {
    uint64_t operator()(const vector<int>& a) const
    {
        uint64_t x;
        uint64_t hash = a.size();
        for (int i = 0; i < 26; ++i)
        {
            x = hash + a[i];
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            hash ^= x ^ (x >> 31);
        }
        return hash;
    }
}; 
//****// 
// https://ianyepan.github.io/posts/cpp-custom-hash/
// p is a pair<string, int>
hash<string>{}(p.first) ^ hash<int>{}(p.second); // simple and effective
//****
struct PairHash {
  template <typename T1, typename T2>
  auto operator()(const pair<T1, T2> &p) const -> size_t {
    return hash<T1>{}(p.first) ^ hash<T2>{}(p.second);
  }
}; 
// https://usaco.guide/gold/hashmaps?lang=cpp
