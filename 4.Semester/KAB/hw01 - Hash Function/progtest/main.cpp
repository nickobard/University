#include "src/Hasher.hpp"
#include <chrono>

using namespace std;

constexpr int TEST_BITS_COUNT_MAX = 23;
constexpr int TEST_ITERATIONS = 30;

#define TIME_MEASURE
//#define WOLFRAM

int findHashTimeMeasure(int bits) {
    auto function = Hasher();
    function.init(bits);
    return function.findHashWithZeroBits(bits);
}

struct TimeMeasurer {

    using measure_unit = chrono::nanoseconds;

    void start() {
        _start = chrono::steady_clock::now();
    }

    TimeMeasurer &end() {
        _end = chrono::steady_clock::now();
        _delta = chrono::duration_cast<measure_unit>(_end - _start);
        return *this;
    }

    void wolframFormatPrint(int bits) const {
        cout << "{" << bits << ", " << _delta.count() << "}, " << flush;
    }

    void pythonFormatPrint(int bits) const {
        cout << "[" << bits << ", " << _delta.count() << "], " << flush;
    }

    void test(int bits, bool wolframFormat = true) {
        int iterations = TEST_ITERATIONS;
        for (int i = 0; i < iterations; i++) {
            start();
            findHashTimeMeasure(bits);
            end();
            if (wolframFormat)
                wolframFormatPrint(bits);
            else
                pythonFormatPrint(bits);
        }
    }

    chrono::time_point<chrono::steady_clock> _start;
    chrono::time_point<chrono::steady_clock> _end;
    measure_unit _delta;
};

int main(void) {


    char *message, *hash;
    assert(findHash(0, &message, &hash) == 1);
    assert(message && hash && checkHash(0, hash));
    free(message);
    free(hash);
    assert(findHash(1, &message, &hash) == 1);
    assert(message && hash && checkHash(1, hash));
    free(message);
    free(hash);
    assert(findHash(2, &message, &hash) == 1);
    assert(message && hash && checkHash(2, hash));
    free(message);
    free(hash);
    assert(findHash(3, &message, &hash) == 1);
    assert(message && hash && checkHash(3, hash));
    free(message);
    free(hash);
    assert(findHash(-1, &message, &hash) == 0);

    assert(findHash(10, &message, &hash) == 1);
    assert(message && hash && checkHash(10, hash));
    free(message);
    free(hash);


    assert(findHash(14, &message, &hash) == 1);
    assert(message && hash && checkHash(14, hash));
    free(message);
    free(hash);


    assert(findHash(20, &message, &hash) == 1);
    assert(message && hash && checkHash(20, hash));
    free(message);
    free(hash);

    assert(findHash(8, &message, &hash) == 1);
    assert(message && hash && checkHash(8, hash));
    free(message);
    free(hash);

    assert(findHash(-123, &message, &hash) == 0);
    assert(findHash(513, &message, &hash) == 0);
    assert(findHash(23423423, &message, &hash) == 0);

#ifdef TIME_MEASURE

#ifdef WOLFRAM
    bool useWolframFormat = true;
#else
    bool useWolframFormat = false;
#endif

    TimeMeasurer t;

    for (int bits = 0; bits < TEST_BITS_COUNT_MAX + 1; bits++)
        t.test(bits, useWolframFormat);
#endif

    return EXIT_SUCCESS;
}
