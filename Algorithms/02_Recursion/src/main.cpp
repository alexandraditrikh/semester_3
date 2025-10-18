#include <iostream>
#include <math.h>
#include <cctype>
#include <string>
using namespace std;

int my_pow(int x, int n)
{
    if (n < 0)
        return -1;
    if (n == 0)
        return 1;
    if (n == 1)
        return x;

    return x * my_pow(x, n - 1);
}

int counting_c_mn(int n, int m)
{
    if (m < 0 || m > n)
        return -1;
    if (m == 0 || m == n)
        return 1;

    return counting_c_mn(n - 1, m) + counting_c_mn(n - 1, m - 1);
}

typedef double (*function)(double);
double f(double x)
{
    return x * x - 4;
}
double root(function f, double a, double b, double e)
{
    if (e <= 0)
        return -1;
    if (a >= b)
        return -1;

    if (f(a) * f(b) > 0)
        return -1;

    double mid = (a + b) / 2.0;

    if (fabs(b - a) < e)
        return mid;
    if (fabs(f(mid)) < e)
        return mid;
    if (f(mid) == 0)
        return mid;

    if (f(a) * f(mid) < 0) return root(f, a, mid, e);
    else return root(f, mid, b, e);
}

bool is_power_of(int n, int k)
{
    if (k == 0)
        return n == 0;
    if (k == 1)
        return n == 1;
    if (k == -1)
        return n == 1 || n == -1;

    if (n == 0)
        return false;
    if (n == 1)
        return true;

    if (n % k != 0)
        return false;

    return is_power_of(n / k, k);
}

template <class T>
T find_min(T arr[], int size)
{
    if (size == 1)
        return arr[0];

    T min = find_min(arr, size - 1);
    return (arr[size - 1] < min) ? arr[size - 1] : min;
}

template <class T>
int find_count_max(T arr[], int size, T max, int count)
{
    if (size == 0)
        return count;

    if (arr[size - 1] == max)
        return find_count_max(arr, size - 1, max, count + 1);
    if (arr[size - 1] > max)
        return find_count_max(arr, size - 1, arr[size - 1], count = 1);
    else
        return find_count_max(arr, size - 1, max, count);
}

void output_bin_seq(string seq, int n)
{
    if (seq.length() == n)
    {
        cout << seq << endl;
        return;
    }

    output_bin_seq(seq + "0", n);
    output_bin_seq(seq + "1", n);
}

int find_sum_of_positive(int seq[], int n, int sum)
{
    if (n == 0)
        return sum;

    if (seq[n - 1] >= 0)
        return find_sum_of_positive(seq, n - 1, sum += seq[n - 1]);
    return find_sum_of_positive(seq, n - 1, sum);
}

bool issign(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}
int calculate(int l, char sign, int r)
{
    switch (sign)
    {
    case '+':
        return l + r;
    case '-':
        return l - r;
    case '*':
        return l * r;
    case '/':
        if (r == 0)
            return 0;
        return l / r;
    case '%':
        return l % r;
    }
    return 0;
}
int find_val_of_formula()
{
    char c;
    cin >> c;

    if (isdigit(c))
    {
        return c - '0';
    }

    if (c == '(')
    {
        int left = find_val_of_formula();

        char sign;
        cin >> sign;

        int right = find_val_of_formula();

        return calculate(left, sign, right);
    }
    return 0;
}

bool is_valid_formula() // TODO: 11
{
    char c;
    if (!(cin >> c))
        return false;

    if (isdigit(c))
        return true;

    if (c == '(')
    {
        if (!is_valid_formula())
            return false;

        char op;
        if (!(cin >> op) || !issign(op))
            return false;

        if (!is_valid_formula())
            return false;

        if (!(cin >> c) || c != ')')
            return false;

        char err;
        if (cin >> err)
            return false;

        return true;
    }
    return false;
}


