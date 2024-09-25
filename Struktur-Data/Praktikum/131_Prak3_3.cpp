#include <bits/stdc++.h>
using namespace std;
#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

// Struktur untuk menyimpan data tanggal lahir
struct date {
    int day;
    int month;
    int year;
};

// Struktur untuk menyimpan data supir
struct datasopir {
    string id;
    string nama;
    date lahir;
    char kelamin;
    string alamat;
};

// Struktur untuk menyimpan node linked list
struct node {
    datasopir data;
    node *next;
    node *prev;
};

// Deklarasi variabel global yang digunakan sebagai head dan tail dari linked list
node *head, *tail;

// Deklarasi head dan tail sebagai NULL
void init() {
    head = NULL;
    tail = NULL;
}

// Fungsi untuk mengecek apakah linked list kosong atau tidak
int isEmpty() {
    if (tail == NULL) {
        return 1;
    } else {
        return 0;
    }
}

// Struktur untuk menyimpan data order
struct order {
    string idorder;
    string nama_pelanggan;
    string nama_supir;
    string plat;
    string tujuan;
    order *next;
    order *prev;
};

// Struktur untuk menyimpan data mobil
struct datamobil {
    string platNomor;
    string jenis;
    string brand;
    datamobil *next;
    datamobil *prev;
};

typedef datamobil *mblptr;
mblptr headmbl;
mblptr tailmbl;

mblptr headmobil = nullptr;
mblptr tailmobil = headmobil;


typedef order *orderptr;
orderptr heads;
orderptr tails;

orderptr headorder = nullptr;
orderptr tailorder = headorder;

int isempty() {
    if (headmbl == nullptr) {
        return 1;
    } else {
        return 0;
    }
}



string generateID(const datasopir &supir) {
    string id;

    // Dapatkan 2 digit pertama berdasarkan urutan huruf pertama dan terakhir dari nama supir
    char first_char = tolower(supir.nama.front());
    char last_char = tolower(supir.nama.back());
    int first_two_digits = abs(first_char - last_char);
    if (first_two_digits < 10)
    {
        id += "0";
    }
    id += to_string(first_two_digits);

    // Digit ke-3 berdasarkan jenis kelamin
    if (supir.kelamin == 'L' || supir.kelamin == 'l') {
        id += "1";
    } else {
        id += "0";
    }

    // Digit ke-4 berdasarkan tanggal lahir
    int day = supir.lahir.day % 10;
    int month = supir.lahir.month % 10;
    int year = supir.lahir.year % 10;
    int fourth_digit = (day + month + year) % 9;
    id += to_string(fourth_digit);

    // Digit ke-5 akan diset sesuai dengan kondisi kemungkinan duplikasi
    id += "0";

    return id;
}



// Fungsi untuk menghapus data supir
void hapusdata() {
    node *hapus;
    string idhapus;
    if (isEmpty() == 0) {
        cout << "Masukkan ID Supir yang ingin dihapus : ";
        cin >> idhapus;
        cin.ignore();
        hapus = head;

        while (hapus->data.id != idhapus) {
            if (hapus->next == head) {
                cout << "Data tidak ditemukan !" << endl;
                return;
            }
            hapus = hapus->next;
        }

        if (hapus == head) {
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete hapus;
        } else if (hapus == tail) {
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
            delete hapus;
        } else {
            hapus->prev->next = hapus->next;
            hapus->next->prev = hapus->prev;
            delete hapus;
        }
        cout << "Data berhasil dihapus !" << endl;
    } else {
        cout << "Data kosong !" << endl;
    }
    return;
}



void tambahdata(const datasopir &sopirbaru) {
    node *baru, *bantu;
    baru = new node;
    baru->data = sopirbaru;

    // Menghasilkan ID berdasarkan aturan yang ditentukan
    baru->data.id = generateID(sopirbaru);

    baru->next = baru;
    baru->prev = baru;

    if (isEmpty() == 1) {
        head = baru;
        tail = baru;
        head->next = head;
        head->prev = head;
        tail->prev = tail;
        tail->prev = tail;
    } else {
        baru->next = head;
        head->prev = baru;
        head = baru;
        head->prev = tail;
        tail->next = head;
    }
    cout << "Data berhasil ditambahkan !" << endl;
}



