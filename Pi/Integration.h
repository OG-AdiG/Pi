#pragma once

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <vector>
#include <thread>
#include <functional>

struct ThreadData {
    long long start; 
    long long end;   
    double step;
    double result = 0.0; 
};

class Integration {
public:
    Integration(long long num_intervals, int num_threads);
    double calculatePi();
    static double function(double x); 
private:
    long long num_intervals; 
    int num_threads;
    double step;
    std::vector<std::thread> threads; 
    std::vector<ThreadData> thread_data;

    static void threadTask(ThreadData& data); 
};

#endif // INTEGRATION_H
