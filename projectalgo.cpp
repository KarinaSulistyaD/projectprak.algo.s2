#include <iostream>
#include <iomanip>
#include <string>
#include <fstream> // Untuk operasi file
#include <windows.h> // Untuk fungsi Sleep()

using namespace std;

struct Lokasi {
    string *kota;
    string *negara;
};

struct Waktu {
    int *jam;
    int *menit;
};

struct Cuaca {
    string tanggal;
    float suhu;
    string kondisi;
    Lokasi lokasi;
    Waktu waktu;
};

Cuaca data_cuaca[100];
int jumlah_data = 0;

// Fungsi deklarasi
void tampilkan_menu();
void masukkan_data();
void lihat_data();
void menuCariData();
void menuSorting();
void simpanKeFile();
void bacaDariFile();
void animasiLoading(const string& pesan, int durasi = 3);
void animasiMemulaiProgram();

// Fungsi urutan dan pencarian
void bubbleSortTanggal();
int binarySearchTanggal(string tanggal);
void linearSearchSuhuMaksimum();
void insertionSortKota();
void selectionSortNegara();
int partitionSuhu(int low, int high);
void quickSortSuhu(int low, int high);
int jumpSearchKota(string kota);
void linearSearchNegara(string negara);
void linearSearchKondisi(string kondisi);

void tampilkan_header() {
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl; // Garis atas tabel
    cout << left << "| " << setw(15) << "Lokasi"
         << "| " << setw(15) << "Negara"
         << "| " << setw(15) << "Tanggal"
         << "| " << setw(8) << "Suhu (°C)"
         << "| " << setw(10) << "Kondisi"
         << "| " << setw(5) << "Waktu" << " |" << endl;
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl; // Garis bawah header
}

void tampilkan_data(const Cuaca& data) {
    cout << left << "| " << setw(15) << *data.lokasi.kota
         << "| " << setw(15) << *data.lokasi.negara
         << "| " << setw(15) << data.tanggal
         << "| " << setw(10) << fixed << setprecision(1) << data.suhu
         << "| " << setw(10) << data.kondisi
         << "| " << setw(2) << setfill('0') << *data.waktu.jam << ":"
         << setw(2) << *data.waktu.menit << setfill(' ') << " |" << endl;
}

void tampilkan_footer() {
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl; // Garis bawah tabel
}

// Fungsi untuk memberikan efek animasi loading
void animasiLoading(const string& pesan, int durasi) {
    cout << pesan;
    for (int i = 0; i < durasi; ++i) {
        cout << ".";
        cout.flush();
        Sleep(500); // Jeda 500ms
    }
    cout << endl;
}

// Fungsi untuk memberikan animasi saat memulai program
void animasiMemulaiProgram() {
    cout << "Memulai program";
    for (int i = 0; i < 5; ++i) { // Animasi titik-titik
        cout << ".";
        cout.flush();
        Sleep(500); // Jeda 500ms
    }
    cout << "\nProgram siap digunakan!\n";
}

// Fungsi untuk menyimpan data ke file
void simpanKeFile() {
    ofstream file("data_cuaca.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menyimpan data.\n";
        return;
    }

    for (int i = 0; i < jumlah_data; ++i) {
        file << *data_cuaca[i].lokasi.kota << ";"
             << *data_cuaca[i].lokasi.negara << ";"
             << data_cuaca[i].tanggal << ";"
             << data_cuaca[i].suhu << ";"
             << data_cuaca[i].kondisi << ";"
             << *data_cuaca[i].waktu.jam << ";"
             << *data_cuaca[i].waktu.menit << "\n";
    }
    file.close();
    animasiLoading("Menyimpan data ke file", 3);
    cout << "Data berhasil disimpan ke file.\n";
}

