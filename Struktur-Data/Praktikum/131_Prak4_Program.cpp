#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Struktur data Buku
struct Buku {
    string judul;
    string penulis;
    int tahun;
    int hashKey;
};

// Struktur data untuk Node Linked List Buku
struct BookNode {
    Buku data;
    BookNode* next;
};

// Struktur data untuk Peminjaman Buku
struct Loan {
    int nomorpinjam;
    int kodepinjam;
    string namapinjam;
    int kodebuku;
    int tglpinjam;
    int tglkembali;
    string judul;
    string penulis;
    int tahun;
};

// Struktur Hash Table
const int TABLE_SIZE = 10;
BookNode* hashTable[TABLE_SIZE];
Loan loans[TABLE_SIZE];
int loanCount = 0;
int bookCount = 0; // Counter untuk jumlah buku saat ini

// Fungsi untuk membuat node buku baru
BookNode* buatnodebuku(string judul, string penulis, int tahun, int hashKey) {
    BookNode* newNode = new BookNode;
    newNode->data = { judul, penulis, tahun, hashKey };
    newNode->next = nullptr;
    return newNode;
}

// Fungsi untuk memeriksa apakah slot hash table kosong atau diisi oleh node buku
bool isOccupied(int index) {
    return hashTable[index] != nullptr;
}

// Fungsi untuk menambahkan buku ke Hash Table dengan linear probing
void tambahbuku(string judul, string penulis, int tahun, int hashKey) {
    int index = hashKey % TABLE_SIZE;
    int originalIndex = index;

    // Linear probing untuk menemukan slot kosong
    while (isOccupied(index)) {
        index = (index + 1) % TABLE_SIZE;
        // Jika kembali ke posisi awal, maka table penuh
        if (index == originalIndex) {
            cout << "Hash table penuh. Tidak bisa menambahkan buku baru." << endl;
            return;
        }
    }

    BookNode* newNode = buatnodebuku(judul, penulis, tahun, hashKey);
    hashTable[index] = newNode;
    bookCount++;
}

// Fungsi untuk menghapus buku dari hash table berdasarkan hash key
void hapusbuku(int hashKey) {
    int index = hashKey % TABLE_SIZE;
    int originalIndex = index;

    // Linear probing untuk menemukan buku yang cocok
    while (hashTable[index] != nullptr) {
        if (hashTable[index]->data.hashKey == hashKey) {
            delete hashTable[index];
            hashTable[index] = nullptr;
            bookCount--;
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            cout << "Buku dengan kode " << hashKey << " tidak ditemukan." << endl;
            return;
        }
    }
}

// Fungsi untuk menampilkan buku yang terakhir dimasukkan
void displayBooks() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != nullptr) {
            BookNode* current = hashTable[i];
            while (current != nullptr) {
                cout << "-------------------------\n";
                cout << "=========================\n";
                cout << "Kode Buku: " << current->data.hashKey << "\n";
                cout << "Judul    : " << current->data.judul << "\n";
                cout << "Penulis  : " << current->data.penulis << "\n";
                cout << "Tahun    : " << current->data.tahun << "\n";
                cout << "=========================\n";
                cout << "-------------------------\n";
                cout << endl;
                current = current->next;
            } 
        }
    }
}

