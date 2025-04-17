#include <iostream>
#include <cstring>

using namespace std;

class Package {
protected:
    // Sender information
    char senderName[50];
    char senderAddress[100];
    char senderCity[50];
    char senderState[50];
    char senderZIP[20];
    
    // Recipient information
    char recipientName[50];
    char recipientAddress[100];
    char recipientCity[50];
    char recipientState[50];
    char recipientZIP[20];
    
    // Package details
    double weight; // in ounces
    double costPerOunce;

public:
    Package(const char* sName, const char* sAddr, const char* sCity, const char* sState, const char* sZIP,
            const char* rName, const char* rAddr, const char* rCity, const char* rState, const char* rZIP,
            double w, double cpo) {
        
        // Copy sender info
        strncpy(senderName, sName, 49);
        senderName[49] = '\0';
        
        strncpy(senderAddress, sAddr, 99);
        senderAddress[99] = '\0';
        
        strncpy(senderCity, sCity, 49);
        senderCity[49] = '\0';
        
        strncpy(senderState, sState, 49);
        senderState[49] = '\0';
        
        strncpy(senderZIP, sZIP, 19);
        senderZIP[19] = '\0';
        
        // Copy recipient info
        strncpy(recipientName, rName, 49);
        recipientName[49] = '\0';
        
        strncpy(recipientAddress, rAddr, 99);
        recipientAddress[99] = '\0';
        
        strncpy(recipientCity, rCity, 49);
        recipientCity[49] = '\0';
        
        strncpy(recipientState, rState, 49);
        recipientState[49] = '\0';
        
        strncpy(recipientZIP, rZIP, 19);
        recipientZIP[19] = '\0';
        
        // Set weight and cost (with validation)
        weight = (w > 0.0) ? w : 1.0; // Default to 1 oz if invalid
        costPerOunce = (cpo > 0.0) ? cpo : 1.0; // Default to $1 if invalid
    }
    
    virtual ~Package() {}
    
    virtual double calculateCost() const {
        return weight * costPerOunce;
    }
    
    virtual void displayDetails() const {
        cout << "\nPackage Details:";
        cout << "\n----------------";
        cout << "\nSender Information:";
        cout << "\n  Name: " << senderName;
        cout << "\n  Address: " << senderAddress;
        cout << "\n  City: " << senderCity;
        cout << "\n  State: " << senderState;
        cout << "\n  ZIP: " << senderZIP;
        
        cout << "\n\nRecipient Information:";
        cout << "\n  Name: " << recipientName;
        cout << "\n  Address: " << recipientAddress;
        cout << "\n  City: " << recipientCity;
        cout << "\n  State: " << recipientState;
        cout << "\n  ZIP: " << recipientZIP;
        
        cout << "\n\nPackage Information:";
        cout << "\n  Weight: " << weight << " ounces";
        cout << "\n  Cost Per Ounce: $" << costPerOunce;
        cout << "\n  Shipping Cost: $" << calculateCost();
    }
    
    void getInfo() {
        cout << "\nEnter Sender Information:";
        cout << "\nName: ";
        cin.ignore();
        cin.getline(senderName, 50);
        
        cout << "Address: ";
        cin.getline(senderAddress, 100);
        
        cout << "City: ";
        cin.getline(senderCity, 50);
        
        cout << "State: ";
        cin.getline(senderState, 50);
        
        cout << "ZIP: ";
        cin.getline(senderZIP, 20);
        
        cout << "\nEnter Recipient Information:";
        cout << "\nName: ";
        cin.getline(recipientName, 50);
        
        cout << "Address: ";
        cin.getline(recipientAddress, 100);
        
        cout << "City: ";
        cin.getline(recipientCity, 50);
        
        cout << "State: ";
        cin.getline(recipientState, 50);
        
        cout << "ZIP: ";
        cin.getline(recipientZIP, 20);
        
        cout << "\nEnter Package Information:";
        cout << "\nWeight (in ounces): ";
        cin >> weight;
        
        // Validate weight
        while (weight <= 0.0) {
            cout << "Weight must be positive. Enter again: ";
            cin >> weight;
        }
        
        cout << "Cost per ounce: $";
        cin >> costPerOunce;
        
        // Validate cost per ounce
        while (costPerOunce <= 0.0) {
            cout << "Cost per ounce must be positive. Enter again: $";
            cin >> costPerOunce;
        }
    }
};

class TwoDayPackage : public Package {
private:
    double flatFee; 

public:
    TwoDayPackage(const char* sName, const char* sAddr, const char* sCity, const char* sState, const char* sZIP,
                  const char* rName, const char* rAddr, const char* rCity, const char* rState, const char* rZIP,
                  double w, double cpo, double fee)
        : Package(sName, sAddr, sCity, sState, sZIP, rName, rAddr, rCity, rState, rZIP, w, cpo) {
        
        flatFee = (fee > 0.0) ? fee : 5.0; // Default to $5 if invalid
    }
    
