#include <stdio.h>
#include <math.h>
#include "fun.h"
#include <string.h>

#define EPS 1e-4
#define COEF_P 1/15
#define COEF_IN 1/3

static int iterations = 0;

double root(double (*f)(double), double (*g)(double), double a, double b,  double eps, double (*df)(double), double (*dg)(double)) {
    double x0;

    //f''(x) < 0 ~ ploot - hoord > 0
    // This is the readson why <0 not >0
    if ((f(a) - g(a)) * (f((b + a) / 2) - g(b + a) / 2 - (f(a) - g (a) + f(b) - g(b)) / 2) < 0) {
        x0 = a;
    } else {
        x0 = b;
        eps = -eps;
    }

    double x = x0;

    while ((f(x) - g(x)) * (f(x + eps) - g(x + eps)) > 0) {
        iterations++;

        x = x - (f(x) - g(x)) / (df(x) - dg(x));
    }

    return x;
}

double I_n (double (*f) (double), double a, double b, int n) {
    double in = f(a) + f(b);
    double h = (b - a) / n;

    for (int i = 1; i < n; i++) {
        double fi = f(a + i * h);

        in += i % 2 == 1 ? 4 * fi : 2 * fi;
    }

    in *= (h * COEF_IN);

    return in;
}

double integral(double (*f) (double), double a, double b, double eps) {
    int n = 20;

    double A[2];
    A[0] = I_n(f, a, b, n);

    n *= 2;
    A[1] = I_n(f, a, b, n);

    while (fabs((A[1] - A[0])) * COEF_P >= eps) {
        n *= 2;

        A[0] = A[1];
        A[1] = I_n(f, a, b, n);
    }

    return A[1];
}

double zero(double x) {
    return 0;
}

void test_root(void) {
    printf("Testing root\n");

    double (*f_arr[4])(double) = {zero, f1, f2, f3};
    double (*df_arr[4])(double) = {zero, df1, df2, df3};
    int f, g;
    double a, b, eps;

    printf("Input №f(input 0 to use zero function) №g(input 0 to use zero function) a b eps\n");

    scanf("%d %d %lf %lf %lf", &f, &g, &a, &b, &eps);

    printf("Root approximately equal to %lf\n", root(f_arr[f], f_arr[g], a, b, eps, df_arr[f], df_arr[g]));

    printf("Iterations = %d\n", iterations);
}

void test_integral() {
    printf("Testing integral\n");

    double (*f_arr[3])(double) = {f1, f2, f3};
    int f;
    double a, b, eps;

    printf("Input №f a b eps\n");

    scanf("%d %lf %lf %lf", &f, &a, &b, &eps);

    printf("Integral approximately equal to %lf\n", integral(f_arr[f - 1], a, b, eps));
}

int main(int argc, char **argv) {
    char flag = 0;

    if (argc != 1) {
        if (strcmp(argv[1], "-help") == 0) {
            printf("One key is expected\n");
            printf("Keys list:\n");
            printf("-help (printing all keys)\n-root (printing roots)\n-iterations (printting count of iteration in root's calcualtions)\n");
            printf("-itest (function integral test)\n-rtest (function root test with iterations)\n");

            return 0;
        } else if (strcmp(argv[1], "-root") == 0) {
            flag = flag | 0x11;
        } else if (strcmp(argv[1], "-iterations") == 0) {
          flag = flag | 0x10;
        } else if (strcmp(argv[1], "-rtest") == 0) {
            test_root();

            return 0;
        } else if (strcmp(argv[1], "-itest") == 0){
            test_integral();

            return 0;
        } else {
            printf("This key does not exist\n");

            return 0;
        }
    }

    double x_arr[3]; // points array in ascending order
    x_arr[2] = root(f1, f2, 5.0, 7.0, EPS, df1, df2);//F1
    x_arr[0] = root(f1, f3, 2.1, 4.0, EPS, df1, df3);//F2
    x_arr[1] = root(f2, f3, 4.0, 5.0, EPS, df2, df3);//F3

    if (flag == 0x11) {
        printf("x1(f1 = f3): %lf, x2(f2 = f3): %lf, x3(f1 = f2): %lf\n", x_arr[0], x_arr[1], x_arr[2]);
    }

    if (flag == 0x10) {
        printf("Iterations = %d\n", iterations);
    }

    double i_arr[3];
    i_arr[0] = integral(f3, x_arr[0], x_arr[1], EPS);
    i_arr[1] = integral(f2, x_arr[1], x_arr[2], EPS);
    i_arr[2] = integral(f1, x_arr[0], x_arr[2], EPS);

    printf("Square approximately equal to %lf\n", i_arr[0] + i_arr[1] - i_arr[2]);

    return 0;
}
