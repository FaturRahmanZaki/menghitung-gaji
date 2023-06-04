#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Menghitung Pajak (PPH21)
int hitungPPH21Tahunan(float gaji_kena_pajak)//100jt
{
    int pph21_tahunan = 0;

    if (gaji_kena_pajak < 0){
        return pph21_tahunan;
    }

    if (gaji_kena_pajak > 60000000)
    {
        pph21_tahunan += 60000000 *0.05;
        gaji_kena_pajak -= 60000000;
    }
    else
    {
        pph21_tahunan += gaji_kena_pajak *0.05;
        return pph21_tahunan;
    }

    if (gaji_kena_pajak > 250000000)
    {
        pph21_tahunan += 250000000 *0.15;
        gaji_kena_pajak -= 250000000;
    }
    else
    {
        pph21_tahunan += gaji_kena_pajak *0.15;
        return pph21_tahunan;
    }

    if (gaji_kena_pajak > 500000000)
    {
        pph21_tahunan = 500000000 *0.25;
        gaji_kena_pajak -= 500000000;
    }
    else
    {
        pph21_tahunan += gaji_kena_pajak *0.25;
        return pph21_tahunan;
    }

    return pph21_tahunan;

}

//Menghitung Jam Lembur


float hitungLembur(int lama_kerja, float gaji_per_jam)
{
    if (lama_kerja > 155)
    {
        return (float)(lama_kerja-155)*gaji_per_jam;
    }

    return 0;
}


float hitungGaji(int lama_kerja, float gaji_pokok, float gaji_per_jam)
{
    if (lama_kerja >= 155)
    {
        return gaji_pokok;
    }

    return (gaji_per_jam*lama_kerja);
}

