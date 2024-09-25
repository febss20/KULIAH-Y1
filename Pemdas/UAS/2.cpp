#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// Struktur untuk merepresentasikan jenis kamar hotel
struct RoomType {
    string name;
    double pricePerNight;
};

// Struktur untuk merepresentasikan informasi pelanggan
struct Customer {
    string name;
    string email;
};

// Struktur untuk merepresentasikan layanan tambahan
struct AdditionalService {
    string name;
    double price;
};

// Struktur untuk merepresentasikan pemesanan kamar
struct Reservation {
    RoomType roomType;
    Customer customer;
    int duration;
    double roomCost;
    vector<AdditionalService> services;
    double totalCost;
    bool paid;
};

// Fungsi untuk menampilkan tiket pemesanan
void displayTicket(const Reservation& reservation) {
    cout << "\n========================================" << endl;
    cout << "             Tiket Pemesanan             " << endl;
    cout << "========================================" << endl;
    cout << "Jenis Kamar: " << reservation.roomType.name << endl;
    cout << "Durasi Menginap: " << reservation.duration << " malam" << endl;
    cout << "Biaya Kamar: Rp" << fixed << setprecision(2) << reservation.roomCost << endl;

    if (!reservation.services.empty()) {
        cout << "\nLayanan Tambahan:" << endl;
        for (const auto& service : reservation.services) {
            cout << "- " << service.name << ": Rp" << fixed << setprecision(2) << service.price << endl;
        }
    }

    cout << "\nTotal Biaya Pemesanan: Rp" << fixed << setprecision(2) << reservation.totalCost << endl;
    cout << "Pelanggan: " << reservation.customer.name << endl;
    cout << "Email: " << reservation.customer.email << endl;
    cout << "Status Pembayaran: " << (reservation.paid ? "Lunas" : "Belum Lunas") << endl;
    cout << "========================================\n" << endl;
}

// Fungsi untuk menampilkan riwayat pemesanan
void displayBookingHistory(const vector<Reservation>& reservations) {
    if (reservations.empty()) {
        cout << "Belum ada riwayat pemesanan." << endl;
    } else {
        cout << "=== Riwayat Pemesanan ===" << endl;
        for (size_t i = 0; i < reservations.size(); ++i) {
            cout << i + 1 << ". " << "Pelanggan: " << reservations[i].customer.name
                 << ", Jenis Kamar: " << reservations[i].roomType.name
                 << ", Durasi: " << reservations[i].duration << " malam"
                 << ", Total Biaya: Rp" << fixed << setprecision(2) << reservations[i].totalCost
                 << (reservations[i].paid ? " (Lunas)" : " (Belum Lunas)") << endl;
        }
        cout << endl;
    }
}

int main() {
    vector<RoomType> roomTypes = {{"Standard Room", 100.0},
                                  {"Deluxe Room", 150.0},
                                  {"Suite", 200.0}};

    vector<AdditionalService> additionalServices = {{"Spa", 50.0},
                                                   {"Breakfast", 20.0},
                                                   {"Airport Shuttle", 30.0}};

    vector<Reservation> reservations;

    // Menampilkan jenis kamar yang tersedia
    cout << "=== Jenis Kamar Hotel ===" << endl;
    for (size_t i = 0; i < roomTypes.size(); ++i) {
        cout << i + 1 << ". " << roomTypes[i].name << " - Rp" << fixed << setprecision(2) << roomTypes[i].pricePerNight << " per malam" << endl;
    }

    // Meminta pengguna memilih jenis kamar
    cout << "\nPilih jenis kamar yang diinginkan (masukkan nomor jenis kamar): ";

    int roomChoice;
    cin >> roomChoice;

    if (roomChoice > 0 && roomChoice <= roomTypes.size()) {
        int duration;
        cout << "Masukkan durasi menginap (jumlah malam): ";
        cin >> duration;

        // Meminta informasi pelanggan
        Customer newCustomer;
        cout << "Masukkan nama pelanggan: ";
        cin.ignore();
        getline(cin, newCustomer.name);
        cout << "Masukkan email pelanggan: ";
        cin >> newCustomer.email;

        // Memilih layanan tambahan
        vector<AdditionalService> selectedServices;
        char addService;
        do {
            cout << "\nLayanan Tambahan yang Tersedia:" << endl;
            for (size_t i = 0; i < additionalServices.size(); ++i) {
                cout << i + 1 << ". " << additionalServices[i].name << " - Rp" << fixed << setprecision(2) << additionalServices[i].price << endl;
            }

            cout << "Ingin menambahkan layanan tambahan? (Y/N): ";
            cin >> addService;

            if (toupper(addService) == 'Y') {
                cout << "Pilih layanan tambahan (masukkan nomor layanan): ";
                int serviceChoice;
                cin >> serviceChoice;

                if (serviceChoice > 0 && serviceChoice <= additionalServices.size()) {
                    selectedServices.push_back(additionalServices[serviceChoice - 1]);
                    cout << "Layanan tambahan ditambahkan." << endl;
                } else {
                    cout << "Nomor layanan tidak valid." << endl;
                }
            }
        } while (toupper(addService) == 'Y');

        // Membuat reservasi
        Reservation newReservation;
        newReservation.roomType = roomTypes[roomChoice - 1];
        newReservation.customer = newCustomer;
        newReservation.duration = duration;
        newReservation.roomCost = roomTypes[roomChoice - 1].pricePerNight * duration;
        newReservation.services = selectedServices;

        // Menghitung total biaya pemesanan
        newReservation.totalCost = newReservation.roomCost;
        for (const auto& service : newReservation.services) {
            newReservation.totalCost += service.price;
        }

        newReservation.paid = false;

        // Menampilkan tiket pemesanan
        displayTicket(newReservation);

        // Meminta apakah pelanggan sudah membayar atau belum
        char paymentStatus;
        cout << "Apakah pelanggan sudah membayar? (Y/N): ";
        cin >> paymentStatus;
        newReservation.paid = (toupper(paymentStatus) == 'Y');

        // Menambahkan reservasi ke daftar
        reservations.push_back(newReservation);

        cout << "Pemesanan berhasil ditambahkan." << endl;

        // Menampilkan daftar reservasi
        displayBookingHistory(reservations);
    } else {
        cout << "Nomor jenis kamar tidak valid. Pemesanan dibatalkan." << endl;
    }

    return 0;
}