// Fungsi untuk menampilkan data supir pada menu admin
void tampildataadmin() {
    node *bantu = head;
    if (isEmpty() == 0) {
        int choice;

        do {
            string jenis_kelamin;

            if (bantu->data.kelamin == 'L' || bantu->data.kelamin == 'l') {
                jenis_kelamin = "Laki-laki";
            } else if (bantu->data.kelamin == 'P' || bantu->data.kelamin == 'p') {
                jenis_kelamin = "Perempuan";
            } else {
                jenis_kelamin = "Tidak diketahui";
            }

            cout << "|-------------------------------|\n";
            cout << "|ID Supir       : " << setw(14) << left << bantu->data.id << "|\n";
            cout << "|Nama Supir     : " << setw(14) << left << bantu->data.nama << "|\n";
            cout << "|Tanggal Lahir  : " << bantu->data.lahir.day << "-" << bantu->data.lahir.month << "-" << bantu->data.lahir.year << "     |\n";
            cout << "|Jenis Kelamin  : " << setw(14) << left << jenis_kelamin << "|\n";
            cout << "|Alamat         : " << setw(14) << left << bantu->data.alamat << "|\n";
            cout << "|-------------------------------|\n";
            cout << " " << endl;

            cout << "1. Next\n";
            cout << "2. Previous\n";
            cout << "3. Exit\n";
            cout << "Pilihan Anda : ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                if (bantu->next != nullptr)
                    bantu = bantu->next;
                else
                    cout << "Anda sudah berada pada data terakhir.\n";
                system("cls");
                break;
            case 2:
                if (bantu->prev != nullptr)
                    bantu = bantu->prev;
                else
                    cout << "Anda sudah berada pada data pertama.\n";
                system("cls");
                break;
            case 3:
                //cout << "Kembali ke menu utama.\n";
                system("cls");
                return;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
            }
        } while (true);
    } else {
        cout << "Data kosong !" << endl;
    }
    return;
}



void prosesPesanan(orderptr &head) {
    int pilihan5;
    orderptr current = head;
    orderptr temp;

    if (current == nullptr) {
        cout << "Antrian kosong" << endl;
        return;
    }

    while (current != nullptr) {
        if (current->idorder == "") {
            temp = current;
            current = current->prev;
            delete temp;
        }

        cout << "|------------------------|\n";
        cout << "|ID      : " << setw(14) << left << current->idorder << "|\n";
        cout << "|Nama    : " << setw(14) << left << current->nama_pelanggan << "|\n";
        cout << "|Supir   : " << setw(14) << left << current->nama_supir << "|\n";
        cout << "|Plat    : " << setw(14) << left << current->plat << "|\n";
        cout << "|Tujuan  : " << setw(14) << left << current->tujuan << "|\n";
        cout << "|------------------------|\n";

        cout << endl;
        cout << "1. Accept" << endl;
        cout << "2. Reject" << endl;
        cout << "3. Exit" << endl;
        cin >> pilihan5;
        switch (pilihan5) {
        case 1:
            cout << "Pesanan dengan " << current->idorder << " telah diproses !!" << endl;
            break;
        case 2:
            cout << "Pesanan dengan " << current->idorder << " telah ditolak !!" << endl;
            break;
        case 3:
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }
        temp = current;
        current = current->prev;

        delete temp;
    }

    // Setelah menghapus pesanan, perbarui headorder dan tailorder
    head = nullptr;
    tailorder = nullptr;
}



