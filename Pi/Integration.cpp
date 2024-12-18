#include "Integration.h"
#include <cmath>

// Konstruktor inicjalizujący
Integration::Integration(long long num_intervals, int num_threads)
    : num_intervals(num_intervals), num_threads(num_threads) {
    step = 1.0 / num_intervals;
    threads.reserve(num_threads); // Rezerwacja miejsca dla wątków
    thread_data.resize(num_threads); // Przygotowanie danych dla wątków
}

// Funkcja do całkowania
double Integration::function(double x) {
    return std::sqrt(1 - x * x);
}

// Funkcja wątku
void Integration::threadTask(ThreadData& data) {
    double local_sum = 0.0;
    for (long long i = data.start; i < data.end; ++i) { // Użycie long long
        double x = i * data.step + data.step / 2.0;
        local_sum += function(x) * data.step;
    }
    data.result = local_sum;
}

// Główna metoda obliczająca wartość π
double Integration::calculatePi() {
    long long intervals_per_thread = num_intervals / num_threads;
    long long remainder = num_intervals % num_threads;

    long long current_start = 0;
    for (int i = 0; i < num_threads; ++i) {
        long long current_end = current_start + intervals_per_thread + (i < remainder ? 1 : 0);
        thread_data[i] = { current_start, current_end, step, 0.0 };
        current_start = current_end;
    }

    // Uruchamianie wątków
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(threadTask, std::ref(thread_data[i]));
    }

    // Dołączenie wątków
    for (auto& thread : threads) {
        thread.join();
    }

    // Algorytm Kahana do stabilnego sumowania wyników
    double total_sum = 0.0;
    double compensation = 0.0; // Korekcja dla błędów zaokrągleń

    for (const auto& data : thread_data) {
        double y = data.result - compensation;
        double t = total_sum + y;
        compensation = (t - total_sum) - y;
        total_sum = t;
    }

    return total_sum * 4.0;
}
