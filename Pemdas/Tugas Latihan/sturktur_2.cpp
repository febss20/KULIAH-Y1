#include <iostream>
#include <string>
using namespace std;

struct NilaiMatakuliah {
    string namaMatakuliah;
    double nilaiTugas;
    double nilaiUTS;
    double nilaiUAS;
};

int main() {
    NilaiMatakuliah nilaiMatkul;
    nilaiMatkul.namaMatakuliah = "Pemrogramman Dasar";
    nilaiMatkul.nilaiTugas = 95.3;
    nilaiMatkul.nilaiUTS = 95.4;
    nilaiMatkul.nilaiUAS = 95.5;

    cout << "Mata Kuliah : " << nilaiMatkul.namaMatakuliah << endl;
    cout << "Nilai Tugas : " << nilaiMatkul.nilaiTugas << endl;
    cout << "Nilai UTS   : " << nilaiMatkul.nilaiUTS << endl;
    cout << "Nilai UAS   : " << nilaiMatkul.nilaiUAS << endl;

    return 0;
}