// Fungsi untuk mengubah data supir
void ubahdata() {
    node *bantu;
    string idubah;

    if (isEmpty() == 0) {
        cout << "Masukkan ID Supir yang ingin diubah : ";
        cin >> idubah;
        cin.ignore();
        bantu = head;

        while (bantu->data.id != idubah) {
            if (bantu->next == head) {
                cout << "Data tidak ditemukan !" << endl;
                return;
            }
            bantu = bantu->next;
        }

        cout << "|----------------------------------|\n";
        cout << "|ID Supir       : " << setw(14) << left << bantu->data.id << "|\n";
        cout << "|Nama Supir     : " << setw(14) << left << bantu->data.nama << "|\n";
        cout << "|Tanggal Lahir  : " << bantu->data.lahir.day << "-" << bantu->data.lahir.month << "-" << bantu->data.lahir.year << "     |\n";
        cout << "|Jenis Kelamin  : " << setw(14) << left << bantu->data.kelamin << "|\n";
        cout << "|Alamat         : " << setw(14) << left << bantu->data.alamat << "|\n";
        cout << "|----------------------------------|\n";

        cout << "Masukkan Nama Supir baru : ";
        cin.ignore();
        getline(cin, bantu->data.nama);
        cout << "Masukkan Tanggal Lahir baru : ";
        cin >> bantu->data.lahir.day >> bantu->data.lahir.month >> bantu->data.lahir.year;
        cin.ignore();
        cout << "Masukkan Jenis Kelamin baru : ";
        cin >> bantu->data.kelamin;
        cin.ignore();
        cout << "Masukkan Alamat baru : ";
        cin.ignore();
        getline(cin, bantu->data.alamat);

        // Menghasilkan ID baru berdasarkan aturan yang ditentukan
        bantu->data.id = generateID(bantu->data);

        cout << "Data berhasil diubah !" << endl;
    } else {
        cout << "Data kosong !" << endl;
    }
}



void pushmbl(mblptr &headmbl, mblptr &tailmbl, node *curr) {
    mblptr newmbl = new datamobil;
    string platNomor;
    string jenis;
    string brand;
    cin.ignore();
    cout << "Masukkan plat nomor mobil : " << endl;
    getline(cin, platNomor);
    cout << "Masukkan jenis mobil : " << endl;
    getline(cin, jenis);
    cout << "Masukkan brand mobil : " << endl;
    getline(cin, brand);

    newmbl->platNomor = platNomor;
    newmbl->jenis = jenis;
    newmbl->brand = brand;

    if (headmbl == nullptr) {
        headmbl = newmbl;
        tailmbl = newmbl;
        newmbl->next = nullptr;
        newmbl->prev = nullptr;
    } else {
        newmbl->next = headmbl;
        newmbl->prev = nullptr;

        headmbl->prev = newmbl;
        headmbl = newmbl;
    }
    cout << "Mobil telah ditambahkan !!!" << endl;
    cout << "platNomor:" << newmbl->platNomor << endl;
    cout << "Jenis    :" << newmbl->jenis << endl;
    cout << "brand    :" << newmbl->brand << endl;

    // Mengecek apakah pengguna ingin melakukan tambah unit lagi
    char lagi;
    cout << "Ingin menambahkan unit lain? (y/n) > ";
    cin >> lagi;

    if (lagi == 'y' || lagi == 'Y') {
        // Memanggil kembali fungsi tambah unit jika pengguna ingin melanjutkan
        pushmbl(headmbl, tailmbl, curr);
    }  
}



void popmbl(mblptr &headmbl, mblptr &tailmbl) {
    mblptr temp;
    if (headmbl == nullptr) {
        cout << "Unit mobil sedang kosong harap menunggu" << endl;
    } else {
        temp = headmbl;
        if (headmbl == tailmbl) {
            headmbl = nullptr;
            tailmbl = nullptr;
        } else {
            headmbl = headmbl->next;
            headmbl->prev = nullptr;
        }
        delete temp;
    }
}



