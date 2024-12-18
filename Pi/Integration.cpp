/**
 * @file Integration.cpp
 * @brief Implementacja klasy Integration, służącej do obliczania wartości liczby π
 *        metodą całkowania numerycznego przy użyciu wielowątkowości.
 */

#include "Integration.h"
#include <cmath>

 /**
  * @brief Konstruktor klasy Integration.
  * @param num_intervals Liczba przedziałów do całkowania.
  * @param num_threads Liczba wątków, które mają być wykorzystane do równoległego obliczania.
  */
Integration::Integration(long long num_intervals, int num_threads)
    : num_intervals(num_intervals), num_threads(num_threads) {
    step = 1.0 / num_intervals;  ///< Obliczenie długości kroku całkowania.
    threads.reserve(num_threads);  ///< Rezerwacja miejsca w wektorze dla wątków.
    thread_data.resize(num_threads);  ///< Inicjalizacja wektora danych dla wątków.
}

/**
 * @brief Funkcja matematyczna, której całka jest obliczana.
 * @param x Argument funkcji.
 * @return Wartość funkcji w punkcie x (√(1 - x²)).
 */
double Integration::function(double x) {
    return std::sqrt(1 - x * x);  // Funkcja podcałkowa: √(1 - x^2).
}

/**
 * @brief Funkcja wykonywana przez każdy wątek podczas równoległego obliczania.
 * @param data Referencja do struktury danych przechowującej zakres obliczeń i wynik lokalny.
 */
void Integration::threadTask(ThreadData& data) {
    double local_sum = 0.0;  ///< Lokalna suma obliczana przez wątek.
    for (long long i = data.start; i < data.end; ++i) {
        double x = i * data.step + data.step / 2.0; ///< Środek bieżącego przedziału.
        local_sum += function(x) * data.step; ///< Obliczenie i dodanie wartości całki dla bieżącego przedziału.
    }
    data.result = local_sum;  ///< Zapisanie wyniku obliczonego przez wątek.
}

/**
 * @brief Główna metoda klasy obliczająca przybliżoną wartość liczby π metodą numerycznego całkowania.
 * @return Przybliżona wartość liczby π.
 */
double Integration::calculatePi() {
    // Obliczenie liczby przedziałów przypadających na każdy wątek.
    long long intervals_per_thread = num_intervals / num_threads;
    long long remainder = num_intervals % num_threads; ///< Reszta do równomiernego rozdzielenia zakresów.

    long long current_start = 0; ///< Początkowy indeks zakresu dla wątków.
    for (int i = 0; i < num_threads; ++i) {
        // Wyznaczenie zakresu obliczeń dla każdego wątku.
        long long current_end = current_start + intervals_per_thread + (i < remainder ? 1 : 0);
        thread_data[i] = { current_start, current_end, step, 0.0 }; ///< Inicjalizacja danych wątku.
        current_start = current_end; ///< Aktualizacja początku zakresu.
    }

    // Tworzenie i uruchamianie wątków.
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(threadTask, std::ref(thread_data[i])); ///< Przekazanie danych wątku do funkcji.
    }

    // Czekanie na zakończenie obliczeń przez wszystkie wątki.
    for (auto& thread : threads) {
        thread.join(); ///< Synchronizacja wątków z wątkiem głównym.
    }

    // Algorytm Kahana zapewniający stabilne sumowanie zmiennoprzecinkowe.
    double total_sum = 0.0;    ///< Całkowita suma.
    double compensation = 0.0; ///< Korekta błędów zaokrągleń.

    for (const auto& data : thread_data) {
        double y = data.result - compensation; ///< Skorygowanie wyniku w celu zmniejszenia błędu.
        double t = total_sum + y;              ///< Aktualizacja sumy po uwzględnieniu korekty.
        compensation = (t - total_sum) - y;    ///< Uaktualnienie kompensacji błędu.
        total_sum = t;                         ///< Zapisanie nowej sumy.
    }

    return total_sum * 4.0; ///< Wynik pomnożony przez 4 dla uzyskania liczby π.
}
