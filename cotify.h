#ifndef COTIFY_H_INCLUDED
#define COTIFY_H_INCLUDED

#include <iostream>
using namespace std;

// =========== ADT LAGU ========
struct lagu{
    int id_lagu;
    string judul;
    string artis;
    string album;
    string genre;
    int durasi;
    int tahun;
};

typedef struct elmList_lagu *address_lagu;

struct elmList_lagu{
    lagu info;
    address_lagu next;
    address_lagu prev;
};

struct List_lagu{
    address_lagu first;
    address_lagu last;
};

// ========== ADT USER ==========

struct infoUser{
    string username;
    string nama_lengkap;
    string email;
    string negara;
    string tipe_akun;
    int umur;
};

typedef struct elmUser *adrUser;
typedef struct elmPlaylist *adrPlaylist;
typedef struct elmPlaylistItem *adrItem;

struct infoPlaylist{
    int id;
    string nama;
    string deskripsi;
    string tanggal_dibuat;
};

struct elmPlaylistItem{
    address_lagu lagu;
    int play_count;
    string tanggal_ditambah;
    adrItem next;
};

struct elmPlaylist{
    infoPlaylist info;
    adrPlaylist next;
    adrItem firstItem;
};

struct elmUser{
    infoUser info;
    adrUser next;
    adrPlaylist firstPlaylist;
};

struct ListUser{
    adrUser first;
};

// ========== ADT MENU ===========
struct CurrentUser {
    string username;
    string role;
    bool isLoggedIn;
};

// =================== USER ===================
void createListUser(ListUser &L);
adrUser alokasiUser(infoUser x);
void insertLastUser(ListUser &L, adrUser P);
adrUser findUser(ListUser L, string username);
void deleteUser(ListUser &L, adrUser &P);
void printAllUsers(ListUser L);
void showUser(adrUser P);
adrUser inputUser();
void editUser(adrUser &P);
int hitungUser(ListUser L);
void dataUser(ListUser &L);

// ========== PLAYLIST FUNCTIONS ==========
adrPlaylist alokasiPlaylist(infoPlaylist x);
void insertLastPlaylist(adrUser U, adrPlaylist P);
adrPlaylist findPlaylist(adrUser U, string nama);
void deletePlaylist(adrUser &U, adrPlaylist &P);
void printAllPlaylists(adrUser U);
void showPlaylist(adrPlaylist P);
adrPlaylist inputPlaylist(adrUser U);
void editPlaylist(adrPlaylist &P);
int hitungPlaylist(adrUser U);
int getTotalLaguInPlaylist(adrPlaylist P);
int getTotalDurasiPlaylist(adrPlaylist P);

// ========== PLAYLIST ITEM FUNCTIONS ==========
adrItem alokasiItem(address_lagu L);
void insertLastItem(adrPlaylist PL, adrItem P);
adrItem findItem(adrPlaylist PL, address_lagu L);
void deleteItem(adrPlaylist &PL, adrItem &P);
void printIsiPlaylist(adrPlaylist PL);
void playLagu(adrPlaylist PL, address_lagu L);
adrItem getCurrentItem(adrPlaylist PL, address_lagu L);
int getTotalPlayCount(adrPlaylist PL);
address_lagu getLaguTerpopulerDiPlaylist(adrPlaylist PL);

// ========== HELPER FUNCTIONS ==========
void tambahLaguKePlaylist(adrUser U, adrPlaylist PL, address_lagu L);
void hapusLaguDariPlaylist(adrPlaylist PL, address_lagu L);
void printSpaces(int count);
void printLine(char c, int length);
void printWithWidth(string text, int width);
void printBox(string text, int width);
void showNowPlayingBar();

// ===================== LAGU ===========================
void createList_lagu(List_lagu &L);
address_lagu alokasi_lagu(lagu x);
void insertLast_lagu(List_lagu &L, address_lagu P);
address_lagu findElm_lagu(List_lagu L, string judul);
address_lagu findLaguByID(List_lagu L, int id);
void deleteSearch_lagu(List_lagu &L, address_lagu &P);
void printInfo_lagu(List_lagu L);
void showLagu(address_lagu P);
address_lagu input_lagu();
void editInfo_lagu(address_lagu &P);
void data_lagu(List_lagu &L);
string formatDurasi(int detik);
int hitungLagu(List_lagu L);

// ========== AUTHENTICATION ==========
void tampilkanHeader();
bool login(CurrentUser &current, ListUser LU);
void logout(CurrentUser &current);

// ========== MAIN MENU ==========
void menuAdmin(ListUser &LU, List_lagu &LL);
void menuUser(ListUser &LU, List_lagu &LL, string username);
string toLowerString(string str);

// ========== SUBMENU HANDLERS ==========
void playlistManagementMenu(adrUser U, List_lagu &LL);
void searchDiscoveryMenu(adrUser U, List_lagu &LL, ListUser &LU);

// ========== USER OPERATIONS ==========
void lihatSemuaPlaylist(adrUser U);
void buatPlaylistBaru(adrUser U);
void hapusPlaylistUser(adrUser U);
void editPlaylistUser(adrUser U);
void tambahLaguKePlaylistMenu(adrUser U, List_lagu LL);
void hapusLaguDariPlaylistMenu(adrUser U);
void playLaguMenu(adrUser U);
void lihatIsiPlaylistMenu(adrUser U);
void sortingPlaylistMenu(adrUser U);

// ========== MUSIC PLAYER ==========
void musicPlayer(adrPlaylist PL);
void quickPlay(List_lagu LL);
void sortPlaylistByID(adrPlaylist PL);
void sortPlaylistByAbjad(adrPlaylist PL);

// ========== SEARCH & DISCOVERY ==========
void searchingMenu(List_lagu LL);
void searchLaguByJudul(List_lagu LL);
void searchLaguByArtis(List_lagu LL);
void searchLaguByGenre(List_lagu LL);
void searchLaguByAlbum(List_lagu LL);
void searchLaguInPlaylist(adrUser U);

// ========== STATISTICS ==========
void statistikGlobal(ListUser LU, List_lagu LL);
void laguTerpopulerUser(adrUser U);

// ========== DATA DUMMY ==========
void dataDummy(ListUser &LU, List_lagu &LL);

#endif // USER_H_INCLUDED
