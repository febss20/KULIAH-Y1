# Package Manager

## Apa itu package/paket? 
Source code dari sebuah perangkat lunak akan dikompilasi/dicompile kedalam bentuk 
binary oleh pengembang. Baik source code maupun binary akan dikemas dalam 
format tertentu oleh distribusi GNU/Linux untuk di distribusikan. 
Bentuk kemasan inilah yang disebut __Package/paket__.
Untuk format pendistribusiannya, bagi paket yang berisi source code biasanya
akan berformat .tar.gz, sedangkan untuk yang sudah berupa binary akan 
menggunakan format .deb untuk distribusi berbasis Debian dan Ubuntu.

## Apa itu repository?
Repository merupakan tempat untuk menyimpan paket yang bisa diakses secara remote.
Contoh repository untuk Ubuntu adalah:

- archive.ubuntu.com/ubuntu

## Apa itu mirror?
Mirror merupakan salinan dari repository utama. Mirror berguna apabila
repository utama terlalu jauh dari jangkauan internet pengguna. Dengan adanya
mirror, akan menambah kecepatan untuk mengunduh paket apabila lokasi mirror
berada dekat dengan pengguna. Contoh mirror ubuntu di Surabaya adalah:

- kartolo.sby.datautama.net.id/ubuntu
- buaya.klas.or.id/ubuntu

## Apa itu dependensi?
Contoh ketika anda tidak bisa menginstall software A sebelum menginstall .NET
Framework di Windows, maka .NET adalah dependensi untuk A. Hubungan ketergantungan
ini dinamakan dependensi(ketergantungan), dimana Paket A butuh paket B, paket B 
butuh paket C, dst, maka ini disebut dependensi.

## Apa itu Package Manager?
Package manager adalah perangkat lunak yang digunakan untuk menginstall dan
menghapus program dari sistem. Package Manager juga melakukan manajemen dependensi
untuk memastikan setiap program yang di install juga di install beserta dependensinya.

Beberapa contoh package manager yaitu APT untuk Ubuntu dan Debian based, pacman
untuk Arch base, portage untuk Gentoo, dan masih banyak lagi.
Dalam kasus Ubuntu dan Debian, APT bertugas mengunduh paket, sedangkan paket
yang diinstall dalam bentuk .deb.

## Praktikum
Dalam praktikum ini, akan digunakan APT sebagai package manager.

```bash
# Update list repository dari aplikasi yang terinstall di sistem
sudo apt update
# Install Update untuk aplikasi yang terinstall di sistem
sudo apt upgrade
# Upgrade system dan menghapus aplikasi/software versi lama bila diperlukan
sudo apt full-upgrade
# Menghapus dependency yang sudah tidak dibutuhkan oleh package manapun
sudo apt autoremove

# Studi kasus package fping
# Mencari software di repository
sudo apt search fping
# install software
sudo apt install fping
# Uninstall software
sudo apt remove fping
```
> ```sudo``` memberikan akses root ke user anda selama 15 menit agar anda bisa menjalankan perintah ```apt```

## Manage Mirror Repository
Dalam praktikum ini, kita akan mengganti repository Ubuntu dari default yaitu
UK ke repository Indonesia agar proses download berlangsung lebih cepat.

1. Jalankan aplikasi bernama "Software Updates" (software-properties-gtk)
1. Klik pilihan "Download from: " > klik Others.
1. Pilih Indonesia
1. Pilih Kartolo "kartolo.sby.datautama.net.id"
1. Tutup Software Updates
1. Biarkan sistem mengganti repository dengan milik kartolo

![Software Updates](https://nscdn.nstec.com/1661318581529.jpg)

Kita bisa menguji apakah repository sudah diganti dengan menjalankan perintah 
```bash
sudo apt update
```

hasil dari penggantian repository akan ditulis di /etc/apt/sources.list
```bash
cat /etc/apt/sources.list
```
