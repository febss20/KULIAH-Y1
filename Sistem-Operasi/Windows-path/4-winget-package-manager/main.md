# Package Manager

## Apa itu package/paket?
Source code dari sebuah perangkat lunak akan dikompilasi/dicompile
kedalam bentuk binary oleh pengembang. Baik source code maupun binary
akan dikemas dalam format tertentu oleh pengembang untuk di distribusikan.
Bentuk kemasan inilah yang disebut __Package/paket__.

## Apa itu repository?
Repository merupakan tempat untuk menyimpan paket agar bisa diakses secara remot.
Dalam kasus Windows sendiri adalah server milik Microsoft.

## Apa itu dependensi?
Contoh ketika anda tidak bisa menginstall software A sebelum menginstall .NET
Framework di Windows, maka .NET adalah dependensi untuk A. Hubungan ketergantungan
ini dinamakan dependensi(ketergantungan), dimana Paket A butuh paket B, paket B 
butuh paket C, dst, maka ini disebut dependensi.

## Apa itu Package Manager?
Package manager adalah perangkat lunak yang digunakan untuk menginstall dan
menghapus program dari sistem. Package Manager juga melakukan manajemen dependensi
untuk memastikan setiap program yang di install juga di install beserta dependensinya.

Beberapa contoh package manager untuk Windows adalah winget, chocholatey, dan
scoop. Bentuk dari package yang didownload bisa berupa .msi ataupun jenis file
kemasan yang lain yang didukung Windows.

## Praktikum
Dalam praktikum ini, akan digunakan winget sebagai package manager.
Winget sudah terinstall secara bawaan pada Windows 11 dan versi modern dari
Windows 10 sebagai bagian dari __App Installer__. Winget hanya mendukung
Windows 10 1709 (build 16299) keatas beserta Windows 11.

```powershell
# Mencari nama paket
winget search nano
# Menginstall paket
winget install GNU.Nano
# Menguninstall paket
winget uninstall GNU.Nano
# Mengupgrade paket yang terintall
winget upgrade GNU.Nano
```
