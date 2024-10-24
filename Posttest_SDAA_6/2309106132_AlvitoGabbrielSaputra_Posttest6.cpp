#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Penumpang {
    unsigned long int nim;
    string nama;
};

struct Penerbangan {
    string nama_penerbangan;
    string tujuan;
    string waktu;
    int harga;
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
void searchHarga(Tiket* data);
void searchNama(Tiket* data);

// Boyer-Moore Search 
void badCharHeuristic(string str, int size, int badchar[256]) {
    for (int i = 0; i < 256; i++)
        badchar[i] = -1;
    for (int i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

int boyerMooreSearch(string text, string pattern) {
    int m = pattern.size();
    int n = text.size();
    int badchar[256];
    
    badCharHeuristic(pattern, m, badchar);
    
    int s = 0;
    while(s <= (n - m)) {
        int j = m - 1;
        while(j >= 0 && pattern[j] == text[s + j])
            j--;
        if (j < 0) {
            return s;
        } else {
            s += max(1, j - badchar[text[s + j]]);
        }
    }
    return -1;
}

// Fibonacci Search 
int fibonacciSearch(vector<int> arr, int x, int n) {
    int fib2 = 0;
    int fib1 = 1;
    int fib = fib2 + fib1;
    
    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }
    
    int offset = -1;
    while (fib > 1) {
        int i = min(offset + fib2, n - 1);
        if (arr[i] < x) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }
        else if (arr[i] > x) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
        else return i;
    }
    if (fib1 && arr[offset + 1] == x)
        return offset + 1;
    return -1;
}

// Jump Search 
int jumpSearch(vector<int> arr, int x, int n) {
    int step = sqrt(n);
    int prev = 0;
    
    while (arr[min(step, n)-1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }
    
    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n))
            return -1;
    }
    
    if (arr[prev] == x)
        return prev;
    return -1;
}

vector<int> getHargaVector(Tiket* data) {
    vector<int> prices;
    Penerbangan* current = data->head;
    while (current != nullptr) {
        prices.push_back(current->harga);
        current = current->next;
    }
    return prices;
}

void searchHarga(Tiket* data) {
    if (data->banyak_tiket == 0) {
        cout << "Daftar tiket kosong" << endl;
        return;
    }

    int searchPrice;
    cout << "Masukkan harga yang dicari: ";
    cin >> searchPrice;
    
    vector<int> prices = getHargaVector(data);
    sort(prices.begin(), prices.end());  
    
    cout << "Pilih metode pencarian:\n";
    cout << "1. Fibonacci Search\n";
    cout << "2. Jump Search\n";
    int pilihan;
    cout << "Pilihan: ";
    cin >> pilihan;

    cout << "\nHasil Pencarian:\n";
    Penerbangan* current = data->head;
    bool found = false;
    int index = 0;

    if (pilihan == 1) {
        int fibResult = fibonacciSearch(prices, searchPrice, prices.size());
        if (fibResult != -1) {
            while (current != nullptr) {
                if (current->harga == searchPrice) {
                    cout << "Harga ditemukan pada indeks " << index << ":\n";
                    cout << "Nama Penerbangan: " << current->nama_penerbangan << "\n";
                    cout << "Tujuan: " << current->tujuan << "\n";
                    cout << "Waktu: " << current->waktu << "\n";
                    cout << "Harga: " << current->harga << "\n\n";
                    found = true;
                    break;
                }
                current = current->next;
                index++;
            }
        } else {
            cout << "Harga tidak ditemukan\n";
        }
    } else if (pilihan == 2) {
        int jumpResult = jumpSearch(prices, searchPrice, prices.size());
        if (jumpResult != -1) {
            while (current != nullptr) {
                if (current->harga == searchPrice) {
                    cout << "Harga ditemukan pada indeks " << index << ":\n";
                    cout << "Nama Penerbangan: " << current->nama_penerbangan << "\n";
                    cout << "Tujuan: " << current->tujuan << "\n";
                    cout << "Waktu: " << current->waktu << "\n";
                    cout << "Harga: " << current->harga << "\n\n";
                    found = true;
                    break;
                }
                current = current->next;
                index++;
            }
        } else {
            cout << "Harga tidak ditemukan\n";
        }
    } else {
        cout << "Pilihan tidak valid\n";
    }

    if (!found) {
        cout << "Harga tiket tidak ditemukan.\n";
    }
}

void searchNama(Tiket* data) {
    if (data->banyak_tiket == 0) {
        cout << "Daftar tiket kosong" << endl;
        return;
    }

    string searchName;
    cout << "Masukkan nama penerbangan yang dicari: ";
    cin.ignore();
    getline(cin, searchName);
    
    cout << "\nHasil Pencarian Boyer-Moore:\n";
    Penerbangan* current = data->head;
    bool found = false;
    int index = 0;
    
    while (current != nullptr) {
        if (boyerMooreSearch(current->nama_penerbangan, searchName) != -1) {
            cout << "Penerbangan ditemukan pada indeks " << index << ":\n";
            cout << "Nama: " << current->nama_penerbangan << "\n";
            cout << "Tujuan: " << current->tujuan << "\n";
            cout << "Waktu: " << current->waktu << "\n";
            cout << "Harga: " << current->harga << "\n\n";
            found = true;
        }
        current = current->next;
        index++;
    }
    
    if (!found)
        cout << "Penerbangan tidak ditemukan\n";
}

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

    Penerbangan* current = data.head;
    while (current != nullptr) {
        Penerbangan* temp = current;
        current = current->next;
        delete temp;
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

        cout << "Masukkan Nama: ";
        cin.ignore(); 
        getline(cin, nama_login); 
        cout << "Masukkan NIM: ";
        cin >> nim_login;

        if (nim_login == data->penumpang.nim && nama_login == data->penumpang.nama) {
            cout << "Berhasil Login!" << endl;
            return 1; 
        } else {
            cout << "Login Gagal! Coba lagi." << endl;
            ulang++;
        }
    }
    
    cout << "Anda telah gagal login 3 kali. Program berhenti." << endl;
    return 0; 
}


