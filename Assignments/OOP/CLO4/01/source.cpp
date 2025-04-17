#include <iostream>

class Date;
class Order;
class Item;
class Mart;
class Customer;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() : day(0), month(0), year(0) {} // Default constructor
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    void setDate(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }

    void displayDate() const {
        std::cout << month << "/" << day << "/" << year;
    }
};

class Item {
private:
    std::string name;
    std::string description;
    float price;
    int quantity;

public:
    Item() : price(0.0f), quantity(0) {}  //Default Constructor
    Item(const std::string& n, const std::string& desc, float p, int q)
        : name(n), description(desc), price(p), quantity(q) {}

    float getPriceForQuantity() const {
        return price * quantity;
    }

    void setItem(const std::string& n, const std::string& desc, float p, int q){
        name = n;
        description = desc;
        price = p;
        quantity = q;
    }

    void displayItem() const {
        std::cout << "Item: " << name << ", Description: " << description
                  << ", Price: $" << price << ", Quantity: " << quantity << std::endl;
    }
};

class Order {
private:
    Date date;
    bool status;
    Item items[10]; 
    int itemCount;

public:
    Order() : status(false), itemCount(0) {} 

    void setOrder(const Date& d, bool s){
        date = d;
        status = s;
    }

    void addItem(const Item& item) {
        if (itemCount < 10) {
            items[itemCount++] = item;
        } else {
            std::cout << "Order is full. Cannot add more items." << std::endl;
        }
    }

    float calcTax() const {
        float total = calcTotal();
        return total * 0.08; 

    float calcTotal() const {
        float total = 0.0f;
        for (int i = 0; i < itemCount; ++i) {
            total += items[i].getPriceForQuantity();
        }
        return total;
    }

    void displayOrder() const {
        std::cout << "Order Date: ";
        date.displayDate();
        std::cout << ", Status: " << (status ? "Completed" : "Pending") << std::endl;
        std::cout << "Items:\n";
        for (int i = 0; i < itemCount; ++i) {
            items[i].displayItem();
        }
        std::cout << "Total: $" << calcTotal() << ", Tax: $" << calcTax() << std::endl;
    }
};

class Customer {
private:
    std::string name;
    std::string address;

public:
    Customer() {}
    Customer(const std::string& n, const std::string& addr) : name(n), address(addr) {}

    void setCustomer(const std::string &n, const std::string &addr){
        name = n;
        address = addr;
    }
    std::string getName() const { return name; }

    void displayCustomer() const {
        std::cout << "Customer Name: " << name << ", Address: " << address << std::endl;
    }
};

class Mart {
private:
    std::string name;
    Customer customers[50]; 
    int customerCount;
    Order orders[100];
    int orderCount;

public:
    Mart() : customerCount(0), orderCount(0) {}
    Mart(const std::string& martName) : name(martName), customerCount(0), orderCount(0) {}

    void setMart(const std::string& martName){
        name = martName;
    }

    void addCustomer(const Customer& customer) {
        if (customerCount < 50) {
            customers[customerCount++] = customer;
        } else {
            std::cout << "Mart is full. Cannot add more customers." << std::endl;
        }
    }

     void addOrder(const Order& order) {
        if (orderCount < 100) {
            orders[orderCount++] = order;
        } else {
            std::cout << "Mart orders are full. Cannot add more orders." << std::endl;
        }
    }

    void customerHistory(const std::string& customerName) const {
        std::cout << "Order history for Customer: " << customerName << std::endl;
        for (int i = 0; i < orderCount; ++i) {
            for(int j=0; j<customerCount; j++){
                orders[i].displayOrder();
            }

        }
    }

    float totalSale() const {
        float total = 0.0f;
        for (int i = 0; i < orderCount; ++i) {
            total += orders[i].calcTotal();
        }
        return total;
    }

    void displayMart() const {
        std::cout << "Mart Name: " << name << std::endl;
        std::cout << "\nCustomers:\n";
        for (int i = 0; i < customerCount; ++i) {
            customers[i].displayCustomer();
        }
        std::cout << "\nOrders:\n";
        for (int i = 0; i < orderCount; ++i) {
            orders[i].displayOrder();
        }
        std::cout << "\nTotal Sales: $" << totalSale() << std::endl;
    }
};

int main() {
    // Create a Mart
    Mart myMart("SuperMart");

    // Create Customers
    Customer customer1("Alice Smith", "123 Main St");
    Customer customer2("Bob Johnson", "456 Oak Ave");

    myMart.addCustomer(customer1);
    myMart.addCustomer(customer2);

    // Create some Items
    Item item1("Laptop", "High-performance laptop", 1200.0f, 1);
    Item item2("Mouse", "Wireless mouse", 25.0f, 2);
    Item item3("Keyboard", "Mechanical keyboard", 75.0f, 1);

    // Create an Order
    Order order1;
    Date orderDate(20, 3, 2025);
    order1.setOrder(orderDate, true);
    order1.addItem(item1);
    order1.addItem(item2);
    order1.addItem(item3);

    myMart.addOrder(order1);

    //Display Mart Details
    myMart.displayMart();

    return 0;
}