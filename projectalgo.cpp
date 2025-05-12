#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
// coba lagi ini percobaan ke 2
struct Lokasi
{
    string kota;
    string negara;
};

struct Waktu
{
    int jam;
    int menit;
};
// ini ke 3

struct Cuaca
{
    string tanggal;
    float suhu;
    string kondisi;
    Lokasi lokasi;
    Waktu waktu;
};

Cuaca data_cuaca[100] = {}; // Inisialisasi array dengan nilai default
int jumlah_data = 0;

void tampilkan_menu();
void masukkan_data();
void lihat_data();
float cariSuhuMaksimum(int n);
void lihat_suhu_maksimum();
void cariCuacaBerdasarkanTanggal(string tanggal);
void urutkanBerdasarkanSuhu();

int main()
{
    while (true)
    {
        tampilkan_menu();
        int pilihan;
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            masukkan_data();
            break;
        case 2:
            lihat_data();
            break;
        case 3:
            lihat_suhu_maksimum();
            break;
        case 4:
        {
            string tanggal_cari;
            cout << "Masukkan tanggal yang ingin dicari (YYYY-MM-DD): ";
            cin >> tanggal_cari;
            cariCuacaBerdasarkanTanggal(tanggal_cari);
            break;
        }
        case 5:
            urutkanBerdasarkanSuhu();
            break;
        case 6:
            cout << "Keluar dari program..." << endl;
            return 0;
        default:
            cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    }
}

void tampilkan_menu()
{
    cout << "\n=== Menu Cuaca ===" << endl;
    cout << "1. Masukkan Data Cuaca" << endl;
    cout << "2. Lihat Data Cuaca" << endl;
    cout << "3. Cari Suhu Maksimum" << endl;
    cout << "4. Cari Data Berdasarkan Tanggal" << endl;
    cout << "5. Urutkan Data Berdasarkan Suhu (Insertion Sort)" << endl;
    cout << "6. Keluar" << endl;
}

void masukkan_data()
{
    if (jumlah_data < 100)
    {
        cout << "Masukkan nama kota: ";
        getline(cin, data_cuaca[jumlah_data].lokasi.kota);
        cout << "Masukkan nama negara: ";
        getline(cin, data_cuaca[jumlah_data].lokasi.negara);

        cout << "Masukkan tanggal (YYYY-MM-DD): ";
        cin >> data_cuaca[jumlah_data].tanggal;
        cout << "Masukkan suhu (°C): ";
        cin >> data_cuaca[jumlah_data].suhu;
        cin.ignore(); // Bersihkan buffer

        cout << "Masukkan kondisi cuaca (Cerah/Hujan/Berawan): ";
        getline(cin, data_cuaca[jumlah_data].kondisi);

        cout << "Masukkan waktu pengamatan (Jam 0-23): ";
        cin >> data_cuaca[jumlah_data].waktu.jam;
        cout << "Masukkan waktu pengamatan (Menit 0-59): ";
        cin >> data_cuaca[jumlah_data].waktu.menit;

        jumlah_data++;
        cout << "Data cuaca berhasil disimpan!" << endl;
    }
    else
    {
        cout << "Penyimpanan penuh, tidak bisa menambahkan data lagi." << endl;
    }
}

void lihat_data()
{
    cout << "\n=== Data Cuaca ===" << endl;
    if (jumlah_data == 0)
    {
        cout << "Tidak ada data yang tersimpan." << endl;
    }
    else
    {
        cout << left << setw(15) << "Lokasi"
             << setw(15) << "Negara"
             << setw(15) << "Tanggal"
             << setw(10) << "Suhu"
             << setw(15) << "Kondisi"
             << "Waktu" << endl;
        cout << string(75, '-') << endl;
        for (int i = 0; i < jumlah_data; i++)
        {
            cout << left << setw(15) << data_cuaca[i].lokasi.kota
                 << setw(15) << data_cuaca[i].lokasi.negara
                 << setw(15) << data_cuaca[i].tanggal
                 << setw(10) << data_cuaca[i].suhu
                 << setw(15) << data_cuaca[i].kondisi
                 << setw(2) << setfill('0') << data_cuaca[i].waktu.jam << ":"
                 << setw(2) << data_cuaca[i].waktu.menit << setfill(' ') << endl;
        }
    }
}

