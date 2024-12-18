#include <iostream>         // Nagłówek do obsługi wejścia i wyjścia
#include <chrono>           // Nagłówek do pomiaru czasu
#include "Integration.h"    // Nagłówek z deklaracją klasy Integration

int main() {
    long long num_intervals; // Zmienna do przechowywania liczby przedziałów (typ long long dla obsługi dużych wartości)
    int num_threads;         // Zmienna do przechowywania liczby wątków

    // Pobranie danych od użytkownika
    std::cout << "Podaj liczbe przedzialow: ";
    std::cin >> num_intervals;  // Wczytanie liczby przedziałów od użytkownika
    std::cout << "Podaj liczbe watkow: ";
    std::cin >> num_threads;    // Wczytanie liczby wątków od użytkownika

    // Sprawdzenie poprawności wprowadzonych danych
    if (num_intervals <= 0 || num_threads <= 0) {
        // Jeśli liczba przedziałów lub wątków jest niedodatnia, wypisz komunikat o błędzie
        std::cerr << "Liczba przedzialow i watkow musi byc dodatnia!" << std::endl;
        return 1; // Zakończ program z kodem błędu
    }

    // Utworzenie obiektu klasy Integration
    // Konstruktor klasy Integration przyjmuje liczbę przedziałów i liczbę wątków
    Integration integration(num_intervals, num_threads);

    // Pomiar czasu rozpoczęcia obliczeń
    auto start_time = std::chrono::high_resolution_clock::now();

    // Wywołanie metody obliczającej wartość PI
    double pi = integration.calculatePi();

    // Pomiar czasu zakończenia obliczeń
    auto end_time = std::chrono::high_resolution_clock::now();

    // Obliczenie czasu wykonania jako różnicy pomiędzy czasem końcowym a początkowym
    std::chrono::duration<double> elapsed = end_time - start_time;

    // Wyświetlenie wyników obliczeń
    std::cout << "Przyblizona wartosc PI: " << pi << std::endl; // Przybliżona wartość liczby PI
    std::cout << "Czas obliczen: " << elapsed.count() << " sekund" << std::endl; // Czas wykonania obliczeń

    return 0; // Zakończenie programu
}
