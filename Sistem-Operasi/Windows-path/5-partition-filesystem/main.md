# Partition dan Filesystem

## Partition
Partition/partisi merupakan metode pembagian media penyimpanan fisik sekunder menjadi bagian-bagian
individu yang terpisah dan terisolasi secara virtual. Sebagai contoh, satu
HDD atau SSD bisa dipotong menjadi beberapa bagian secara virtual untuk
memudahkan mengorganisir file atau berkas yang didalamnya.

Dalam satu media penyimpanan fisik bisa digunakan untuk satu atau lebih 
partisi. Berapa jumlah maksimum partisi dalam satu perangkat fisik ditentukan
oleh media penyimpanan itu sendiri.

## FIlesystem
Filesystem merupakan kemampuan dari sistem operasi untuk melayani aplikasi di 
komputer yang sama. Filesystem menyediakan layanan penyimpanan data yang 
memungkinkan aplikasi untuk berbagi penyimpanan. Tanpa filesystem, aplikasi 
dapat mengakses penyimpanan dengan cara yang tidak kompatibel yang mengakibatkan
kerusakan atau kehilangan data.

> Singkatnya, filesystem merupakan metode sistem operasi dalam menyimpan data
> pada media penyipaman.

Ada beberapa jenis filesystem yang didukung oleh sistem operasi Windows, yaitu:

* NTFS
* FAT
* FAT32
* ExFAT

Masing-masing memiliki fitur tersendiri, silahkan dicari sendiri di Wikipedia.


## Praktikum Partisi
Dalam praktikum ini, kita akan membuat partisi baru dari sebuah disk kosong
menggunakan PowerShell. Pastikan PowerShell dijalankan sebagai Administrator
agar bisa melakukan operasi ini.

### Identifikasi Disk
lihat daftar Disk yang tersedia. Disk yang baru ditambahkan akan memiliki
DiskNumber yang tinggi. Pada kasus ini, disk utama saya "0" dan disk baru "1".
```powershell
Get-Disk

#output:

Number Friendly Name Serial Number                    HealthStatus         OperationalStatus      Total Size Partition

------ ------------- -------------                    ------------         -----------------      ---------- ----------
0      VBOX HARDDISK VB9316db7d-211fe828              Healthy              Online                      60 GB GPT
1      VBOX HARDDISK VB8369aa9a-26a3e4a2              Healthy              Online                       5 GB RAW
```

### Inisialisasi Disk
Sebelum di partisi, kita akan menginisialisasi disk terlebih dahulu agar bisa
dilakukan operasi pada disk tersebut.
```powershell
Initialize-Disk -Number 1 -PartitionStyle GPT
```
Kita menggunakan gaya partisi GPT untuk kompatibilitas dengan sistem terbaru.

### Membuat Partisi utuh
Kita akan langsung mengubah satu disk fisik menjadi 1 partisi.
```powershell
New-Partition -DiskNumber 1 -UseMaximumSize

# Output:
   DiskPath: \\?\scsi#disk&ven_vbox&prod_harddisk#4&2617aeae&0&020000#{53f56307-b6bf-11d0-94f2-00a0c91efb8b}

PartitionNumber  DriveLetter Offset                                        Size Type
---------------  ----------- ------                                        ---- ----
2                           16777216                                   4.98 GB Basic

```

### Mounting disk ke Drive letter
Untuk melakukan operasi lebih lanjut, kita harus memberi label pada disk yang sudah kita partisi.
Pertama adalah mengidentifikasi nomor partisi dari disk kita.
```powershell
Get-Partition -DiskNumber 1

# Output:
   DiskPath: \\?\scsi#disk&ven_vbox&prod_harddisk#4&2617aeae&0&020000#{53f56307-b6bf-11d0-94f2-00a0c91efb8b}

PartitionNumber  DriveLetter Offset                                        Size Type
---------------  ----------- ------                                        ---- ----
1                           17408                                     15.98 MB Reserved
2                           16777216                                   4.98 GB Basic

```

Kita akan memilih PartitionNumber 2 karena itulah partisi yang kita buat.
Kita tidak menggunakan PartitionNumber 1 karena partisi tersebut merupakan padding untuk tabel GPT.

```powershell
Add-PartitionAccessPath -DiskNumber 1 -PartitionNumber 2 -AccessPath "G:\"

```

### Format Partisi ke NTFS
Kita akan menggunakan NTFS sebagai filesystem yang umum digunakan di Windows untuk
secondary mass storage.

```powershell
Format-Volume -DriveLetter G -FileSystem NTFS

# Output:

DriveLetter FriendlyName FileSystemType DriveType HealthStatus OperationalStatus SizeRemaining    Size
----------- ------------ -------------- --------- ------------ ----------------- -------------    ----
G                        NTFS           Fixed     Healthy      OK                      4.96 GB 4.98 GB

```
