#include <iostream>
#include <cstring>

using namespace std;

// Part (a) and (c)
class Publication {
protected:
    char title[100];
    float price;
public:
    Publication() {
        strcpy(title, "");
        price = 0.0;
    }
    
    virtual void getdata() {
        cout << "Enter title: ";
        cin.ignore();
        cin.getline(title, 100);
        cout << "Enter price: $";
        cin >> price;
        
        // Validate price
        while (price < 0) {
            cout << "Price cannot be negative. Enter again: $";
            cin >> price;
        }
    }
    
    virtual void putdata() const {
        cout << "\nTitle: " << title;
        cout << "\nPrice: $" << price;
    }
    
    virtual ~Publication() {}
};

class Book : public Publication {
private:
    int pageCount;
public:
    Book() : pageCount(0) {}
    
    void getdata() override {
        Publication::getdata();
        cout << "Enter page count: ";
        cin >> pageCount;
        
        // Validate page count
        while (pageCount <= 0) {
            cout << "Page count must be positive. Enter again: ";
            cin >> pageCount;
        }
    }
    
    void putdata() const override {
        Publication::putdata();
        cout << "\nPage Count: " << pageCount;
    }
};

class Tape : public Publication {
private:
    float playingTime;
public:
    Tape() : playingTime(0.0) {}
    
    void getdata() override {
        Publication::getdata();
        cout << "Enter playing time (minutes): ";
        cin >> playingTime;
        
        // Validate playing time
        while (playingTime <= 0) {
            cout << "Playing time must be positive. Enter again: ";
            cin >> playingTime;
        }
    }
    
    void putdata() const override {
        Publication::putdata();
        cout << "\nPlaying Time: " << playingTime << " minutes";
    }
};

class Disk : public Publication {
private:
    char diskType; 
public:
    Disk() : diskType('c') {}
    
    void getdata() override {
        Publication::getdata();
        cout << "Enter disk type (c for CD, d for DVD): ";
        cin >> diskType;
        
        // Validate disk type
        while (diskType != 'c' && diskType != 'd' && diskType != 'C' && diskType != 'D') {
            cout << "Invalid disk type. Enter again (c for CD, d for DVD): ";
            cin >> diskType;
        }
    }
    
    void putdata() const override {
        Publication::putdata();
        cout << "\nDisk Type: " << (diskType == 'c' || diskType == 'C' ? "CD" : "DVD");
    }
};

// Part (b)
class Sales {
private:
    float salesData[3];
public:
    Sales() {
        for (int i = 0; i < 3; i++) {
            salesData[i] = 0.0;
        }
    }
    
    void getdata() {
        cout << "Enter sales for last 3 months:\n";
        for (int i = 0; i < 3; i++) {
            cout << "Month " << (i + 1) << ": $";
            cin >> salesData[i];
            
            // Validate sales
            while (salesData[i] < 0) {
                cout << "Sales cannot be negative. Enter again: $";
                cin >> salesData[i];
            }
        }
    }
    
    void putdata() const {
        cout << "\nSales for last 3 months:";
        for (int i = 0; i < 3; i++) {
            cout << "\nMonth " << (i + 1) << ": $" << salesData[i];
        }
    }
};

class BookWithSales : public Book, public Sales {
public:
    void getdata() override {
        Book::getdata();
        Sales::getdata();
    }
    
    void putdata() const override {
        Book::putdata();
        Sales::putdata();
    }
};

class TapeWithSales : public Tape, public Sales {
public:
    void getdata() override {
        Tape::getdata();
        Sales::getdata();
    }
    
    void putdata() const override {
        Tape::putdata();
        Sales::putdata();
    }
};

class DiskWithSales : public Disk, public Sales {
public:
    void getdata() override {
        Disk::getdata();
        Sales::getdata();
    }
    
    void putdata() const override {
        Disk::putdata();
        Sales::putdata();
    }
};

int main() {
    int choice;
    bool exit = false;
    
    while (!exit) {
        cout << "\n\n----- PUBLISHING COMPANY MENU -----\n";
        cout << "1. Test Book and Tape classes (Part a)\n";
        cout << "2. Test Book and Tape with Sales (Part b)\n";
        cout << "3. Test Book, Tape, and Disk with Sales (Part c)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                // Part (a) test
                cout << "\n----- BOOK DATA -----\n";
                Book book;
                book.getdata();
                cout << "\n----- BOOK DETAILS -----";
                book.putdata();
                
                cout << "\n\n----- TAPE DATA -----\n";
                Tape tape;
                tape.getdata();
                cout << "\n----- TAPE DETAILS -----";
                tape.putdata();
                break;
            }
            case 2: {
                // Part (b) test
                cout << "\n----- BOOK WITH SALES DATA -----\n";
                BookWithSales bookWithSales;
                bookWithSales.getdata();
                cout << "\n----- BOOK WITH SALES DETAILS -----";
                bookWithSales.putdata();
                
                cout << "\n\n----- TAPE WITH SALES DATA -----\n";
                TapeWithSales tapeWithSales;
                tapeWithSales.getdata();
                cout << "\n----- TAPE WITH SALES DETAILS -----";
                tapeWithSales.putdata();
                break;
            }
            case 3: {
                // Part (c) test
                cout << "\n----- DISK WITH SALES DATA -----\n";
                DiskWithSales diskWithSales;
                diskWithSales.getdata();
                cout << "\n----- DISK WITH SALES DETAILS -----";
                diskWithSales.putdata();
                break;
            }
            case 4:
                exit = true;
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}