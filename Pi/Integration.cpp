#include "Integration.h"
#include <cmath>

// Konstruktor inicjalizujący
Integration::Integration(int num_intervals, int num_threads)
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
    for (int i = data.start; i < data.end; ++i) {
        double x = i * data.step + data.step / 2.0;
        local_sum += function(x) * data.step;
    }
    data.result = local_sum;
}

// Główna metoda obliczająca wartość π
double Integration::calculatePi() {
    int intervals_per_thread = num_intervals / num_threads;
    int remainder = num_intervals % num_threads;

    int current_start = 0;
    for (int i = 0; i < num_threads; ++i) {
        int current_end = current_start + intervals_per_thread + (i < remainder ? 1 : 0);
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

    // Zbieranie wyników
    double total_sum = 0.0;
    for (const auto& data : thread_data) {
        total_sum += data.result;
    }

    return total_sum * 4.0;
}

