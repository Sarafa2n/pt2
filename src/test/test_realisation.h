#ifndef DZ_TEST_REALISATION_H
#define DZ_TEST_REALISATION_H

extern "C" {
    #include "../lib/sequential.h"
    #include "../lib/parallel.h"
    #include "../lib/code_error.h"
    #include <sys/sysinfo.h>
}
#include <iostream>
#include <chrono>
#include <string>

#define ERROR_CODE 0

using namespace std;
using namespace std::chrono;

class TimeWork {
public:
    explicit TimeWork(): start(steady_clock::now()) {}

    ~TimeWork() {
        time_point<steady_clock> finish = steady_clock::now();
        high_resolution_clock::duration dur = finish - start;
        cerr << duration_cast<milliseconds>(dur).count()
             << " ms" << endl;
    }
private:
    steady_clock::time_point start;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define TimeWork() TimeWork UNIQ_ID(__LINE__);

#endif
