#include <iostream>
#include <chrono>
#include "Integration.h"

int main() {
    long long num_intervals; // Zmieniona na long long
    int num_threads;

    // Pobranie danych od użytkownika
    std::cout << "Podaj liczbe przedzialow (1,000,000 - 10,000,000): ";
    std::cin >> num_intervals;
    std::cout << "Podaj liczbe watkow: ";
    std::cin >> num_threads;

    if (num_intervals <= 0 || num_threads <= 0) {
        std::cerr << "Liczba przedzialow i watkow musi byc dodatnia!" << std::endl;
        return 1;
    }

    if (num_intervals < 1000000 || num_intervals > 10000000) {
        std::cerr << "Liczba przedzialow musi byc w zakresie 1,000,000 - 10,000,000!" << std::endl;
        return 1;
    }

    // Utworzenie obiektu klasy Integration
    Integration integration(num_intervals, num_threads);

    // Pomiar czasu
    auto start_time = std::chrono::high_resolution_clock::now();
    double pi = integration.calculatePi();
    auto end_time = std::chrono::high_resolution_clock::now();

    // Obliczenie czasu wykonania
    std::chrono::duration<double> elapsed = end_time - start_time;

    // Wyświetlenie wyników
    std::cout << "Przyblizona wartosc PI: " << pi << std::endl;
    std::cout << "Czas obliczen: " << elapsed.count() << " sekund" << std::endl;

    return 0;
}
