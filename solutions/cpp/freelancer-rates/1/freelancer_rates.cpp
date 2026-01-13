#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace freelancer {

constexpr double HOURS_PER_DAY = 8.0;
constexpr int WORKDAYS_PER_MONTH = 22;

void require(bool condition, const char* message) {
    if (!condition) throw std::invalid_argument(message);
}

double daily_rate(double hourly_rate) {
    require(hourly_rate >= 0.0, "hourly_rate must be >= 0");
    return hourly_rate * HOURS_PER_DAY;
}

double apply_discount(double price, double discount) {
    require(price >= 0.0, "price must be >= 0");
    require(discount >= 0.0 && discount <= 100.0, "discount must be in [0, 100]");
    return price * (1.0 - discount / 100.0);
}

int monthly_rate(double hourly_rate, double discount) {
    double monthly = daily_rate(hourly_rate) * WORKDAYS_PER_MONTH;
    return static_cast<int>(std::ceil(apply_discount(monthly, discount)));
}

int days_in_budget(int budget, double hourly_rate, double discount) {
    require(budget >= 0, "budget must be >= 0");

    double daily = apply_discount(daily_rate(hourly_rate), discount);
    if (daily == 0.0) return 0;

    return static_cast<int>(std::floor(budget / daily));
}

}  // namespace freelancer

template <typename T>
T read_value(const std::string& label) {
    T value{};
    while (true) {
        std::cout << label;
        if (std::cin >> value) return value;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    try {
        double hourly = read_value<double>("Hourly rate: ");
        double discount = read_value<double>("Discount (0-100): ");
        int budget = read_value<int>("Budget: ");

        std::cout << "\n--- Results ---\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Daily rate: $" 
                  << freelancer::daily_rate(hourly) << "\n";
        std::cout << "Monthly rate: $" 
                  << freelancer::monthly_rate(hourly, discount) << "\n";
        std::cout << "Days in budget: " 
                  << freelancer::days_in_budget(budget, hourly, discount) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
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
