#include <iostream>
#include <iomanip>  // For formatting output

using namespace std;

// Structure to hold bus details
struct Bus {
    string destination;
    string stops[5];
    float fares[5];  // Different fares for each stop
};

// Function to display available buses
void showBuses(Bus* buses, int size) { // Using pointer to array
    cout << "\n🚌 Welcome to Zanzibar Travel Agency!\n";
    cout << "Choose your destination:\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << (buses + i)->destination << endl;
    }
}

// Function to display stops and fare for a selected bus
void showStops(Bus* bus) { // Pointer to Bus
    cout << "\n🚏 Stops for " << bus->destination << ":\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << bus->stops[i] << " - TZS " 
             << fixed << setprecision(2) << bus->fares[i] << endl;
    }
}

// Function to process payment
void processPayment(string* customerName, Bus* bus, int stopIndex) { // Using pointers
    static int receiptCounter = 1000; // Static variable to generate unique receipt numbers
    float amountPaid, change;
    float fare = bus->fares[stopIndex];

    cout << "\n💰 The fare to " << bus->stops[stopIndex] << " is TZS " << fare << ". Enter amount to pay: ";
    cin >> amountPaid;

    while (amountPaid < fare) {
        cout << "❌ Insufficient amount. Please enter at least TZS " << fare << ": ";
        cin >> amountPaid;
    }

    change = amountPaid - fare;
    if (change > 0) {
        cout << "✅ Payment successful! Your change is TZS " << fixed << setprecision(2) << change << endl;
    } else {
        cout << "✅ Payment successful! No change needed.\n";
    }

    // Generate a unique receipt number
    int receiptNumber = receiptCounter++;

    // Display receipt
    cout << "\n🧾 TRAVEL RECEIPT\n";
    cout << "--------------------------------\n";
    cout << "🚌 Zanzibar Travel Agency\n";
    cout << "👤 Customer: " << *customerName << endl; // Dereferencing pointer
    cout << "🎯 Destination: " << bus->destination << endl;
    cout << "🚏 Stop: " << bus->stops[stopIndex] << endl;
    cout << "🆔 Receipt No: #" << receiptNumber << endl;
    cout << "💰 Paid: TZS " << fixed << setprecision(2) << amountPaid << endl;
    cout << "--------------------------------\n";
} 

int main() {
    // Travel agency buses with actual stop names
    Bus buses[3] = {
        {"Fuoni-Bububu", {"Kwerekwe", "Amani", "Daraja bovu", "Bel-tras", "Kwanyanya"}, {500.0, 600.0, 700.0, 700.0, 800.0}},
        {"Chuokikuua", {"Fuoni", "Bango la mkoa ", "Suza", "Tunguu", "Chuokikuu"}, {500.0, 600.0, 700.0, 800.0, 90.0}},
        {"Nyamanzi", {"Mombasa round about", "kisauni", "Mitini", "", "Maungani"}, {500.0, 600.0, 700.0, 800.0, 900.0}}
    };

    string customerName;
    int busChoice, stopChoice;

    cout << "Enter your name: ";
    getline(cin, customerName);

    // Select bus
    showBuses(buses, 3);
    cout << "\nEnter your choice (1-3): ";
    cin >> busChoice;
    
    while (busChoice < 1 || busChoice > 3) {
        cout << "❌ Invalid choice. Please select a valid bus (1-3): ";
        cin >> busChoice;
    }

    Bus* selectedBus = &buses[busChoice - 1]; // Pointer to selected bus

    // Select stop
    showStops(selectedBus);
    cout << "\nEnter stop number (1-5): ";
    cin >> stopChoice;

    while (stopChoice < 1 || stopChoice > 5) {
        cout << "❌ Invalid choice. Please select a valid stop (1-5): ";
        cin >> stopChoice;
    }

    // Process payment and print receipt
    processPayment(&customerName, selectedBus, stopChoice - 1);

    cout << "\n✅ Thank you for using Zanzibar Travel Agency. Have a safe trip!\n";

    return 0;
}
    