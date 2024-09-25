#include <iostream>
#include <string>
using namespace std;

// Definisi struktur untuk identitas
struct Identitas {
    int NIM;
    string nama;
    string gender;
    string alamat;
};

// Definisi struktur untuk nilai
struct NilaiMatakuliah {
    string namaMatakuliah;
    double nilaiTugas;
    double nilaiUTS;
    double nilaiUAS;
};

// Definisi struktur utama yang menggabungkan kedua struktur di atas
struct Mahasiswa {
    Identitas identitas;
    NilaiMatakuliah nilai;
};

int main() {
    // Contoh penggunaan struktur Mahasiswa
    Mahasiswa mahasiswa1;

    // Inisialisasi identitas
    mahasiswa1.identitas.NIM = 131;
    mahasiswa1.identitas.nama = "Alif Rasyid Febriansyah";
    mahasiswa1.identitas.gender = 'M';
    mahasiswa1.identitas.alamat = "Blok Tegalan, RT/RW 036/009, Desa jamblang, Kec Jamblang, Kab. Cirebon, Jawa Barat, 45156.";

    // Inisialisasi nilai
    mahasiswa1.nilai.namaMatakuliah = "Pemrogramman Dasar";
    mahasiswa1.nilai.nilaiTugas = 95.3;
    mahasiswa1.nilai.nilaiUTS = 95.4;
    mahasiswa1.nilai.nilaiUAS = 95.5;

    // Mengakses salah satu anggota struktur dari variabel Mahasiswa
    cout << "NIM        : " << mahasiswa1.identitas.NIM <<endl;
    cout << "Nama       : " << mahasiswa1.identitas.nama << endl;
    cout << "Gender     : " << mahasiswa1.identitas.gender << endl;
    cout << "Alamat     : " << mahasiswa1.identitas.alamat << endl;
    cout << "Matakuliah : " << mahasiswa1.nilai.namaMatakuliah << endl;
    cout << "Nilai Tugas: " << mahasiswa1.nilai.nilaiTugas << endl;
    cout << "Nilai UTS  : " << mahasiswa1.nilai.nilaiUTS << endl;
    cout << "Nilai UAS  : " << mahasiswa1.nilai.nilaiUAS << endl;

    return 0;
}
