#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <bits/stdc++.h>
using namespace std;

void showBar(string name, double time) {
    int bars = time * 100000;
    bars = min(bars, 50);

    cout << name << " | ";
    for(int i = 0; i < bars; i++) cout << "#";
    cout << " (" << time << " sec)\n";
}

#endif