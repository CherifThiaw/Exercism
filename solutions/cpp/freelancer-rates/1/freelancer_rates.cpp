#include <cmath>
#include <iostream>

// Calculates the daily rate given an hourly rate
double daily_rate(double hourly_rate) {
    return hourly_rate * 8;
}

// Calculates the price after applying a discount (percentage)
double apply_discount(double price, double discount) {
    return price * (1 - discount / 100);
}

// Calculates the monthly rate (22 workdays), rounded up
int monthly_rate(double hourly_rate, double discount) {
    double monthly = daily_rate(hourly_rate) * 22;
    double discounted = apply_discount(monthly, discount);
    return std::ceil(discounted);
}

// Calculates how many full workdays fit in the budget (rounded down)
int days_in_budget(int budget, double hourly_rate, double discount) {
    double daily = apply_discount(daily_rate(hourly_rate), discount);
    return std::floor(budget / daily);
}






/*// INFO: Headers from the standard library should be inserted at the top via
// #include <LIBRARY_NAME>
#include <cmath>
#include <iostream>

// daily_rate calculates the daily rate given an hourly rate
double daily_rate(double hourly_r) {
    // TODO: Implement a function to calculate the daily rate given an hourly
    // rate
    return hourly_r * 8;
}

// apply_discount calculates the price after a discount
double apply_discount(double before_d, double discount) {
    // TODO: Implement a function to calculate the price after a discount.
    return before_d - (before_d * discount) / 100;
}

// monthly_rate calculates the monthly rate, given an hourly rate and a discount
// The returned monthly rate is rounded up to the nearest integer.
int monthly_rate(double hourly_rate, double discount) {
    // TODO: Implement a function to calculate the monthly rate, and apply a
    // discount.
    return std::ceil(((hourly_rate * 8) * 22) - ((((hourly_rate * 8) * discount) /100) *22));
}

// days_in_budget calculates the number of workdays given a budget, hourly rate,
// and discount The returned number of days is rounded down (take the floor) to
// the next integer.
int days_in_budget(int budget, double hourly_rate, double discount) {
    // TODO: Implement a function that takes a budget, an hourly rate, and a
    // discount, and calculates how many complete days of work that covers.
    return budget / ((hourly_rate - (hourly_rate * discount) / 100 )* 8);
}
*/
