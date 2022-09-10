#include <stdio.h>
#include <math.h>
#include "../lib/random.h"

#define MAX 8
#define N 1000

double array_sum(double *arr)
{
    double sum = 0;

    for (int i = 0; i < 8; i++)
    {
        sum += arr[i];
    }

    return sum;
}

double calc_mathematical_expectation(double *values, double *probabilities)
{
    double mathematical_expectation = 0;

    for (int i = 0; i < MAX; i++)
    {
        mathematical_expectation += values[i] * probabilities[i];
    }

    return mathematical_expectation;
}

double calc_mathematical_expectation_pow(double *values, double *probabilities)
{
    double mathematical_expectation = 0;

    for (int i = 0; i < MAX; i++)
    {
        mathematical_expectation += values[i] * values[i] * probabilities[i];
    }

    return mathematical_expectation;
}

double *f(double *probabilities)
{
    double *distr;

    distr = malloc(sizeof(*probabilities) * MAX);

    distr[0] = probabilities[0];

    double sum = probabilities[0];

    for (int i = 1; i < MAX + 1; i++)
    {
        sum += probabilities[i];
        distr[i] = sum;
    }

    return distr;
}

int main()
{
    doseed();
    double X[] = {170, 180, 200, 230, 240, 250, 280, 300};
    double Y[] = {240, 200, 190, 180, 170, 160, 159, 140};
    double P[MAX];

    double Y_sum = array_sum(Y);

    for (int i = 0; i < MAX; i++)
    {
        P[i] = Y[i] / Y_sum;
    }

    double mathematical_expectation = calc_mathematical_expectation(X, P);
    double mathematical_expectation_in_pow = calc_mathematical_expectation_pow(X, P);

    double dispersion = mathematical_expectation_in_pow - (mathematical_expectation * mathematical_expectation);

    double *distr = f(P);
    int counters[] = {0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < N; i++)
    {
        double rand_num = randfrac();

        for (int j = 0; j < sizeof(X) / sizeof(*X); j++)
        {
            if (rand_num < distr[j])
            {
                counters[j] += 1;
                break;
            }
        }
    }

    printf("    |%-6s |%-6s |%-6s |%-5s|\n", "Vi", "Xi", "Yi", "Pi");
    printf("-----------------------------------\n");
    for (int i = 0; i < MAX; i++)
    {
        printf("|X%d |", i + 1);

        printf("%-3.4lf |", get_probability(counters[i], 1000));
        printf("%-6.2lf |", X[i]);
        printf("%-6.2lf |", Y[i]);
        printf("%-3.2lf |\n", P[i]);
        printf("-----------------------------------\n");
    }

    printf("\nМатематичне очікуваня: %lf\n", mathematical_expectation);
    printf("Математичне очікуваня в квадраті: %lf\n", mathematical_expectation_in_pow);
    printf("Дисперсія: %lf", dispersion);

    return 0;
}