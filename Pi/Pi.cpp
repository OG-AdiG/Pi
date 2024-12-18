#include <iostream>         // Nagłówek do obsługi wejścia i wyjścia
#include <chrono>           // Nagłówek do pomiaru czasu
#include "Integration.h"    // Nagł\uwek z deklaracją klasy Integration

/**
 * @brief Funkcja główna programu.
 *
 * Program oblicza przybliżoną wartość liczby PI przy użyciu metody numerycznej.
 * Użytkownik podaje liczbę przedziałów i liczbę wątków,
 * a wynik oraz czas obliczeń są wypisywane na standardowym wyjściu.
 *
 * @return Zwraca 0 w przypadku powodzenia, 1 w przypadku błędu.
 */
int main() {
    long long num_intervals; ///< Liczba przedziałów do podziału obszaru pod krzywą.
    int num_threads;         ///< Liczba wątków do wykorzystania w obliczeniach.

    // Pobranie danych od użytkownika
    std::cout << "Podaj liczbe przedzialow: ";
    std::cin >> num_intervals;  ///< Wczytanie liczby przedziałów od użytkownika.
    std::cout << "Podaj liczbe watkow: ";
    std::cin >> num_threads;    ///< Wczytanie liczby wątków od użytkownika.

    /**
     * @brief Walidacja danych wejściowych.
     *
     * Program sprawdza, czy liczba przedziałów i liczba wątków są dodatnie.
     * W przypadku błędnych danych wypisuje komunikat i przerywa działanie.
     */
    if (num_intervals <= 0 || num_threads <= 0) {
        std::cerr << "Liczba przedzialow i watkow musi byc dodatnia!" << std::endl;
        return 1; ///< Zakończenie programu z kodem błędu.
    }

    /**
     * @brief Tworzenie obiektu klasy Integration.
     *
     * Obiekt tej klasy odpowiada za obliczenia przybliżonej wartości liczby PI
     * z użyciem podanej liczby przedziałów i wątków.
     */
    Integration integration(num_intervals, num_threads);

    // Pomiar czasu rozpoczęcia obliczeń
    auto start_time = std::chrono::high_resolution_clock::now();

    /**
     * @brief Obliczanie wartości liczby PI.
     *
     * Wywoływana metoda klasy Integration dokonuje obliczeń numerycznych.
     * @return Przybliżona wartość liczby PI.
     */
    double pi = integration.calculatePi();

    // Pomiar czasu zakończenia obliczeń
    auto end_time = std::chrono::high_resolution_clock::now();

    /**
     * @brief Obliczenie czasu wykonania obliczeń.
     *
     * Różnica czasu zakończenia i rozpoczęcia obliczeń podana w sekundach.
     */
    std::chrono::duration<double> elapsed = end_time - start_time;

    // Wyświetlenie wyników obliczeń
    std::cout << "Przyblizona wartosc PI: " << pi << std::endl; ///< Przybliżona wartość liczby PI.
    std::cout << "Czas obliczen: " << elapsed.count() << " sekund" << std::endl; ///< Czas wykonania obliczeń.

    return 0; ///< Zakończenie programu.
}