void menu(Tiket *data) {
    int pilihan, nomor;
    do {
        cout << "+-------------------------------------+" << endl;
        cout << "|        PEMBELIAN TIKET PESAWAT      |" << endl;
        cout << "+-------------------------------------+" << endl;
        cout << "| 1. Tampilkan Tiket                  |" << endl;
        cout << "| 2. Tambah Tiket                     |" << endl;
        cout << "| 3. Ubah Tiket                       |" << endl;
        cout << "| 4. Hapus Tiket                      |" << endl;
        cout << "| 5. Cari Tiket Berdasarkan Harga     |" << endl;
        cout << "| 6. Cari Tiket Berdasarkan Nama      |" << endl;
        cout << "| 7. Keluar                           |" << endl;
        cout << "+-------------------------------------+" << endl;

        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkan(data);
                break;
            case 2:
                tambah(data);
                break;
            case 3:
                tampilkan(data);
                cout << "Nomor tiket yang ingin diubah: ";
                cin >> nomor;
                ubah(data, &nomor);
                break;
            case 4:
                tampilkan(data);
                cout << "Nomor tiket yang ingin dihapus: ";
                cin >> nomor;
                hapus(data, &nomor);
                break;
            case 5:
                searchHarga(data);
                break;
            case 6:
                searchNama(data);
                break;
            case 7:
                cout << "Keluar dari program" << endl;
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
                break;
        }
    } while (pilihan != 0);
}

// Fungsi untuk menampilkan daftar tiket
void tampilkan(Tiket *data) {
    if (data->banyak_tiket == 0) {
        cout << "Daftar tiket kosong" << endl;
        return;
    }

    Penerbangan* current = data->head;
    int index = 0;

    cout << "+-----------------------------------------------------+" << endl;
    cout << "|                    DAFTAR TIKET                    |" << endl;
    cout << "+-----------------------------------------------------+" << endl;

    while (current != nullptr) {
        cout << "Tiket " << index + 1 << ":\n";
        cout << "Nama Penerbangan: " << current->nama_penerbangan << endl;
        cout << "Tujuan          : " << current->tujuan << endl;
        cout << "Waktu           : " << current->waktu << endl;
        cout << "Harga           : " << current->harga << endl;
        cout << "+-----------------------------------------------------+" << endl;
        current = current->next;
        index++;
    }

    if (index == 0) {
        cout << "|              Tidak ada tiket tersedia               |" << endl;
        cout << "+-----------------------------------------------------+" << endl;
    }

}

// Fungsi untuk menambah tiket
void tambah(Tiket *data) {
    Penerbangan* new_tiket = new Penerbangan;

    cout << "Masukkan nama penerbangan: ";
    cin.ignore();
    getline(cin, new_tiket->nama_penerbangan);
    cout << "Masukkan tujuan: ";
    getline(cin, new_tiket->tujuan);
    cout << "Masukkan waktu keberangkatan: ";
    getline(cin, new_tiket->waktu);
    cout << "Masukkan harga tiket: ";
    cin >> new_tiket->harga;

    new_tiket->next = nullptr;
    new_tiket->prev = nullptr;

    if (data->head == nullptr) {
        data->head = new_tiket;
        data->tail = new_tiket;
    } else {
        data->tail->next = new_tiket;
        new_tiket->prev = data->tail;
        data->tail = new_tiket;
    }

    data->banyak_tiket++;
}

// Fungsi untuk mengubah tiket
void ubah(Tiket *data, int *nomor) {
    if (data->banyak_tiket == 0) {
        cout << "Daftar tiket kosong" << endl;
        return;
    }

    Penerbangan* current = data->head;
    int index = 1;
    while (current != nullptr && index < *nomor) {
        current = current->next;
        index++;
    }

    if (current == nullptr) {
        cout << "Tiket tidak ditemukan" << endl;
        return;
    }

    cout << "Masukkan nama penerbangan baru: ";
    cin.ignore();
    getline(cin, current->nama_penerbangan);
    cout << "Masukkan tujuan baru: ";
    getline(cin, current->tujuan);
    cout << "Masukkan waktu keberangkatan baru: ";
    getline(cin, current->waktu);
    cout << "Masukkan harga tiket baru: ";
    cin >> current->harga;
}

// Fungsi untuk menghapus tiket
void hapus(Tiket *data, int *nomor) {
    if (data->banyak_tiket == 0) {
        cout << "Daftar tiket kosong" << endl;
        return;
    }

    Penerbangan* current = data->head;
    int index = 1;
    while (current != nullptr && index < *nomor) {
        current = current->next;
        index++;
    }

    if (current == nullptr) {
        cout << "Tiket tidak ditemukan" << endl;
        return;
    }

    if (current == data->head) {
        data->head = current->next;
        if (data->head != nullptr) {
            data->head->prev = nullptr;
        }
    } else if (current == data->tail) {
        data->tail = current->prev;
        if (data->tail != nullptr) {
            data->tail->next = nullptr;
        }
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    delete current;
    data->banyak_tiket--;
}
