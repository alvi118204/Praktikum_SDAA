#include <iostream>
#include <string>
using namespace std;

struct Penumpang {
    unsigned long int nim; 
    string nama; 
};

// Struktur untuk menyimpan data penerbangan
struct Penerbangan {
    string nama_penerbangan; 
    string tujuan; 
    string waktu; 
};

struct Tiket {
    Penerbangan daftar_penerbangan[10]; 
    int banyak_tiket = 0; 
    Penumpang penumpang; 
};

int fungsi_login(unsigned long int nim, string nama, Tiket *data);
void menu(Tiket *data);
void tampilkan(Tiket *data);
void tambah(Tiket *data);
void ubah(Tiket *data, int *nomor);
void hapus(Tiket *data, int *nomor);

int main() {
    Tiket data;
    data.penumpang.nim = 2309106132;
    data.penumpang.nama = "Alvito"; 
    int status_login = fungsi_login(data.penumpang.nim, data.penumpang.nama, &data);

    if (status_login == 1) {
        menu(&data);
    } else {
        cout << "Program Berhenti" << endl;
    }
    return 0;
}

int fungsi_login(unsigned long int nim, string nama, Tiket *data) {
    unsigned long int nim_login;
    string nama_login;
    int ulang = 0;

    while (ulang < 3) {
        cout << "+-----------------------------------------+" << endl;
        cout << "|        PEMBELIAN TIKET PESAWAT         |" << endl;
        cout << "|-----------------------------------------|" << endl;
        cout << "|  SILAHKAN LOGIN MENGGUNAKAN NAMA & NIM  |" << endl;
        cout << "+-----------------------------------------+" << endl;

        cout << "Masukkan Nama: "; fflush(stdin);
        getline(cin, nama_login); fflush(stdin);
        cout << "Masukkan NIM: "; fflush(stdin);
        cin >> nim_login; fflush(stdin);
        cout << endl;

        if (nama == nama_login && nim == nim_login) {
            cout << "Login Berhasil" << endl;
            cout << endl;
            return 1; 
        } else {
            cout << "Nama atau NIM salah, silahkan coba lagi" << endl;
            cout << endl;
            ulang++;
        }
        if (ulang == 3) {
            cout << "Anda telah salah 3 kali" << endl;
            return 0; 
        }
    }
    return 0;
}

void menu(Tiket *data) {
    int pilihan;

    do {
        cout << "+-----------------------------------------+" << endl;
        cout << "|        PEMBELIAN TIKET PESAWAT         |" << endl;
        cout << "|-----------------------------------------|" << endl;
        cout << "|1| TAMPILKAN PENERBANGAN                |" << endl;
        cout << "|2| TAMBAHKAN TIKET                      |" << endl;
        cout << "|3| UBAH TIKET                           |" << endl;
        cout << "|4| HAPUS TIKET                          |" << endl;
        cout << "|5| KELUAR                               |" << endl;
        cout << "+-----------------------------------------+" << endl;

        cout << "Pilihan: "; fflush(stdin);
        cin >> pilihan; fflush(stdin);
        cout << endl;

        switch (pilihan) {
            case 1:
                tampilkan(data);
                break;
            case 2:
                tambah(data);
                break;
            case 3:
                ubah(data, &(data->banyak_tiket));
                break;
            case 4:
                hapus(data, &(data->banyak_tiket));
                break;
            case 5:
                cout << "Terima kasih! Sampai jumpa!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 5);
}

void tampilkan(Tiket *data) {
    if (data->banyak_tiket == 0) {
        cout << "Daftar tiket kosong" << endl;
    } else {
        cout << "+----------------------------------------+" << endl;
        cout << "|          DAFTAR TIKET                 |" << endl;
        cout << "+----------------------------------------+" << endl;
        for (int i = 0; i < data->banyak_tiket; i++) {
            cout << i + 1 << ". " << data->daftar_penerbangan[i].nama_penerbangan 
                 << " | Tujuan: " << data->daftar_penerbangan[i].tujuan 
                 << " | Waktu: " << data->daftar_penerbangan[i].waktu << endl;
        }
        cout << "+----------------------------------------+" << endl;
    }
    cout << endl;
}

void tambah(Tiket *data) {
    if (data->banyak_tiket >= 10) {
        cout << "Daftar tiket sudah penuh" << endl;
        cout << endl;
    } else {
        cout << "Masukkan nama penerbangan: "; fflush(stdin);
        getline(cin, data->daftar_penerbangan[data->banyak_tiket].nama_penerbangan); fflush(stdin);
        cout << "Masukkan tujuan penerbangan: "; fflush(stdin);
        getline(cin, data->daftar_penerbangan[data->banyak_tiket].tujuan); fflush(stdin);
        cout << "Masukkan waktu penerbangan: "; fflush(stdin);
        getline(cin, data->daftar_penerbangan[data->banyak_tiket].waktu); fflush(stdin);
        cout << "Tiket berhasil ditambahkan." << endl;
        cout << endl;
        data->banyak_tiket++;
    }
}

void ubah(Tiket *data, int *nomor) {
    tampilkan(data);
    cout << endl;
    cout << "Pilih tiket yang ingin diubah: "; fflush(stdin);
    cin >> *nomor; fflush(stdin);
    cout << endl;
    if (*nomor < 1 || *nomor > data->banyak_tiket) {
        cout << "Pilihan tidak ada" << endl;
    } else {
        cout << "Masukkan nama penerbangan baru: "; fflush(stdin);
        getline(cin, data->daftar_penerbangan[*nomor - 1].nama_penerbangan); fflush(stdin);
        cout << "Masukkan tujuan penerbangan baru: "; fflush(stdin);
        getline(cin, data->daftar_penerbangan[*nomor - 1].tujuan); fflush(stdin);
        cout << "Masukkan waktu penerbangan baru: "; fflush(stdin);
        getline(cin, data->daftar_penerbangan[*nomor - 1].waktu); fflush(stdin);
        cout << "Tiket berhasil diubah." << endl;
        cout << endl;
    }
}

void hapus(Tiket *data, int *nomor) {
    tampilkan(data);
    cout << endl;
    cout << "Pilih tiket yang ingin dihapus: "; fflush(stdin);
    cin >> *nomor; fflush(stdin);
    cout << endl;
    if (*nomor < 1 || *nomor > data->banyak_tiket) {
        cout << "Pilihan tidak ada" << endl;
    } else {
        for (int i = *nomor - 1; i < data->banyak_tiket - 1; i++) {
            data->daftar_penerbangan[i] = data->daftar_penerbangan[i + 1];
        }
        data->banyak_tiket--;
        cout << "Tiket berhasil dihapus." << endl;
    }
    cout << endl;
}
