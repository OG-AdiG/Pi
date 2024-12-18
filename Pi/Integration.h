#pragma once

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <vector>
#include <thread>
#include <functional>

struct ThreadData {
    int start;
    int end;
    double step;
    double result = 0.0; // Inicjalizacja wyniku
};

class Integration {
public:
    Integration(int num_intervals, int num_threads);
    double calculatePi();
    static double function(double x); // Funkcja do ca³kowania
private:
    int num_intervals;
    int num_threads;
    double step;
    std::vector<std::thread> threads; // Poprawiona deklaracja
    std::vector<ThreadData> thread_data;

    static void threadTask(ThreadData& data); // Funkcja dla w¹tku
};

#endif // INTEGRATION_H
