#include <iostream>

using namespace std;

const int MAX_TRAINS = 100;
const int MAX_STATIONS = 100;
const int HASH_TABLE_SIZE = 10;
#define MAX_QUEUE_SIZE 100
const int INF = 1e9;

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
    Edge* next;

    Edge(const string& tujuan, int jarak) : tujuan(tujuan), jarak(jarak), next(nullptr) {}
};

// Struct untuk Node dalam LinkedList Graph
struct Node {
    string stasiun;
    Edge* head;
    Node* next;

    Node(const string& stasiun) : stasiun(stasiun), head(nullptr), next(nullptr) {}
};

// Struct untuk Kereta
struct Train {
    int trainID;
    string namaKereta;
    int kursiTersedia;
    string rute[MAX_STATIONS];
    int jarakRute[MAX_STATIONS - 1];
    int ukuranRute;
};

// Struct untuk Node Kereta
struct TrainNode {
    Train kereta;
    TrainNode* next;

    TrainNode(const Train& _kereta) : kereta(_kereta), next(nullptr) {}
};

void copyTrainListToArray(TrainNode* head, Train* array, int size) {
    TrainNode* currentNode = head;
    for (int i = 0; i < size && currentNode != nullptr; ++i) {
        array[i] = currentNode->kereta; // Salin Train dari TrainNode ke array Train
        currentNode = currentNode->next;
    }
}

// Struct untuk Ticket
struct Ticket {
    int ticketID;
    User user;
    Train kereta;
};

// Struct untuk Queue
struct Queue {
    Ticket data[MAX_QUEUE_SIZE];
    int front;
    int rear;

    Queue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return (rear + 1) % MAX_QUEUE_SIZE == front;
    }

    bool isEmpty() const {
        return front == -1;
    }

    void enqueue(Ticket ticket) {
        if (isFull()) {
            cout << "Antrian penuh. Tidak dapat menambahkan tiket.\n";
            return;
        }
        if (isEmpty()) {
            front = 0;
        }
        rear = (rear + 1) % MAX_QUEUE_SIZE;
        data[rear] = ticket;
    }

    Ticket dequeue() {
        if (isEmpty()) {
            cout << "Antrian kosong. Tidak ada tiket untuk diambil.\n";
            return {};
        }
        Ticket ticket = data[front];
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % MAX_QUEUE_SIZE;
        }
        return ticket;
    }

    Ticket peek() {
        if (isEmpty()) {
            cout << "Antrian kosong.\n";
            return {};
        }
        return data[front];
    }
};

// Class untuk mengelola Graph
class Graph {
public:
    Node* adjList[MAX_STATIONS];
    int jumlahStasiun;

    Graph() : jumlahStasiun(0) {
        for (int i = 0; i < MAX_STATIONS; ++i) {
            adjList[i] = nullptr;
        }
    }

    Node* getOrCreateNode(const string& stasiun) {
        for (int i = 0; i < jumlahStasiun; ++i) {
            if (adjList[i]->stasiun == stasiun) {
                return adjList[i];
            }
        }
        Node* newNode = new Node(stasiun);
        adjList[jumlahStasiun++] = newNode;
        return newNode;
    }

    void tambahEdge(const string& sumber, const string& tujuan, int jarak) {
        Node* srcNode = getOrCreateNode(sumber);
        Node* destNode = getOrCreateNode(tujuan);

        Edge* newEdge = new Edge(tujuan, jarak);
        newEdge->next = srcNode->head;
        srcNode->head = newEdge;

        // Menambahkan edge balik untuk graf tidak berarah
        Edge* backEdge = new Edge(sumber, jarak);
        backEdge->next = destNode->head;
        destNode->head = backEdge;
    }

