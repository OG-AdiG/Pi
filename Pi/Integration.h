#pragma once

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <vector>
#include <thread>
#include <functional>

/**
 * @brief Struktura przechowuj�ca dane dla poszczeg�lnych w�tk�w.
 *
 * Struktura zawiera informacje o zakresie iteracji, kroku oraz wynikach oblicze�.
 */
struct ThreadData {
    long long start; ///< Poczatkowy indeks przedzia�u dla w�tku.
    long long end;   ///< Ko�cowy indeks przedzia�u dla w�tku.
    double step;     ///< D�ugo�� kroku w podziale przedzia�u.
    double result = 0.0; ///< Wynik oblicze� w danym w�tku (domy�lnie 0.0).
};

/**
 * @brief Klasa Integration do obliczania warto�ci liczby PI metod� numeryczn�.
 *
 * Klasa wykorzystuje podej�cie wielow�tkowe do podzia�u pracy
 * na kilka w�tk�w w celu obliczenia przybli�onej warto�ci liczby PI.
 */
class Integration {
public:
    /**
     * @brief Konstruktor klasy Integration.
     *
     * Inicjalizuje liczbe przedzia��w, liczbe w�tk�w oraz inne wymagane zmienne.
     *
     * @param num_intervals Liczba przedzia��w do podzia�u obszaru.
     * @param num_threads Liczba w�tk�w do u�ycia w obliczeniach.
     */
    Integration(long long num_intervals, int num_threads);

    /**
     * @brief G��wna metoda obliczaj�ca warto�� liczby PI.
     *
     * Metoda dzieli obszar na przedzia�y i rozdziela prac� mi�dzy w�tki.
     *
     * @return Przybli�ona warto�� liczby PI.
     */
    double calculatePi();

    /**
     * @brief Funkcja reprezentuj�ca wz�r matematyczny do zintegrowania.
     *
     * @param x Warto�� wej�ciowa funkcji.
     * @return Wynik obliczenia funkcji dla danego x.
     */
    static double function(double x);

private:
    long long num_intervals; ///< Liczba przedzia��w u�ytych w obliczeniach.
    int num_threads;         ///< Liczba w�tk�w u�ytych w obliczeniach.
    double step;             ///< D�ugo�� kroku w podziale przedzia�u.
    std::vector<std::thread> threads; ///< Wektor obiekt�w w�tk�w.
    std::vector<ThreadData> thread_data; ///< Wektor danych dla ka�dego w�tku.

    /**
     * @brief Funkcja wykonywana przez ka�dy w�tek.
     *
     * W�tek oblicza cz�� sumy Riemanna na podstawie zakresu danych w strukturze ThreadData.
     *
     * @param data Referencja do struktury ThreadData zawieraj�cej dane dla w�tku.
     */
    static void threadTask(ThreadData& data);
};

#endif // INTEGRATION_H