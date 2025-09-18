#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* index_nilai(float nilai) {   // awalnya: index_nilai(nilai) → tidak ada tipe parameter
    if (nilai >= 86.0f) {
        return "A";
    } else if (nilai >= 76.0f) {
        return "AB";
    } else if (nilai >= 66.0f) {
        return "B";
    } else if (nilai >= 61.0f) {
        return "BC";
    } else if (nilai >= 56.0f) {
        return "C";
    } else if (nilai >= 41.0f) {
        return "D";
    } else {
        return "E";
    }
}

float kalkulasi_ip(const float *matkul, const int *sks, int n) { 
    // awalnya: float kalkulasi_ip(*matkul, int *sks, int n) → parameter *matkul tidak ada tipenya
    float totalNilai = 0.0f;   // awalnya: variabel ini tidak pernah dideklarasikan
    int totalSKS = 0;          // awalnya: variabel ini juga tidak ada

    for (int i = 0; i < n; i++) {
        totalNilai += matkul[i] * sks[i];
        totalSKS += sks[i];
    }

    if (totalSKS == 0) return 0.0f; // awalnya tidak ada proteksi, bisa bagi nol
    return totalNilai / totalSKS; 
}

int main(void) {
    char nama[100];
    char NRP[20];   // awalnya: NRP pakai int, hasil print bisa salah (5022251114 → 727283818)
    int umur = 0;   // awalnya: umur dipakai di scanf tapi belum dideklarasikan

    printf("Masukkan nama: ");
    fgets(nama, sizeof(nama), stdin);
    size_t len = strlen(nama);
    if (len > 0 && nama[len - 1] == '\n') nama[len - 1] = '\0'; // awalnya newline dari fgets tidak dihapus

    printf("Umur: ");
    scanf("%d", &umur);

    printf("NRP: ");
    scanf("%s", NRP);   // awalnya: scanf("%d", &NRP) → salah format specifier, bikin angka aneh

    int n = 0;
    printf("Jumlah matkul semester ini: ");
    scanf("%d", &n);

    float *matkul = malloc(n * sizeof(float)); // awalnya: malloc(n * sizeof(int)) untuk float (salah ukuran)
    int *sks = malloc(n * sizeof(int));
    if (!matkul || !sks) return 1;

    for (int i = 0; i < n; i++) {
        printf("Masukkan nilai matkul %d: ", i + 1);
        scanf("%f", &matkul[i]);   // awalnya: format specifier salah (%d atau %lf)

        printf("Masukkan SKS matkul %d: ", i + 1);
        scanf("%d", &sks[i]);

        if (matkul[i] < 0.0f || sks[i] < 0) { // awalnya: pakai (matkul[i] < 0 && sks[i] < 0)
            printf("Nilai/SKS tidak boleh negatif. Menghentikan input.\n");
            free(matkul);
            free(sks);
            return 1;
        }
    }

    printf("\nNama: %s\n", nama);
    printf("Umur: %d\n", umur);
    printf("NRP: %s\n\n", NRP); // awalnya: printf("%d", NRP) → salah, NRP string bukan int

    for (int j = 0; j < n; j++) {
        printf("Matkul %d: nilai = %.2f, SKS = %d, indeks = %s\n",
               j + 1, matkul[j], sks[j], index_nilai(matkul[j]));
    }

    float ip = kalkulasi_ip(matkul, sks, n);
    printf("\nIndeks Prestasi (IP): %.2f (%s)\n", ip, index_nilai(ip));

    free(matkul);
    free(sks);
    return 0;
}