    void hapusEdge(const string& sumber, const string& tujuan, int jarak) {
        Node* srcNode = getOrCreateNode(sumber);
        Node* destNode = getOrCreateNode(tujuan);

        // Hapus edge dari sumber ke tujuan
        Edge* prev = nullptr;
        Edge* curr = srcNode->head;
        while (curr != nullptr) {
            if (curr->tujuan == tujuan && curr->jarak == jarak) {
                if (prev == nullptr) {
                    srcNode->head = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                break;
            }
            prev = curr;
            curr = curr->next;
        }

        // Hapus edge balik dari tujuan ke sumber
        prev = nullptr;
        curr = destNode->head;
        while (curr != nullptr) {
            if (curr->tujuan == sumber && curr->jarak == jarak) {
                if (prev == nullptr) {
                    destNode->head = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    string dijkstra(const string& start, const string& end) {
    int jarak[MAX_STATIONS];
    string previous[MAX_STATIONS];
    bool visited[MAX_STATIONS];
    string stasiun[MAX_STATIONS];

    for (int i = 0; i < jumlahStasiun; ++i) {
        jarak[i] = INF;
        visited[i] = false;
        stasiun[i] = adjList[i]->stasiun;
    }

    int startIdx = -1, endIdx = -1;
    for (int i = 0; i < jumlahStasiun; ++i) {
        if (stasiun[i] == start) startIdx = i;
        if (stasiun[i] == end) endIdx = i;
    }
    if (startIdx == -1 || endIdx == -1) return "Path not found";

    jarak[startIdx] = 0;

    for (int count = 0; count < jumlahStasiun - 1; ++count) {
        int minDist = INF, minIndex = -1;

        for (int v = 0; v < jumlahStasiun; ++v) {
            if (!visited[v] && jarak[v] <= minDist) {
                minDist = jarak[v];
                minIndex = v;
            }
        }

        if (minIndex == -1) break;

        int u = minIndex;
        visited[u] = true;

        for (Edge* neighbor = adjList[u]->head; neighbor != nullptr; neighbor = neighbor->next) {
            int neighborIdx = -1;
            for (int i = 0; i < jumlahStasiun; ++i) {
                if (stasiun[i] == neighbor->tujuan) {
                    neighborIdx = i;
                    break;
                }
            }
            if (neighborIdx != -1 && !visited[neighborIdx] && jarak[u] != INF &&
                jarak[u] + neighbor->jarak < jarak[neighborIdx]) {
                jarak[neighborIdx] = jarak[u] + neighbor->jarak;
                previous[neighborIdx] = stasiun[u];
            }
        }
    }

    string path = end;
    for (string at = end; at != start && !at.empty(); ) {
        int idx = -1;
        for (int i = 0; i < jumlahStasiun; ++i) {
            if (stasiun[i] == at) {
                idx = i;
                break;
            }
        }
        at = previous[idx];
        path = at + " -> " + path;
    }
    return path;
}
};

// Class untuk mengelola Kereta
class TrainManager {
public:
    TrainNode* hashTable[HASH_TABLE_SIZE];
    Graph graph;

    TrainManager() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    int hashFunction(int key) {
        return key % HASH_TABLE_SIZE;
    }

    void tambahKereta(int trainID, const string& namaKereta, int kursiTersedia, const string rute[], const int jarak[], int ukuranRute) {
        TrainNode* newNode = new TrainNode({ trainID, namaKereta, kursiTersedia, {}, {}, ukuranRute });
        int index = hashFunction(trainID);

        // Linear probing untuk menemukan slot kosong berikutnya jika indeks sudah terisi
        while (hashTable[index] != nullptr) {
            index = (index + 1) % HASH_TABLE_SIZE; // Geser ke slot berikutnya
        }

        newNode->next = hashTable[index];
        hashTable[index] = newNode;

        Train& kereta = newNode->kereta; // Mendapatkan referensi ke objek kereta di newNode
        copy(rute, rute + ukuranRute, kereta.rute);
        copy(jarak, jarak + ukuranRute - 1, kereta.jarakRute);

        for (int i = 0; i < ukuranRute - 1; ++i) {
            graph.tambahEdge(rute[i], rute[i + 1], jarak[i]);
        }
    }

    void hapusKereta(int trainID) {
        int index = hashFunction(trainID);
        int start = index;
        TrainNode* curr = hashTable[index];
        TrainNode* prev = nullptr;

        while (curr != nullptr && curr->kereta.trainID != trainID) {
            index = (index + 1) % HASH_TABLE_SIZE; // Geser ke slot berikutnya menggunakakn linear probing
            if (index == start) break;
            prev = curr;
            curr = hashTable[index];
        }

        if (curr != nullptr && curr->kereta.trainID == trainID) {
            // Hapus rute dari graf
            for (int i = 0; i < curr->kereta.ukuranRute - 1; ++i) {
                graph.hapusEdge(curr->kereta.rute[i], curr->kereta.rute[i + 1], curr->kereta.jarakRute[i]);
            }

            delete curr;
            hashTable[index] = nullptr;
            cout << "Kereta dengan ID " << trainID << " berhasil dihapus.\n";
        } else {
            cout << "Kereta dengan ID " << trainID << " tidak ditemukan.\n";
        }
    }

    void editKereta(int trainID, const string& namaKereta, int kursiTersedia, const string rute[], const int jarak[], int ukuranRute) {
        int index = hashFunction(trainID);
        int start = index;
        TrainNode* curr = hashTable[index];

        while (curr != nullptr && curr->kereta.trainID != trainID) {
            index = (index + 1) % HASH_TABLE_SIZE; // Geser ke slot berikutnya menggunakan linear probing
            if (index == start) break;
            curr = hashTable[index];
        }

        if (curr != nullptr && curr->kereta.trainID == trainID) {
            // Hapus rute lama dari graf
            for (int i = 0; i < curr->kereta.ukuranRute - 1; ++i) {
                graph.hapusEdge(curr->kereta.rute[i], curr->kereta.rute[i + 1], curr->kereta.jarakRute[i]);
            }

            curr->kereta.namaKereta = namaKereta;
            curr->kereta.kursiTersedia = kursiTersedia;
            curr->kereta.ukuranRute = ukuranRute;
            copy(rute, rute + ukuranRute, curr->kereta.rute);
            copy(jarak, jarak + ukuranRute - 1, curr->kereta.jarakRute);

            // Tambah rute baru ke graf
            for (int i = 0; i < ukuranRute - 1; ++i) {
                graph.tambahEdge(rute[i], rute[i + 1], jarak[i]);
            }
            cout << "Kereta dengan ID " << trainID << " berhasil diedit.\n";
        } else {
            cout << "Kereta dengan ID " << trainID << " tidak ditemukan.\n";
        }
    }

    void cariKereta(const string& kataKunci) {
        bool ditemukan = false;
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            TrainNode* curr = hashTable[i];
            while (curr != nullptr) {
                const Train& kereta = curr->kereta;
                if (to_string(kereta.trainID).find(kataKunci) != string::npos ||
                    kereta.namaKereta.find(kataKunci) != string::npos) {
                    ditemukan = true;
                    cetakInformasiKereta(kereta);
                } else {
                    for (int j = 0; j < kereta.ukuranRute; ++j) {
                        if (kereta.rute[j].find(kataKunci) != string::npos) {
                            ditemukan = true;
                            cetakInformasiKereta(kereta);
                            break;
                        }
                    }
                }
                curr = curr->next;
            }
        }
        if (!ditemukan) {
            cout << "Kereta dengan kata kunci \"" << kataKunci << "\" tidak ditemukan.\n";
        }
    }

void cetakInformasiKereta(const Train& kereta) {
    cout << "==================================================\n";
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


    void urutkanKereta() {
    // Buat salinan sementara dari hash table dengan kapasitas maksimal
    Train tempHashTable[HASH_TABLE_SIZE];
    int count = 0;

    // Salin data dari hash table ke array sementara
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        TrainNode* currentNode = hashTable[i];
        while (currentNode != nullptr) {
            tempHashTable[count++] = currentNode->kereta;
            currentNode = currentNode->next;
        }
    }

    // Lakukan pengurutan pada array sementara
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (tempHashTable[j].trainID > tempHashTable[j + 1].trainID) {
                swap(tempHashTable[j], tempHashTable[j + 1]);
            }
        }
    }

    // Tampilkan hasil pengurutan
    cout << "Kereta berhasil diurutkan berdasarkan ID.\n";
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
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
            cout << "\nJarak          : ";
            for (int j = 0; j < kereta.ukuranRute - 1; ++j) {
                cout << kereta.jarakRute[j] << " km";
                if (j < kereta.ukuranRute - 2) cout << ", ";
            }
            cout << "\n";
            cout << "==================================================\n";
            cout << "\n\n";
        }
    } else {
        cout << "Tidak ada kereta yang tersedia.\n";
    }
}


