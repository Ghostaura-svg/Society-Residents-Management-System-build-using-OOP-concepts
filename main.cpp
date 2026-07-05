#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <map>
using namespace std;

void exception_num(string &roll ){
    int cou=0;
    do
{
    cou=0;
    for(int i=0;i<roll.length(); i++)
    {
       for(int j=48;j<=57;j++)
       {
           if(roll[i]==j)
           {
               cou++;
           }
       }
    }
    try{
    if(cou!=roll.length())
    {
        throw(cou);
    }
    }
    catch(int c)
    {
        cout<< "Enter the Roll No Only in the Numbers:  ";
        cin>> roll;
    }
}while(cou!=roll.length());
}

void exception_str(string &name){
    int cou=0;
    do
{
    cou=0;
    for(int i=0;i<name.length(); i++)
    {
           if((name[i]>64 && name[i]<91) || (name[i]>96 && name[i]<123) || name[i]==32 )
           {
               cou++;
           }
    }
    try{
    if(cou!=name.length())
    {
        throw(cou);
    }
    }
    catch(int c)
    {
        cout<< "Enter the Data Only in Alphabets:  ";
        cin.ignore();
        getline(cin,name);
    }
}while(cou!=name.length());
}

class House {
private:
    int marlaSize;
    int choice;

public:
    House(int size = 0) : marlaSize(size), choice(0) {}

    void askHouseRequirement() {
        while (choice != 1 && choice != 2 && choice != 3) {
            cout << "Available house sizes (in marlas):\n";
            cout << "1. 5 marla\n";
            cout << "2. 10 marla\n";
            cout << "3. 20 marla\n";
            cout << "Choose your house size (1-3): ";
            cin >> choice;

            switch (choice) {
                case 1:
                    marlaSize = 5;
                    break;
                case 2:
                    marlaSize = 10;
                    break;
                case 3:
                    marlaSize = 20;
                    break;
                default:
                    cout << "Invalid choice, Please select again\n";
                    break;
            }
        }
    }

    void showHouseDetails() const {
        cout << "Assigned house of " << marlaSize << " marlas." << endl;
    }

    int getMarlaSize() const {
        return marlaSize;
    }

    void setMarlaSize(int size) {
        marlaSize = size;
    }
};

class Resident {
public:
    string username;
    string password;
    string name;
    string phone;
    double balance;
    House house;

public:
    Resident() : balance(0) {}

    void registerResident() {
        cin.ignore();
        cout << "Enter Your Good Name: ";
        getline(cin, name);
        exception_str(name);
        cout << "Enter 11 digit Phone Number: ";
        getline(cin, phone);
        exception_num(phone);
        while(phone.length() < 11 || phone.length() > 11)
        {
        cout << "Enter 11 digit Phone Number: ";
        getline(cin, phone);
        exception_num(phone);

        }
        cout << "Enter your bank balance: ";
        cin >> balance;
        house.askHouseRequirement();
    }

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    void setCredentials(string u, string p) {
        username = u;
        password = p;
    }

    void showResidentDetails() const {
        cout << "\n--- Resident Details ---\n";
        cout << "Username: " << username << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        house.showHouseDetails();
    }
};

class Complaint : public Resident {
private:
    string complaintType;
    string complaintDetails;
    bool complaintFiled;

public:
    Complaint() : complaintFiled(false) {}

    void registerComplaint() {
        cout << "\n--- Register a Complaint ---\n";
        cout << "Select Complaint Type:\n";
        cout << "1. Water Issue\n";
        cout << "2. Electricity Issue\n";
        cout << "3. Security Issue\n";
        cout << "4. Other\n";
        cout << "Enter choice (1-4): ";

        int typeChoice;
        cin >> typeChoice;
        cin.ignore();

        switch (typeChoice) {
            case 1:
                complaintType = "Water Issue";
                break;
            case 2:
                complaintType = "Electricity Issue";
                break;
            case 3:
                complaintType = "Security Issue";
                break;
            case 4:
                complaintType = "Other";
                break;
            default:
                complaintType = "Unknown";
                break;
        }

        cout << "Please describe the issue in detail: ";
        getline(cin, complaintDetails);

        if (complaintDetails.empty()) {
            cout << "Complaint details cannot be empty. Try again.\n";
            return;
        }

        complaintFiled = true;

        ofstream fout("complaints.txt", ios::app);
        if (fout.is_open()) {
            fout << "Username: " << getUsername() << endl;
            fout << "Complaint Type: " << complaintType << endl;
            fout << "Details: " << complaintDetails << endl;
            fout << "------------------------------\n";
            fout.close();
        }

        cout << "Complaint registered successfully.\n";
    }

