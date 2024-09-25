#include <bits/stdc++.h>

using namespace std;

const int MAX_TRAINS = 100;
const int MAX_STATIONS = 100;
const int HASH_TABLE_SIZE = 10;

// Struct untuk User
struct User {
    int userID;
    string nama;
    string email;
};

// Struct untuk Edge di Graph
struct Edge {
    string tujuan;
    int jarak;
};

// Struct untuk Train
struct Train {
    int trainID;
    string namaKereta;
    int kursiTersedia;
    string rute[MAX_STATIONS];
    int jarakRute[MAX_STATIONS - 1];
    int ukuranRute;
};

// Struct untuk Ticket
struct Ticket {
    int ticketID;
    User user;
    Train kereta;
};

// Class untuk mengelola Graph
class Graph {
public:
    Edge adjList[MAX_STATIONS][MAX_STATIONS];
    int adjListSize[MAX_STATIONS];
    string namaStasiun[MAX_STATIONS];
    int jumlahStasiun;

    Graph() {
        jumlahStasiun = 0;
        for (int i = 0; i < MAX_STATIONS; ++i) {
            adjListSize[i] = 0;
        }
    }

    int getStasiunIndex(const string& stasiun) {
        for (int i = 0; i < jumlahStasiun; ++i) {
            if (namaStasiun[i] == stasiun) return i;
        }
        return -1;
    }

    void tambahEdge(const string& sumber, const string& tujuan, int jarak) {
        int srcIdx = getStasiunIndex(sumber);
        if (srcIdx == -1) {
            srcIdx = jumlahStasiun++;
            namaStasiun[srcIdx] = sumber;
        }
        int destIdx = getStasiunIndex(tujuan);
        if (destIdx == -1) {
            destIdx = jumlahStasiun++;
            namaStasiun[destIdx] = tujuan;
        }
        adjList[srcIdx][adjListSize[srcIdx]++] = { tujuan, jarak };
        adjList[destIdx][adjListSize[destIdx]++] = { sumber, jarak };
    }

    void hapusEdge(const string& sumber, const string& tujuan, int jarak) {
    int srcIdx = getStasiunIndex(sumber);
    int destIdx = getStasiunIndex(tujuan);
    if (srcIdx == -1 || destIdx == -1) return;

    auto& srcList = adjList[srcIdx];
    auto& destList = adjList[destIdx];

    for (int i = 0; i < adjListSize[srcIdx]; ++i) {
        if (srcList[i].tujuan == tujuan && srcList[i].jarak == jarak) {
            for (int j = i; j < adjListSize[srcIdx] - 1; ++j) {
                srcList[j] = srcList[j + 1];
            }
            adjListSize[srcIdx]--;
            break;
        }
    }

    for (int i = 0; i < adjListSize[destIdx]; ++i) {
        if (destList[i].tujuan == sumber && destList[i].jarak == jarak) {
            for (int j = i; j < adjListSize[destIdx] - 1; ++j) {
                destList[j] = destList[j + 1];
            }
            adjListSize[destIdx]--;
            break;
        }
    }
}


    string dijkstra(const string& start, const string& end) {
        int startIndex = getStasiunIndex(start);
        int endIndex = getStasiunIndex(end);

        int jarak[MAX_STATIONS];
        string previous[MAX_STATIONS];
        bool visited[MAX_STATIONS] = { false };

        fill(jarak, jarak + MAX_STATIONS, numeric_limits<int>::max());
        jarak[startIndex] = 0;

        auto cmp = [&](const int& left, const int& right) { return jarak[left] > jarak[right]; };
        priority_queue<int, vector<int>, decltype(cmp)> queue(cmp);
        queue.push(startIndex);

        while (!queue.empty()) {
            int current = queue.top();
            queue.pop();

            if (current == endIndex) break;

            if (visited[current]) continue;
            visited[current] = true;

            for (int i = 0; i < adjListSize[current]; ++i) {
                Edge& neighbor = adjList[current][i];
                int neighborIndex = getStasiunIndex(neighbor.tujuan);
                int newDist = jarak[current] + neighbor.jarak;
                if (newDist < jarak[neighborIndex]) {
                    jarak[neighborIndex] = newDist;
                    previous[neighborIndex] = namaStasiun[current];
                    queue.push(neighborIndex);
                }
            }
        }

        string path = end;
        for (string at = end; at != start && !at.empty(); at = previous[getStasiunIndex(at)]) {
            path = previous[getStasiunIndex(at)] + " -> " + path;
        }
        return path;
    }
};

