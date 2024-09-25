#include <iostream>
#include <string>

using namespace std;

bool isValidInput(const string& kalimat) {
    // Cek panjang kalimat
    if (kalimat.length() < 1 || kalimat.length() > 100) {
        return false;
    }
    
    // Cek setiap karakter
    for (char c : kalimat) {
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
            return false;
        }
    }
    return true;
}

int main() {
    string kalimat;

    cout << "Masukkan Kalimat: " << endl;
    getline(cin, kalimat);

    // Validasi input
    if (!isValidInput(kalimat)) {
        cout << "Kalimat tidak valid. Pastikan terdiri atas 1 sampai 100 karakter dan hanya berupa a-z, A-Z, atau spasi." << endl;
        return 1; // Keluar dari program jika input tidak valid
    }

    cout << "Kalimat Yang Anda Masukkan: " << kalimat << endl;

    return 0;
}