// Fungsi untuk membaca data dari file
void bacaDariFile() {
    ifstream file("data_cuaca.txt");
    if (!file.is_open()) {
        cout << "File data_cuaca.txt tidak ditemukan. Data akan dibuat baru.\n";
        return;
    }

    jumlah_data = 0;
    while (!file.eof()) {
        Cuaca cuaca;
        cuaca.lokasi.kota = new string;
        cuaca.lokasi.negara = new string;
        cuaca.waktu.jam = new int;
        cuaca.waktu.menit = new int;

        getline(file, *cuaca.lokasi.kota, ';');
        if (file.eof()) break;
        getline(file, *cuaca.lokasi.negara, ';');
        getline(file, cuaca.tanggal, ';');
        file >> cuaca.suhu;
        file.ignore();
        getline(file, cuaca.kondisi, ';');
        file >> *cuaca.waktu.jam;
        file.ignore();
        file >> *cuaca.waktu.menit;
        file.ignore();

        data_cuaca[jumlah_data++] = cuaca;
    }
    file.close();
    animasiLoading("Memuat data dari file", 3);
    cout << "Data berhasil dimuat dari file.\n";
}

int main() {
    animasiMemulaiProgram(); // Menampilkan animasi saat program dimulai
    cout << "PERINGATAN: Jangan keluar dari program secara paksa (misalnya dengan menutup jendela)\n";
    cout << "Gunakan menu '0. Keluar' untuk memastikan database tersimpan dengan benar.\n";
    system("pause"); // Tunggu pengguna membaca peringatan
    bacaDariFile(); // Memuat data dari file saat program dimulai

    while (true) {
        system("cls"); // Bersihkan layar sebelum menampilkan menu utama
        tampilkan_menu();
        int pilihan;
        cout << "Pilih menu (0-4): ";
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer input

        switch (pilihan) {
            case 1:
                masukkan_data();
                break;
            case 2:
                lihat_data();
                break;
            case 3:
                menuCariData();
                break;
            case 4: // Menu Sorting
                menuSorting();
                break;
            case 0:
                cout << "Menyimpan data sebelum keluar...\n";
                simpanKeFile(); // Simpan data ke file sebelum keluar
                cout << "Keluar dari program..." << endl;
                for (int i = 0; i < jumlah_data; ++i) {
                    delete data_cuaca[i].lokasi.kota;
                    delete data_cuaca[i].lokasi.negara;
                    delete data_cuaca[i].waktu.jam;
                    delete data_cuaca[i].waktu.menit;
                }
                return 0;
            default:
                cout << "Pilihan tidak valid.\n";
        }

    }
}

void tampilkan_menu() {
    cout << "\n=== Menu Cuaca ===" << endl;
    cout << "1. Masukkan Data Cuaca" << endl;
    cout << "2. Lihat Data Cuaca" << endl;
    cout << "3. Cari Data" << endl;
    cout << "4. Sorting Data Cuaca" << endl; // Menu Sorting tetap di nomor 4
    cout << "0. Keluar" << endl; // Simpan data dilakukan saat keluar
}

void masukkan_data() {
    system("cls"); // Bersihkan layar sebelum memasukkan data
    if (jumlah_data < 100) {
        data_cuaca[jumlah_data].lokasi.kota = new string;
        data_cuaca[jumlah_data].lokasi.negara = new string;
        data_cuaca[jumlah_data].waktu.jam = new int;
        data_cuaca[jumlah_data].waktu.menit = new int;

        cout << "Masukkan nama kota: ";
        getline(cin, *data_cuaca[jumlah_data].lokasi.kota);
        cout << "Masukkan nama negara: ";
        getline(cin, *data_cuaca[jumlah_data].lokasi.negara);
        cout << "Masukkan tanggal (YYYY-MM-DD): ";
        cin >> data_cuaca[jumlah_data].tanggal;
        cout << "Masukkan suhu (°C): ";
        cin >> data_cuaca[jumlah_data].suhu;
        cin.ignore();
        cout << "Masukkan kondisi cuaca (Cerah/Berawan/Hujan): ";
        getline(cin, data_cuaca[jumlah_data].kondisi);
        cout << "Masukkan jam (0-23): ";
        cin >> *data_cuaca[jumlah_data].waktu.jam;
        cout << "Masukkan menit (0-59): ";
        cin >> *data_cuaca[jumlah_data].waktu.menit;
        cin.ignore();
        jumlah_data++;
        animasiLoading("Menyimpan data", 3); // Animasi saat menyimpan data
        cout << "Data berhasil ditambahkan.\n";
        system("pause"); // Tunggu pengguna sebelum kembali ke menu
    } else {
        animasiLoading("Data penuh", 2); // Animasi jika data penuh
        cout << "Data penuh!\n";
        system("pause"); // Tunggu pengguna sebelum kembali ke menu
    }
}

