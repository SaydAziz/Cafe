#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>
#include <cmath>

class MenuItem {
public:
    MenuItem(const std::string& name, float price) : name_(name), price_(price) {}

    const std::string& name() const {
        return name_;
    }

    float price() const {
        return price_;
    }

private:
    std::string name_;
    float price_;
};

class Cafe {
public:
    Cafe() : menu_{
            MenuItem("Coffee", 5.10),
            MenuItem("Hot Chocolate", 10.55),
            MenuItem("Cheesecake", 13.75),
            MenuItem("Tea", 4.25),
            MenuItem("Muffin", 3.64)

    } {}

    void displayMenu() const {
        std::cout << "Menu:\n";
        for (size_t i = 0; i < menu_.size(); ++i) {
            std::cout << i + 1 << ". " << menu_[i].name() << " - $" << menu_[i].price() << "\n";
        }
    }

    void handleUserInput() {
        int choice = getMenuChoice();
        int payment = getPaymentAmount(menu_[choice - 1].price());

        int dollars, quarters, dimes, nickels;
        calculateChange(menu_[choice - 1].price(), payment, dollars, quarters, dimes, nickels);

        std::cout << "Here is your " << menu_[choice - 1].name() << ", and your change is:\n";
        if (dollars > 0) {
            std::cout << "Dollars: " << dollars << "\n";
        }
        if (quarters > 0) {
            std::cout << "Quarters: " << quarters << "\n";
        }
        if (dimes > 0) {
            std::cout << "Dimes: " << dimes << "\n";
        }
        if (nickels > 0) {
            std::cout << "Nickels: " << nickels << "\n";
        }
        if (dollars == 0 && quarters == 0 && dimes == 0 && nickels == 0) {
            std::cout << "None\n";
        }
    }

private:
    std::vector<MenuItem> menu_;

    int getMenuChoice() {
        int choice;

        while (true) {
            std::cout << "Enter your choice (1-5): ";
            std::cin >> choice;

            if (std::cin.fail() || choice < 1 || choice > 5) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Please try again.\n";
            } else {
                break;
            }
        }

        return choice;
    }

    int getPaymentAmount(float price) {
        int payment;

        while (true) {
            std::cout << "Enter the amount of whole dollars you will pay with: ";
            std::cin >> payment;

            if (std::cin.fail() || payment < price) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid or insufficient payment. Please try again.\n";
            } else {
                break;
            }
        }

        // Round off the payment to the nearest integer
        payment = static_cast<int>(std::round(payment));

        return payment;
    }

    void calculateChange(float price, int payment, int& dollars, int& quarters, int& dimes, int& nickels) {
        float change = payment - price;
        int cents = static_cast<int>(std::round(change * 100));

        if (cents == 0) {
            dollars = quarters = dimes = nickels = 0;
            return;
        }

        dollars = cents / 100;
        cents %= 100;

        quarters = cents / 25;
        cents %= 25;
        dimes = cents / 10;
        cents %= 10;

        nickels = cents / 5;
    }
};

int main() {
    Cafe cafe;
    while (true) {
        cafe.displayMenu();
        cafe.handleUserInput();

        char exitChoice;
        std::cout << "Do you want to exit? (y/n): ";
        std::cin >> exitChoice;
        if (tolower(exitChoice) == 'y') {
            break;
        }
    }

    return 0;
}