// Fungsi untuk mencari buku berdasarkan kata kunci menggunakan sequential search
void caribukubykata(const string& keyword) {
    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower); // Convert to lowercase

    // Tentukan jumlah maksimum kata yang bisa disimpan (disini diasumsikan tidak lebih dari 1000 kata)
    const int MAX_WORDS = 1000;
    Buku* books[MAX_WORDS];
    int bookCount = 0;

    // Mengumpulkan semua buku yang memiliki kata kunci
    for (int i = 0; i < TABLE_SIZE; i++) {
        BookNode* current = hashTable[i];
        while (current != nullptr) {
            string judul = current->data.judul;
            string penulis = current->data.penulis;
            string tahun = to_string(current->data.tahun);

            transform(judul.begin(), judul.end(), judul.begin(), ::tolower); // Convert to lowercase
            transform(penulis.begin(), penulis.end(), penulis.begin(), ::tolower); // Convert to lowercase

            // Cek apakah kata kunci cocok dengan bagian mana pun dari judul, penulis, atau tahun terbit
            if (judul.find(lowerKeyword) != string::npos ||
                penulis.find(lowerKeyword) != string::npos ||
                tahun.find(lowerKeyword) != string::npos) {
                books[bookCount++] = &current->data;
            }

            current = current->next;
        }
    }

    // Jika buku ditemukan, cetak detail buku
    if (bookCount > 0) {
        cout << "Buku ditemukan untuk kata kunci \"" << keyword << "\":\n";
        for (int i = 0; i < bookCount; i++) {
            cout << "-------------------------\n";
            cout << "=========================\n";
            cout << "Kode Buku: " << books[i]->hashKey << "\n";
            cout << "Judul    : " << books[i]->judul << "\n";
            cout << "Penulis  : " << books[i]->penulis << "\n"; 
            cout << "Tahun    : " << books[i]->tahun << "\n";
            cout << "=========================\n";
            cout << "-------------------------\n";
            cout << endl;
        }
    } else {
        cout << "Buku tidak ditemukan untuk kata kunci \"" << keyword << "\".\n";
    }
}

// Fungsi untuk menghitung jumlah buku di hash table
int countBooksInHashTable() {
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        BookNode* current = hashTable[i];
        while (current != nullptr) {
            count++;
            current = current->next;
        }
    }
    return count;
}

// Fungsi untuk mengubah hash table ke array
void hashTableToArray(Buku books[]) {
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        BookNode* current = hashTable[i];
        while (current != nullptr) {
            books[count++] = current->data;
            current = current->next;
        }
    }
}

