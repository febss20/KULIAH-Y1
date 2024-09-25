# Remote Access

Pada materi kali ini, kita akan membahas bagaimana cara mengakses sistem operasi
melalui perantara jaringan. Ini diperlukan untuk memudahkan baik manajemen maupun
_troubleshooting_ sistem operasi. Dengan metode Remote Access, kita tidak perlu
berhadapan dengan perangkat secara fisik untuk melakukan suatu operasi. Sehingga
kegiatan manajemen dapat dilakukan dimana saja dan kapan saja.

## Remote Access berdasarkan perantara
Berdasarkan perantaranya, metode Remote Access dibagi menjadi dua kategori, yaitu:

* Direct connect
* Intermediate Connect

__Direct Connect__ ialah jenis Remote Access yang dimana koneksinya tanpa bantuan
pihak ketiga dengan infrastruktur dan koneksi berada dalam kendali penuh 
Administrator. Beberapa metode Remote Access yang membutuhkan Direct Connect
antara lain adalah :
* Telnet
* SSH (Secure Shell)
* VNC
* RDP

Semua metode Direct Connect menggunakan metode Client<=>Server yang berarti
ada satu perangkat yang diremote jarak jauh sebagai server / penyedia
koneksi remote. Dimana setiap perangkat yang terkoneksi dengan server bersifat
sebagai client.

__Intermediate Connect__ ialah jenis Remote Access yang dimana koneksinya
bergantung pada layanan pihak ketiga. Koneksi antara satu perangkat dengan
perangkat lain harus melewati media perantara yang telah disediakan oleh pihak
penyedia layanan. Beberapa metode Remote Access yang menggunakan Intermediate 
Connect adalah:
* Chrome Remote Desktop
* Team Viewer
* Anydesk

|Direct Connect|Intermediate Connect|
|--------------|--------------------|
|Delay tergantung jarak fisik|Traffic harus melewati server provider|
|Koneksi privat | Koneksi kemungkinan disadap penyedia|
|Dibangun secara manual| Tinggal install aplikasi client|
|Kendali penuh terhadap protokol dan jaringan | Protokol ditentukan oleh penyedia layanan|
|Mayoritas gratis dan penggunaan tanpa batas | Beberapa berbayar untuk fitur tertentu|

## Telnet (Teletype Network)
__WARNING!!__
Telnet tidak aman digunakan di production karena tidak menggunakan enkripsi.

Teletype Network (Telnet) adalah aplikasi yang menggunakan protokol client/server
untuk memberikan akses ke virtual terminal dari sistem remot pada Local Area Network (LAN)
atau Internet. Penggunaan telnet ditinggalkan seiring waktu karena digantikan oleh
SSH yang memberi lebih banyak fitur dan lebih aman karena menggunakan enkripsi 
dalam proses koneksinya. Kini telnet hanya digunakan untuk manajemen perangkat local
yang tidak krusial atau yang berhubungan langsung dengan jaringan internet.

## SSH (Secure Shell)
Secure Shell Protocol merupakan protokol yang awalnya ditulis oleh Tatu Yienen
pada tahun 1995 sebagai respon kecelakaan peretasan di jaringan Universitas Finlandia.
Sebuah password sniffer telah terpasang di sebuah server yang terkoneksi secara
langsung ke backbone, dan ketika ditemukan, memiliki ribuan username dan password
di databasenya.

SSH memungkinkan kita mengakses shell secara remote tanpa harus mengakses terminal
fisik. Ini menjadi solusi yang mutakhir karena server tidak perlu menjalankan 
sistem grafis sehingga mengurangi beban kerja server.

Kini SSH digunakan untuk memanajemen lebih dari setengah infrastruktur di internet,
baik itu on premise maupun cloud. SSH digunakan karena dinilai dan terbukti
cara paling mudah dan aman untuk memberikan akses secara remote ke sistem operasi.

### Setup SSH Server di Ubuntu
Untuk membuat SSH server di Ubuntu, kita tinggal menginstall paket yang bernama
'openssh-server', kemudian mengaktifkan service ssh daemon.
```bash
sudo apt install openssh-server
sudo systemctl enable --now ssh
```

Dengan ini, openssh-server sudah dapat kita akses melalui jaringan menggunakan
openssh-client. Apabila belum terinstall, kita bisa install openssh-client
menggunakan perintah berikut:
```bash
sudo apt install openssh-client
```

Untuk menyambungkan ke openssh-server, gunakan perintah berikut ini:
`ssh username@IP` kemudian klik <kbd>Enter</kbd> dan masukkan password user kita.

Secara default, ssh menggunakan port 22 untuk koneksinya. Port ini harus
kita ganti apabila sudah masuk production karena merupakan port yang mudah
ditebak oleh hacker. 

Untuk konfigurasi ssh, dapat kita lihat di file `/etc/ssh/sshd_config`.
Dalam file ini, kita bisa mengatur port, metode login, banner, motd, dll yang bisa
kita gunakan baik untuk mengamankan SSH maupun mengkostumisasi saat kita masuk ke 
koneksi SSH.

## VNC (Virtual Network Computing)
VNC merupakan sistem berbagi desktop grafis yang menggunakan Remote Frame Buffer
(RFB) untuk mengendalikan komputer lain secara remote. VNC dapat digunakan
untuk berbagi layar dan tidak harus layar fisik karena VNC server dapat
berjalan secara _headless_ atau tanpa monitor.

Ada beberapa implementasi VNC diantaranya adalah UltraVNC, RealVNC, dan TightVNC.
Masing-masing memiliki fitur tersendiri yang dibangun diatas protokol VNC.

Untuk client VNC, ada beberapa yang sering digunakan yaitu Remmina, TigerVNC dan
RealVNC client. Bahkan kita bisa mengendalikan VNC melalui web browser dengan
Apache Guacamolle.

### Setup VNC Server di Ubuntu
Untuk kali ini, kita akan menggunakan tightvncserver untuk melakukan setup
VNC server pada Ubuntu 22.04

Install tightvnc server:
```bash
sudo apt install tightvncserver
```

Kemudian, jalankan perintah `vncserver` untuk membuat password akses VNC, membuat
file konfigurasi awal, dan memulai server VNC:

```bash
vncserver
```

Anda akan diminta untuk memasukkan password dan verifikasi password akses untuk
mengendalikan sistem operasi secara remote:

```bash
Output
You will require a password to access your desktops.

Password:
Verify:
```
>Password harus memiliki panjang 6-8 karakter. Password yang melebihi 8 character
akan otomatis di potong.

Setelah memverifikasi password, kita akan diberi pilihan untuk membuat view-only
password. Pengguna yang login dengan view-only password tidak dapat mengendalikan
VNC dengan keyboard dan mouse. Opsi ini berguna apabila anda ingin mendemonstrasikan
sesuatu ke orang lain menggunakan VNC server anda, tapi ini tidak diwajibkan.





