#include <iostream>
#include <string>
using namespace std;

struct Idetitas {
    int NIM;
    string nama;
    char gender;
    string alamat;
};

int main() {
    // Contoh penggunaan struktur Mahasiswa
    Idetitas Idetitas1;
    Idetitas1.NIM = 131;
    Idetitas1.nama = "Alif Rasyid Febriansyah";
    Idetitas1.gender = 'M';
    Idetitas1.alamat = "Blok Tegalan, RT/RW 036/009, Desa jamblang, Kec Jamblang, Kab. Cirebon, Jawa Barat, 45156.";

    cout << "NIM   : " << Idetitas1.NIM << endl;
    cout << "Nama  : " << Idetitas1.nama << endl;
    cout << "Gender: " << Idetitas1.gender << endl;
    cout << "Alamat: " << Idetitas1.alamat << endl;

    return 0;
}