    void showComplaintDetails() const {
        if (!complaintFiled) {
            cout << "You haven't filed any complaint yet.\n";
        } else {
            cout << "\n--- Complaint Details ---\n";
            cout << "Complaint Type: " << complaintType << endl;
            cout << "Details: " << complaintDetails << endl;
        }
    }

    bool hasComplaint() const {
        return complaintFiled;
    }

    void inheritResident(const Resident& r) {
        setCredentials(r.getUsername(), r.getPassword());
        name = r.name;
        phone = r.phone;
        balance = r.balance;
        house = r.house;
    }
};

class Bill : public Resident, public House {
protected:
    float amount, p_amount;
    string date;

public:
    Bill() : amount(0), p_amount(0) {}

    void setResidentData(const Resident& r) {
        setCredentials(r.getUsername(), r.getPassword());
        name = r.name;
        phone = r.phone;
        balance = r.balance;
        house = r.house;
        setMarlaSize(r.house.getMarlaSize()); // Explicitly set House base class marlaSize
    }

     float calculateBill() {
        int size = getMarlaSize();
        cout << "Debug: House size in calculateBill: " << size << endl; // Debug output
        if (size == 5) amount = 3000 * 1.05;
        else if (size == 10) amount = 5000 * 1.10;
        else if (size == 20) amount = 8000 * 1.15;
        else amount = 0; // Default case for invalid size
        cout << "Debug: Calculated amount: " << amount << endl; // Debug output
        return amount;
    }

    void displayBill(int d, int m) {
        cout << "Due Date: " << 9 << endl;
        cout << "Username: " << getUsername() << endl;
        cout << "Resident Name: " << name << endl;
        cout << "House Size: " << getMarlaSize() << " Marla/Kanal" << endl;
        cout << "Bill Amount: Rs. " << amount << endl;
    }

    void penalty(int daygone, float& p_amount) {
        p_amount = daygone * 97.3;
        cout << "Your Penalty is " << p_amount << endl;
        cout << "Your Final Amount of the Bill is " << (p_amount + amount) << endl;
        p_amount = p_amount + amount;
    }

    void paybill(float pbill) {
        if (balance >= pbill) {
            balance = balance - pbill;
            cout << "Congrats, Your Bill is Paid Successfully" << endl;
            cout << "Your Bank Balance is " << balance << endl;
        } else {
            cout << "Insufficient balance to pay the bill!" << endl;
        }
    }
};

class ElectricityBill : virtual public Bill {
    float pbill;
    int pday;

public:
    float ecalculateBill() {
        return Bill::calculateBill();
    }

    void edisplay(int d, int m) {
        displayBill(d, m);
    }

    void pay(int d) {
        pbill = amount;
        if (d > 9) {
            cout << "The Due date of the Bill is Gone, Now you Pay Extra Charges" << endl;
            pday = d - 9;
            penalty(pday, pbill);
            paybill(pbill);
        } else {
            paybill(pbill);
        }
    }
};

class Security : virtual public Bill {
    float pbill;
    int pday;

public:
    void scalculateBill(int c, string k) {
        if (k == "s") {
            amount = c * 1000;
        }
        if (k == "c") {
            amount = c * 500;
        }
    }

    void display() {
        cout << "Security Bill Amount: Rs. " << amount << endl;
    }
};

class Gas : virtual public Bill {
    float pbill;
    int pday;

public:
    float gcalculateBill() {
        return Bill::calculateBill();
    }

    void gdisplay(int d, int m) {
        displayBill(d, m);
    }

    void gpay(int d) {
        pbill = amount;
        if (d > 9) {
            cout << "The Due date of the Bill is Gone, Now you Pay Extra Charges" << endl;
            pday = d - 9;
            penalty(pday, pbill);
            paybill(pbill);
        } else {
            paybill(pbill);
        }
    }
};

class billsystem : public ElectricityBill, public Gas, public Security {
    int pday, ch;
    float billamount;

public:
    void setResidentData(const Resident& r) {
        ElectricityBill::setResidentData(r);
        Gas::setResidentData(r);
        Security::setResidentData(r);
    }

    void elec(int d, int m, const Resident& r) {
        setResidentData(r);
        billamount = ecalculateBill(); // Ensure bill is calculated
        edisplay(d, m);
        cout << "Press 1 to pay Your Bill: " << endl;
        cout << "Press any number to Exit: " << endl;
        cin >> pday;
        if (pday == 1) {
            pay(d);
        }
    }

    void gas(int d, int m, const Resident& r) {
        setResidentData(r);
        billamount = gcalculateBill();
        gdisplay(d, m);
        cout << "Press 1 to pay Your Bill: " << endl;
        cout << "Press any number to Exit: " << endl;
        cin >> pday;
        if (pday == 1) {
            gpay(d);
        }
    }

