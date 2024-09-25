# Dasar Penggunaan PowerShell Windows
Pada dokumen ini, akan diberikan dasar-dasar penggunaan PowerShell.
Berinteraksi dengan console seringkali lebih cepat dibandingkan GUI.
Dengan console, kita juga bisa melakukan serangkaian perintah yang ideal untuk
otomasi.

## Definisi
Powershell merupakan program automasi dan manajemen konfigurasi dari Microsoft
yang terdiri dari command-line shell dan bahasa scripting. Pada awalnya
hanya merupakan komponen Windows yang dikenal dengan Windows PowerShell.
PowerShell kemudian di open-source dan dibuat cross-platform pada 18 Agustus 2016
dengan dikenalkannya PowerShell Core yang dibuat diatas .NET Framework.

PowerShell sudah di paketkan secara bawaan dengan Windows Versi 10 keatas
dan bisa di install di MacOS dan Linux. Sejak Windows 10 build 14971,
PowerShell menggantikan Command Prompt (cmd.exe) dan menjadi
command shell default untuk File Explorer.

Dalam PowerShell, pekerjaan administrative biasanya di lakukan melalui 
_cmdlets_ (dibaca _command-lets_) yang merupakan class .NET khusus diimplementasikan
untuk operasi tertentu. 

PowerShell mendukung .NET Remoting, WS-Management, CIM, dan SSH yang memungkinkan
administrator melaksanakan pekerjaan administratif baik di lokal maupun remot.

## Komponen PowerShell
Kita bisa membuka PowerShell dengan mencarinya di Start Menu. Kita bisa mengecek
detail tentang PowerShell kita dengan menjalankan perintah dibawah:

```powershell
$PSVersionTable
```

Output yang keluar sekiranya seperti ini:

```powershell
Name                           Value
----                           -----
PSVersion                      5.1.19041.2673
PSEdition                      Desktop
PSCompatibleVersions           {1.0, 2.0, 3.0, 4.0...}
BuildVersion                   10.0.19041.2673
CLRVersion                     4.0.30319.42000
WSManStackVersion              3.0
PSRemotingProtocolVersion      2.3
SerializationVersion           1.1.0.1
```

Output berisi informasi tentang versi PowerShell, dan platform serta edisi. 
Untuk hanya menampilkan versi PowerShell, kita bisa menjalankan versi modifikasi
dari `$PSVersionTable`

```powershell
$PSVersionTable.PSVersion
```

Output yang keluar sekiranya seperti ini:

```powershell
Major  Minor  Build  Revision
-----  -----  -----  --------
5      1      19041  2673
```

Menjalankan `$PSVersionTable` menghasilkan output yang berupa tabel, tapi
sesungguhnya merupakan sebuah objek. Untuk alasan ini, kita bisa menggunakan
titik (.) untuk mengakses properti spesifik sepeteri `PSVersion`.

### Navigasi
Di bagian ini, kita akan belajar mengenai navigasi directory.
|cmd-lets|Fungsi|
|--------|------|
Get-ChildItem | Menampilkan isi dari directory tempat kita berada
Set-Location | Mengganti directory tempat kita bekerja
Get-Location | Menampilkan directory tempat kita bekerja
New-Item -ItemType Directory -Name "Folder" | Membuat directory bernama "Folder"
Remove-Item | menghapus item
Remove-Item "Directory" -Recurse | Menghapus directory beserta isinya
Copy-Item | Menyalin item
Copy-Item "Directory" "C:\Destination" -Recurse | Menyalin directory beserta isinya ke lokasi lain

Kita sebenarnya bisa menggunakan perintah yang sama seperti UNIX / UNIX-like system
seperti cd, ls, pwd. Ini dapat dilakukan karena PowerShell memiliki Alias
atau nama lain dari cmd-lets yang sudah ada. Daftar alias ini dapat kita akses
menggunakan
```powershell
Get-Alias
```

### Redirection
Redirection merupakan metode untuk mengalihkan standard output ke tujuan lain
|Perintah | Fungsi|
|---------|-------|
Get-Content |  Menampilkan isi dari berkas |
Write-Output | Menampilkan text ke console|

Contoh:
```powershell
Write-Output "Hallo" > test.txt 
#Menulis "Hallo" ke file test.txt
Write-Output "Anda" >> test.txt 
#Menulis "Anda" di baris baru ke file test.txt
Write-Output "Pagi" > test.txt 
#Menulis "Anda" ke file test.txt dengan mengapus semua isi file test.txt sebelumnya
Get-Content test.txt
#Menampilkan isi dari test.txt
```

### Pipes
Pipe adalah salah satu bentuk ridirection, Pipe dilambangkan dengan karakter '|' tegak lurus

Contoh:
```powershell
Get-Process | Where-Object {$_.WorkingSet -gt 100MB}
```
`Get-Process` akan menampilkan informasi tentang proses yang berjalan.

`Where-Object` (memiliki alias `Where`) akan menyaring output dari `Get-Process`
berdasarkan kondisi. Dalam kasus ini, menyaring proses dimana working set size
lebih dari 100MB