void lihat_data() {
    system("cls"); // Bersihkan layar sebelum menampilkan data
    if (jumlah_data == 0) {
        animasiLoading("Memuat data", 2); // Animasi saat memuat data
        cout << "Tidak ada data cuaca.\n";
        system("pause"); // Tunggu pengguna sebelum kembali ke menu
        return;
    }

    animasiLoading("Menampilkan data cuaca", 3); // Animasi saat menampilkan data
    cout << "\n=== Data Cuaca ===" << endl;
    tampilkan_header();
    for (int i = 0; i < jumlah_data; ++i) {
        tampilkan_data(data_cuaca[i]);
    }
    tampilkan_footer(); // Tambahkan garis bawah tabel
    system("pause"); // Tunggu pengguna sebelum kembali ke menu
}

void menuCariData() {
    system("cls"); // Bersihkan layar sebelum menampilkan menu pencarian
    animasiLoading("Memuat menu pencarian", 2); // Animasi saat memuat menu pencarian
    int pilihan;
    cout << "\n=== Menu Cari Data ===\n";
    cout << "1. Cari berdasarkan Tanggal (Binary Search)\n";
    cout << "2. Cari Suhu Maksimum\n";
    cout << "3. Cari berdasarkan Kota (Jump Search)\n";
    cout << "4. Cari berdasarkan Negara (Linear Search)\n";
    cout << "5. Cari berdasarkan Kondisi (Linear Search)\n";
    cout << "6. Kembali\n";
    cout << "Pilih: ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan) {
        case 1: {
            string tgl;
            bubbleSortTanggal();
            cout << "Masukkan tanggal yang dicari: ";
            getline(cin, tgl);
            animasiLoading("Mencari data berdasarkan tanggal", 3); // Animasi saat mencari data
            int idx = binarySearchTanggal(tgl);
            if (idx != -1) {
                system("cls"); // Bersihkan layar sebelum menampilkan hasil pencarian
                cout << "\n=== Hasil Pencarian (Binary Search) ===" << endl;
                tampilkan_header();
                tampilkan_data(data_cuaca[idx]);
                tampilkan_footer();
            } else {
                cout << "Tanggal tidak ditemukan.\n";
            }
            system("pause"); // Tunggu pengguna sebelum kembali ke menu
            break;
        }
        case 2: {
            system("cls"); // Bersihkan layar sebelum menampilkan hasil pencarian
            animasiLoading("Mencari suhu maksimum", 3); // Animasi saat mencari suhu maksimum
            linearSearchSuhuMaksimum();
            system("pause"); // Tunggu pengguna sebelum kembali ke menu
            break;
        }
        case 3: {
            string kota;
            insertionSortKota();
            cout << "Masukkan kota yang dicari: ";
            getline(cin, kota);
            animasiLoading("Mencari data berdasarkan kota", 3); // Animasi saat mencari data
            int idx = jumpSearchKota(kota);
            if (idx != -1) {
                system("cls"); // Bersihkan layar sebelum menampilkan hasil pencarian
                cout << "\n=== Hasil Pencarian (Jump Search) ===" << endl;
                tampilkan_header();
                tampilkan_data(data_cuaca[idx]);
                tampilkan_footer();
            } else {
                cout << "Kota tidak ditemukan.\n";
            }
            system("pause"); // Tunggu pengguna sebelum kembali ke menu
            break;
        }
        case 4: {
            string negara;
            cout << "Masukkan negara yang dicari: ";
            getline(cin, negara);
            system("cls"); // Bersihkan layar sebelum menampilkan hasil pencarian
            animasiLoading("Mencari data berdasarkan negara", 3); // Animasi saat mencari data
            linearSearchNegara(negara);
            system("pause"); // Tunggu pengguna sebelum kembali ke menu
            break;
        }
        case 5: {
            string kondisi;
            cout << "Masukkan kondisi cuaca yang dicari: ";
            getline(cin, kondisi);
            system("cls"); // Bersihkan layar sebelum menampilkan hasil pencarian
            animasiLoading("Mencari data berdasarkan kondisi", 3); // Animasi saat mencari data
            linearSearchKondisi(kondisi);
            system("pause"); // Tunggu pengguna sebelum kembali ke menu
            break;
        }
        case 6:
            return;
        default:
            cout << "Pilihan tidak valid.\n";
            system("pause"); // Tunggu pengguna sebelum kembali ke menu
    }
}

