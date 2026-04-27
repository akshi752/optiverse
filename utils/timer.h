#ifndef TIMER_H
#define TIMER_H

#include <bits/stdc++.h>
using namespace std;

double getTime(clock_t start, clock_t end) {
    return double(end - start) / CLOCKS_PER_SEC;
}

#endif