bool find_value_formula2() // TODO: 12
{
    char c;
    cin >> c;

    if (c == 'f' || c == 't')
    {
        if (c == 'f')
        {
            string rest;
            cin >> rest;
            if (rest != "alse")
                throw invalid_argument("");
            return false;
        }
        if (c == 't')
        {
            string rest;
            cin >> rest;
            if (rest != "rue")
                throw invalid_argument("");
            return true;
        }
    }

    if (c == 'n' || c == 'a' || c == 'o')
    {

        bool is_not = 1, is_and = 1, is_or = 1;
        if (c == 'n')
        {
            string rest;
            cin >> rest;
            if (rest != "ot")
                throw invalid_argument("");
            is_not = true;
        }
        if (c == 'a')
        {
            string rest;
            cin >> rest;
            if (rest != "nd")
                throw invalid_argument("");
            is_and = 0;
        }
        if (c == 'o')
        {
            string rest;
            cin >> rest;
            if (rest != "r")
                throw invalid_argument("");
            is_or = true;
        }

        if (c == '(' && (is_and || is_not || is_or))
        {
        }
        else
            throw;
    }
}

/*bool parse_expression();

bool parse_operand() {
    return parse_expression();
}

bool parse_operands() {

    bool result = parse_operand();

    char c;
    while (cin >> c && c == ',') {
        bool next_operand = parse_operand();

    }

    if (cin) cin.putback(c);

    return result;
}

bool parse_expression() {
    char c;
    cin >> c;

    if (c == 'f') {

        string rest;
        cin >> rest;
        return false;
    }
    else if (c == 't') {

        string rest;
        cin >> rest;
        return true;
    }
    else if (c == 'n') {

        string rest;
        cin >> rest;
        cin >> c;
        bool operand = parse_operand();
        cin >> c;
        return !operand;
    }
    else if (c == 'a') {
        string rest;
        cin >> rest;
        cin >> c;

        bool result = parse_operand();

        while (cin >> c && c == ',') {
            bool next_operand = parse_operand();
            result = result && next_operand;
        }


        if (cin) cin.putback(c);
        cin >> c;

        return result;
    }
    else if (c == 'o') {

        string rest;
        cin >> rest;
        cin >> c;

        bool result = parse_operand();

        while (cin >> c && c == ',') {
            bool next_operand = parse_operand();
            result = result || next_operand;
        }

        if (cin) cin.putback(c);
        cin >> c;

        return result;
    }

    return false;
}

int is_valid_formula2() {
    return parse_expression() ? 1 : 0;
}*/

int main()
{
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        int x = 5, n = 2;
        int res = my_pow(x, n);
        if (res == -1)
            return -1;
        cout << x << "^" << n << " = " << res << endl;
        break;
    }
    case 2:
    {
        int n = 5, m = 2;
        int res = counting_c_mn(n, m);
        if (res == -1)
            return 1;
        cout << "c(" << n << ", " << m << ") = " << res << endl;
        break;
    }
    case 3:
    {
        double a = 1.0, b = 3.0, epsilon = 0.0001;
        double res = root(f, a, b, epsilon);
        if (res == -1)
            return -1;
        cout << "root func [" << a << ", " << b << "] = " << res << endl;
        break;
    }
    case 4:
    {
        int n, k;
        if (!(cin >> n >> k))
            return 1;
        cout << (is_power_of(n, k) ? "yes\n" : "no\n");
        break;
    }
    case 5:
    {
        int arr[4] = {1, 2, -5, 3};
        cout << find_min(arr, 4) << endl;
        break;
    }
    case 6:
    {
        int arr[7] = {0, 1, 3, 0, 2, 3, 3};
        cout << find_count_max(arr, 7, arr[0], 1) << endl;
        break;
    }
    case 7:
    {
        int n = 3;
        string seq = "";
        output_bin_seq(seq, n);
        break;
    }
    case 8:
    {
        int n = 4;
        int arr[4] = {-1, 2, 1, -2};
        int sum = 0;
        cout << find_sum_of_positive(arr, n, sum) << endl;
        break;
    }
    case 9:
    {
        cout << find_val_of_formula() << endl;
        break;
    }
    case 10:
    {
        cout << (is_valid_formula() ? "yes\n" : "no\n");
        break;
    }
    case 12:
    {
        //cout << (is_valid_formula2() ? "yes\n" : "no\n");
        break;
    }
    default:
    {
        cout << "enter 1-9" << endl;
        return 1;
    }
    }
    return 0;
}