// Class untuk mengelola Trains
class TrainManager {
public:
    Train hashTable[HASH_TABLE_SIZE];
    Graph graph;

    TrainManager() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i].trainID = -1;  // Inisialisasi hash table dengan -1 (menandakan kosong)
        }
    }

    int hashFunction(int key) {
        return key % HASH_TABLE_SIZE;
    }

    void tambahKereta(int trainID, const string& namaKereta, int kursiTersedia, const string rute[], const int jarak[], int ukuranRute) {
        Train kereta = { trainID, namaKereta, kursiTersedia, {}, {}, ukuranRute };
        copy(rute, rute + ukuranRute, kereta.rute);
        copy(jarak, jarak + ukuranRute - 1, kereta.jarakRute);

        int hashIndex = hashFunction(trainID);
        while (hashTable[hashIndex].trainID != -1) {
            hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;  // Linear probing
        }
        hashTable[hashIndex] = kereta;

        for (int i = 0; i < ukuranRute - 1; ++i) {
            graph.tambahEdge(rute[i], rute[i + 1], jarak[i]);
        }
    }

    void hapusKereta(int trainID) {
    int hashIndex = hashFunction(trainID);
    while (hashTable[hashIndex].trainID != -1) {
        if (hashTable[hashIndex].trainID == trainID) {
            Train& kereta = hashTable[hashIndex];
            // Hapus rute dari graf
            for (int i = 0; i < kereta.ukuranRute - 1; ++i) {
                graph.hapusEdge(kereta.rute[i], kereta.rute[i + 1], kereta.jarakRute[i]);
            }
            hashTable[hashIndex].trainID = -1;
            cout << "Kereta dengan ID " << trainID << " berhasil dihapus.\n";
            return;
        }
        hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
    }
    cout << "Kereta dengan ID " << trainID << " tidak ditemukan.\n";
}


    void editKereta(int trainID, const string& namaKereta, int kursiTersedia, const string rute[], const int jarak[], int ukuranRute) {
        int hashIndex = hashFunction(trainID);
        while (hashTable[hashIndex].trainID != -1) {
            if (hashTable[hashIndex].trainID == trainID) {
                Train& kereta = hashTable[hashIndex];
                kereta.namaKereta = namaKereta;
                kereta.kursiTersedia = kursiTersedia;
                kereta.ukuranRute = ukuranRute;
                copy(rute, rute + ukuranRute, kereta.rute);
                copy(jarak, jarak + ukuranRute - 1, kereta.jarakRute);

                // Perbarui graph
                for (int i = 0; i < ukuranRute - 1; ++i) {
                    graph.tambahEdge(rute[i], rute[i + 1], jarak[i]);
                }
                cout << "Kereta dengan ID " << trainID << " berhasil diedit.\n";
                return;
            }
            hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
        }
        cout << "Kereta dengan ID " << trainID << " tidak ditemukan.\n";
    }

    void cariKereta(const string& kataKunci) {
        bool ditemukan = false;
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            if (hashTable[i].trainID != -1) {
                const Train& kereta = hashTable[i];
                if (to_string(kereta.trainID).find(kataKunci) != string::npos ||
                    kereta.namaKereta.find(kataKunci) != string::npos) {
                    ditemukan = true;
                    cout << "==================================================\n";
                    cout << "ID Kereta      : " << kereta.trainID << "\n";
                    cout << "Nama           : " << kereta.namaKereta << "\n";
                    cout << "Kursi Tersedia : " << kereta.kursiTersedia << "\n";
                    cout << "Rute           : ";
                    for (int j = 0; j < kereta.ukuranRute; ++j) {
                        cout << kereta.rute[j];
                        if (j < kereta.ukuranRute - 1) cout << " -> ";
                    }
                    cout << "\nJarak        : ";
                    for (int j = 0; j < kereta.ukuranRute - 1; ++j) {
                        cout << kereta.jarakRute[j] << " km";
                        if (j < kereta.ukuranRute - 2) cout << ", ";
                    }
                    cout << "\n";
                    cout << "==================================================\n";
                    cout << "\n\n";
                } else {
                    for (int j = 0; j < kereta.ukuranRute; ++j) {
                        if (kereta.rute[j].find(kataKunci) != string::npos) {
                            ditemukan = true;
                            cout << "==================================================\n";
                            cout << "ID Kereta      : " << kereta.trainID << "\n";
                            cout << "Nama           : " << kereta.namaKereta << "\n";
                            cout << "Kursi Tersedia : " << kereta.kursiTersedia << "\n";
                            cout << "Rute           : ";
                            for (int j = 0; j < kereta.ukuranRute; ++j) {
                                cout << kereta.rute[j];
                                if (j < kereta.ukuranRute - 1) cout << " -> ";
                            }
                            cout << "\nJarak        : ";
                            for (int j = 0; j < kereta.ukuranRute - 1; ++j) {
                                cout << kereta.jarakRute[j] << " km";
                                if (j < kereta.ukuranRute - 2) cout << ", ";
                            }
                            cout << "\n";
                            cout << "==================================================\n";
                            cout << "\n\n";
                            break;
                        }
                    }
                }
            }
        }
        if (!ditemukan) {
            cout << "Kereta dengan kata kunci \"" << kataKunci << "\" tidak ditemukan.\n";
        }
    }

    void urutkanKereta() {
    // Buat salinan sementara dari hash table
    Train tempHashTable[HASH_TABLE_SIZE];
    copy(begin(hashTable), end(hashTable), begin(tempHashTable));

    // Lakukan pengurutan pada salinan
    for (int i = 0; i < HASH_TABLE_SIZE - 1; ++i) {
        for (int j = 0; j < HASH_TABLE_SIZE - i - 1; ++j) {
            if (tempHashTable[j].trainID > tempHashTable[j + 1].trainID) {
                swap(tempHashTable[j], tempHashTable[j + 1]);
            }
        }
    }

    // Tampilkan hasil pengurutan
    cout << "Kereta berhasil diurutkan berdasarkan ID.\n";
    bool adaKereta = false;
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        if (tempHashTable[i].trainID != -1) {
            adaKereta = true;
            const Train& kereta = tempHashTable[i];
            cout << "==================================================\n";
            cout << "ID Kereta      : " << kereta.trainID << "\n";
            cout << "Nama           : " << kereta.namaKereta << "\n";
            cout << "Kursi Tersedia : " << kereta.kursiTersedia << "\n";
            cout << "Rute           : ";
            for (int j = 0; j < kereta.ukuranRute; ++j) {
                cout << kereta.rute[j];
                if (j < kereta.ukuranRute - 1) cout << " -> ";
            }
            cout << "\nJarak        : ";
            for (int j = 0; j < kereta.ukuranRute - 1; ++j) {
                cout << kereta.jarakRute[j] << " km";
                if (j < kereta.ukuranRute - 2) cout << ", ";
            }
            cout << "\n";
            cout << "==================================================\n";
            cout << "\n\n";
        }
    }
    if (!adaKereta) {
        cout << "Tidak ada kereta yang tersedia.\n";
    }
}


    void tampilkanKereta() const {
        bool adaKereta = false;
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            if (hashTable[i].trainID != -1) {
                adaKereta = true;
                const Train& kereta = hashTable[i];
                cout << "=================================================\n";
                cout << "ID Kereta      : " << kereta.trainID << "\n";
                cout << "Nama           : " << kereta.namaKereta << "\n";
                cout << "Kursi Tersedia : " << kereta.kursiTersedia << "\n";
                cout << "Rute           : ";
                for (int j = 0; j < kereta.ukuranRute; ++j) {
                    cout << kereta.rute[j];
                    if (j < kereta.ukuranRute - 1) cout << " -> ";
                }
                cout << "\nJarak          : ";
                for (int j = 0; j < kereta.ukuranRute - 1; ++j) {
                    cout << kereta.jarakRute[j] << " km";
                    if (j < kereta.ukuranRute - 2) cout << ", ";
                }
                cout << "\n";
                cout << "==================================================\n";
                cout << "\n\n";
            }
        }
        if (!adaKereta) {
            cout << "Tidak ada kereta yang tersedia.\n";
        }
    }

    pair<string, int> ruteTerpendek(const string& startStation, const string& endStation) {
    // Misalkan ini adalah algoritma yang mencari rute terpendek
    // Temukan kereta dengan rute terpendek dari startStation ke endStation
    string ruteTerpendek;
    int keretaID = -1;
    int jarakTerpendek = INT_MAX;

    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        if (hashTable[i].trainID != -1) {
            const Train& kereta = hashTable[i];
            for (int j = 0; j < kereta.ukuranRute; ++j) {
                if (kereta.rute[j] == startStation) {
                    int jarak = 0;
                    string rute = startStation;
                    for (int k = j + 1; k < kereta.ukuranRute; ++k) {
                        jarak += kereta.jarakRute[k - 1];
                        rute += " -> " + kereta.rute[k];
                        if (kereta.rute[k] == endStation) {
                            if (jarak < jarakTerpendek) {
                                jarakTerpendek = jarak;
                                ruteTerpendek = rute;
                                keretaID = kereta.trainID;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    return {ruteTerpendek, keretaID};
}

};

// Class untuk mengelola Tiket
class TicketManager {
public:
    Ticket hashTable[HASH_TABLE_SIZE];
    queue<User> antrianTunggu;
    stack<string> historyStack; // Tambahkan stack untuk melacak riwayat operasi


    TicketManager() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i].ticketID = -1;  // Inisialisasi hash table dengan -1 (menandakan kosong)
        }
    }

    int hashFunction(int key) {
        return key % HASH_TABLE_SIZE;
    }

    void pesanTiket(User& user, Train& kereta) {
        if (kereta.kursiTersedia > 0) {
            Ticket tiket = { rand() % 1000, user, kereta };
            int hashIndex = hashFunction(tiket.ticketID);
            while (hashTable[hashIndex].ticketID != -1) {
                hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;  // Linear probing
            }
            hashTable[hashIndex] = tiket;
            kereta.kursiTersedia--;
            cout << "Tiket berhasil dipesan untuk " << user.nama << " pada kereta " << kereta.namaKereta << endl;
            // Setelah berhasil pesan tiket, tambahkan operasi ke dalam stack
            historyStack.push("Pemesanan tiket oleh " + user.nama);
        } else {
            antrianTunggu.push(user);
            cout << "Tidak ada kursi tersedia. User " << user.nama << " ditambahkan ke antrian tunggu.\n";
            historyStack.push("User " + user.nama + " ditambahkan ke antrian tunggu.");
        }
    }

    void tampilkanTiket() const {
        bool adaTiket = false;
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            if (hashTable[i].ticketID != -1) {
                adaTiket = true;
                const Ticket& tiket = hashTable[i];
                cout << "=================================\n";
                cout << "ID Tiket : " << tiket.ticketID << "\n";
                cout << "User     : " << tiket.user.nama << "\n";
                cout << "Kereta   : " << tiket.kereta.namaKereta << "\n";
                cout << "=================================\n";
            }
        }
        if (!adaTiket) {
            cout << "Tidak ada tiket yang dipesan.\n";
        }
    }

    void tampilkanAntrianTunggu() const {
        if (antrianTunggu.empty()) {
            cout << "Tidak ada pengguna dalam antrian tunggu.\n";
            return;
        }

        queue<User> tempQueue = antrianTunggu;  // Buat salinan antrian
        while (!tempQueue.empty()) {
            User user = tempQueue.front();
            tempQueue.pop();
            cout << "ID User : " << user.userID << "\n";
            cout << "Nama    : " << user.nama << "\n";
            cout << "Email   : " << user.email << "\n";
            cout << "---------------------------------\n";
        }
    }


    // Fungsi untuk menampilkan riwayat operasi terakhir
    void tampilkanRiwayatOperasi() {
        if (!historyStack.empty()) {
            cout << "Riwayat operasi terakhir: " << historyStack.top() << endl;
        } else {
            cout << "Riwayat operasi kosong." << endl;
        }
    }    
};

// Fungsi untuk mengelola menu User
void userMenu(TrainManager& trainManager, TicketManager& ticketManager) {
    int pilihan;
    do {
        cout << "=============================\n";
        cout << " SELAMAT DATANG DI MENU USER \n";
        cout << "=============================\n";
        cout << "1. Pesan Tiket\n";
        cout << "2. Lihat Semua Kereta\n";
        cout << "3. Lihat Antrian Tunggu\n";
        cout << "4. Keluar\n";
        cout << "=============================\n";
        cout << "Pilih Opsi: "; cin >> pilihan;
        cout << "=============================\n";

        switch (pilihan) {
            case 1: {
                User user;
                cout << "Masukkan ID User: ";
                cin >> user.userID;
                cout << "Masukkan Nama: ";
                cin.ignore();
                getline(cin, user.nama);
                cout << "Masukkan Email: ";
                cin >> user.email;

                string startStation, endStation;
cout << "Masukkan Stasiun Awal: ";
cin >> startStation;
cout << "Masukkan Stasiun Tujuan: ";
cin >> endStation;

pair<string, int> result = trainManager.ruteTerpendek(startStation, endStation);
string path = result.first;
int keretaID = result.second;

if (!path.empty()) {
    cout << "Rute Terpendek dari " << startStation << " ke " << endStation << " adalah:\n" << path << "\n";
    cout << "ID Kereta untuk rute ini: " << keretaID << "\n";

    int pilihanKereta;
    cout << "Masukkan ID Kereta yang Ingin Dipesan (atau 0 untuk Batalkan): ";
    cin >> pilihanKereta;

    if (pilihanKereta > 0) {
        int hashIndex = trainManager.hashFunction(pilihanKereta);
        while (trainManager.hashTable[hashIndex].trainID != pilihanKereta && trainManager.hashTable[hashIndex].trainID != -1) {
            hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
        }
        if (trainManager.hashTable[hashIndex].trainID == pilihanKereta) {
            ticketManager.pesanTiket(user, trainManager.hashTable[hashIndex]);
        } else {
            cout << "Kereta dengan ID tersebut tidak ditemukan.\n";
        }
    } else {
        cout << "Pesanan dibatalkan.\n";
    }
} else {
    cout << "Tidak ada kereta yang tersedia untuk rute tersebut.\n";
}

                break;
            }
            case 2:
                trainManager.tampilkanKereta();
                break;
            case 3:
                ticketManager.tampilkanAntrianTunggu();  // Panggil fungsi ini
                break;            
            case 4:
                cout << "Keluar dari menu user...\n";
                cout << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Coba lagi.\n";
                break;
        }
    } while (pilihan != 3);
}

// Fungsi untuk mengelola menu Admin
void adminMenu(TrainManager& trainManager, TicketManager& ticketManager) {
    int pilihan;
    do {
        cout << "==============================\n";
        cout << " SELAMAT DATANG DI MENU ADMIN \n";
        cout << "==============================\n";
        cout << "1. Tambah Kereta\n";
        cout << "2. Hapus Kereta\n";
        cout << "3. Edit Kereta\n";
        cout << "4. Cari Kereta\n";
        cout << "5. Urutkan Kereta\n";
        cout << "6. Lihat Semua Kereta\n";
        cout << "7. Lihat Daftar Tiket\n";
        cout << "8. Lihat Antrian Tunggu\n";
        cout << "9. Keluar\n";        
        cout << "==============================\n";
        cout << "Pilih Opsi: "; cin >> pilihan;
        cout << "==============================\n";

        switch (pilihan) {
            case 1: {
                int trainID, kursiTersedia;
                string namaKereta;
                string rute[MAX_STATIONS];
                int jarak[MAX_STATIONS - 1];
                int ukuranRute = 0;

                cout << "Masukkan ID Kereta: ";
                cin >> trainID;
                cout << "Masukkan Nama Kereta: ";
                cin.ignore();
                getline(cin, namaKereta);
                cout << "Masukkan Jumlah Kursi Tersedia: ";
                cin >> kursiTersedia;

                string stasiun;
                int jarakStasiun;
                cout << "Masukkan Rute Stasiun (Ketik 'selesai' untuk selesai):\n";
                while (true) {
                    cout << "Masukkan Stasiun: ";
                    cin >> stasiun;
                    if (stasiun == "selesai") break;
                    rute[ukuranRute++] = stasiun;
                    if (ukuranRute > 1) {
                        cout << "Masukkan Jarak Dari Stasiun Sebelumnya: ";
                        cin >> jarakStasiun;
                        jarak[ukuranRute - 2] = jarakStasiun;
                    }
                }

                trainManager.tambahKereta(trainID, namaKereta, kursiTersedia, rute, jarak, ukuranRute);
                cout << "Kereta berhasil ditambahkan.\n";
                break;
            }
            case 2: {
                int trainID;
                cout << "Masukkan ID Kereta yang Ingin Dihapus: ";
                cin >> trainID;
                trainManager.hapusKereta(trainID);
                break;
            }
            case 3: {
                int trainID, kursiTersedia;
                string namaKereta;
                string rute[MAX_STATIONS];
                int jarak[MAX_STATIONS - 1];
                int ukuranRute = 0;

                cout << "Masukkan ID Kereta yang Ingin Diedit: ";
                cin >> trainID;
                cout << "Masukkan Nama Kereta: ";
                cin.ignore();
                getline(cin, namaKereta);
                cout << "Masukkan Jumlah Kursi Tersedia: ";
                cin >> kursiTersedia;

                string stasiun;
                int jarakStasiun;
                cout << "Masukkan Rute Stasiun (Ketik 'selesai' untuk selesai):\n";
                while (true) {
                    cout << "Masukkan Stasiun: ";
                    cin >> stasiun;
                    if (stasiun == "selesai") break;
                    rute[ukuranRute++] = stasiun;
                    if (ukuranRute > 1) {
                        cout << "Masukkan Jarak Dari Stasiun Sebelumnya: ";
                        cin >> jarakStasiun;
                        jarak[ukuranRute - 2] = jarakStasiun;
                    }
                }

                trainManager.editKereta(trainID, namaKereta, kursiTersedia, rute, jarak, ukuranRute);
                break;
            }
            case 4: {
                string kataKunci;
                cout << "Masukkan Kata Kunci untuk Pencarian: ";
                cin.ignore();
                getline(cin, kataKunci);
                trainManager.cariKereta(kataKunci);
                break;
            }
            case 5:
                trainManager.urutkanKereta();
                break;
            case 6:
                trainManager.tampilkanKereta();
                break;
            case 7:
                ticketManager.tampilkanTiket();
                break;
            case 8:
                ticketManager.tampilkanAntrianTunggu();
                break;            
            case 9:
                cout << "Keluar dari menu admin...\n";
                cout << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Coba lagi.\n";
                break;
        }
    } while (pilihan != 9);
}

int main() {
    TrainManager trainManager;
    TicketManager ticketManager;
    int pilihan;
    do {
        cout << "===========================================\n";
        cout << " SELAMAT DATANG DI SISTEM TIKET KERETA API \n";
        cout << "===========================================\n";
        cout << "-----=====-----\n";
        cout << "  Menu Utama  \n";
        cout << "-----=====-----\n";
        cout << "1. Menu Admin\n";
        cout << "2. Menu User\n";        
        cout << "3. Keluar\n";
        cout << "-----=====-----\n";
        cout << "Pilih Opsi: "; cin >> pilihan;
        cout << "-----=====-----\n";

        switch (pilihan) {
            case 1:
                adminMenu(trainManager, ticketManager);
                break;
            case 2:
                userMenu(trainManager, ticketManager);
                break; 
            case 3:
                cout << "Keluar dari program...\n";
                break;
            default:
                cout << "Pilihan tidak valid! Coba lagi.\n";
                break;
        }
    } while (pilihan != 3);

    return 0;
}