    void tampilkanKereta() const {
        bool adaKereta = false;
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            TrainNode* curr = hashTable[i];
            while (curr != nullptr) {
                adaKereta = true;
                const Train& kereta = curr->kereta;
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
                curr = curr->next;
            }
        }
        if (!adaKereta) {
            cout << "Tidak ada kereta yang tersedia.\n";
        }
    }

    Train* cariKeretaDenganRute(const string& start, const string& end) {
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        TrainNode* curr = hashTable[i];
        while (curr != nullptr) {
            Train& kereta = curr->kereta;
            for (int j = 0; j < kereta.ukuranRute - 1; ++j) {
                if (kereta.rute[j] == start && kereta.rute[j + 1] == end) {
                    return &kereta;
                }
            }
            curr = curr->next;
        }
    }
    return nullptr;
}

    pair<string, Train*> ruteTerpendek(const string& start, const string& end) {
    string path = graph.dijkstra(start, end);
    if (path == "Path not found") {
        return { "", nullptr };
    }
    Train* kereta = cariKeretaDenganRute(start, end);
    return { path, kereta };
}

};

// Class untuk mengelola Tiket
class TicketManager {
public:
    Queue antrianTiket;

    void pesanTiket(User& user, Train& kereta) {
        if (kereta.kursiTersedia > 0) {
            Ticket tiket = { rand() % 1000, user, kereta };
            antrianTiket.enqueue(tiket);
            kereta.kursiTersedia--;
            cout << "Tiket berhasil dipesan untuk " << user.nama << " pada kereta " << kereta.namaKereta << endl;
        } else {
            cout << "Tidak ada kursi tersedia. Tiket tidak dapat dipesan.\n";
        }
    }