void menuSorting() {
    system("cls"); // Bersihkan layar sebelum menampilkan menu sorting
    animasiLoading("Memuat menu sorting", 2); // Animasi saat memuat menu sorting
    int pilihan;
    do {
        cout << "\n=== Menu Sorting Data Cuaca ===\n";
        cout << "1. Sort berdasarkan Kota (Insertion Sort)\n";
        cout << "2. Sort berdasarkan Negara (Selection Sort)\n";
        cout << "3. Sort berdasarkan Tanggal (Bubble Sort)\n";
        cout << "4. Sort berdasarkan Suhu (Quick Sort)\n";
        cout << "5. Kembali ke menu utama\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                system("cls"); // Bersihkan layar sebelum menampilkan hasil sorting
                animasiLoading("Mengurutkan data berdasarkan kota", 3); // Animasi saat sorting
                insertionSortKota();
                cout << "\nData berhasil diurutkan berdasarkan Kota (Insertion Sort)\n";
                lihat_data();
                break;
            case 2:
                system("cls"); // Bersihkan layar sebelum menampilkan hasil sorting
                animasiLoading("Mengurutkan data berdasarkan negara", 3); // Animasi saat sorting
                selectionSortNegara();
                cout << "\nData berhasil diurutkan berdasarkan Negara (Selection Sort)\n";
                lihat_data();
                break;
            case 3:
                system("cls"); // Bersihkan layar sebelum menampilkan hasil sorting
                animasiLoading("Mengurutkan data berdasarkan tanggal", 3); // Animasi saat sorting
                bubbleSortTanggal();
                cout << "\nData berhasil diurutkan berdasarkan Tanggal (Bubble Sort)\n";
                lihat_data();
                break;
            case 4:
                system("cls"); // Bersihkan layar sebelum menampilkan hasil sorting
                animasiLoading("Mengurutkan data berdasarkan suhu", 3); // Animasi saat sorting
                quickSortSuhu(0, jumlah_data - 1);
                cout << "\nData berhasil diurutkan berdasarkan Suhu (Quick Sort)\n";
                lihat_data();
                break;
            case 5:
                cout << "Kembali ke menu utama...\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                system("pause"); // Tunggu pengguna sebelum kembali ke menu
        }
    } while (pilihan != 5);
}

void bubbleSortTanggal() {
    for (int i = 0; i < jumlah_data - 1; ++i) {
        for (int j = 0; j < jumlah_data - i - 1; ++j) {
            if (data_cuaca[j].tanggal > data_cuaca[j + 1].tanggal) {
                swap(data_cuaca[j], data_cuaca[j + 1]);
            }
        }
    }
}

