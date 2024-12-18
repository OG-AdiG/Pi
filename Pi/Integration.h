#pragma once

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <vector>
#include <thread>
#include <functional>

struct ThreadData {
    long long start; // Zmiana na long long
    long long end;   // Zmiana na long long
    double step;
    double result = 0.0; // Inicjalizacja wyniku
};

class Integration {
public:
    Integration(long long num_intervals, int num_threads);
    double calculatePi();
    static double function(double x); // Funkcja do ca³kowania
private:
    long long num_intervals; // Zmiana na long long
    int num_threads;
    double step;
    std::vector<std::thread> threads; // Poprawiona deklaracja
    std::vector<ThreadData> thread_data;

    static void threadTask(ThreadData& data); // Funkcja dla w¹tku
};

#endif // INTEGRATION_H