int main()
{
    // Deklarasi variabel
    char nama_pt[50] = "Arya Duta";
    char nama[50];
    char* jabatan;
    int golongan,lama_kerja,tunjangan_konsumsi ;
    float gaji_pokok, lembur,gaji_per_jam, gaji_tanpa_lembur, gaji_bersih;
    float gaji_dipotong_jabatan, gaji_bersih_setahun,gaji_kena_pajak, pph21_setahun, pph21_sebulan;
    float potongan_bpjs,total_jaminan_pensiun;
    float gaji_setelah_bpjs;
    int pilihan = 1;
    int lama_lembur;


    tunjangan_konsumsi = 450000.00;

    while (pilihan !=0) {


    printf("****************** Payrol Arya Duta ******************\n", nama_pt);
    printf("======================================================\n");
    // Input data karyawan
    printf("Masukkan Nama Karyawan                  : ");
    scanf("%[^\n]", nama);
    printf("Masukkan Golongan (1-7)                 : ");
    scanf("%d", &golongan);
    printf("Masukkan Jumlah Jam Kerja (1 bulan/jam) : ");
    scanf("%d", &lama_kerja);
    printf("\n\n");
    printf("======================================================\n");


    // Hitung gaji pokok
    switch (golongan)
    {
    case 1:
        jabatan = "Room Attendant";
        gaji_pokok = 4000000;
        gaji_per_jam = 4000;

        break;
    case 2:
        jabatan = "Housekeeping Supervisor";
        gaji_pokok = 5000000;
        gaji_per_jam = 5000;

        break;
    case 3:

        jabatan = "Assistant Housekeeper";
        gaji_pokok = 8000000;
        gaji_per_jam = 8000;

        break;
    case 4:
        jabatan = "Executive Housekeeper";
        gaji_pokok = 10000000;
        gaji_per_jam = 10000;

        break;
    case 5:
        jabatan = "Human Resource Department";
        gaji_pokok = 20000000;
        gaji_per_jam = 20000;

        break;
    case 6:
        jabatan = "General Manager";
        gaji_pokok = 30000000;
        gaji_per_jam = 30000;

        break;
    case 7:
        jabatan = "Direktur";
        gaji_pokok = 100000000;
        gaji_per_jam = 100000;
        break;

    default:

        printf("Golongan yang dimasukkan tidak valid.\n");
        return 0;

    }
    //Menentukan tanggal
    srand(time(NULL));

    // Menghasilkan nomor acak antara 1 hingga 12 untuk bulan
    int month = rand() % 12 + 1;

    // Mendapatkan waktu saat ini
    time_t now = time(NULL);

    // Mengonversi waktu ke dalam struktur tm
    struct tm *local = localtime(&now);

    // Mengatur bulan dan tanggal menjadi 1
    local->tm_mon = month - 1;  // Mengurangi 1 karena tm_mon dimulai dari 0
    local->tm_mday = 1;

    // Mengonversi waktu kembali ke bentuk time_t
    time_t modified_time = mktime(local);

    // Mengonversi waktu yang telah diubah ke dalam struktur tm
    struct tm *modified_local = localtime(&modified_time);

    // Mendapatkan tahun
    int year = modified_local->tm_year + 1900;  // Perlu ditambah 1900 karena tahun dimulai dari 1900

    //Mencari Gaji Bersih
    lembur = hitungLembur(lama_kerja,gaji_per_jam);
    gaji_tanpa_lembur = hitungGaji( lama_kerja,  gaji_pokok,  gaji_per_jam);
    gaji_dipotong_jabatan = (gaji_tanpa_lembur+lembur)- ((gaji_tanpa_lembur+lembur)*0.05); //gaji sebulan yang sudah dikurangin dengan biaya jabatan sebsar 5% dari total gaji

    gaji_bersih_setahun = gaji_dipotong_jabatan * 12;

    gaji_kena_pajak = gaji_bersih_setahun - 54000000;//ptkp
    pph21_setahun = hitungPPH21Tahunan(gaji_kena_pajak);
    pph21_sebulan = pph21_setahun / 12;
    potongan_bpjs = (gaji_tanpa_lembur + lembur) * 0.01;
    total_jaminan_pensiun = (gaji_tanpa_lembur + lembur) * 0.03;
    gaji_bersih = (gaji_tanpa_lembur + lembur+tunjangan_konsumsi) - pph21_sebulan - potongan_bpjs - total_jaminan_pensiun;
    lama_lembur = lama_kerja - 155;

    // Output gaji karyawan
    printf("******************************************************\n");
    printf("                   SLIP GAJI KARYAWAN                 \n");
    printf("******************************************************\n");
    printf("%s \n", nama_pt);
    printf("Jl Jendral Sudirman Kav 29\n");
    printf("Kuningan, DKI Jakarta");
    printf("         ");
    printf("Tanggal     :01/%02d/%d\n", month, year);
    printf("lama lembur : %djam\n,", lama_lembur);
    printf("******************************************************\n");
    printf("Nama        : %s \n", nama);
    printf("Jabatan     : %s \n", jabatan);
    printf("======================================================\n");
    printf("(+) \n");
    printf("Gaji Pokok                          : Rp. %.2f\n", gaji_tanpa_lembur);
    printf("Gaji Lembur                         : Rp. %.2f\n", lembur);
    printf("Tunjangan Konsumsi                  : Rp. %i\n", tunjangan_konsumsi);
    printf("(-) \n");
    printf("PPH21                               : Rp. %.2f\n", pph21_sebulan);
    printf("Potongan BPJS                       : Rp. %.2f\n", potongan_bpjs);
    printf("Jaminan Pensiun                     : Rp. %.2f\n", total_jaminan_pensiun);
    printf("======================================================\n");
    printf("Gaji bersih                         : Rp. %.2f\n", gaji_bersih);
    printf("======================================================\n\n");
    printf("Apakah Anda ingin menghitung gaji karyawan lain?\n");
    printf("1. Lanjutkan  (pilih angka 1 untuk mengulangi program)\n");
    printf("0. Keluar     (pilih angka 0 untuk keluar program)\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);
    printf("\n\n");
    system("clear");
    system("cls");
    getchar();
    }
    return 0;
}
