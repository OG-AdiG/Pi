#pragma once

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <vector>
#include <thread>
#include <functional>

/**
 * @brief Struktura przechowuj¹ca dane dla poszczególnych w¹tków.
 *
 * Struktura zawiera informacje o zakresie iteracji, kroku oraz wynikach obliczeñ.
 */
struct ThreadData {
    long long start; ///< Poczatkowy indeks przedzia³u dla w¹tku.
    long long end;   ///< Koñcowy indeks przedzia³u dla w¹tku.
    double step;     ///< D³ugoœæ kroku w podziale przedzia³u.
    double result = 0.0; ///< Wynik obliczeñ w danym w¹tku (domyœlnie 0.0).
};

/**
 * @brief Klasa Integration do obliczania wartoœci liczby PI metod¹ numeryczn¹.
 *
 * Klasa wykorzystuje podejœcie wielow¹tkowe do podzia³u pracy
 * na kilka w¹tków w celu obliczenia przybli¿onej wartoœci liczby PI.
 */
class Integration {
public:
    /**
     * @brief Konstruktor klasy Integration.
     *
     * Inicjalizuje liczbe przedzia³ów, liczbe w¹tków oraz inne wymagane zmienne.
     *
     * @param num_intervals Liczba przedzia³ów do podzia³u obszaru.
     * @param num_threads Liczba w¹tków do u¿ycia w obliczeniach.
     */
    Integration(long long num_intervals, int num_threads);

    /**
     * @brief G³ówna metoda obliczaj¹ca wartoœæ liczby PI.
     *
     * Metoda dzieli obszar na przedzia³y i rozdziela pracê miêdzy w¹tki.
     *
     * @return Przybli¿ona wartoœæ liczby PI.
     */
    double calculatePi();

    /**
     * @brief Funkcja reprezentuj¹ca wzór matematyczny do zintegrowania.
     *
     * @param x Wartoœæ wejœciowa funkcji.
     * @return Wynik obliczenia funkcji dla danego x.
     */
    static double function(double x);

private:
    long long num_intervals; ///< Liczba przedzia³ów u¿ytych w obliczeniach.
    int num_threads;         ///< Liczba w¹tków u¿ytych w obliczeniach.
    double step;             ///< D³ugoœæ kroku w podziale przedzia³u.
    std::vector<std::thread> threads; ///< Wektor obiektów w¹tków.
    std::vector<ThreadData> thread_data; ///< Wektor danych dla ka¿dego w¹tku.

    /**
     * @brief Funkcja wykonywana przez ka¿dy w¹tek.
     *
     * W¹tek oblicza czêœæ sumy Riemanna na podstawie zakresu danych w strukturze ThreadData.
     *
     * @param data Referencja do struktury ThreadData zawieraj¹cej dane dla w¹tku.
     */
    static void threadTask(ThreadData& data);
};

#endif // INTEGRATION_H