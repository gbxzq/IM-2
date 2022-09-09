#include <stdio.h>
#include <math.h>
#include "../lib/random.h"

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

    for (int i = 0; i < 8; i++)
    {
        mathematical_expectation += values[i] * probabilities[i];
    }

    return mathematical_expectation;
}

double calc_mathematical_expectation_pow(double *values, double *probabilities)
{
    double mathematical_expectation = 0;

    for (int i = 0; i < 8; i++)
    {
        mathematical_expectation += values[i] * values[i] * probabilities[i];
    }

    return mathematical_expectation;
}

double *f(double *probabilities)
{
    double *distr;

    distr = malloc(sizeof(double) * (sizeof(probabilities) / sizeof(*probabilities)));

    distr[0] = probabilities[0];

    double sum = probabilities[0];

    for (int i = 1; i < (sizeof(probabilities) / sizeof(*probabilities)) + 1; i++)
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
    double P[8];

    double Y_sum = array_sum(Y);

    for (int i = 0; i < 8; i++)
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

    for (int i = 0; i < 8; i++)
    {
        printf("X%d ", i + 1);
        printf("%lf ", P[i]);

        // printf("%i ", counters[i]);
        // printf("%lf ", X[i]);
        // printf("%lf ", Y[i]);
        // printf("%lf \n", P[i]);
    }

    return 0;
}