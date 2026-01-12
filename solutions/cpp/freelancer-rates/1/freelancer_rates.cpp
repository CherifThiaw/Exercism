#include <cmath>
#include <iostream>
#include <stdexcept>

namespace freelancer {

bool valid_discount(double discount) {
    return discount >= 0.0 && discount <= 100.0;
}

// Calculates the daily rate given an hourly rate
double daily_rate(double hourly_rate) {
    if (hourly_rate < 0.0) throw std::invalid_argument("hourly_rate must be >= 0");
    return hourly_rate * 8.0;
}

// Calculates the price after applying a discount (percentage)
double apply_discount(double price, double discount) {
    if (price < 0.0) throw std::invalid_argument("price must be >= 0");
    if (!valid_discount(discount)) throw std::invalid_argument("discount must be between 0 and 100");
    return price * (1.0 - discount / 100.0);
}

// Calculates the monthly rate (22 workdays), rounded up
int monthly_rate(double hourly_rate, double discount) {
    const double monthly = daily_rate(hourly_rate) * 22.0;
    const double discounted = apply_discount(monthly, discount);
    return static_cast<int>(std::ceil(discounted));
}

// Calculates how many full workdays fit in the budget (rounded down)
int days_in_budget(int budget, double hourly_rate, double discount) {
    if (budget < 0) throw std::invalid_argument("budget must be >= 0");
    const double daily = apply_discount(daily_rate(hourly_rate), discount);

    // Avoid division by zero if daily == 0 (hourly_rate = 0 or discount = 100)
    if (daily == 0.0) return 0;

    return static_cast<int>(std::floor(budget / daily));
}

}  // namespace freelancer

int main() {
    try {
        double hourly_rate = 0.0;
        double discount = 0.0;
        int budget = 0;

        std::cout << "Hourly rate: ";
        if (!(std::cin >> hourly_rate)) return 1;

        std::cout << "Discount (0-100): ";
        if (!(std::cin >> discount)) return 1;

        std::cout << "Budget: ";
        if (!(std::cin >> budget)) return 1;

        std::cout << "\n--- Results ---\n";
        std::cout << "Daily rate: " << freelancer::daily_rate(hourly_rate) << "\n";
        std::cout << "Monthly rate (22 days, rounded up): "
                  << freelancer::monthly_rate(hourly_rate, discount) << "\n";
        std::cout << "Days in budget (rounded down): "
                  << freelancer::days_in_budget(budget, hourly_rate, discount) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
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