// Fungsi Bubble Sort untuk mengurutkan buku berdasarkan hash key
void bubbleSortBooksByHashKey(Buku books[], int size) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < size - 1; i++) {
            if (books[i].hashKey > books[i + 1].hashKey) {
                swap(books[i], books[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

// Fungsi untuk peminjaman buku
void pinjambuku(int nomorpinjam, int kodepinjam, const string& namapinjam, 
                int kodebuku, int tglpinjam, int tglkembali) {
    // Cari buku di hash table
    int index = kodebuku % TABLE_SIZE;
    BookNode* current = hashTable[index];
    while (current != nullptr && current->data.hashKey != kodebuku) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Buku dengan kode " << kodebuku << " tidak ditemukan." << endl;
        return;
    }

    // Simpan informasi peminjaman, termasuk detail buku
    loans[loanCount++] = {nomorpinjam, kodepinjam, namapinjam, kodebuku, tglpinjam, 
    tglkembali, current->data.judul, current->data.penulis, current->data.tahun};

    // Hapus buku dari hash table
    hapusbuku(kodebuku);
    cout << "Buku dengan kode " << kodebuku << " berhasil dipinjam oleh " << namapinjam << "." << endl;
}


// Fungsi untuk pengembalian buku
void kembalikanbuku(int kodepinjam) {
    // Cari peminjaman berdasarkan kode peminjam
    for (int i = 0; i < loanCount; i++) {
        if (loans[i].kodepinjam == kodepinjam) {
            Loan loan = loans[i];

            // Tambahkan buku kembali ke hash table dengan informasi asli
            tambahbuku(loan.judul, loan.penulis, loan.tahun, loan.kodebuku);

            // Hapus informasi peminjaman dengan menggeser elemen array
            for (int j = i; j < loanCount - 1; j++) {
                loans[j] = loans[j + 1];
            }
            loanCount--;

            cout << "Buku dengan kode " << loan.kodebuku 
            << " berhasil dikembalikan oleh " << loan.namapinjam << "." << endl;
            return;
        }
    }
    cout << "Peminjaman dengan kode peminjam " << kodepinjam << " tidak ditemukan." << endl;
}


// Fungsi untuk login
bool login() {
    string username, password;
    cout << "=============================================\n";
    cout << "   Selamat Datang Di Aplikasi Perpustakaan\n";
    cout << "=============================================\n";
    cout << endl;
    cout << "Silahkan Login terlebih dahulu\n"; 
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    cout << endl;
    // Login sederhana, dapat dikembangkan lebih lanjut
    return (username == "Admin" && password == "1");
}

// Fungsi untuk menampilkan menu utama
void mainMenu() {
    int choice;
    do {
        cout << "==============================\n";
        cout << "    Menu Utama Perpustakaan\n";
        cout << "==============================\n";
        cout << "1. Input Data Buku\n";
        cout << "2. Lihat Daftar Buku\n";
        cout << "3. Cari Buku\n";
        cout << "4. Urutkan Data Buku\n";
        cout << "5. Peminjaman Buku\n";
        cout << "6. Pengembalian Buku\n";
        cout << "7. Keluar\n";
        cout << "==============================\n";
        cout << "Pilih opsi: "; cin >> choice;
        cout << "==============================\n";
        cout << endl;

        string judul, penulis, keyword, namapinjam;
        int tahun, hashKey, nomorpinjam, kodepinjam, kodebuku, tglpinjam, tglkembali;

        switch (choice) {
            case 1:
                do {
                    cout << "Masukkan kode buku: ";
                    cin >> hashKey;
                    cout << "Masukkan Judul Buku: ";
                    cin.ignore();
                    getline(cin, judul);
                    cout << "Masukkan Penulis Buku: ";
                    getline(cin, penulis);
                    cout << "Masukkan Tahun Terbit Buku: ";
                    cin >> tahun;
                    tambahbuku(judul, penulis, tahun, hashKey);
                    cout << "Buku Berhasil Ditambahkan\n";
                    cout << "Apakah ingin menambahkan buku lagi? (y/n): ";
                    char moreBooks;
                    cin >> moreBooks;
                    if (tolower(moreBooks) != 'y') {
                        break;
                    }
                } while (true);
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                cout << "Masukkan Kata Kunci Pencarian: ";
                cin.ignore();
                getline(cin, keyword);
                caribukubykata(keyword);
                break;
            case 4:
                {
                    int totalBooks = countBooksInHashTable();
                    if (totalBooks > 0) {
                        Buku* books = new Buku[totalBooks];
                        hashTableToArray(books);
                        bubbleSortBooksByHashKey(books, totalBooks);
                        cout << "Buku berhasil diurutkan berdasarkan Kode Buku.\n";
                        for (int i = 0; i < totalBooks; i++) {
                            cout << "-------------------------\n";
                            cout << "=========================\n";
                            cout << "Kode Buku: " << books[i].hashKey << "\n";
                            cout << "Judul    : " << books[i].judul << "\n";
                            cout << "Penulis  : " << books[i].penulis <<"\n";
                            cout << "Tahun    : " << books[i].tahun << "\n";
                            cout << "=========================\n";
                            cout << "-------------------------\n";
                            cout << endl;
                        }
                        delete[] books;
                    } else {
                        cout << "Tidak ada buku untuk diurutkan.\n";
                    }
                }
                break;
            case 5: // Peminjaman buku
                displayBooks();
                cout << endl;
                cout << "Masukkan Nomor Peminjaman: ";
                cin >> nomorpinjam;
                cout << "Masukkan Kode Peminjam: ";
                cin >> kodepinjam;
                cout << "Masukkan Nama Peminjam: ";
                cin.ignore();
                getline(cin, namapinjam);
                cout << "Masukkan Kode Buku: ";
                cin >> kodebuku;
                cout << "Masukkan Tanggal Pinjam: ";
                cin >> tglpinjam;
                cout << "Masukkan Tanggal Kembali: ";
                cin >> tglkembali;
                pinjambuku(nomorpinjam, kodepinjam, namapinjam, kodebuku, tglpinjam, tglkembali);
                break;
            case 6: // Pengembalian buku
                cout << "Masukkan Kode Peminjam: ";
                cin >> kodepinjam;
                kembalikanbuku(kodepinjam);
                break;
            case 7:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Opsi tidak valid.\n";
                break;
        }
    } while (choice != 7);
}

int main() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        hashTable[i] = nullptr;
    }

    if (login()) {
        mainMenu();
    } else {
        cout << "===Login gagal===\n";
    }
    return 0;
}

