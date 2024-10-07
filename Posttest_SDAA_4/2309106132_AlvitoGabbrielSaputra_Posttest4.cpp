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
    int mode; 
};

int fungsi_login(unsigned long int nim, string nama, Tiket *data);
void menu(Tiket *data);
void pilih_mode(Tiket *data);
void tampilkan(Tiket *data);
void tambah(Tiket *data);
void hapus(Tiket *data);
void menu_mode(Tiket *data);

int main() {
    Tiket data;
    data.head = nullptr;
    data.tail = nullptr;
    data.banyak_tiket = 0;
    data.mode = 0;
    data.penumpang.nim = 2309106132;
    data.penumpang.nama = "Alvito";
    int status_login = fungsi_login(data.penumpang.nim, data.penumpang.nama, &data);

    if (status_login == 1) {
        pilih_mode(&data);
        menu(&data);
    } else {
        cout << "Program Berhenti" << endl;
    }
    return 0;
}

void pilih_mode(Tiket *data) {
    int pilihan;
    do {
        cout << "+-----------------------------------------+" << endl;
        cout << "|        PILIH MODE OPERASI TIKET        |" << endl;
        cout << "|-----------------------------------------|" << endl;
        cout << "|1| STACK (LIFO - Last In First Out)     |" << endl;
        cout << "|2| QUEUE (FIFO - First In First Out)    |" << endl;
        cout << "+-----------------------------------------+" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        
        if (pilihan == 1 || pilihan == 2) {
            data->mode = pilihan;
            cout << "Mode " << (pilihan == 1 ? "STACK" : "QUEUE") << " dipilih." << endl;
            cout << endl;
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan pilih 1 atau 2." << endl;
        }
    } while (true);
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
        getline(cin, nama_login);
        cout << "Masukkan NIM: ";
        cin >> nim_login;
        cin.ignore();
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
        cout << "Mode saat ini: " << (data->mode == 1 ? "STACK" : "QUEUE") << endl;
        cout << "|-----------------------------------------|" << endl;
        cout << "|1| TAMPILKAN PENERBANGAN                |" << endl;
        cout << "|2| TAMBAH TIKET                         |" << endl;
        cout << "|3| HAPUS TIKET                          |" << endl;
        cout << "|4| GANTI MODE                           |" << endl;
        cout << "|5| KELUAR                               |" << endl;
        cout << "+-----------------------------------------+" << endl;

        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();
        cout << endl;

        switch (pilihan) {
            case 1:
                tampilkan(data);
                break;
            case 2:
                tambah(data);
                break;
            case 3:
                hapus(data);
                break;
            case 4:
                pilih_mode(data);
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
        cout << "|          DAFTAR TIKET                  |" << endl;
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
    cout << "Masukkan nama penerbangan: ";
    getline(cin, newNode->nama_penerbangan);
    cout << "Masukkan tujuan penerbangan: ";
    getline(cin, newNode->tujuan);
    cout << "Masukkan waktu penerbangan: ";
    getline(cin, newNode->waktu);

    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (data->head == nullptr) {
        data->head = newNode;
        data->tail = newNode;
    } else if (data->mode == 1) { 
        newNode->next = data->head;
        data->head->prev = newNode;
        data->head = newNode;
    } else { 
        data->tail->next = newNode;
        newNode->prev = data->tail;
        data->tail = newNode;
    }

    data->banyak_tiket++;
    cout << "Tiket berhasil ditambahkan." << endl;
    cout << endl;
}

void hapus(Tiket *data) {
    if (data->banyak_tiket == 0) {
        cout << "Tidak ada tiket yang dapat dihapus." << endl;
        return;
    }

    Penerbangan* nodeToDelete;
    if (data->mode == 1) { 
        nodeToDelete = data->head;
        data->head = data->head->next;
        if (data->head != nullptr) {
            data->head->prev = nullptr;
        } else {
            data->tail = nullptr;
        }
    } else { 
        nodeToDelete = data->head;
        data->head = data->head->next;
        if (data->head != nullptr) {
            data->head->prev = nullptr;
        } else {
            data->tail = nullptr;
        }
    }

    cout << "Tiket yang dihapus:" << endl;
    cout << "Nama Penerbangan: " << nodeToDelete->nama_penerbangan << endl;
    cout << "Tujuan: " << nodeToDelete->tujuan << endl;
    cout << "Waktu: " << nodeToDelete->waktu << endl;

    delete nodeToDelete;
    data->banyak_tiket--;
    cout << "Tiket berhasil dihapus." << endl;
    cout << endl;
}