#include "Integration.h"
#include <cmath>

/// @brief Konstruktor klasy Integration.
/// @param num_intervals Liczba przedziałów do całkowania.
/// @param num_threads Liczba wątków do wykorzystania.
Integration::Integration(long long num_intervals, int num_threads)
    : num_intervals(num_intervals), num_threads(num_threads) {
    step = 1.0 / num_intervals;  // Obliczenie rozmiaru kroku całkowania.
    threads.reserve(num_threads);  // Rezerwacja miejsca w wektorze dla wątków.
    thread_data.resize(num_threads);  // Przygotowanie wektora danych dla wątków.
}

/// @brief Funkcja matematyczna do całkowania.
/// @param x Argument funkcji.
/// @return Wartość funkcji w punkcie x.
double Integration::function(double x) {
    return std::sqrt(1 - x * x);  // Funkcja podcałkowa: √(1 - x^2).
}

/// @brief Funkcja wykonywana przez każdy wątek.
/// @param data Referencja do struktury z danymi wątku.
void Integration::threadTask(ThreadData& data) {
    double local_sum = 0.0;  // Lokalna suma dla wątku.
    for (long long i = data.start; i < data.end; ++i) { // Iteracja po przedziałach.
        double x = i * data.step + data.step / 2.0; // Środek przedziału.
        local_sum += function(x) * data.step;  // Dodanie wartości całki dla przedziału.
    }
    data.result = local_sum;   // Zapisanie wyniku do struktury wątku.
}

/// @brief Główna metoda obliczająca wartość liczby π.
/// @return Przybliżona wartość liczby π.
double Integration::calculatePi() {
    long long intervals_per_thread = num_intervals / num_threads; // Liczba przedziałów na wątek.
    long long remainder = num_intervals % num_threads; // Reszta do rozdzielenia.

    long long current_start = 0;  // Początek pierwszego zakresu.
    for (int i = 0; i < num_threads; ++i) {
        long long current_end = current_start + intervals_per_thread + (i < remainder ? 1 : 0); // Koniec zakresu.
        thread_data[i] = { current_start, current_end, step, 0.0 }; // Inicjalizacja danych wątku.
        current_start = current_end;  // Aktualizacja początku zakresu.
    }

    // Tworzenie i uruchamianie wątków.
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(threadTask, std::ref(thread_data[i])); // Przekazanie danych wątku do funkcji.
    }

    // Dołączenie wątków do głównego wątku.
    for (auto& thread : threads) {
        thread.join();  // Oczekiwanie na zakończenie każdego wątku.
    }

    // Algorytm Kahana do stabilnego sumowania wyników.
    double total_sum = 0.0;    // Całkowita suma.
    double compensation = 0.0; // Korekcja błędów zaokrągleń.

    for (const auto& data : thread_data) {
        double y = data.result - compensation; // Korekcja błędu dla bieżącego wyniku.
        double t = total_sum + y;              // Dodanie skorygowanej wartości do sumy.
        compensation = (t - total_sum) - y;    // Aktualizacja kompensacji.
        total_sum = t;                         // Zapisanie zaktualizowanej sumy.
    }

    return total_sum * 4.0;   // Przemnożenie wyniku przez 4 dla uzyskania π.
}
