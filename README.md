#  TugasBesar_StrukturData

👥 **Anggota Kelompok:**
###### **Ida Sri Rahayu - 103052400069**
###### **Windi Pramudya Wardani - 103052400006**
###### **Ariel Furqanul Khaq - 103052300113**
---
**Kelas**: DS-48-02  
**Mata Kuliah**: Struktur Data  
**Dosen Pengampu**: Miftahul Adnan Rasyid  
**Tahun Akademik**: 2024/2025



#                                                                 🎵 Cotify - Aplikasi Pemutar Musik
## **Deskripsi Aplikasi**
**Cotify** adalah aplikasi music streaming berbasis console yang dikembangkan menggunakan bahasa pemrograman C++. Aplikasi ini memungkinkan pengguna untuk mengelola playlist musik pribadi, memutar lagu,melihat lagu favorit, dan mencari lagu berdasarkan berbagai kriteria. Cotify dirancang dengan struktur data linked list untuk manajemen user, lagu, dan playlist yang efisien. Aplikasi ini terinspirasi dari platform musik streaming populer seperti Spotify, dengan fitur-fitur yang disesuaikan untuk implementasi berbasis console yang user-friendly.

---

## Fitur-Fitur Utama
### Authentication System
- **Login Admin**: Akses penuh untuk manajemen sistem
- **Login User**: Akses personal untuk setiap pengguna
- **Register**: Pendaftaran akun baru

### Music Player
- **Quick Play**: Putar lagu langsung dari database
- **Playlist Player**: Putar lagu dari playlist yang tersimpan
- **Kontrol Pemutaran**:
  - Play/Pause
  - Next/Previous (untuk playlist)
  - Replay

### Playlist Management
- **Create Playlist**: Buat playlist baru
- **Edit Playlist**: Edit informasi playlist
- **Delete Playlist**: Hapus playlist
- **Add Songs**: Tambahkan lagu ke playlist
- **Remove Songs**: Hapus lagu dari playlist
- **Sort Playlist**: Urutkan berdasarkan ID atau Abjad (A-Z)
- **View Details**: Lihat detail lengkap playlist dan isinya

### Search & Discovery
- **Search by Title**: Cari lagu berdasarkan judul
- **Search by Artist**: Cari lagu berdasarkan nama artis
- **Search by Genre**: Cari lagu berdasarkan genre
- **Search by Album**: Cari lagu berdasarkan album
- **Search Playlist**: Cari playlist milik user
- **Search in Playlist**: Cari lagu dalam playlist tertentu

### Analytics
- **My Favorite Songs**: Lagu favorit personal berdasarkan play count
- **Play Count Tracking**: Setiap lagu mencatat berapa kali diputar

### Admin Features
- **User Management**:
  - View all users
  - View user details & playlists
  - Delete user
- **Music Database Management**:
  - View all songs
  - Add new song
  - Edit song info
  - Delete song
- **Analytics**: Statistik global platform

---

## 🗂️ Struktur Data
Aplikasi menggunakan **Linked List** dengan struktur:
1. **List_lagu** (Doubly Linked List)
   - Menyimpan database lagu dengan navigasi dua arah
2. **ListUser** (Single Linked List)
   - Menyimpan daftar user terdaftar
3. **List Playlist** (Single Linked List)
   - Setiap user memiliki list playlist sendiri
4. **List Playlist Items** (Single Linked List)
   - Setiap playlist berisi list lagu dengan play count

---
## Cara Menjalankan Program
### A. Menggunakan Code::Blocks
1. **Download/Clone Project**
   ```bash
   git clone <repository-url>
   cd cotify
   ```
2. **Buka Project**
   - Jalankan Code::Blocks
   - Klik `File` → `Open` → Pilih file `std2.cbp`
3. **Build Project**
   - Klik `Build` → `Build` (atau tekan `Ctrl + F9`)
   - Tunggu hingga kompilasi selesai
4. **Run Program**
   - Klik `Build` → `Run` (atau tekan `Ctrl + F10`)

### B. Menggunakan Command Line (Manual Compile)
**Windows (MinGW):**
```bash
g++ -o cotify main.cpp menu.cpp user.cpp lagu.cpp
cotify.exe
```
**Linux/Mac:**
```bash
g++ -o cotify main.cpp menu.cpp user.cpp lagu.cpp
./cotify
```
---
## Future Development
Fitur yang dapat dikembangkan di masa depan:
- [ ] File persistence (save/load data)
- [ ] Shuffle  mode
- [ ] Lyrics display
- [ ] Collaborative playlists

*"Music is life, and Cotify makes it better!"* 🎵
