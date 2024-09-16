#include <iostream>
using namespace std;

// fungsi segitiga pascal
int segitiga_pascal(int tinggi, int kolom) {
    if (kolom == 1 || kolom == tinggi) {
        return 1;
    } else {
        return segitiga_pascal(tinggi - 1, kolom - 1) + segitiga_pascal(tinggi - 1, kolom);
    }
}

int main() {

    int tinggi;

    cout << "Tentukan tinggi segitiga: "; fflush(stdin);
    cin >> tinggi; fflush(stdin);
    cout << endl;

    
    cout << "Segitiga Pascal :" << endl;
    for (int i = 1; i <= tinggi; i++) {
        for (int j = 1; j <= i; j++) {
            cout << segitiga_pascal(i, j) << " ";
        }
        cout << endl;
    }
    
    return 0;
}