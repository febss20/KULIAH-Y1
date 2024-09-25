# User and File Management

Pada satu sistem operasi bisa memiliki beberapa user/pengguna yang berbeda.
Masing-masing user bisa memiliki file dan aplikasi sendiri. Setiap user juga
dapat memilih file dan/atau aplikasi manakah yang boleh diakses oleh user lain,
baik itu akses read-only maupun full access.

## User
Untuk menambahkan user baru pada Windows menggunakan PowerShell, gunakan
perintah berikut:
```powershell
New-LocalUser -Name "NewUser" -Password (ConvertTo-SecureString "YourPassword" -AsPlainText -Force) -FullName "Full Name of User" -Description "Description of User"
```
"NewUser" diganti dengan nama user baru.
"YourPassword" masukkan password anda.
"Full Name of User" Masukkan nama lengkap untuk user anda.
"Description of User" Masukkan deskripsi untuk user anda.

Dengan ini anda telah membuat user baru di Windows.

Untuk menghapus user, gunakan perintah dibawah ini:

```powershell
Remove-LocalUser -Name "Username"
```
Masukkan username yang akan dihapus

Untuk melihat daftar user, gunakan perintah berikut:

```powershell
Get-LocalUser

# Output

Name               Enabled Description
----               ------- -----------
Administrator      False   Built-in account for administering the computer/domain
DefaultAccount     False   A user account managed by the system.
Guest              False   Built-in account for guest access to the computer/domain
maulana            True    UserTesting
rizqirazkafi       True
sshd               True
WDAGUtilityAccount False   A user account managed and used by the system for Windows Defender Application Guard scenarios.
```

## File Management

Apabila kita ingin membagikan file kita ke user lain, kita bisa menggunakan
Access Control List (ACL).

Pertama, kita harus mengetahui file apa yang ingin kita bagikan dengan
memberi variabel untuk memudahkannya. Kemudian kita menampilkan ACL dari
file tersebut yang dimana perintah tersebut juga bisa kita masukkan ke variable.

Setelah itu, kita terapkan method Access untuk menampilkan list keseluruhan.
List keseluruhan tersebut kita Pipes kedalam bentuk tabel.
```powershell
$filePath = "C:\Path\To\Yout\File.txt"
$acl = Get-Acl $filePath
$acl.Access | Format-Table -AutoSize

FileSystemRights AccessControlType IdentityReference            IsInherited InheritanceFlags PropagationFlags
---------------- ----------------- -----------------            ----------- ---------------- ----------------
     FullControl             Allow NT AUTHORITY\SYSTEM                 True             None             None
     FullControl             Allow BUILTIN\Administrators              True             None             None
     FullControl             Allow DESKTOP-JOVTJC9\rizqirazkafi        True             None             None
```

Mengatur permission:

```powershell
$filePath = "C:\Path\To\Yout\File.txt"
$rule = New-Object System.Security.AccessControl.FileSystemAccessRule("UserName", "FullControl", "Allow")
$acl = Get-Acl $filePath
$acl.SetAccessRule($rule)
Set-Acl -Path $filePath -AclObject $acl
```

Pada bagian $rule, ada 3 permission yang bisa kita terapkan, yaitu "FullControl".
"Modify","Read",berdasarkan kebutuhan.

__FullControl__ akan memberikan akses untuk membaca, menulis, menjalankan, dan menghapus file.
Ini juga memberi user hak untuk memodifikasi hak akses dari file tersebut.

__Modify__ akan memberikan akses untuk membaca, menjalankan, menulis, dan menghapus file,
namun user tidak bisa mengubah hak akses dari file tersebut.

__Read__ hanya memberikan akses untuk membaca isi dari file tersebut.