    double calculateCost() const override {
        return Package::calculateCost() + flatFee;
    }
    
    void displayDetails() const override {
        Package::displayDetails();
        cout << "\n  Two-Day Delivery Flat Fee: $" << flatFee;
        cout << "\n  Total Shipping Cost: $" << calculateCost();
    }
    
    void getInfo() {
        Package::getInfo();
        
        cout << "Two-Day Delivery Flat Fee: $";
        cin >> flatFee;
        
        // Validate flat fee
        while (flatFee <= 0.0) {
            cout << "Flat fee must be positive. Enter again: $";
            cin >> flatFee;
        }
    }
};

class OvernightPackage : public Package {
private:
    double additionalFeePerOunce; // Additional fee per ounce for overnight delivery

public:
    OvernightPackage(const char* sName, const char* sAddr, const char* sCity, const char* sState, const char* sZIP,
                     const char* rName, const char* rAddr, const char* rCity, const char* rState, const char* rZIP,
                     double w, double cpo, double addFee)
        : Package(sName, sAddr, sCity, sState, sZIP, rName, rAddr, rCity, rState, rZIP, w, cpo) {
        
        additionalFeePerOunce = (addFee > 0.0) ? addFee : 1.0; // Default to $1 if invalid
    }
    
    double calculateCost() const override {
        return weight * (costPerOunce + additionalFeePerOunce);
    }
    
    void displayDetails() const override {
        Package::displayDetails();
        cout << "\n  Overnight Additional Fee Per Ounce: $" << additionalFeePerOunce;
        cout << "\n  Total Cost Per Ounce: $" << (costPerOunce + additionalFeePerOunce);
        cout << "\n  Total Shipping Cost: $" << calculateCost();
    }
    
    void getInfo() {
        Package::getInfo();
        
        cout << "Overnight Additional Fee Per Ounce: $";
        cin >> additionalFeePerOunce;
        
        // Validate additional fee per ounce
        while (additionalFeePerOunce <= 0.0) {
            cout << "Additional fee per ounce must be positive. Enter again: $";
            cin >> additionalFeePerOunce;
        }
    }
};

// Array class to store packages
class PackageArray {
private:
    Package** packages;
    int count;
    int capacity;

public:
    PackageArray(int initialCapacity = 10) {
        capacity = (initialCapacity > 0) ? initialCapacity : 10;
        packages = new Package*[capacity];
        count = 0;
    }
    
    ~PackageArray() {
        for (int i = 0; i < count; ++i) {
            delete packages[i];
        }
        delete[] packages;
    }
    
    void addPackage(Package* package) {
        if (count >= capacity) {
            int newCapacity = capacity * 2;
            Package** newPackages = new Package*[newCapacity];
            
            for (int i = 0; i < count; ++i) {
                newPackages[i] = packages[i];
            }
            
            delete[] packages;
            packages = newPackages;
            capacity = newCapacity;
        }
        
        packages[count++] = package;
    }
    
    int getCount() const {
        return count;
    }
    
    // Display all packages
    void displayAllPackages() const {
        if (count == 0) {
            cout << "\nNo packages to display.\n";
            return;
        }
        
        cout << "\n===== ALL PACKAGES =====\n";
        for (int i = 0; i < count; ++i) {
            cout << "\nPackage #" << (i + 1);
            packages[i]->displayDetails();
            cout << "\n------------------------\n";
        }
    }
    
    double calculateTotalCost() const {
        double total = 0.0;
        for (int i = 0; i < count; ++i) {
            total += packages[i]->calculateCost();
        }
        return total;
    }
};

int main() {
    PackageArray packageArray;
    int choice;
    bool exit = false;
    
    while (!exit) {
        cout << "\n\n===== PACKAGE DELIVERY SERVICE =====\n";
        cout << "1. Add Two-Day Package\n";
        cout << "2. Add Overnight Package\n";
        cout << "3. Display All Packages\n";
        cout << "4. Calculate Total Shipping Cost\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                TwoDayPackage* package = new TwoDayPackage("", "", "", "", "", "", "", "", "", "", 0.0, 0.0, 0.0);
                package->getInfo();
                packageArray.addPackage(package);
                cout << "\nTwo-Day Package added successfully!\n";
                break;
            }
            case 2: {
                OvernightPackage* package = new OvernightPackage("", "", "", "", "", "", "", "", "", "", 0.0, 0.0, 0.0);
                package->getInfo();
                packageArray.addPackage(package);
                cout << "\nOvernight Package added successfully!\n";
                break;
            }
            case 3:
                packageArray.displayAllPackages();
                break;
            case 4:
                cout << "\nTotal Shipping Cost for all packages: $" << packageArray.calculateTotalCost() << endl;
                break;
            case 5:
                exit = true;
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}