    void sec(int d, int m, const Resident& r) {
        setResidentData(r);
        cout << "Welcome Dear, we have the following Security Facilities" << endl;
        cout << "1. Security Guards\n";
        cout << "2. CCTV Monitoring\n";
        cin >> ch;
        if (ch == 1) {
            cout << "The charges per Security Guard are fixed per Month. Extra charges depend on house size\n";
            cout << "1. One Guard\n";
            cout << "2. Two Guards\n";
            cin >> ch;
            if (ch == 1 || ch == 2) {
                scalculateBill(ch, "s");
                display();
            } else {
                cout << "Invalid choice\n";
            }
        } else if (ch == 2) {
            cout << "The charges per CCTV are fixed per Month. Extra charges depend on quantity\n";
            cout << "Please Enter Number of CCTVs: ";
            cin >> ch;
            scalculateBill(ch, "c");
            display();
        } else {
            cout << "Invalid choice\n";
        }
    }
};

class Event {
public:
    string id;
    string name;
    string date;
    int capacity;
    string ticketType;
    double ticketPrice;
    vector<string> bookedUsers;

    Event(string id, string name, string date, int capacity, string ticketType, double ticketPrice)
        : id(id), name(name), date(date), capacity(capacity), ticketType(ticketType), ticketPrice(ticketPrice) {}
};

class EventManager {
private:
    vector<Event> events;

public:
    void addEvent(Event event) {
        events.push_back(event);
    }

    void displayEvents() {
        cout << "\nAvailable Events:\n";
        cout << "ID\tName\t\tDate\t\tCapacity\tBooked\tTicket Type\tPrice($)\n";
        for (const auto& event : events) {
            cout << event.id << "\t" << event.name << "\t" << event.date << "\t"
                 << event.capacity << "\t\t" << event.bookedUsers.size() << "\t"
                 << event.ticketType << "\t\t" << event.ticketPrice << "\n";
        }
    }
    bool bookEvent(string userId, string eventId) {
        // Check if user has already booked an event on the same day
        for (const auto& event : events) {
            for (const auto& bookedUser : event.bookedUsers) {
                if (bookedUser == userId) {
                    for (const auto& targetEvent : events) {
                        if (targetEvent.id == eventId && targetEvent.date == event.date) {
                            cout << "Booking failed. You already have a booking on " << event.date << ".\n";
                            return false;
                        }
                    }
                }
            }
        }

        for (auto& event : events) {
            if (event.id == eventId && event.bookedUsers.size() < event.capacity) {
                for (const auto& bookedUser : event.bookedUsers) {
                    if (bookedUser == userId) {
                        return false; // User already booked this event
                    }
                }
                event.bookedUsers.push_back(userId);
                cout << "Ticket Type: " << event.ticketType << ", Price: $" << event.ticketPrice << "\n";
                return true;
            }
        }
        return false;
    }

