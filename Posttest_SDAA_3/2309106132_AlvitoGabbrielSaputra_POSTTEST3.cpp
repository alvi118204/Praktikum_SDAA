#include <iostream>
#include <string>
using namespace std;

struct Penumpang {
    unsigned long int nim;
    string nama;
};

struct Penerbangan {
    string nama_penerbangan;
    string tujuan;
    string waktu;
    Penerbangan* prev;
    Penerbangan* next;
};

struct Tiket {
    Penerbangan* head;
    Penerbangan* tail;
    int banyak_tiket;
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
    data.head = nullptr;
    data.tail = nullptr;
    data.banyak_tiket = 0;
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
        Penerbangan* current = data->head;
        int i = 1;
        while (current != nullptr) {
            cout << i << ". " << current->nama_penerbangan 
                 << " | Tujuan: " << current->tujuan 
                 << " | Waktu: " << current->waktu << endl;
            current = current->next;
            i++;
        }
        cout << "+----------------------------------------+" << endl;
    }
    cout << endl;
}

void tambah(Tiket *data) {
    Penerbangan* newNode = new Penerbangan();
    cout << "Masukkan nama penerbangan: "; fflush(stdin);
    getline(cin, newNode->nama_penerbangan); fflush(stdin);
    cout << "Masukkan tujuan penerbangan: "; fflush(stdin);
    getline(cin, newNode->tujuan); fflush(stdin);
    cout << "Masukkan waktu penerbangan: "; fflush(stdin);
    getline(cin, newNode->waktu); fflush(stdin);

    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (data->head == nullptr) {
        data->head = newNode;
        data->tail = newNode;
    } else {
        data->tail->next = newNode;
        newNode->prev = data->tail;
        data->tail = newNode;
    }

    data->banyak_tiket++;
    cout << "Tiket berhasil ditambahkan." << endl;
    cout << endl;
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
        Penerbangan* current = data->head;
        for (int i = 1; i < *nomor; i++) {
            current = current->next;
        }
        cout << "Masukkan nama penerbangan baru: "; fflush(stdin);
        getline(cin, current->nama_penerbangan); fflush(stdin);
        cout << "Masukkan tujuan penerbangan baru: "; fflush(stdin);
        getline(cin, current->tujuan); fflush(stdin);
        cout << "Masukkan waktu penerbangan baru: "; fflush(stdin);
        getline(cin, current->waktu); fflush(stdin);
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
        Penerbangan* current = data->head;
        for (int i = 1; i < *nomor; i++) {
            current = current->next;
        }
        if (current->prev == nullptr) {
            data->head = current->next;
            if (data->head != nullptr) {
                data->head->prev = nullptr;
            }
        } else if (current->next == nullptr) {
            data->tail = current->prev;
            data->tail->next = nullptr;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        delete current;
        data->banyak_tiket--;
        cout << "Tiket berhasil dihapus." << endl;
    }
    cout << endl;
}