    void tampilkanTiket() const {
        if (antrianTiket.isEmpty()) {
            cout << "Tidak ada tiket yang dipesan.\n";
            return;
        }
        cout << "Daftar Tiket:\n";
        int index = antrianTiket.front;
        while (index != antrianTiket.rear) {
            const Ticket& tiket = antrianTiket.data[index];
            cout << "==============================\n";
            cout << "ID Tiket : " << tiket.ticketID << "\n";
            cout << "User     : " << tiket.user.nama << "\n";
            cout << "email    : " << tiket.user.email << "\n";
            cout << "Kereta   : " << tiket.kereta.namaKereta << "\n";
            cout << "==============================\n";
            index = (index + 1) % MAX_QUEUE_SIZE;
        }
        const Ticket& tiket = antrianTiket.data[index];
        cout << "==============================\n";
        cout << "ID Tiket : " << tiket.ticketID << "\n";
        cout << "User     : " << tiket.user.nama << "\n";
        cout << "email    : " << tiket.user.email << "\n";
        cout << "Kereta   : " << tiket.kereta.namaKereta << "\n";
        cout << "==============================\n";
    
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
        cout << "3. Keluar\n";
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
                cout << "Masukkan Stasiun Keberangkatan: ";
                cin >> startStation;
                cout << "Masukkan Stasiun Tujuan: ";
                cin >> endStation;

                auto result = trainManager.ruteTerpendek(startStation, endStation); // Gunakan auto untuk mendeklarasikan variabel

                // Dapatkan path dan kereta dari hasil
                string path = result.first;
                Train* kereta = result.second;

                if (!path.empty()) {
                    cout << "Rute Terpendek dari " << startStation << " ke " << endStation << " adalah:\n" << path << "\n";
                if (kereta != nullptr) {
                    cout << "Menggunakan Kereta ID: " << kereta->trainID << "\n";
                    cout << "Nama Kereta          : " << kereta->namaKereta << "\n";
                } else {
                    cout << "Tidak ada kereta yang ditemukan untuk rute tersebut.\n";
                }

                    int pilihanKereta;
                    cout << "Masukkan ID Kereta yang Ingin Dipesan (atau 0 untuk Batalkan): ";
                    cin >> pilihanKereta;

                    if (pilihanKereta > 0) {
                        int hashIndex = trainManager.hashFunction(pilihanKereta);
                        int startIndex = hashIndex;
                        TrainNode* curr = trainManager.hashTable[hashIndex];

                        while (curr != nullptr && curr->kereta.trainID != pilihanKereta) {
                            hashIndex = (hashIndex + 1) % HASH_TABLE_SIZE;
                            if (hashIndex == startIndex) {
                                curr = nullptr; // Jika sudah kembali ke posisi awal, hentikan pencarian
                                break;
                            }
                            curr = trainManager.hashTable[hashIndex];
                        }

                        if (curr != nullptr && curr->kereta.trainID == pilihanKereta) {
                            ticketManager.pesanTiket(user, curr->kereta);
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
        cout << "8. Keluar\n";
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
                cout << "Keluar dari menu admin...\n";
                cout << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Coba lagi.\n";
                break;
        }
    } while (pilihan != 8);
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