    bool cancelBooking(string userId, string eventId) {
        for (auto& event : events) {
            if (event.id == eventId) {
                for (auto it = event.bookedUsers.begin(); it != event.bookedUsers.end(); ++it) {
                    if (*it == userId) {
                        event.bookedUsers.erase(it);
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void displayUserBookings(string userId) {
        cout << "\nYour Bookings:\n";
        cout << "Event ID\tEvent Name\tDate\t\tTicket Type\tPrice($)\n";
        for (const auto& event : events) {
            for (const auto& bookedUser : event.bookedUsers) {
                if (bookedUser == userId) {
                    cout << event.id << "\t\t" << event.name << "\t" << event.date << "\t"
                         << event.ticketType << "\t\t" << event.ticketPrice << "\n";
                }
            }
        }
    }
};

class Member {
private:
    string name;
    string id;
    EventManager& manager;

public:
    Member(string name, string id, EventManager& manager)
        : name(name), id(id), manager(manager) {}

    void displayMenu() {
        cout << "\nEvent Booking Menu\n";
        cout << "1. View Available Events\n";
        cout << "2. Book Event\n";
        cout << "3. Cancel Booking\n";
        cout << "4. View Booking History\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            manager.displayEvents();
        } else if (choice == 2) {
            string eventId;
            cout << "Enter Event ID to book: ";
            getline(cin, eventId);
            if (manager.bookEvent(id, eventId)) {
                cout << "Booking successful!\n";
            } else {
                cout << "Booking failed. Event may be full, not exist, or you have a conflicting booking.\n";
            }
        } else if (choice == 3) {
            string eventId;
            cout << "Enter Event ID to cancel: ";
            getline(cin, eventId);
            if (manager.cancelBooking(id, eventId)) {
                cout << "Booking cancelled successfully!\n";
            } else {
                cout << "Cancellation failed. Booking may not exist.\n";
            }
        } else if (choice == 4) {
            manager.displayUserBookings(id);
        } else if (choice == 5) {
            exit(0);
        }
    }
};

class Account {
protected:
    string username;
    string password;

public:
    Account() {}

    virtual string displayRole() {
        return "Account";
    }

    string getUsername() { return username; }
    string getPassword() { return password; }
};

class Product {
private:
    string name;
    int quantity;
    double price;

public:
    Product() {}

    Product(string n, int q, double p) {
        name = n;
        quantity = q;
        price = p;
    }

    string getName() { return name; }
    int getQuantity() { return quantity; }
    double getPrice() { return price; }

    void setQuantity(int q) { quantity = q; }
    void setPrice(double p) { price = p; }

    void updateQuantity(int newQuantity) {
        quantity += newQuantity;
    }

    bool buyProduct(int qty = 1) {
        if (quantity >= qty) {
            quantity -= qty;
            return true;
        }
        return false;
    }

    void displayProduct() {
        cout << left << setw(20) << name
             << setw(10) << quantity
             << "$" << fixed << setprecision(2) << price << endl;
    }
};

class CartItem {
public:
    Product product;
    int quantity;

    CartItem(Product p, int q) : product(p), quantity(q) {}

    double getTotalPrice() {
        return product.getPrice() * quantity;
    }

    void display() {
        cout << left << setw(20) << product.getName()
             << setw(8) << quantity
             << "$" << fixed << setprecision(2) << product.getPrice()
             << " | Total: $" << getTotalPrice() << endl;
    }
};

class Cart {
private:
    vector<CartItem> cartItems;

public:
    void addItem(Product product, int quantity) {
        for (int i = 0; i < cartItems.size(); i++) {
            if (cartItems[i].product.getName() == product.getName()) {
                cartItems[i].quantity += quantity;
                return;
            }
        }
        cartItems.push_back(CartItem(product, quantity));
    }

    void removeItem(string name) {
        for (int i = 0; i < cartItems.size(); i++) {
            if (cartItems[i].product.getName() == name) {
                cartItems.erase(cartItems.begin() + i);
                cout << "Item removed from cart!" << endl;
                return;
            }
        }
        cout << "Item not found in cart!" << endl;
    }

    void viewCart() {
        if (cartItems.empty()) {
            cout << "Your cart is empty!" << endl;
            return;
        }

        cout << "\n YOUR CART " << endl;
        cout << left << setw(20) << "Product"
             << setw(8) << "Qty"
             << setw(15) << "Unit Price"
             << "Total" << endl;
        cout << "------------------------------------------------------------------------" << endl;

        for (int i = 0; i < cartItems.size(); i++) {
            cartItems[i].display();
        }
        cout << "------------------------------------------------------------------------" << endl;
        cout << "Total Bill: $" << fixed << setprecision(2) << calculateTotal() << endl;
    }

    double calculateTotal() {
        double total = 0;
        for (int i = 0; i < cartItems.size(); i++) {
            total += cartItems[i].getTotalPrice();
        }
        return total;
    }

    vector<CartItem> &getItems() { return cartItems; }

    void clearCart() { cartItems.clear(); }

    bool isEmpty() { return cartItems.empty(); }
};

class Admin : public Account {
public:
    void createAdmin(string u, string p) {
        username = u;
        password = p;
    }

    string displayRole() {
        return "Admin";
    }

    void saveCredentials() {
        ofstream file("admin.txt", ios::app);
        if (file.is_open()) {
            file << username << " " << password << endl;
            file.close();
        }
    }

    bool findAdmin(string u, string p) {
        ifstream file("admin.txt");
        string fileUser, filePass;
        while (file >> fileUser >> filePass) {
            if (fileUser == u && filePass == p) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
};

class User : public Account {
private:
    string email;

public:
    string displayRole() {
        return "User";
    }

    void registerUser(string u, string p, string e) {
        username = u;
        password = p;
        email = e;
    }

    void saveUserCredits() {
        ofstream file("user.txt", ios::app);
        if (file.is_open()) {
            file << username << " " << password << " " << email << endl;
            file.close();
        }
    }

    bool findUser(string u, string p) {
        ifstream file("user.txt");
        string fileUser, filePass, fileEmail;
        while (file >> fileUser >> filePass >> fileEmail) {
            if (fileUser == u && filePass == p) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
};

class Store {
private:
    vector<Product> products;

public:
    void loadProducts() {
        products.clear();
        ifstream file("products.txt");
        string name;
        int quantity;
        double price;

        while (file >> name >> quantity >> price) {
            for (int i = 0; i < name.length(); i++) {
                if (name[i] == '_')
                    name[i] = ' ';
            }
            products.push_back(Product(name, quantity, price));
        }
        file.close();
    }

    void saveProducts() {
        ofstream file("products.txt");
        for (int i = 0; i < products.size(); i++) {
            string name = products[i].getName();
            for (int j = 0; j < name.length(); j++) {
                if (name[j] == ' ')
                    name[j] = '_'; // just for convience changing spaces with underscore for better analyzing of data if admin useses this data for analysis
            }
            file << name << " " << products[i].getQuantity() << " " << products[i].getPrice() << endl;
        }
        file.close();
    }

    void addProduct() {
        string name;
        int quantity;
        double price;

        cout << "Enter product name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter price: $";
        cin >> price;

        for (int i = 0; i < products.size(); i++) {
            if (products[i].getName() == name) {
                products[i].updateQuantity(quantity);
                saveProducts();
                cout << "Product quantity updated!" << endl;
                return;
            }
        }

        Product newProduct(name, quantity, price);
        products.push_back(newProduct);
        saveProducts();
        cout << "Product added successfully!" << endl;
    }

    void updatePrice() {
        string name;
        double price;

        cout << "Enter product name to update price: ";
        cin.ignore();
        getline(cin, name);

        for (int i = 0; i < products.size(); i++) {
            if (products[i].getName() == name) {
                cout << "Current price: $" << products[i].getPrice() << endl;
                cout << "Enter new price: $";
                cin >> price;
                products[i].setPrice(price);
                saveProducts();
                cout << "Price updated successfully!" << endl;
                return;
            }
        }
        cout << "Product not found!" << endl;
    }

    void showAvailableItems() {
        loadProducts();
        if (products.empty()) {
            cout << "No products available!" << endl;
            return;
        }

        cout << "\n=== AVAILABLE PRODUCTS ===" << endl;
        cout << left << setw(20) << "Product Name"
             << setw(10) << "Stock"
             << "Price" << endl;
        cout << string(40, '-') << endl;

        for (int i = 0; i < products.size(); i++) {
            if (products[i].getQuantity() > 0) {
                products[i].displayProduct();
            }
        }
        cout << string(40, '-') << endl;
    }

    Product *findProduct(string name) {
        for (int i = 0; i < products.size(); i++) {
            if (products[i].getName() == name) {
                return &products[i];
            }
        }
        return nullptr;
    }

    bool buyProduct(string name, int quantity) {
        Product *product = findProduct(name);
        if (product && product->buyProduct(quantity)) {
            saveProducts();
            return true;
        }
        return false;
    }

    vector<Product> getProducts() { return products; }
};

class InvoiceGenerator {
public:
    void generateInvoice(string username, Cart &cart) {
        if (cart.isEmpty()) {
            cout << "Cannot generate invoice for empty cart!" << endl;
            return;
        }

        time_t now = time(0);
        string filename = "invoice_" + username + ".txt";

        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error creating invoice file!" << endl;
            return;
        }
        file << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
        file << "                 INVOICE                        " << endl;
        file << "888888888888888888888888888888888888888888888888" << endl;
        file << "Customer: " << username << endl;
        file << "Date: " << ctime(&now);
        file << "________________________________________________" << endl;
        file << left << setw(20) << "Product"
             << setw(8) << "Qty"
             << setw(12) << "Unit Price"
             << "Total" << endl;
        file << "___________________________________________________" << endl;

        vector<CartItem> &items = cart.getItems();
        for (int i = 0; i < items.size(); i++) {
            file << left << setw(20) << items[i].product.getName()<< setw(8) << items[i].quantity
                 << "$" << setw(11) << fixed << setprecision(2) << items[i].product.getPrice()
                 << "$" << items[i].getTotalPrice() << endl;
        }

        file << "------------------------------------------------" << endl;
        file << "TOTAL AMOUNT: $" << fixed << setprecision(2) << cart.calculateTotal() << endl;
        file << "________________________________________________" << endl;
        file << "        Thank you for your purchase!            " << endl;
        file << "________________________________________________" << endl;

        file.close();
        cout << "Invoice generated: " << filename << endl;
        cout << "Total Amount: $" << fixed << setprecision(2) << cart.calculateTotal() << endl;
    }
};

bool adminLogin() {
    string username, password;
    Admin admin;

    cout << "\n---- ADMIN LOGIN ----" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (admin.findAdmin(username, password)) {
        cout << "Admin login successful!" << endl;
        return true;
    }
    else {
        cout << "Invalid admin credentials!" << endl;
        return false;
    }
}

bool userLogin(string &username) {
    string password;
    User user;

    cout << "\n=== USER LOGIN ===" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (user.findUser(username, password)) {
        cout << "Login successful! Welcome " << username << "!" << endl;
        return true;
    }
    else {
        cout << "Invalid credentials!" << endl;
        return false;
    }
}

bool userRegister() {
    string username, password, email;
    User user;

    cout << "\n=== USER REGISTRATION ===" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter email: ";
    cin >> email;

    user.registerUser(username, password, email);
    user.saveUserCredits();

    cout << "Registration successful! You can now login." << endl;
    return true;
}

void adminMenu(Store &store) {
    int choice;

    while (true) {
        cout << "\n---- ADMIN MENU -----" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Update Product Price" << endl;
        cout << "3. View All Products" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            store.addProduct();
            break;
        case 2:
            store.updatePrice();
            break;
        case 3:
            store.showAvailableItems();
            break;
        case 4:
            cout << "Admin logged out successfully!" << endl;
            return;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}

void userMenu(Store &store, string username) {
    Cart cart;
    InvoiceGenerator invoiceGen;
    int choice;

    while (true) {
        cout << "\n=== USER MENU ===" << endl;
        cout << "1. View Products" << endl;
        cout << "2. Add to Cart" << endl;
        cout << "3. View Cart" << endl;
        cout << "4. Remove from Cart" << endl;
        cout << "5. Checkout & Generate Invoice" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            store.showAvailableItems();
            break;
        case 2: {
            store.showAvailableItems();
            string productName;
            int quantity;

            cout << "Enter product name to add to cart: ";
            cin.ignore();
            getline(cin, productName);

            Product *product = store.findProduct(productName);
            if (product && product->getQuantity() > 0) {
                cout << "Enter quantity (Available: " << product->getQuantity() << "): ";
                cin >> quantity;

                if (quantity > 0 && quantity <= product->getQuantity()) {
                    cart.addItem(*product, quantity);
                    cout << "Item added to cart!" << endl;
                }
                else {
                    cout << "Invalid quantity!" << endl;
                }
            }
            else {
                cout << "Product not found or out of stock!" << endl;
            }
            break;
        }
        case 3:
            cart.viewCart();
            break;
        case 4: {
            cart.viewCart();
            if (!cart.isEmpty()) {
                string productName;
                cout << "Enter product name to remove: ";
                cin.ignore();
                getline(cin, productName);
                cart.removeItem(productName);
            }
            break;
        }
        case 5: {
            if (cart.isEmpty()) {
                cout << "Your cart is empty!" << endl;
                break;
            }

            cart.viewCart();
            cout << "\nConfirm purchase? (y/n): ";
            char confirm;
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                vector<CartItem> &items = cart.getItems();
                bool success = true;

                for (int i = 0; i < items.size(); i++) {
                    if (!store.buyProduct(items[i].product.getName(), items[i].quantity)) {
                        success = false;
                        cout << "Error: " << items[i].product.getName()
                             << " is out of stock!" << endl;
                    }
                }

                if (success) {
                    invoiceGen.generateInvoice(username, cart);
                    cart.clearCart();
                    cout << "Purchase completed successfully!" << endl;
                }
            }
            break;
        }
        case 6:
            cout << "User logged out successfully!" << endl;
            return;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}

class Doctor {
public:
    string name;
    string contact_no;
    bool is_available;

    Doctor(string n, string cont_n)
        : name(n), contact_no(cont_n), is_available(true) {}

    void book_appointment() {
        is_available = false;
    }
};

class Patient {
public:
    string disease;
    Doctor* d;

    void book_doctor() {
             d->book_appointment();
        }
};

class Hospital {
public:
    static const int max_doctors = 10;
    static const int max_diseases = 5;
    static const int max_patients = 10;

    Doctor* d1[max_doctors];
    Patient p1[max_patients];
    int patient_count = 0;

    Hospital() {
        d1[0] = new Doctor("Dr. Ali", "+92321-3747345");
        d1[1] = new Doctor("Dr. Naqvi", "+92345-2372099");
        d1[2] = new Doctor("Dr. Ahmed", "+92365-3248593");
        d1[3] = new Doctor("Dr. Fahad", "+92325-5783239");
        d1[4] = new Doctor("Dr. Raheel", "+92312-9080901");
        d1[5] = new Doctor("Dr. Siddique", "+92318-2849229");
        d1[6] = new Doctor("Dr. Jahanzaib", "+92323-4522907");
        d1[7] = new Doctor("Dr. Maheen", "+92345-7264786");
        d1[8] = new Doctor("Dr. Abdullah", "+92335-2873912");
        d1[9] = new Doctor("Dr. Zainab", "+92321-4545534");
    }

    ~Hospital() {
        for (int i = 0; i < max_doctors; i++) {
            delete d1[i];
        }
    }

    void register_patient() {
        if (patient_count >= max_patients) {
            cout << "Patient limit reached!\n";
            return;
        }

        Patient& p = p1[patient_count++];
        cout << "Select disease:\n";
        cout << "1. Fever\n2. Headache\n3. Malaria\n4. Typhoid\n5. Diabetes\n";
        int diseasechoice;
        cout << "Enter choice (1-5): ";
        cin >> diseasechoice;

        if (diseasechoice < 1 || diseasechoice > max_diseases) {
            cout << "Invalid selection!\n";
            return;
        }

        static const string diseases[max_diseases] = {
            "Fever", "Headache", "Malaria", "Typhoid", "Diabetes"
        };
        p.disease = diseases[diseasechoice - 1];

        int doctor_start = (diseasechoice - 1) * 2;
        int option_count = 0;

        cout << "\nSelect one of the following options:\n";
        for (int i = doctor_start; i < doctor_start + 2 && option_count < 2; i++) {
            if (d1[i]->is_available) {
                cout << option_count + 1 << ". Consult " << d1[i]->name
                     << " (" << d1[i]->contact_no << ")\n";
                option_count++;
            }
        }

        cout << option_count + 1 << ". Follow suggested treatment without doctor consultation\n";

        int selection;
        cout << "Enter choice (1-3): ";
        cin >> selection;

        if (selection >= 1 && selection <= option_count) {
            p.d = d1[selection - 1];
            p.book_doctor();
            cout << "\nAppointment booked!\n";
            cout << "Disease: " << p.disease << endl;
            cout << "Doctor: Dr. " << p.d->name << endl;
        } else if (selection == option_count + 1) {
            cout << "\nYou chose to follow the suggested treatment.\n";
        } else {
            cout << "Invalid choice!\n";
            return;
        }

        cout << "Suggested Treatment: ";
        switch (diseasechoice) {
        case 1:
            cout << "Rest, hydration, and antipyretics.\n1. Paracetamol \n2.Ibuprofen \n3.Dipyrone\n ";
            break;
        case 2:
            cout << "Pain relievers, hydration, and rest.\n1. Paracetamol \n2.Ibuprofen \n3.Aspirin \n";
            break;
        case 3:
            cout << "Antimalarial medications as prescribed.\n Uncomplicated Malaria: \n1.Artemether-lumefantrine (Coartem, Riamet, Lonart):\n2.Artesunate-amodiaquine (ASAQ)\n3.Artesunate-mefloquine\nSevere Malaria \n1.Intravenous (IV) or intramuscular (IM) artesunate\n ";
            break;
        case 4:
            cout << "Antibiotics and supportive care.\n1.Azithromycin\n 2. Ceftriaxone\n 3. Chloramphenicoln 4.Cefixime\n";
            break;
        case 5:
            cout << "Blood sugar monitoring and insulin therapy.\n1. Metformin\n 2.Sulfonylureas\n 3.DPP-4 Inhibitors\n 4.SGLT2 Inhibitors\n5.Alpha-Glucosidase Inhibitors\n";
            break;
        }
    }

    void emergency_case() {
        cout << "\nEMERGENCY PROTOCOL ACTIVATED!\n";
        for (int i = 0; i < max_doctors; i++) {
            if (d1[i]->is_available) {
                cout << "Dr. " << d1[i]->name << " booked for emergency\n";
                d1[i]->book_appointment();
                return;
            }
        }
        cout << "No doctors available! Please wait\n";
    }
};

class workflow : public Resident {
private:
    int sizee = 5, cap = 0, subChoice;
    int c = 0;
    int option;
    billsystem paid;
    Complaint* object = new Complaint[sizee];

public:
    void reg() {
        registerResident();
    }

    void user(string uname, string pass) {
        setCredentials(uname, pass);
    }

    void complaintmenue() {
        cout << "1. Add Complaint\n";
        cout << "2. View Previous Complaint\n";
        cout << "0. Logout\n";
        cout << "Enter your choice: ";
        cin >> subChoice;
        cin.ignore();

        if (subChoice == 1) {
            if (cap < sizee) {
                object[cap].registerComplaint();
                object[cap].inheritResident(*this);
                cap++;
            } else {
                cout << "Complaint storage full!\n";
            }
        } else if (subChoice == 2) {
            if (cap == 0) {
                cout << "No complaints registered yet.\n";
            } else {
                for (int i = 0; i < cap; i++) {
                    object[i].showComplaintDetails();
                }
            }
        } else if (subChoice == 0) {
            cout << "Logging out...\n";
        } else {
            cout << "Invalid option. Try again.\n";
        }
    }

    void billpayment() {
        int day, mon, year;

        time_t now = time(0);
        tm* ltm = localtime(&now);
        day = ltm->tm_mday;
        mon = 1 + ltm->tm_mon;
        year = 1900 + ltm->tm_year;

        cout << "Day   : " << day << endl;
        cout << "Month : " << mon << endl;
        cout << "Year  : " << year << endl;

        cout << "\n--- Bill Payment System ---\n";
        cout << "1. Pay The Bills \n2. See Previous History \n: ";
        cin >> option;
        switch (option) {
        case 1:
            cout << "1. Electricity Bills \n2. Security Bills \n3. Gas Bills \n: ";
            cin >> option;
            switch (option) {
            case 1:
                paid.elec(day, mon, *this);
                c++;
                break;
            case 2:
                paid.sec(day, mon, *this);
                break;
            case 3:
                paid.gas(day, mon, *this);
                c++;
                break;
            default:
                cout << "Invalid Option\n";
            }
            break;
        default:
            cout << "Invalid Option\n";
        }
    }
    void event()
    {
        EventManager manager;
    manager.addEvent(Event("E001", "Music Concert", "10-06-2025", 100, "VIP", 50.0));
    manager.addEvent(Event("E002", "Tech Conference", "15-06-2025", 200, "General", 30.0));
    manager.addEvent(Event("E003", "Art Exhibition", "10-06-2025", 50, "Standard", 20.0));
    manager.addEvent(Event("E004", "Football Match", "15-06-2025", 150, "VIP", 120.0));
    manager.addEvent(Event("E005", "Cricket Match", "20-06-2025", 250, "GENERAL", 100.0));
    manager.addEvent(Event("E006", "Volleyball Match", "25-06-2025", 300, "STANDARD", 80.0));

    Member member("John Doe", "M001", manager);

    while (true) {
        member.displayMenu();
    }

    }
    int grocery()
    {
          Store myStore;
    myStore.loadProducts();
    int choice;

    cout << "_______________________________________________" << endl;
    cout << "    Welcome to Dream Store - Buy Your Dreams!  " << endl;
    cout << "_______________________________________________" << endl;

    while (true) {
        cout << "\n--- LOGIN MENU ---" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. User Login" << endl;
        cout << "3. User Registration" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (adminLogin()) {

                Admin admin;
                Account *acc = &admin;
                cout << "Logged in as: " << acc->displayRole() << endl;
                adminMenu(myStore);
            }
            break;
        case 2: {
            string username;
            if (userLogin(username)) {

                User user;
                Account *acc = &user;
                cout << "Logged in as: " << acc->displayRole() << endl;
                userMenu(myStore, username);
            }
            break;
        }
        case 3:
            userRegister();
            break;
        case 4:
            cout << "Thank you for visiting Dream Store!" << endl;
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    }
    void hospitality()
    {
         Hospital h;
    int choice;

    while (true) {
        cout << "\nWelcome to Hospital Management System!\n";
        cout << "1. Register Patient\n";
        cout << "2. Emergency Case\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            h.register_patient();
            break;
        case 2:
            h.emergency_case();
            break;
        case 3:
            cout << "Exiting system...\n";
        default:
            cout << "Invalid choice! Try again\n";
        }
    }
    }

    ~workflow() {
        delete[] object;
    }
};

int main() {
    int choice, index = -1;
    string search1, search2;
    string uname, pass;
    int sizee = 5, cap = 0;
    workflow* obj = new workflow[sizee];

    while (choice != 3) {
        bool check = true;
        cout << " Welcome to the Society Resident App" << endl;
        cout << " 1. Registration" << endl;
        cout << " 2. Sign in" << endl;
        cout << " 3. Exit" << endl;
        cout << " Please Enter your Choice: ";
        cin >> choice;

        if (choice == 1) {
            if (cap < sizee) {
                obj[cap].reg();
                cout << "Set User-Name: ";
                cin >> uname;
                exception_str(uname);
                cout << "Set Your Password (6 to 10 Digits): ";
                cin >> pass;
                 exception_num(pass);
                for (int i = 0; i < cap; i++) {
                    if (uname == obj[i].username && pass == obj[i].password) {
                        check = false;
                        break;
                    }
                }
                if (check) {
                    obj[cap].user(uname, pass);
                    cap++;
                } else {
                    cout << "Username already exists!\n";
                }
            } else {
                cout << "Resident storage full!\n";
            }
        }
        if (choice == 2) {
            if (cap != 0) {
                cout << "Please Enter User-Name: ";
                cin >> search1;
                exception_str(search1);
                cout << "Please Enter your Password: ";
                cin >> search2;

                exception_num(search2);
                for (int i = 0; i < cap; i++) {
                    if (search1 == obj[i].username && search2 == obj[i].password) {
                        index = i;
                        break;
                    }
                }
                if (index == -1) {
                    cout << "Invalid username or password!\n";
                }
            } else {
                cout << "In our Record No Resident Found\n";
            }
            if (index != -1) {
                cout << "Welcome Mr. " << obj[index].name << " To our App\n";
                cout << "1. Complain System\n";
                cout << "2. Bill Payment System\n";
                cout << "3. Event System\n";
                cout << "4. Grocery Store\n";
                cout << "5. Hospital Facility\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice) {
                case 1:
                    obj[index].complaintmenue();
                    break;
                case 2:
                    obj[index].billpayment();
                    break;
                case 3:
                    obj[index].event();
                    break;
                case 4:
                    obj[index].grocery();
                    break;
                case 5:
                    obj[index].hospitality();
                    break;
                default:
                    cout << "Invalid choice\n";
                }
            }
        }
        index = -1;
    }

    delete[] obj;
    return 0;
}