float cariSuhuMaksimum(int n)
{
    if (n == 1)
        return data_cuaca[0].suhu;
    return max(data_cuaca[n - 1].suhu, cariSuhuMaksimum(n - 1));
}

void lihat_suhu_maksimum()
{
    if (jumlah_data == 0)
    {
        cout << "Tidak ada data untuk dihitung." << endl;
    }
    else
    {
        float suhu_maks = cariSuhuMaksimum(jumlah_data);
        cout << "\n=== Suhu Maksimum ===" << endl;
        cout << left << setw(15) << "Lokasi"
             << setw(15) << "Negara"
             << setw(15) << "Tanggal"
             << setw(10) << "Suhu (°C)"
             << setw(15) << "Kondisi"
             << "Waktu" << endl;
        cout << string(75, '-') << endl;
        for (int i = 0; i < jumlah_data; i++)
        {
            if (data_cuaca[i].suhu == suhu_maks)
            {
                cout << left << setw(15) << data_cuaca[i].lokasi.kota
                     << setw(15) << data_cuaca[i].lokasi.negara
                     << setw(15) << data_cuaca[i].tanggal
                     << setw(10) << data_cuaca[i].suhu
                     << setw(15) << data_cuaca[i].kondisi
                     << setw(2) << setfill('0') << data_cuaca[i].waktu.jam << ":"
                     << setw(2) << data_cuaca[i].waktu.menit << setfill(' ') << endl;
            }
        }
    }
}

void cariCuacaBerdasarkanTanggal(string tanggal)
{
    bool ditemukan = false;
    cout << "\n=== Data Cuaca pada " << tanggal << " ===" << endl;
    cout << left << setw(15) << "Lokasi"
         << setw(15) << "Negara"
         << setw(15) << "Tanggal"
         << setw(10) << "Suhu (°C)"
         << setw(15) << "Kondisi"
         << "Waktu" << endl;
    cout << string(75, '-') << endl;

    for (int i = 0; i < jumlah_data; i++)
    {
        if (data_cuaca[i].tanggal == tanggal)
        {
            cout << left << setw(15) << data_cuaca[i].lokasi.kota
                 << setw(15) << data_cuaca[i].lokasi.negara
                 << setw(15) << data_cuaca[i].tanggal
                 << setw(10) << data_cuaca[i].suhu
                 << setw(15) << data_cuaca[i].kondisi
                 << setw(2) << setfill('0') << data_cuaca[i].waktu.jam << ":"
                 << setw(2) << data_cuaca[i].waktu.menit << setfill(' ') << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan)
    {
        cout << "Data tidak ditemukan!" << endl;
    }
}

void urutkanBerdasarkanSuhu()
{
    if (jumlah_data == 0)
    {
        cout << "Tidak ada data untuk diurutkan." << endl;
        return;
    }

    // Insertion Sort
    for (int i = 1; i < jumlah_data; i++)
    {
        Cuaca key = data_cuaca[i];
        int j = i - 1;

        while (j >= 0 && data_cuaca[j].suhu > key.suhu)
        {
            data_cuaca[j + 1] = data_cuaca[j];
            j--;
        }
        data_cuaca[j + 1] = key;
    }

    cout << "\n=== Data Cuaca Setelah Diurutkan (Suhu Ascending) ===" << endl;
    cout << left << setw(15) << "Lokasi"
         << setw(15) << "Negara"
         << setw(15) << "Tanggal"
         << setw(10) << "Suhu"
         << setw(15) << "Kondisi"
         << "Waktu" << endl;
    cout << string(75, '-') << endl;
    for (int i = 0; i < jumlah_data; i++)
    {
        cout << left << setw(15) << data_cuaca[i].lokasi.kota
             << setw(15) << data_cuaca[i].lokasi.negara
             << setw(15) << data_cuaca[i].tanggal
             << setw(10) << data_cuaca[i].suhu
             << setw(15) << data_cuaca[i].kondisi
             << setw(2) << setfill('0') << data_cuaca[i].waktu.jam << ":"
             << setw(2) << data_cuaca[i].waktu.menit << setfill(' ') << endl;
    }
}
