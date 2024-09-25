#include <iostream>
#include <string>
using namespace std; 

int main() {
    string N;
    getline(cin, N); 

    string jiko = "hai aku ";
    size_t pos = N.find(jiko); 

    if (pos != string::npos) {
        string nama_member = N.substr(pos + jiko.length()); 
        cout << nama_member << endl;
    } else {
        cout << "Tidak ada nama member yang ditemukan" << endl;
    }

    return 0;
}