int binarySearchTanggal(string tanggal) {
    int low = 0, high = jumlah_data - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (data_cuaca[mid].tanggal == tanggal) {
            return mid;
        } else if (data_cuaca[mid].tanggal < tanggal) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

void linearSearchSuhuMaksimum() {
    if (jumlah_data > 0) {
        float suhu_maks = -99999.0f;
        int index_maks = -1;
        for (int i = 0; i < jumlah_data; ++i) {
            if (data_cuaca[i].suhu > suhu_maks) {
                suhu_maks = data_cuaca[i].suhu;
                index_maks = i;
            }
        }
        cout << "\n=== Suhu Maksimum (Linear Search) ===" << endl;
        tampilkan_header();
        tampilkan_data(data_cuaca[index_maks]);
        tampilkan_footer();
    } else {
        cout << "Belum ada data cuaca yang dimasukkan.\n";
    }
}

void insertionSortKota() {
    for (int i = 1; i < jumlah_data; ++i) {
        Cuaca key = data_cuaca[i];
        int j = i - 1;
        while (j >= 0 && *data_cuaca[j].lokasi.kota > *key.lokasi.kota) {
            data_cuaca[j + 1] = data_cuaca[j];
            j--;
        }
        data_cuaca[j + 1] = key;
    }
}

void selectionSortNegara() {
    for (int i = 0; i < jumlah_data - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < jumlah_data; ++j) {
            if (*data_cuaca[j].lokasi.negara < *data_cuaca[min_idx].lokasi.negara) {
                min_idx = j;
            }
        }
        swap(data_cuaca[i], data_cuaca[min_idx]);
    }
}

int partitionSuhu(int low, int high) {
    float pivot = data_cuaca[high].suhu;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (data_cuaca[j].suhu < pivot) {
            i++;
            swap(data_cuaca[i], data_cuaca[j]);
        }
    }

    swap(data_cuaca[i + 1], data_cuaca[high]);
    return i + 1;
}

void quickSortSuhu(int low, int high) {
    if (low < high) {
        int pi = partitionSuhu(low, high);
        quickSortSuhu(low, pi - 1);
        quickSortSuhu(pi + 1, high);
    }
}

int jumpSearchKota(string kota) {
    int n = jumlah_data;
    int step = 1;
    while (step * step < n) {
        step++;
    }
    step--;

    int prev = 0;
    while (step < n && *data_cuaca[step].lokasi.kota < kota) {
        prev = step;
        step += step;
        if (prev >= n) return -1;
    }

    for (int i = prev; i < (step < n ? step + 1 : n); i++) {
        if (*data_cuaca[i].lokasi.kota == kota) {
            return i;
        }
    }
    return -1;
}

void linearSearchNegara(string negara) {
    bool found = false;
    cout << "\n=== Hasil Pencarian (Linear Search) Berdasarkan Negara ===" << endl;
    tampilkan_header();
    for (int i = 0; i < jumlah_data; ++i) {
        if (*data_cuaca[i].lokasi.negara == negara) {
            tampilkan_data(data_cuaca[i]);
            found = true;
        }
    }
    if (!found) {
        cout << "| " << setw(87) << "Data dengan negara tersebut tidak ditemukan." << " |" << endl;
    }
    tampilkan_footer(); // Tambahkan garis bawah tabel
    system("pause"); // Tunggu pengguna sebelum kembali ke menu
}

void linearSearchKondisi(string kondisi) {
    bool found = false;
    cout << "\n=== Hasil Pencarian (Linear Search) Berdasarkan Kondisi ===" << endl;
    tampilkan_header();
    for (int i = 0; i < jumlah_data; ++i) {
        if (data_cuaca[i].kondisi == kondisi) {
            tampilkan_data(data_cuaca[i]);
            found = true;
        }
    }
    if (!found) {
        cout << "| " << setw(87) << "Data dengan kondisi cuaca tersebut tidak ditemukan." << " |" << endl;
    }
    tampilkan_footer(); // Tambahkan garis bawah tabel
    system("pause"); // Tunggu pengguna sebelum kembali ke menu
}