#pragma once

// The actual algorithm
namespace rnd {
	static uint64_t s[4];
	uint64_t mySeed;
	uint64_t seedNext() {
			uint64_t z = (mySeed += UINT64_C(0x9E3779B97F4A7C15));
			z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
			z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
			return z ^ (z >> 31);
		}
	void seed(const uint64_t val) {
		mySeed = val;
		for(int i = 0; i < 4; i++) s[i] = seedNext();
	}
	static  uint64_t rotl(const uint64_t x, int k) {
		return (x << k) | (x >> (64 - k));
	}
	inline uint64_t random64(void) {
		const uint64_t result = s[0] + s[3];
		const uint64_t t = s[1] << 17;
		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];
		s[2] ^= t;
		s[3] = rotl(s[3], 45);
		return result;
	}
	inline float randomf() {
		return static_cast<float>(random64())/UINT64_MAX;
	}
	inline float randomf(const float max) {
		return static_cast<float>(random64())/(UINT64_MAX/(max-0.00001f));
	}
	inline float randomf(const float min, const float max) {
		return min + static_cast<float>(random64())/(UINT64_MAX/(max-0.00001f));
	}
	inline double randomd() {
		return static_cast<double>(random64())/UINT64_MAX;
	}
	inline double randomd(const double max) {
		return static_cast<double>(random64())/(UINT64_MAX/(max - 0.00001));
	}
	inline double randomd(const double min, const double max) {
		return min + static_cast<double>(random64())/(UINT64_MAX/(max - 0.00001));
	}
}