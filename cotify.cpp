#include "cotify.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

void printLine(char c = '=', int length = 80);

// ========== USER  ==========
void createListUser(ListUser &L){
    L.first = NULL;
}

adrUser alokasiUser(infoUser x){
    adrUser P = new elmUser;
    P->info = x;
    P->next = NULL;
    P->firstPlaylist = NULL;
    return P;
}

void insertLastUser(ListUser &L, adrUser P){
    if(L.first == NULL){
        L.first = P;
    }else{
        adrUser Q = L.first;
        while(Q->next != NULL){
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrUser findUser(ListUser L, string username){
    adrUser P = L.first;
    while(P != NULL){
        if(P->info.username == username){
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void deleteUser(ListUser &L, adrUser &P){
    if(P == NULL) return;
    adrPlaylist PL = P->firstPlaylist;

    while(PL != NULL){
        adrPlaylist temp = PL;
        PL = PL->next;
        adrItem IT = temp->firstItem;

        while(IT != NULL){
            adrItem tempIT = IT;
            IT = IT->next;
            delete tempIT;
        }
        delete temp;
    }
    if(P == L.first){
        L.first = P->next;
    }else{
        adrUser Q = L.first;
        while(Q->next != P){
            Q = Q->next;
        }
        Q->next = P->next;
    }
    delete P;
}

void printAllUsers(ListUser L){
    adrUser P = L.first;
    if(P == NULL){
        cout << "\n  User tersebut belum terdaftar\n" << endl;
        return;
    }

    cout << "\n";
    printLine('=', 80);
    cout << left << setw(15) << "  Username"
         << setw(25) << "Nama"
         << setw(30) << "Email"
         << "Playlists" << endl;
    printLine('-', 80);

    while(P != NULL){
        cout << "  " << left << setw(13) << P->info.username
             << setw(25) << P->info.nama_lengkap
             << setw(30) << P->info.email
             << hitungPlaylist(P) << endl;
        P = P->next;
    }
    printLine('=', 80);
}

void showUser(adrUser P){
    cout << "  Username       : " << P->info.username << endl;
    cout << "  Nama Lengkap   : " << P->info.nama_lengkap << endl;
    cout << "  Email          : " << P->info.email << endl;
    cout << "  Negara         : " << P->info.negara << endl;
    cout << "  Tahun          : " << P->info.umur << endl;
    cout << "  Total Playlist : " << hitungPlaylist(P) << endl;
}

adrUser inputUser(){
    infoUser x;
    cin.ignore();
    cout << "  Username: ";
    getline(cin, x.username);
    cout << "  Nama Lengkap: ";
    getline(cin, x.nama_lengkap);
    cout << "  Email: ";
    getline(cin, x.email);
    cout << "  Negara: ";
    getline(cin, x.negara);
    cout << "  Umur: ";
    cin >> x.umur;
    return alokasiUser(x);
}

void editUser(adrUser &P){
    cout << "  Username: " << P->info.username << " (cannot be changed)" << endl;
    cout << "  Nama Lengkap: ";
    cin.ignore();
    getline(cin, P->info.nama_lengkap);
    cout << "  Email: ";
    getline(cin, P->info.email);
    cout << "  Negara: ";
    getline(cin, P->info.negara);
    cout << "  Tahun: ";
    cin >> P->info.umur;
}

int hitungUser(ListUser L){
    int count = 0;
    adrUser P = L.first;
    while(P != NULL){
        count++;
        P = P->next;
    }
    return count;
}

void dataUser(ListUser &L){
    infoUser u;
    adrUser P;

    u.username = "windi";
    u.nama_lengkap = "Windi Pramudya W.";
    u.email = "windi@email.com";
    u.negara = "USA";
    u.umur = 25;
    P = alokasiUser(u);
    insertLastUser(L, P);

    u.username = "ariel";
    u.nama_lengkap = "Ariel Furqanul K.";
    u.email = "ariel@email.com";
    u.negara = "UK";
    u.umur = 28;
    P = alokasiUser(u);
    insertLastUser(L, P);

    u.username = "ida";
    u.nama_lengkap = "Ida Sri Rahayu";
    u.email = "idasrr@email.com";
    u.negara = "Australia";
    u.umur = 30;
    P = alokasiUser(u);
    insertLastUser(L, P);
}

// ========== PLAYLIST FUNCTIONS ==========
adrPlaylist alokasiPlaylist(infoPlaylist x){
    adrPlaylist P = new elmPlaylist;
    P->info = x;
    P->next = NULL;
    P->firstItem = NULL;
    return P;
}

void insertLastPlaylist(adrUser U, adrPlaylist P){
    if(U->firstPlaylist == NULL){
        U->firstPlaylist = P;
    }else{
        adrPlaylist Q = U->firstPlaylist;
        while(Q->next != NULL){
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrPlaylist findPlaylist(adrUser U, string nama){
    adrPlaylist P = U->firstPlaylist;
    while(P != NULL){
        if(P->info.nama == nama){
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void deletePlaylist(adrUser &U, adrPlaylist &P){
    if(P == NULL) return;

    adrItem IT = P->firstItem;
    while(IT != NULL){
        adrItem temp = IT;
        IT = IT->next;
        delete temp;
    }

    if(P == U->firstPlaylist){
        U->firstPlaylist = P->next;
    }else{
        adrPlaylist Q = U->firstPlaylist;
        while(Q->next != P){
            Q = Q->next;
        }
        Q->next = P->next;
    }
    delete P;
}

void printAllPlaylists(adrUser U){
    adrPlaylist P = U->firstPlaylist;
    if(P == NULL){
        cout << "\n  Belum ada playlist yang dibuat\n" << endl;
        return;
    }

    int no = 1;
    while(P != NULL){
        cout << "  " << no++ << ". " << left << setw(30) << P->info.nama
             << " | " << getTotalLaguInPlaylist(P) << " Lagu | "
             << getTotalPlayCount(P) << "x pemutaran\n";
        cout << "     " << P->info.deskripsi << "\n\n";
        P = P->next;
    }
}

void showPlaylist(adrPlaylist P){
    cout << "  Nama Playlist      : " << P->info.nama << endl;
    cout << "  Tanggal Pembuatan  : " << P->info.tanggal_dibuat << endl;
    cout << "  Total Lagu         : " << getTotalLaguInPlaylist(P) << endl;
    cout << "  Total Dimainkan    : " << getTotalPlayCount(P) << "x" << endl;
    cout << "  Total Durasi       : " << formatDurasi(getTotalDurasiPlaylist(P)) << endl;
}

adrPlaylist inputPlaylist(adrUser U){
    infoPlaylist x;
    static int counter = 1;
    x.id = counter++;
    cin.ignore();
    cout << "  Nama Playlist: ";
    getline(cin, x.nama);
    cout << "  Date (DD/MM/YYYY): ";
    getline(cin, x.tanggal_dibuat);
    return alokasiPlaylist(x);
}

void editPlaylist(adrPlaylist &P){
    cout << "  Nama Playlist: ";
    cin.ignore();
    getline(cin, P->info.nama);
}

int hitungPlaylist(adrUser U){
    int count = 0;
    adrPlaylist P = U->firstPlaylist;
    while(P != NULL){
        count++;
        P = P->next;
    }
    return count;
}

int getTotalLaguInPlaylist(adrPlaylist P){
    int count = 0;
    adrItem IT = P->firstItem;
    while(IT != NULL){
        count++;
        IT = IT->next;
    }
    return count;
}

int getTotalDurasiPlaylist(adrPlaylist P){
    int total = 0;
    adrItem IT = P->firstItem;
    while(IT != NULL){
        total += IT->lagu->info.durasi;
        IT = IT->next;
    }
    return total;
}

// ========== PLAYLIST ITEM FUNCTIONS ==========
adrItem alokasiItem(address_lagu L){
    adrItem P = new elmPlaylistItem;
    P->lagu = L;
    P->play_count = 0;
    P->tanggal_ditambah = "29/11/2024";
    P->next = NULL;
    return P;
}

void insertLastItem(adrPlaylist PL, adrItem P){
    if(PL->firstItem == NULL){
        PL->firstItem = P;
    }else{
        adrItem Q = PL->firstItem;
        while(Q->next != NULL){
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrItem findItem(adrPlaylist PL, address_lagu L){
    adrItem P = PL->firstItem;
    while(P != NULL){
        if(P->lagu == L){
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void deleteItem(adrPlaylist &PL, adrItem &P){
    if(P == NULL) return;

    if(P == PL->firstItem){
        PL->firstItem = P->next;
    }else{
        adrItem Q = PL->firstItem;
        while(Q->next != P){
            Q = Q->next;
        }
        Q->next = P->next;
    }
    delete P;
}

void printIsiPlaylist(adrPlaylist PL){
    adrItem P = PL->firstItem;
    if(P == NULL){
        cout << "\n  Playlist kosong!\n" << endl;
        return;
    }

    cout << "\n";
    printLine('-', 80);
    cout << "  Total: " << getTotalLaguInPlaylist(PL) << " lagu | "
         << formatDurasi(getTotalDurasiPlaylist(PL)) << " | "
         << getTotalPlayCount(PL) << "x dimainkan" << endl;
    printLine('-', 80);

    int no = 1;
    while(P != NULL){
        cout << "  " << no++ << ". " << left << setw(30) << P->lagu->info.judul
             << " - " << setw(20) << P->lagu->info.artis
             << " [" << setw(10) << P->lagu->info.genre << "]"
             << " (" << formatDurasi(P->lagu->info.durasi) << ")"
             << " | " << P->play_count << "x\n";
        P = P->next;
    }
    printLine('-', 80);
}

void playLagu(adrPlaylist PL, address_lagu L){
    adrItem P = findItem(PL, L);
    if(P != NULL){
        P->play_count++;
        cout << "\n>>> NOW PLAYING: " << L->info.judul
             << " - " << L->info.artis << " <<<" << endl;
        cout << "Play count: " << P->play_count << "x" << endl;
    }
}

adrItem getCurrentItem(adrPlaylist PL, address_lagu L){
    return findItem(PL, L);
}

int getTotalPlayCount(adrPlaylist PL){
    int total = 0;
    adrItem P = PL->firstItem;
    while(P != NULL){
        total += P->play_count;
        P = P->next;
    }
    return total;
}

address_lagu getLaguTerpopulerDiPlaylist(adrPlaylist PL){
    if(PL->firstItem == NULL) return NULL;

    adrItem P = PL->firstItem;
    adrItem max = P;

    while(P != NULL){
        if(P->play_count > max->play_count){
            max = P;
        }
        P = P->next;
    }
    return max->lagu;
}

// ========== HELPER FUNCTIONS ==========
void tambahLaguKePlaylist(adrUser U, adrPlaylist PL, address_lagu L){
    adrItem cek = findItem(PL, L);
    if(cek != NULL){
        cout << "\n  [ERROR] Lagu sudah ada di playlist!" << endl;
        return;
    }

    adrItem P = alokasiItem(L);
    insertLastItem(PL, P);
    cout << "\n  [SUCCESS] Lagu berhasil ditambahkan ke playlist!" << endl;
}

void hapusLaguDariPlaylist(adrPlaylist PL, address_lagu L){
    adrItem P = findItem(PL, L);
    if(P == NULL){
        cout << "\n  [ERROR] Lagu tidak ada di playlist!" << endl;
        return;
    }

    deleteItem(PL, P);
    cout << "\n  [SUCCESS] Lagu berhasil dihapus dari playlist!" << endl;
}


string formatDurasi(int detik){
    int menit = detik / 60;
    int sisa = detik % 60;
    string hasil = to_string(menit) + ":";
    if(sisa < 10) hasil += "0";
    hasil += to_string(sisa);
    return hasil;
}

void createList_lagu(List_lagu &L){
    L.first = NULL;
    L.last = NULL;
}

address_lagu alokasi_lagu(lagu x){
    address_lagu P = new elmList_lagu;
    P->info = x;
    P->next = NULL;
    P->prev = NULL;
    return P;
}

void insertLast_lagu(List_lagu &L, address_lagu P){
    if(L.first == NULL){
        L.first = P;
        L.last = P;
    }
    else{
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
}

address_lagu findElm_lagu(List_lagu L, string judul){
    address_lagu P = L.first;
    while(P != NULL){
        if(P->info.judul == judul){
            return P;
        }
        P = P->next;
    }
    return NULL;
}

address_lagu findLaguByID(List_lagu L, int id){
    address_lagu P = L.first;
    while(P != NULL){
        if(P->info.id_lagu == id){
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void deleteSearch_lagu(List_lagu &L, address_lagu &P){
    if(P == NULL) return;

    if(P == L.first && P == L.last){
        L.first = NULL;
        L.last = NULL;
    }
    else if(P == L.first){
        L.first = P->next;
        L.first->prev = NULL;
    }
    else if(P == L.last){
        L.last = P->prev;
        L.last->next = NULL;
    }
    else{
        P->prev->next = P->next;
        P->next->prev = P->prev;
    }
}

void showLagu(address_lagu P){
    cout << "  ID     : " << P->info.id_lagu << endl;
    cout << "  Judul  : " << P->info.judul << endl;
    cout << "  Artist : " << P->info.artis << endl;
    cout << "  Album  : " << P->info.album << endl;
    cout << "  Genre  : " << P->info.genre << endl;
    cout << "  Durasi : " << formatDurasi(P->info.durasi) << endl;
    cout << "  Tahun  : " << P->info.tahun << endl;
}

void printInfo_lagu(List_lagu L){
    address_lagu P = L.first;
    if(P == NULL){
        cout << "\n  Tidak ada lagu di database\n" << endl;
        return;
    }

    system("cls");
    printLine('=', 80);
    cout << "|";
    printSpaces(28);
    cout << "SONGS DATABASE";
    printSpaces(37);
    cout << "|" << endl;
    printLine('=', 80);

    cout << "  ";
    printWithWidth("ID", 5);
    printWithWidth("Judul", 28);
    printWithWidth("Artis", 20);
    printWithWidth("Genre", 12);
    printWithWidth("Durasi", 8);
    cout << "Tahun" << endl;
    printLine('-', 80);

    while(P != NULL){
        string title = P->info.judul;
        if(title.length() > 26) title = title.substr(0, 23) + "...";

        string artist = P->info.artis;
        if(artist.length() > 18) artist = artist.substr(0, 15) + "...";

        cout << "  ";
        cout << P->info.id_lagu;
        printSpaces(5 - to_string(P->info.id_lagu).length());
        printWithWidth(title, 28);
        printWithWidth(artist, 20);
        printWithWidth(P->info.genre, 12);
        printWithWidth(formatDurasi(P->info.durasi), 8);
        cout << P->info.tahun << endl;
        P = P->next;
    }

    printLine('=', 80);
}

void editInfo_lagu(address_lagu &P){
    cout << "  ID: ";
    cin >> P->info.id_lagu;
    cout << "  Judul: ";
    cin.ignore();
    getline(cin, P->info.judul);
    cout << "  Artist: ";
    getline(cin, P->info.artis);
    cout << "  Album: ";
    getline(cin, P->info.album);
    cout << "  Genre: ";
    getline(cin, P->info.genre);
    cout << "  Durasi (detik): ";
    cin >> P->info.durasi;
    cout << "  Tahun: ";
    cin >> P->info.tahun;
}

address_lagu input_lagu(){
    lagu x;
    static int counter = 101;
    x.id_lagu = counter++;
    cin.ignore();
    cout << "  ID: " << x.id_lagu << " (Auto)" << endl;
    cout << "  Judul: ";
    getline(cin, x.judul);
    cout << "  Artist: ";
    getline(cin, x.artis);
    cout << "  Album: ";
    getline(cin, x.album);
    cout << "  Genre: ";
    getline(cin, x.genre);
    cout << "  Durasi (detik): ";
    cin >> x.durasi;
    cout << "  Tahun: ";
    cin >> x.tahun;
    return alokasi_lagu(x);
}

int hitungLagu(List_lagu L){
    int count = 0;
    address_lagu P = L.first;
    while(P != NULL){
        count++;
        P = P->next;
    }
    return count;
}

void insert_new_song(List_lagu &L, int id, const string& judul, const string& artis, const string& album, const string& genre, int durasi, int tahun) {
    lagu lg;
    lg.id_lagu = id;
    lg.judul = judul;
    lg.artis = artis;
    lg.album = album;
    lg.genre = genre;
    lg.durasi = durasi;
    lg.tahun = tahun;

    address_lagu P = alokasi_lagu(lg);
    insertLast_lagu(L, P);
}

void data_lagu(List_lagu &L) {
    insert_new_song(L, 1, "Bohemian Rhapsody", "Queen", "A Night at Opera", "Rock", 354, 1975);
    insert_new_song(L, 2, "Shape of You", "Ed Sheeran", "Divide", "Pop", 233, 2017);
    insert_new_song(L, 3, "Blinding Lights", "The Weeknd", "After Hours", "Synthwave", 200, 2019);
    insert_new_song(L, 4, "Starboy", "The Weeknd", "Starboy", "R&B", 230, 2016);
    insert_new_song(L, 5, "Someone Like You", "Adele", "21", "Pop", 285, 2011);
    insert_new_song(L, 6, "Bad Guy", "Billie Eilish", "When We All Fall", "Pop", 194, 2019);
    insert_new_song(L, 7, "Levitating", "Dua Lipa", "Future Nostalgia", "Pop", 203, 2020);
    insert_new_song(L, 8, "Stay", "Justin Bieber", "Justice", "Pop", 141, 2021);
    insert_new_song(L, 9, "As It Was", "Harry Styles", "Harry's House", "Pop", 167, 2022);
    insert_new_song(L, 10, "Anti-Hero", "Taylor Swift", "Midnights", "Pop", 200, 2022);
}

const string ADMIN_USER = "admin";
const string ADMIN_PASS = "admin123";

struct NowPlaying {
    bool isPlaying;
    string judul;
    string artis;
    string playlist;
    bool isPaused;
} nowPlaying = {false, "", "", "", false};

// ========== HELPER FUNCTIONS ==========
string toLowerString(string str){
    string result = str;
    size_t i = 0;
    while(i < result.length()){
        if(result[i] >= 'A' && result[i] <= 'Z'){
            result[i] = result[i] + 32;
        }
        i++;
    }
    return result;
}

void printSpaces(int count){
    int i = 0;
    while(i < count){
        cout << " ";
        i++;
    }
}

void printLine(char c, int length){
    int i = 0;
    while(i < length){
        cout << c;
        i++;
    }
    cout << endl;
}

void printWithWidth(string text, int width){
    cout << text;
    int spaces = width - text.length();
    if(spaces > 0){
        printSpaces(spaces);
    }
}

void printBox(string text, int width){
    int padding = (width - text.length() - 2) / 2;
    cout << "|";
    printSpaces(padding);
    cout << text;
    printSpaces(width - text.length() - padding - 2);
    cout << "|" << endl;
}

// ========== PLAYING BAR  ==========
void showNowPlayingBar(){
    if(nowPlaying.isPlaying){
        cout << "\n";
        printLine('=', 80);
        cout << "| ";
        if(nowPlaying.isPaused) cout << "[||] ";
        else cout << "[>] ";

        string info = nowPlaying.judul + " - " + nowPlaying.artis;
        if(!nowPlaying.playlist.empty()){
            info += " [" + nowPlaying.playlist + "]";
        }

        if(info.length() > 70) info = info.substr(0, 67) + "...";
        cout << info;

        int spaces = 73 - (int)info.length();
        printSpaces(spaces);
        cout << " |" << endl;
        printLine('=', 80);
    }
}

// ========== AUTHENTICATION ==========
void tampilkanHeader(){
    printLine('=', 80);
    printBox("C O T I F Y", 80);
    printBox("Aplikasi Pemutar Musik", 80);
    printLine('=', 80);
}

bool login(CurrentUser &current, ListUser LU){
    string username, password;
    int pilihan;

    system("cls");
    tampilkanHeader();
    cout << "|  [1] Login sebagai Admin                                                     |\n";
    cout << "|  [2] Login sebagai User                                                      |\n";
    cout << "|  [3] Buat Akun Baru                                                          |\n";
    cout << "|  [0] Keluar Aplikasi                                                         |\n";
    printLine('-', 80);
    cout << "\n  >> Masukkan Pilihan: ";
    cin >> pilihan;

    if(pilihan == 0) return false;

    system("cls");
    tampilkanHeader();

    if(pilihan == 1){
        cout << "\n";
        printBox("ADMIN LOGIN", 80);
        printLine('-', 80);
        cout << "  Username: ";
        cin >> username;
        cout << "  Password: ";
        cin >> password;

        if(username == ADMIN_USER && password == ADMIN_PASS){
            current.username = username;
            current.role = "admin";
            current.isLoggedIn = true;
            printLine('-', 80);
            cout << "\n  [SUCCESS] Selmat Datang Admin!\n";
            system("pause");
            return true;
        }
        cout << "\n  [ERROR] Username atau password salah!\n";
        printLine('=', 80);
        system("pause");
        return false;
    }
    else if(pilihan == 2){
        cout << "\n";
        printBox("USER LOGIN", 80);
        printLine('-', 80);

        adrUser temp = LU.first;
        cout << "\n  User yang tersedia:\n";
        cout << "  ";
        printLine('-', 76);
        int count = 1;
        while(temp != NULL){
            cout << "  " << count++ << ". " << temp->info.username
                 << " (" << temp->info.nama_lengkap << ")\n";
            temp = temp->next;
        }
        cout << "  ";
        printLine('-', 76);

        cout << "\n  Masukkan username: ";
        cin >> username;

        adrUser U = findUser(LU, username);
        if(U != NULL){
            current.username = username;
            current.role = "user";
            current.isLoggedIn = true;
            cout << "\n  [SUCCESS] Selamat datang " << U->info.nama_lengkap << "!\n";
            printLine('=', 80);
            system("pause");
            return true;
        }
        cout << "\n  [ERROR] User tidak ditemukan!\n";
        printLine('=', 80);
        system("pause");
        return false;
    }
    else if(pilihan == 3){
        adrUser U = inputUser();
        insertLastUser(LU, U);
        cout << "\n  [SUCCESS] Akun berhasil dibuat! Username: " << U->info.username << "\n";
        printLine('=', 80);
        system("pause");
        return login(current, LU);
    }

    cout << "\n  [ERROR] Invalid option!\n";
    printLine('=', 80);
    system("pause");
    return false;
}

void logout(CurrentUser &current){
    current.username = "";
    current.role = "";
    current.isLoggedIn = false;
    nowPlaying.isPlaying = false;
}

// ========== QUICK PLAY FEATURE ==========
void quickPlay(List_lagu LL){
    printInfo_lagu(LL);

    int idLagu;
    cout << "\n  Masukkan ID lagu (0 to cancel): ";
    cin >> idLagu;

    if(idLagu == 0) return;

    address_lagu L = findLaguByID(LL, idLagu);
    if(L == NULL){
        cout << "\n  [ERROR] Lagu tidak ditemukan!\n";
        system("pause");
        return;
    }

    char pilihan = ' ';

    nowPlaying.isPlaying = true;
    nowPlaying.judul = L->info.judul;
    nowPlaying.artis = L->info.artis;
    nowPlaying.playlist = "Quick Play";
    nowPlaying.isPaused = false;

    bool playing = true;
    while(playing){
        system("cls");
        printLine('=', 80);
        printBox("Q U I C K   P L A Y", 80);
        printLine('=', 80);

        cout << "\n";
        printLine('-', 80);
        if(nowPlaying.isPaused){
            cout << "|  STATUS: [PAUSED]";
            printSpaces(61);
            cout << "|\n";
        } else {
            cout << "|  STATUS: [PLAYING]";
            printSpaces(60);
            cout << "|\n";
        }
        printLine('-', 80);
        cout << "|  Judul: " << L->info.judul;
        printSpaces(70 - L->info.judul.length());
        cout << "|\n";
        cout << "|  Artist: " << L->info.artis;
        printSpaces(69 - L->info.artis.length());
        cout << "|\n";
        cout << "|  Album: " << L->info.album;
        printSpaces(70 - L->info.album.length());
        cout << "|\n";
        cout << "|  Genre: " << L->info.genre;
        printSpaces(70 - L->info.genre.length());
        cout << "|\n";
        cout << "|  Durasi: " << formatDurasi(L->info.durasi);
        printSpaces(67 - formatDurasi(L->info.durasi).length());
        cout << "|\n";
        string yearStr = to_string(L->info.tahun);
        cout << "|  Tahun: " << yearStr;
        printSpaces(71 - yearStr.length());
        cout << "|\n";
        printLine('-', 80);

        cout << "\n";
        printLine('-', 80);
        cout << "|  [S] Pause/Resume  |  [Q] Stop & Exit  |\n";
        printLine('-', 80);
        cout << "\n  >> Masukkan pilihan: ";
        cin >> pilihan;

        if(pilihan == 'S' || pilihan == 's'){
            nowPlaying.isPaused = !nowPlaying.isPaused;
            if(nowPlaying.isPaused){
                cout << "\n  [INFO] Lagu terjeda...\n";
            } else {
                cout << "\n  [INFO] Berhasil melanjutkan lagu...\n";
            }
            system("pause");
        }
        else if(pilihan == 'Q' || pilihan == 'q'){
            cout << "\n  [INFO] Lagu Terhenti...\n";
            nowPlaying.isPlaying = false;
            system("pause");
            playing = false;
        }
        else{
            cout << "\n  [ERROR] Invalid command!\n";
            system("pause");
        }
    }
}

// ========== MUSIC PLAYER ==========
void musicPlayer(adrPlaylist PL){
    if(PL->firstItem == NULL){
        cout << "\n  [ERROR] Playlist kosong!\n";
        system("pause");
        return;
    }

    adrItem current = PL->firstItem;
    char pilihan = ' ';
    bool isPaused = false;

    current->play_count++;

    bool playing = true;
    while(playing){
        system("cls");
        printLine('=', 80);
        printBox("M U S I C   P L A Y E R", 80);
        printLine('=', 80);

        cout << "\n  Playlist: " << PL->info.nama << "\n\n";

        printLine('-', 80);
        if(isPaused){
            cout << "|  STATUS: [PAUSED]";
            printSpaces(61);
            cout << "|\n";
        } else {
            cout << "|  STATUS: [PLAYING]";
            printSpaces(60);
            cout << "|\n";
        }
        printLine('-', 80);

        cout << "|  Judul: " << current->lagu->info.judul;
        printSpaces(70 - current->lagu->info.judul.length());
        cout << "|\n";

        cout << "|  Artist: " << current->lagu->info.artis;
        printSpaces(69 - current->lagu->info.artis.length());
        cout << "|\n";

        cout << "|  Album: " << current->lagu->info.album;
        printSpaces(70 - current->lagu->info.album.length());
        cout << "|\n";

        cout << "|  Genre: " << current->lagu->info.genre;
        printSpaces(70 - current->lagu->info.genre.length());
        cout << "|\n";

        cout << "|  Durasi: " << formatDurasi(current->lagu->info.durasi);
        printSpaces(67 - formatDurasi(current->lagu->info.durasi).length());
        cout << "|\n";

        string playCountStr = "Play Count: " + to_string(current->play_count) + "x";
        cout << "|  " << playCountStr;
        printSpaces(76 - playCountStr.length());
        cout << "|\n";
        printLine('-', 80);

        nowPlaying.isPlaying = true;
        nowPlaying.judul = current->lagu->info.judul;
        nowPlaying.artis = current->lagu->info.artis;
        nowPlaying.playlist = PL->info.nama;
        nowPlaying.isPaused = isPaused;

        cout << "\n";
        printLine('-', 80);
        cout << "|  [P] Previous  |  [N] Next  |  [R] Replay  |  [S] Pause/Resume  |  [Q] Quit  |\n";
        printLine('-', 80);
        cout << "\n  >> Masukkan pilihan: ";
        cin >> pilihan;

        if(pilihan == 'P' || pilihan == 'p'){
            if(current == PL->firstItem){
                cout << "\n  [INFO] Sudah berada di lagu pertama!\n";
                system("pause");
            }else{
                adrItem temp = PL->firstItem;
                while(temp->next != current){
                    temp = temp->next;
                }
                current = temp;
                current->play_count++;
                isPaused = false;
            }
        }
        else if(pilihan == 'N' || pilihan == 'n'){
            if(current->next == NULL){
                cout << "\n  [INFO] Sudah berada di lagu terakhir!\n";
                system("pause");
            }else{
                current = current->next;
                current->play_count++;
                isPaused = false;
            }
        }
        else if(pilihan == 'R' || pilihan == 'r'){
            current->play_count++;
            isPaused = false;
            cout << "\n  [INFO] Mengulang lagu... Play count: " << current->play_count << "x\n";
            system("pause");
        }
        else if(pilihan == 'S' || pilihan == 's'){
            isPaused = !isPaused;
            if(isPaused){
                cout << "\n  [INFO] Lagu terjeda...\n";
            } else {
                cout << "\n  [INFO] Lagu dilanjutkan kembali...\n";
            }
            system("pause");
        }
        else if(pilihan == 'Q' || pilihan == 'q'){
            cout << "\n  [INFO] Keluar dari pemutaran musik...\n";
            nowPlaying.isPlaying = false;
            system("pause");
            playing = false;
        }
        else{
            cout << "\n  [ERROR] Invalid command!\n";
            system("pause");
        }
    }
}

// ========================SORTING LAGU==============

void sortPlaylistByAbjad(adrPlaylist PL){
    if(PL->firstItem == NULL || PL->firstItem->next == NULL) return;

    bool swapped = true;
    while(swapped) {
        swapped = false;
        adrItem current = PL->firstItem;
        adrItem prev = NULL;

        while(current->next != NULL){
            string judul1 = toLowerString(current->lagu->info.judul);
            string judul2 = toLowerString(current->next->lagu->info.judul);

            if(judul1 > judul2){
                adrItem temp = current->next;
                current->next = temp->next;
                temp->next = current;

                if(prev == NULL){
                    PL->firstItem = temp;
                } else {
                    prev->next = temp;
                }

                prev = temp;
                swapped = true;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
}

void sortingPlaylistMenu(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    showNowPlayingBar();

    string namaPlaylist;
    cout << "\n  Masukkan Nama Playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL == NULL){
        cout << "\n  [ERROR] Playlist tidak ditemukan!\n";
        system("pause");
        return;
    }

    if(PL->firstItem == NULL){
        cout << "\n  [ERROR] Playlist kosong!\n";
        system("pause");
        return;
    }

    int pilihan;
    cout << "\n";
    system("cls");
    printLine('-', 80);
    cout << "  [1] Urutkan berdasarkan ID\n";
    cout << "  [2] Urutkan berdasarkan judul (A-Z)\n";
    printLine('-', 80);
    cout << "\n  >> Masukkan pilihan: ";
    cin >> pilihan;

    if(pilihan == 1){
        sortPlaylistByID(PL);
        cout << "\n  [SUCCESS] Terurut berdasarkan ID!\n";
    } else if(pilihan == 2){
        sortPlaylistByAbjad(PL);
        cout << "\n  [SUCCESS] Terurut berdasarkan abjad!\n";
    } else {
        cout << "\n  [ERROR] Invalid option!\n";
    }

    system("pause");
}

void sortPlaylistByID(adrPlaylist PL){
    if(PL->firstItem == NULL || PL->firstItem->next == NULL) return;

    bool swapped = true;
    while(swapped) {
        swapped = false;
        adrItem current = PL->firstItem;
        adrItem prev = NULL;

        while(current->next != NULL){
            if(current->lagu->info.id_lagu > current->next->lagu->info.id_lagu){
                adrItem temp = current->next;
                current->next = temp->next;
                temp->next = current;

                if(prev == NULL){
                    PL->firstItem = temp;
                } else {
                    prev->next = temp;
                }

                prev = temp;
                swapped = true;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
}

// ========== SEARCHING LAGU ==========
void searchLaguByJudul(List_lagu LL){
    system("cls");
    tampilkanHeader();

    string keyword;
    cout << "\n  Masukkan judul lagu: ";
    cin.ignore();
    getline(cin, keyword);

    keyword = toLowerString(keyword);

    cout << "\n";
    printBox("HASIL PENCARIAN", 80);
    printLine('-', 80);

    address_lagu L = LL.first;
    int count = 0;

    while(L != NULL){
        string judul = toLowerString(L->info.judul);

        if(judul == keyword){
            cout << "\n  [" << L->info.id_lagu << "] " << L->info.judul << "\n";
            cout << "      Artis  : " << L->info.artis << "\n";
            cout << "      Album  : " << L->info.album << "\n";
            cout << "      Genre  : " << L->info.genre << "\n";
            cout << "      Durasi : " << formatDurasi(L->info.durasi) << "\n";
            count++;
        }
        L = L->next;
    }

    printLine('-', 80);
    if(count == 0){
        cout << "  Lagu tidak ditemukan! \"" << keyword << "\"\n";
    } else {
        cout << "  Total: " << count << " lagu ditemukan\n";
    }
    printLine('=', 80);
}

void searchLaguByArtis(List_lagu LL){
    system("cls");
    tampilkanHeader();

    string keyword;
    cout << "\n  Masukkan nama artis: ";
    cin.ignore();
    getline(cin, keyword);

    keyword = toLowerString(keyword);

    cout << "\n";
    printBox("HASIL PENCARIAN", 80);
    printLine('-', 80);

    address_lagu L = LL.first;
    int count = 0;

    while(L != NULL){
        string artis = toLowerString(L->info.artis);

        if(artis == keyword){
            cout << "\n  [" << L->info.id_lagu << "] " << L->info.judul << "\n";
            cout << "      Artis  : " << L->info.artis << "\n";
            cout << "      Album  : " << L->info.album << "\n";
            cout << "      Genre  : " << L->info.genre << "\n";
            cout << "      Durasi : " << formatDurasi(L->info.durasi) << "\n";
            count++;
        }
        L = L->next;
    }

    printLine('-', 80);
    if(count == 0){
        cout << "  Tidak ada lagu dari artis tersebut \"" << keyword << "\"\n";
    } else {
        cout << "  Total: " << count << " lagu ditemukan\n";
    }
    printLine('=', 80);
}

void searchLaguByGenre(List_lagu LL){
    system("cls");
    tampilkanHeader();

    string keyword;
    cout << "\n  Masukkan genre: ";
    cin.ignore();
    getline(cin, keyword);

    keyword = toLowerString(keyword);

    cout << "\n";
    printBox("HASIL PENCARIAN", 80);
    printLine('-', 80);

    address_lagu L = LL.first;
    int count = 0;

    while(L != NULL){
        string genre = toLowerString(L->info.genre);

        if(genre == keyword){
            cout << "\n  [" << L->info.id_lagu << "] " << L->info.judul << "\n";
            cout << "      Artis  : " << L->info.artis << "\n";
            cout << "      Album  : " << L->info.album << "\n";
            cout << "      Genre  : " << L->info.genre << "\n";
            cout << "      Durasi : " << formatDurasi(L->info.durasi) << "\n";
            count++;
        }
        L = L->next;
    }

    printLine('-', 80);
    if(count == 0){
        cout << "  Tidak ditemukan lagu dengan genre tersebut! \"" << keyword << "\"\n";
    } else {
        cout << "  Total: " << count << " lagu ditemukan\n";
    }
    printLine('=', 80);
}

void searchingMenu(List_lagu LL){
    int pilihan;
    bool running = true;

    while(running) {
        system("cls");
        tampilkanHeader();
        showNowPlayingBar();

        cout << "\n";
        printBox("SEARCH MENU", 80);
        printLine('-', 80);
        cout << "  [1] Cari berdasarkan judul\n";
        cout << "  [2] Cari berdasarkan artis\n";
        cout << "  [3] Cari berdasarkan genre\n";
        cout << "  [0] Kembali\n";
        printLine('-', 80);
        cout << "\n  >> Masukkan pilihan: ";
        cin >> pilihan;

        if(pilihan == 1){
            searchLaguByJudul(LL);
            system("pause");
        }
        else if(pilihan == 2){
            searchLaguByArtis(LL);
            system("pause");
        }
        else if(pilihan == 3){
            searchLaguByGenre(LL);
            system("pause");
        }
        else if(pilihan == 0){
            running = false;
        }
        else{
            cout << "\n  [ERROR] Invalid option!\n";
            system("pause");
        }
    }
}


void searchLaguInPlaylist(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);

    string namaPlaylist;
    cout << "\n  Masukkan nama playlist ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL == NULL){
        cout << "\n  [ERROR] Playlist tidak ditemukan!\n";
        system("pause");
        return;
    }

    string keyword;
    cout << "  Masukkan judul lagu: ";
    getline(cin, keyword);

    keyword = toLowerString(keyword);

    cout << "\n";
    printBox("HASIL PENCARIAN: " + PL->info.nama, 80);
    printLine('-', 80);

    adrItem IT = PL->firstItem;
    int count = 0;

    while(IT != NULL){
        string judul = toLowerString(IT->lagu->info.judul);

        if(judul == keyword){
            cout << "\n  [" << IT->lagu->info.id_lagu << "] " << IT->lagu->info.judul << "\n";
            cout << "      Artist     : " << IT->lagu->info.artis << "\n";
            cout << "      Album      : " << IT->lagu->info.album << "\n";
            cout << "      Genre      : " << IT->lagu->info.genre << "\n";
            cout << "      Durasi     : " << formatDurasi(IT->lagu->info.durasi) << "\n";
            cout << "      Play Count : " << IT->play_count << "x\n";
            count++;
        }
        IT = IT->next;
    }

    printLine('-', 80);
    if(count == 0){
        cout << "  Lagu tidak ditemukan \"" << keyword << "\"\n";
    } else {
        cout << "  Total: " << count << " lagu ditemukan\n";
    }
    printLine('=', 80);
}

// ========== USER OPERATIONS ==========
void lihatSemuaPlaylist(adrUser U){
    system("cls");
    tampilkanHeader();

    cout << "\n";
    printBox("MY PLAYLISTS - " + U->info.username, 80);
    printLine('-', 80);
    printAllPlaylists(U);
}

void buatPlaylistBaru(adrUser U){
    system("cls");
    tampilkanHeader();

    adrPlaylist P = inputPlaylist(U);
    insertLastPlaylist(U, P);
    cout << "\n  [SUCCESS] Playlist berhasil dibuat!\n";
    printLine('=', 80);
}

void hapusPlaylistUser(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    showNowPlayingBar();

    string nama;
    cout << "\n  Masukkan nama playlist yang akan dihapus: ";
    cin.ignore();
    getline(cin, nama);

    adrPlaylist P = findPlaylist(U, nama);
    if(P != NULL){
        deletePlaylist(U, P);
        cout << "\n  [SUCCESS] Playlist berhasil dihapus!\n";
    }else{
        cout << "\n  [ERROR] Playlist tidak ditemukan!\n";
    }
    printLine('=', 80);
}

// ========== SUBMENU HANDLERS ==========
void playlistManagementMenu(adrUser U, List_lagu &LL){
    int pil;
    bool running = true;

    while(running){
        system("cls");
        tampilkanHeader();
        showNowPlayingBar();

        cout << "\n";
        printBox("PLAYLIST MANAGEMENT", 80);
        printLine('-', 80);
        cout << "  [1] Lihat Semua Playlist\n";
        cout << "  [2] Buat Playlist Baru\n";
        cout << "  [3] Hapus Playlist\n";
        cout << "  [4] Edit Info Playlist\n";
        cout << "  [5] Lihat Detail Playlist\n";
        cout << "  [6] Tambahkan Lagu ke Playlist\n";
        cout << "  [7] Hapus Lagu dari Playlist\n";
        cout << "  [8] Urutkan Playlist\n";
        cout << "  [0] Kembali ke Main Menu\n";
        printLine('-', 80);
        cout << "\n  >> Masukkan pilihan: ";
        cin >> pil;

        if(pil == 1){
            lihatSemuaPlaylist(U);
            showNowPlayingBar();
            system("pause");
        }
        else if(pil == 2){
            buatPlaylistBaru(U);
            system("pause");
        }
        else if(pil == 3){
            hapusPlaylistUser(U);
            system("pause");
        }
        else if(pil == 4){
            editPlaylistUser(U);
            system("pause");
        }
        else if(pil == 5){
            lihatIsiPlaylistMenu(U);
            system("pause");
        }
        else if(pil == 6){
            tambahLaguKePlaylistMenu(U, LL);
            system("pause");
        }
        else if(pil == 7){
            hapusLaguDariPlaylistMenu(U);
            system("pause");
        }
        else if(pil == 8){
            sortingPlaylistMenu(U);
        }
        else if(pil == 0){
            running = false;
        }
        else{
            cout << "\n  [ERROR] Invalid option!\n";
            system("pause");
        }
    }
}

void searchDiscoveryMenu(adrUser U, List_lagu &LL, ListUser &LU){
    int pil;
    bool running = true;

    while(running){
        system("cls");
        tampilkanHeader();
        showNowPlayingBar();

        cout << "\n";
        printBox("SEARCH & DISCOVERY", 80);
        printLine('-', 80);
        cout << "  [1] Cari Lagu (Database)\n";
        cout << "  [2] Cari Lagu di Playlist\n";
        cout << "  [3] Browse All Songs\n";
        cout << "  [4] My Favorite Songs\n";
        cout << "  [0] Back to Main Menu\n";
        printLine('-', 80);
        cout << "\n  >> Masukkan pilihan: ";
        cin >> pil;

        if(pil == 1){
            searchingMenu(LL);
        }
        else if(pil == 2){
            searchLaguInPlaylist(U);
            system("pause");
        }
        else if(pil == 3){
            printInfo_lagu(LL);
            showNowPlayingBar();
            system("pause");
        }
        else if(pil == 4){
            laguTerpopulerUser(U);
            system("pause");
        }else if(pil == 0){
            running = false;
        }
        else{
            cout << "\n  [ERROR] Invalid option!\n";
            system("pause");
        }
    }
}

// ========== MENU ADMIN ==========
void menuAdmin(ListUser &LU, List_lagu &LL){
    int pil;
    string username, judul;
    adrUser U;
    address_lagu L;
    bool running = true;

    while(running){
        system("cls");
        tampilkanHeader();

        cout << "\n";
        printBox("ADMIN DASHBOARD", 80);
        printLine('=', 80);

        cout << "\n  USER MANAGEMENT\n";
        printLine('-', 20);
        cout << "  [1] Lihat Semua Pengguna\n";
        cout << "  [2] Lihat Detail Pengguna dan Playlistnya\n";
        cout << "  [3] Hapus Pengguna";

        cout << "\n  MUSIC DATABASE\n";
        printLine('-', 20);
        cout << "  [4] Lihat Semua Lagu\n";
        cout << "  [5] Tambahkan Lagu Baru\n";
        cout << "  [6] Edit Info Lagu\n";
        cout << "  [7] Hapus Lagu\n";

        cout << "\n  ANALYTICS\n";
        printLine('-', 20);
        cout << "  [8] Global Statistics\n";

        cout << "\n";
        printLine('-', 20);
        cout << "  [0] Logout\n";
        printLine('=', 80);

        cout << "\n  >> Masukkan pilihan: ";
        cin >> pil;

        if(pil == 1){
            system("cls");
            tampilkanHeader();
            printAllUsers(LU);
            system("pause");
        }
        else if(pil == 2){
            system("cls");
            tampilkanHeader();
            printAllUsers(LU);
            cout << "\n  Masukkan username: ";
            cin >> username;
            U = findUser(LU, username);
            if(U != NULL){
                cout << "\n";
                printLine('-', 80);
                showUser(U);
                printAllPlaylists(U);
            }else{
                cout << "\n  [ERROR] User not found!\n";
            }
            printLine('=', 80);
            system("pause");
        }
        else if(pil == 3){
            system("cls");
            tampilkanHeader();
            printAllUsers(LU);
            cout << "\n  Masukkan username yang akan dihapus: ";
            cin >> username;
            U = findUser(LU, username);
            if(U != NULL){
                deleteUser(LU, U);
                cout << "\n  [SUCCESS] User berhasil dihapus!\n";
            }else{
                cout << "\n  [ERROR] User not found!\n";
            }
            printLine('=', 80);
            system("pause");
        }
        else if(pil == 4){
            printInfo_lagu(LL);
            cout << "\n  Total: " << hitungLagu(LL) << " lagu\n";
            printLine('=', 80);
            system("pause");
        }
        else if(pil == 5){
            system("cls");
            tampilkanHeader();
            L = input_lagu();
            insertLast_lagu(LL, L);
            cout << "\n  [SUCCESS] Lagu berhasil ditambahkan!\n";
            printLine('=', 80);
            system("pause");
        }
        else if(pil == 6){
            printInfo_lagu(LL);
            cout << "\n  Masukkan judul lagu yang akan diedit: ";
            cin.ignore();
            getline(cin, judul);
            L = findElm_lagu(LL, judul);
            if(L != NULL){
                editInfo_lagu(L);
                cout << "\n  [SUCCESS] Lagu sudah diupdate!\n";
            }else{
                cout << "\n  [ERROR] Song not found!\n";
            }
            printLine('=', 80);
            system("pause");
        }
        else if(pil == 7){
            printInfo_lagu(LL);
            cout << "\n  Masukkan judul lagu yang akan dihapus: ";
            cin.ignore();
            getline(cin, judul);
            L = findElm_lagu(LL, judul);
            if(L != NULL){
                deleteSearch_lagu(LL, L);
                cout << "\n  [SUCCESS] Lagu sudah dihapus!\n";
            }else{
                cout << "\n  [ERROR] Song not found!\n";
            }
            printLine('=', 80);
            system("pause");
        }
        else if(pil == 8){
            statistikGlobal(LU, LL);
            system("pause");
        }
        else if(pil == 0){
            cout << "\n  [INFO] Logging out...\n";
            printLine('=', 80);
            system("pause");
            running = false;
        }
        else{
            cout << "\n  [ERROR] Invalid option!\n";
            printLine('=', 80);
            system("pause");
        }
    }
}
// ========== MENU USER (REVISED WITH COLLAPSIBLE MENU) ==========
void menuUser(ListUser &LU, List_lagu &LL, string username){
    adrUser U = findUser(LU, username);
    if(U == NULL) return;

    int pil;
    bool running = true;

    while(running){
        system("cls");
        tampilkanHeader();

        cout << "\n";
        printBox("USER: " + U->info.username, 80);
        printLine('-', 80);

        int totalPlay = 0;
        adrPlaylist PL = U->firstPlaylist;
        while(PL != NULL){
            totalPlay += getTotalPlayCount(PL);
            PL = PL->next;
        }

        cout << "  Playlists: " << hitungPlaylist(U) << " | Total Plays: " << totalPlay << "x\n";
        printLine('=', 80);

        // NOW PLAYING BAR - ALWAYS VISIBLE
        showNowPlayingBar();

        cout << "\n";
        printBox("MAIN MENU", 80);
        printLine('-', 80);
        cout << "  [1] Playlist Management\n";
        cout << "  [2] Search & Discovery\n";
        cout << "  [3] Quick Play\n";
        cout << "  [0] Logout\n";
        printLine('=', 80);

        cout << "\n  >> Choose: ";
        cin >> pil;

        if(pil == 1){
            playlistManagementMenu(U, LL);
        }
        else if(pil == 2){
            searchDiscoveryMenu(U, LL, LU);
        }
        else if(pil == 3){
            quickPlay(LL);
        }else if(pil == 0){
            cout << "\n  [INFO] Logging out...\n";
            printLine('=', 80);
            system("pause");
            running = false;
        }
        else{
            cout << "\n  [ERROR] Invalid option!\n";
            printLine('=', 80);
            system("pause");
        }
    }
}

// ========== USER OPERATIONS ==========
void dataDummy(ListUser &LU, List_lagu &LL){
    adrUser U;
    adrPlaylist PL;
    address_lagu L;
    adrItem IT;
    infoPlaylist plInfo;

    U = findUser(LU, "windi");
    if(U != NULL){
        plInfo.id = 1;
        plInfo.nama = "My Favorites";
        plInfo.tanggal_dibuat = "01/01/2024";
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 2);
        IT = alokasiItem(L);
        IT->play_count = 25;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 3);
        IT = alokasiItem(L);
        IT->play_count = 18;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 6);
        IT = alokasiItem(L);
        IT->play_count = 12;
        insertLastItem(PL, IT);
    }

    U = findUser(LU, "ariel");
    if(U != NULL){
        plInfo.id = 3;
        plInfo.nama = "Workout Mix";
        plInfo.tanggal_dibuat = "10/02/2024";
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 5);
        IT = alokasiItem(L);
        IT->play_count = 20;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 10);
        IT = alokasiItem(L);
        IT->play_count = 15;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 16);
        IT = alokasiItem(L);
        IT->play_count = 10;
        insertLastItem(PL, IT);
    }

    U = findUser(LU, "ida");
    if(U != NULL){
        plInfo.id = 6;
        plInfo.nama = "Study Music";
        plInfo.tanggal_dibuat = "15/03/2024";
        PL = alokasiPlaylist(plInfo);
        insertLastPlaylist(U, PL);

        L = findLaguByID(LL, 18);
        IT = alokasiItem(L);
        IT->play_count = 12;
        insertLastItem(PL, IT);

        L = findLaguByID(LL, 19);
        IT = alokasiItem(L);
        IT->play_count = 8;
        insertLastItem(PL, IT);
    }
}

// ========== USER OPERATIONS (yang hilang) ==========
void editPlaylistUser(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    showNowPlayingBar();

    string nama;
    cout << "\n  Masukkan nama playlist: ";
    cin.ignore();
    getline(cin, nama);

    adrPlaylist P = findPlaylist(U, nama);
    if(P != NULL){
        editPlaylist(P);
        cout << "\n  [SUCCESS] Playlist sudah di update!\n";
    }else{
        cout << "\n  [ERROR] Playlist not found!\n";
    }
    printLine('=', 80);
}

void lihatIsiPlaylistMenu(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    showNowPlayingBar();

    string namaPlaylist;
    cout << "\n  Masukkan nama playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL != NULL){
        system("cls");
        tampilkanHeader();

        cout << "\n";
        printBox("PLAYLIST DETAILS", 80);
        printLine('-', 80);
        showPlaylist(PL);
        printIsiPlaylist(PL);

        if(PL->firstItem != NULL){
            char pilihan;
            cout << "\n  Putar lagu sekarang? (Y/N): ";
            cin >> pilihan;

            if(pilihan == 'Y' || pilihan == 'y'){
                musicPlayer(PL);
            }
        }
    }else{
        cout << "\n  [ERROR] Playlist not found!\n";
    }
    printLine('=', 80);
}

void tambahLaguKePlaylistMenu(adrUser U, List_lagu LL){
    system("cls");
    lihatSemuaPlaylist(U);
    showNowPlayingBar();

    string namaPlaylist, judulLagu;
    cout << "\n  Masukkan nama playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL == NULL){
        cout << "\n  [ERROR] Playlist not found!\n";
        return;
    }

    printInfo_lagu(LL);
    cout << "\n  Enter song title: ";
    getline(cin, judulLagu);

    address_lagu L = findElm_lagu(LL, judulLagu);
    if(L != NULL){
        tambahLaguKePlaylist(U, PL, L);
    }else{
        cout << "\n  [ERROR] Song not found!\n";
    }
    printLine('=', 80);
}

void hapusLaguDariPlaylistMenu(adrUser U){
    system("cls");
    lihatSemuaPlaylist(U);
    showNowPlayingBar();

    string namaPlaylist, judulLagu;
    cout << "\n  Masukkan nama playlist: ";
    cin.ignore();
    getline(cin, namaPlaylist);

    adrPlaylist PL = findPlaylist(U, namaPlaylist);
    if(PL == NULL){
        cout << "\n  [ERROR] Playlist not found!\n";
        return;
    }

    printIsiPlaylist(PL);
    cout << "\n  Masukkan judul lagu yang akan dihapus: ";
    getline(cin, judulLagu);

    adrItem IT = PL->firstItem;
    address_lagu L = NULL;
    while(IT != NULL && L == NULL){
        if(IT->lagu->info.judul == judulLagu){
            L = IT->lagu;
        }
        IT = IT->next;
    }

    if(L != NULL){
        hapusLaguDariPlaylist(PL, L);
    }else{
        cout << "\n  [ERROR] Lagu tidak ada di playlist!\n";
    }
    printLine('=', 80);
}

// ========== STATISTICS GLOBAL ==========
void statistikGlobal(ListUser LU, List_lagu LL){
    system("cls");
    tampilkanHeader();

    cout << "\n";
    printBox("GLOBAL STATISTICS", 80);
    printLine('=', 80);

    int totalUser = hitungUser(LU);
    int totalLagu = hitungLagu(LL);
    int totalPlaylist = 0;
    int totalPlay = 0;

    adrUser U = LU.first;
    while(U != NULL){
        totalPlaylist += hitungPlaylist(U);
        adrPlaylist PL = U->firstPlaylist;
        while(PL != NULL){
            totalPlay += getTotalPlayCount(PL);
            PL = PL->next;
        }
        U = U->next;
    }

    cout << "\n  Total pengguna     : " << totalUser << endl;
    cout << "  Total Lagu           : " << totalLagu << endl;
    cout << "  Total Playlist       : " << totalPlaylist << endl;
    cout << "  Total Pemutaran      : " << totalPlay << "x" << endl;

    printLine('=', 80);
}

void laguTerpopulerUser(adrUser U){
    system("cls");
    tampilkanHeader();
    showNowPlayingBar();

    cout << "\n";
    printBox("MY FAVORITE SONGS", 80);
    printLine('-', 80);

    address_lagu laguList[100];
    int playCount[100];
    int totalLagu = 0;

    adrPlaylist PL = U->firstPlaylist;
    while(PL != NULL){
        adrItem IT = PL->firstItem;
        while(IT != NULL){
            bool found = false;
            int i = 0;
            while(i < totalLagu && !found){
                if(laguList[i] == IT->lagu){
                    playCount[i] += IT->play_count;
                    found = true;
                }
                i++;
            }

            if(!found){
                laguList[totalLagu] = IT->lagu;
                playCount[totalLagu] = IT->play_count;
                totalLagu++;
            }

            IT = IT->next;
        }
        PL = PL->next;
    }

    int i = 0;
    while(i < totalLagu - 1){
        int j = 0;
        while(j < totalLagu - i - 1){
            if(playCount[j] < playCount[j+1]){
                int tempCount = playCount[j];
                playCount[j] = playCount[j+1];
                playCount[j+1] = tempCount;

                address_lagu tempLagu = laguList[j];
                laguList[j] = laguList[j+1];
                laguList[j+1] = tempLagu;
            }
            j++;
        }
        i++;
    }

    int limit = (totalLagu < 10) ? totalLagu : 10;

    i = 0;
    while(i < limit){
        if(playCount[i] > 0){
            cout << "  " << (i+1) << ". " << laguList[i]->info.judul
                 << " - " << laguList[i]->info.artis
                 << " (" << playCount[i] << "x)" << endl;
        }
        i++;
    }

    printLine('=', 80);
}
