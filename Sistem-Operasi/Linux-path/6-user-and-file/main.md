# User and File Management

Pada satu sistem operasi bisa memiliki beberapa user/pengguna yang berbeda.
Masing-masing user bisa memiliki file dan aplikasi sendiri. Setiap user juga
dapat memilih file dan/atau aplikasi manakah yang boleh diakses oleh user lain,
baik itu akses read-only maupun full access.

## User Level
Ada beberapa jenis akun user berdasarkan penggunaan dan access level.

- Root User: Akses penuh ke sistem yang dapat mengubah setiap unsur dari sistem.
- Standard User: Akses pengguna terbatas, tidak mampu melakukan aksi yang 
mempengaruhi inti dari pengaturan sistem atau akun pengguna lain.
- Sudo User: Pengguna strandard yang telah diberikan izin untuk menjalankan
perintah tertentu sebagai root user
- System Account: Akun pengguna untuk aplikasi atau layanan otomasi yang butuh
menjalankan pekerjaan spesifik di sistem
- Guest User: Akun sementara dengan akses terbatas dan terkontrol
- User Groups: Izin di berikan ke sekumpulan pengguna yang di organisasikan ke
group logical.

### List User

```bash
cat /etc/passwd
```

### User Existance

Kita bisa membuat user baru dengan perintah dibawah ini:

```bash
sudo useradd newuser
# atau
sudo adduser newuser
# Untuk penambahan informasi user lebih detail

# Untuk menghapus user, gunakan
sudo userdel -r newuser
# ini akan menghapus user beserta home directory
```

### Modify Default user

`usermod` di Linux digunakan untuk memodifikasi atribut dari user yang ada.
* -d - Mengubah directory home dari pengguna
* -s - Mengubah default shell pengguna
* -e - Menetapkan tanggal kadaluarsa akun
* -c - Menambah komentar ke entry pengguna
* -u - Mengubah UID (User ID)
* -aG - Menambah group untuk pengguna yang ada

Di contoh berikut, flag `-d` digunakan untuk mengubah lokasi dari home
directory pengguna.

```bash
sudo usermod -d /var/newuser newuser
```

### Change user
`su` singkatan dari Switch User digunakan untuk berpindah ke user lain.
Apabila tidak didefinisikan, maka akan pindah ke user root.
```bash
su newuser
```

<!-- ### Group Permission -->
<!-- Memodifikasi group akan berefek pada semua user yang berada pada group tersebut. -->
<!---->
<!-- __Create Group__ -->
<!---->
<!-- ```bash -->
<!-- sudo groupadd test_group -->
<!-- # check group -->
<!-- getent group -->
<!-- ``` -->

## File Ownership and Permission
Setiap file dan directory di Linux punya tiga permission berikut untuk tiga jenis
pemilik:

__Permission for files__
* Read - Dapat melihat dan menyalin konten file
* Write - Dapat memodifikasi konten file
* Execute - Dapat menjalankan file (Apabila merupakan executable)

__Permission for directories__
* Read - Dapat melihat dan menyalin semua file dalam directory
* Write - Dapat menambah atau menghapus file dalam directory (Butuh izin Excute juga)
* Execute - Dapat masuk ke directory

Kita bisa mnggunakan perintah `stat` atau `ls` untuk mengetahui file permission.
Apabila kita menggunakan `ls -l` pada sebuah file, maka output akan seperti berikut:
```bash
-rwxrw-r-- 1 abhi itsfoss 457 Aug 10 11:55 agatha.txt
```

Bila digambarkan, maka seperti ini:
![filepermission](https://linuxhandbook.com/content/images/2020/06/file-permission-explanation-1-1.png)

* File type: Menunjukkan tipe file. d berarti directory, - berarti file biasa
* Permission: Bagian ini menunjukkan permission dari file
* Hard link count: Menunjukkan apabila file memiliki hard link, default dihitung satu.
* User: User pemilik file.
* Group: Group yang memiliki akses ke file ini. Hanya satu group yang bisa menjadi pemilik satu file pada satu waktu.
* File size: ukuran dari file dalam bytes
* Modification time: waktu dan tanggal terakhir kali file dimodifikasi
* Filename : nama file atau directory

Dalam perintah diatas, kita melihat file permission ini dalam format 9 digit.

rwxrw-r--

Setiap huruf mencerminkan permission tertentu:
* r : Read
* w : Write 
* x : Execute
* \- : Tidak di atur permission

Permission selalu diururtkan berdasarkan read, write dan execute, contoh: rwx.
Kemudian permission ini dikelompokkan ke tiga jenis pemilik dalam urutan User, Group, dan Other.

Ilutsrasi seperti dibawah ini:
![permission](https://linuxhandbook.com/content/images/2020/06/file-permission-explanation-2-1.png)

Credit to :
* [linuxhandbook](https://linuxhandbook.com/linux-file-permissions/)
* [phoenixap](https://phoenixnap.com/kb/user-management-linux)