string generateidorder(const order &order, node *curr = head) {
    string idorder;

    // Rule 1: 2 digit pertama merupakan urutan alphabet dari character pertama pada plat mobil
    char first_plate_char = headmbl->platNomor[0];
    int first_two_digits = (int)tolower(first_plate_char) - 96; // Convert char to lowercase and subtract ASCII value of 'a' - 96
    idorder += to_string(first_two_digits);

    // Rule 2: Digit ke 3, 4, 5, 6, dan 7 merupakan nomor Id dari supir yang mengendarai taxi.
    string supir_id_digits = curr->data.id;
    idorder += supir_id_digits;

    // Rule 3: Digit 8 dan 9 didapat dari urutan 2 huruf terakhir pada tujuan perjalanan yang ditambahkan.
    string tujuan_last_two_chars = order.tujuan.substr(order.tujuan.length() - 2);                                      // Ambil 2 karakter terakhir dari tujuan
    int destination_digits = (int)tolower(tujuan_last_two_chars[0]) - 96 + (int)tolower(tujuan_last_two_chars[1]) - 96; // Jumlahkan urutan huruf
    idorder += to_string(destination_digits);

    // Rule 4: Digit terakhir merupakan seluruh urutan huruf pada nama pelanggan yang ditambahkan
    // dan diambil digit terakhirnya bila hasil penjumlahan lebih dari 1 digit.
    int sum_of_name_chars = 0;
    for (char c : order.nama_pelanggan) {
        sum_of_name_chars += (int)tolower(c) - 96; // Jumlahkan urutan huruf dalam nama pelanggan
    }
    int last_digit = sum_of_name_chars % 10; // Ambil digit terakhir dari jumlah urutan huruf
    idorder += to_string(last_digit);

    return idorder;
}



void pushorder(orderptr &heads, orderptr &tails, node *curr) {

    orderptr neworder = new order;
    string nama;
    string tujuan;
    neworder->plat = headmbl->platNomor;
    cout << "Masukkan nama anda : " << endl;
    getline(cin, nama);
    cout << "Masukkan tujuan anda : " << endl;
    getline(cin, tujuan);

    neworder->nama_pelanggan = nama;
    neworder->tujuan = tujuan;
    neworder->nama_supir = curr->data.nama;
    neworder->idorder = generateidorder(*neworder);

    if (heads == nullptr) {
        heads = neworder;
        tails = neworder;
        neworder->next = nullptr;
        neworder->prev = nullptr;
    } else {
        neworder->next = heads;
        neworder->prev = nullptr;

        heads->prev = neworder;
        heads = neworder;
    }
    popmbl(headmbl, tailmbl);
    cout << "order telah dilakukan !!!" << endl;
    cout << "|----------------------|\n";
    cout << "|Id     :" << setw(14) << left << neworder->idorder << "|\n";
    cout << "|Nama   :" << setw(14) << left << neworder->nama_pelanggan << "|\n";
    cout << "|Supir  :" << setw(14) << left << neworder->nama_supir << "|\n";
    cout << "|Plat   :" << setw(14) << left << neworder->plat << "|\n";
    cout << "|Tujuan :" << setw(14) << left << neworder->tujuan << "|\n";
    cout << "|----------------------|\n";

    // Memperbarui headorder dan tailorder setelah menambahkan pesanan baru
    heads = neworder;
    if (tails == nullptr) {
        tails = neworder;
    }
}



void tampildatauser() {
    node *curr = head;
    if (isEmpty() == 0) {
        int choice;

        do {
            string jenis_kelamin;

            if (curr->data.kelamin == 'L' || curr->data.kelamin == 'l') {
                jenis_kelamin = "Laki-laki";
            } else if (curr->data.kelamin == 'P' || curr->data.kelamin == 'p') {
                jenis_kelamin = "Perempuan";
            } else {
                jenis_kelamin = "Tidak diketahui";
            }

            cout << "|-------------------------------|\n";
            cout << "|ID Supir       : " << setw(14) << left << curr->data.id << "|\n";
            cout << "|Nama Supir     : " << setw(14) << left << curr->data.nama << "|\n";
            cout << "|Tanggal Lahir  : " << curr->data.lahir.day << "-" << curr->data.lahir.month << "-" << curr->data.lahir.year << "    |\n";
            cout << "|Jenis Kelamin  : " << setw(14) << left << jenis_kelamin << "|\n";
            cout << "|Alamat         : " << setw(14) << left << curr->data.alamat << "|\n";
            cout << "|-------------------------------|\n";
            cout << " " << endl;

            cout << "1. Next\n";
            cout << "2. Previous\n";
            cout << "3. Order\n";
            cout << "4. Exit\n";
            cout << "> ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                if (curr->next != nullptr)
                    curr = curr->next;
                else
                    cout << "Anda sudah berada pada data terakhir.\n";
                system("cls");
                break;
            case 2:
                if (curr->prev != nullptr)
                    curr = curr->prev;
                else
                    cout << "Anda sudah berada pada data pertama.\n";
                system("cls");
                break;
            case 3:
                system("cls");
                if (headmbl == nullptr) {
                    cout << "Mobil sedang kosong harap menunggu" << endl;
                    break;
                }
                pushorder(headorder, tailorder, curr);

                // Setelah pesanan ditambahkan, periksa apakah antrian kosong
                if (headorder == nullptr) {
                    cout << "Antrian kosong." << endl;
                    break;
                }
                break;
            case 4:
                system("cls");
                //cout << "Kembali ke menu utama.\n";
                return;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
            }
        } while (true);
    } else {
        cout << "Data kosong !" << endl;
    }
    return;
}



