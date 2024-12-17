#include <stdio.h>
#include <string.h>

#define MAX_KELIMELER 1000 // words.txt dosyasındaki maksimum kelime sayısı.
#define MAX_UZUNLUK 50   // Kelimelerin maksimum uzunluğu.

// İki kelime arasındaki benzerlik oranını hesaplayan fonksiyon.
double similar_text(const char *kelime1, const char *kelime2) {
    int eslesme = 0;
    int uzunluk1 = strlen(kelime1);
    int uzunluk2 = strlen(kelime2);
    int min_uzunluk = uzunluk1 < uzunluk2 ? uzunluk1 : uzunluk2;

    // Karakter eşleşmelerini sayar.
    for (int i = 0; i < min_uzunluk; i++) {
        if (kelime1[i] == kelime2[i]) {
            eslesme++;
        }
    }

    // Benzerlik oranını döndürür.
    return (double)eslesme / (uzunluk1 > uzunluk2 ? uzunluk1 : uzunluk2);
}

int main() {
    char kelimeler[MAX_KELIMELER][MAX_UZUNLUK];
    int kelime_sayisi = 0;
    char giris[50];
    FILE *dosya = fopen("words", "r");

    if (!dosya) { //Dosyanın açılıp açılmadığını kontrol eder.
        printf("words dosyası açılamadı!\n");
        return 1; //Programı sonlandırır.
    }

    // words dosyasındaki kelimeleri okur.
    while (fscanf(dosya, "%s", kelimeler[kelime_sayisi]) != EOF) {
        kelime_sayisi++;
    }
    fclose(dosya);

    // Kullanıcıdan giriş alır.
    printf("search: ");
    scanf("%s", giris);

    char en_uygun[MAX_UZUNLUK];
    double en_iyi_benzerlik = 0.0;

    // Kelimelerle karşılaştırma yapar.
    for (int i = 0; i < kelime_sayisi; i++) {
        double benzerlik = similar_text(giris, kelimeler[i]);
        if (benzerlik > en_iyi_benzerlik) {
            en_iyi_benzerlik = benzerlik;
            strcpy(en_uygun, kelimeler[i]);
        }
    }

    // Sonucu yazdırır.
    if (  en_iyi_benzerlik >= 0.5 && en_iyi_benzerlik<1) {
        printf("Did you mean ?: %s (%.2f)\n", en_uygun, en_iyi_benzerlik);
    }
  else if(en_iyi_benzerlik==1) {
    printf("%s(%.2f)\n", en_uygun, en_iyi_benzerlik);
}

    else if (en_iyi_benzerlik<0.5) {
        printf("Eşleşme bulunamadı (No matching).\n");
    }

return 0;
}