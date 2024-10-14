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
void menu_sorting(Tiket *data);
void merge_sort_ascending(Penerbangan** headRef);
void quick_sort_descending(Penerbangan* low, Penerbangan* high);
void update_head_tail(Tiket* data);

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
        cout << "|5| SORTING TIKET                        |" << endl;
        cout << "|6| KELUAR                               |" << endl;
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
                menu_sorting(data);
                break;
            case 6:
                cout << "Terima kasih! Sampai jumpa!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 6);
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

void menu_sorting(Tiket *data) {
    int pilihan;
    cout << "+-----------------------------------------+" << endl;
    cout << "|            MENU SORTING TIKET           |" << endl;
    cout << "|-----------------------------------------|" << endl;
    cout << "|1| Merge Sort (Ascending)                |" << endl;
    cout << "|2| Quick Sort (Descending)               |" << endl;
    cout << "+-----------------------------------------+" << endl;
    cout << "Pilihan: ";
    cin >> pilihan;
    cin.ignore();
    cout << endl;

    switch (pilihan) {
        case 1:
            merge_sort_ascending(&(data->head));
            update_head_tail(data); 
            cout << "Tiket telah diurutkan secara ascending menggunakan Merge Sort." << endl;
            break;
        case 2:
            quick_sort_descending(data->head, data->tail);
            update_head_tail(data); 
            cout << "Tiket telah diurutkan secara descending menggunakan Quick Sort." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
    }
    cout << endl;
}

// Fungsi untuk memperbarui pointer head dan tail
void update_head_tail(Tiket* data) {
    if (data->head == nullptr) {
        data->tail = nullptr;
        return;
    }

    Penerbangan* current = data->head;
    while (current->next != nullptr) {
        current = current->next;
    }
    data->tail = current;
}

// Fungsi Merge Sort untuk pengurutan ascending
Penerbangan* sorted_merge_ascending(Penerbangan* a, Penerbangan* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    if (a->nama_penerbangan <= b->nama_penerbangan) {
        a->next = sorted_merge_ascending(a->next, b);
        if (a->next != nullptr) {
            a->next->prev = a;
        }
        a->prev = nullptr;
        return a;
    } else {
        b->next = sorted_merge_ascending(a, b->next);
        if (b->next != nullptr) {
            b->next->prev = b;
        }
        b->prev = nullptr;
        return b;
    }
}

void split(Penerbangan* source, Penerbangan** frontRef, Penerbangan** backRef) {
    Penerbangan* fast;
    Penerbangan* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

void merge_sort_ascending(Penerbangan** headRef) {
    Penerbangan* head = *headRef;
    Penerbangan* a;
    Penerbangan* b;

    if ((head == nullptr) || (head->next == nullptr)) {
        return;
    }

    split(head, &a, &b);

    merge_sort_ascending(&a);
    merge_sort_ascending(&b);

    *headRef = sorted_merge_ascending(a, b);

    (*headRef)->prev = nullptr;
}

// Fungsi untuk partition pada Quick Sort
Penerbangan* partition(Penerbangan* low, Penerbangan* high) {
    string pivot = high->nama_penerbangan;
    Penerbangan* i = low->prev;

    for (Penerbangan* j = low; j != high; j = j->next) {
        if (j->nama_penerbangan > pivot) {
            i = (i == nullptr) ? low : i->next;
            swap(i->nama_penerbangan, j->nama_penerbangan);
            swap(i->tujuan, j->tujuan);
            swap(i->waktu, j->waktu);
        }
    }

    i = (i == nullptr) ? low : i->next;
    swap(i->nama_penerbangan, high->nama_penerbangan);
    swap(i->tujuan, high->tujuan);
    swap(i->waktu, high->waktu);
    return i;
}

// Fungsi Quick Sort untuk pengurutan descending
void quick_sort_descending(Penerbangan* low, Penerbangan* high) {
    if (high != nullptr && low != high && low != high->next) {
        Penerbangan* p = partition(low, high);
        if (p != nullptr && p->prev != nullptr) {
            quick_sort_descending(low, p->prev);  
        }
        if (p != nullptr && p->next != nullptr) {
            quick_sort_descending(p->next, high);  
        }
    }
}