// Fungsi menu program dan pilihan antara admin dan user
int main() {

    int i;
    while (true) {
        cout << "====================\n";
        cout << "   Selamat Datang\n";
        cout << "====================\n";
        cout << "1. Masuk Sebagai Admin\n";
        cout << "2. Masuk Sebagai User\n";
        cout << "0. Exit\n";
        cout << "> ";
        cin >> i;
        cin.ignore();
        system("cls");

        switch (i) {
        case 1:
            int j;
            while (true) {
                cout << "====Dashboard Admin====\n";
                cout << "1. Mencari Data Supir\n";
                cout << "2. Menambah Data Supir\n";
                cout << "3. Mengubah Data Supir\n";
                cout << "4. Menghapus Data Supir\n";
                cout << "5. Proses Pesanan\n";
                cout << "6. Tambah Unit Mobil\n";
                cout << "0. Exit\n";
                cout << "> ";
                cin >> j;
                system("cls");
                datasopir supirbaru;

                switch (j) {
                case 1:
                    system("cls");
                    tampildataadmin();
                    break;
                case 2:
                    system("cls");
                    cout << "Masukkan Nama Supir : ";
                    cin.ignore();
                    getline(cin, supirbaru.nama);
                    cout << "Masukkan Tanggal Lahir : ";
                    cin >> supirbaru.lahir.day >> supirbaru.lahir.month >> supirbaru.lahir.year;
                    cin.ignore();
                    cout << "Masukkan Jenis Kelamin (L/P) : ";
                    cin >> supirbaru.kelamin;
                    cout << "Masukkan Alamat : ";
                    cin.ignore();
                    getline(cin, supirbaru.alamat);
                    tambahdata(supirbaru);
                    break;
                case 3:
                    system("cls");
                    ubahdata();
                    break;
                case 4:
                    system("cls");
                    hapusdata();
                    break;

                case 5:
                    system("cls");
                    if (head == nullptr) {
                        cout << "Tidak ada pesanan" << endl;
                        break;
                    }
                    prosesPesanan(tailorder);
                    break;

                case 6:
                    system("cls");
                    pushmbl(headmbl, tailmbl, head);
                    break;
                case 0:
                    system("cls");
                    break;
                default:
                    system("cls");
                    cout << "Pilihan tidak ada\n";
                    break;
                }

                if (j == 0) {
                    break;
                }
            }
            break;
        case 2:
            int k;
            while (true) {
                cout << "====Dashboard User====\n";
                cout << "1. Tampilkan Data Supir\n";
                cout << "0. Exit\n";
                cout << "> ";
                cin >> k;
                system("cls");
                
                switch (k) {
                case 1: 
                    system("cls");
                    tampildatauser();
                    break;
                case 0:
                    system("cls");
                    break;
                default:
                    system("cls");
                    cout << "Pilihan tidak ada\n";
                }
                if (k == 0) {
                    break;
                }
            }
            break;
        case 0:
            return 0;
        default:
            cout << "Pilihan tidak valid.\n";
            break;
        }
    }
    return 0;
}