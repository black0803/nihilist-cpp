#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_TEXTSIZE 50
#define MAX_KEYSIZE 50

/// global variable declaration
char key[] = "tomato";
char columnar[MAX_KEYSIZE][MAX_TEXTSIZE]; // deklarasi variabel penampung columar yang belum digeser
char resolved[MAX_KEYSIZE][MAX_TEXTSIZE]; // deklarasi variabel columnar yang sudah digeser2

/// function declaration
int keysize(){
    return sizeof(key) / sizeof(key[0]);
}
int arraysize(int ptsize){
    return ((ptsize)/(keysize()-1))+1;
}
void insertpt(char *plaintext, int ptsize){ //fungsi yang menginsersi plaintext ke dalam columnar
  int poskanan=0, posbawah=0; //deklarasi variabel penentu posisi teks dalam array columnar
  for(int i = 0; i<ptsize;i++){ // loop untuk mengcover semua huruf pada plaintext
    columnar[poskanan][posbawah] = plaintext[i]; // meletakkan plainteks di lokasinya
    if(poskanan < keysize()-2) poskanan++; // jika belum sampai ujung maka geser kanan
    else{ // jika sudah
      posbawah++; // geser kebawah
      poskanan = 0;  // kembali ke 0
    }
  }
  while(poskanan < keysize()-1){ // jika ada kosong di kanan, maka isi dengan random ascii a-z
      columnar[poskanan][posbawah]=(rand()%26)+97; //isi sisanya dengan random ascii a-z
      poskanan++; // geser ke kanan
  }
}
void sort(int ptsize){ //fungsi yang mengurutkan nilai dari columnar menjadi hasil akhir
  int possort = 0; // deklarasi posisi awal sort
  for(int i = 0; i<26;i++){ // pengecekan berbasis huruf
    for(int j = 0; j<keysize()-1; j++){ // loop for yang mengecek semua huruf pada key
      if(key[j] == i+97){ // jika huruf cocok
        for (int k = 0; k < arraysize(ptsize); k++){ //loop for yang mengkopas isi dari array posisi j pada possort
          resolved[possort][k] = columnar[j][k]; //mengkopas isi array menjadi posisi possort
        }
        possort++; // inkremen possort
      }
    }
  }
}

int main(){
    srand(time(0));
    printf("WARNING! Nihilist Algorithm is categorized as a classical encryption algorithm and has been depecrated since the development of computers! ");
    printf("Only use this program as a learning reference instead!\n\n");

    char plaintext[MAX_TEXTSIZE];
    int textsize = MAX_TEXTSIZE-1;
    while(1){
        printf("Insert your plaintext (no spaces, max characters: %d) > ", MAX_TEXTSIZE);
        scanf("%s", &plaintext);
        for(int i = 0; i<MAX_TEXTSIZE; i++){
            if (plaintext[i] == 0 || plaintext[i] == '\n'){
                textsize = i;
                break;
            }
        }


//        int poskanan=0, posbawah=0; //deklarasi variabel penentu posisi teks dalam array columnar
//        for(int i = 0; i<textsize;i++){ // loop untuk mengcover semua huruf pada plaintext
//            columnar[poskanan][posbawah] = plaintext[i]; // meletakkan plainteks di lokasinya
//            if(poskanan < keysize()-2) poskanan++; // jika belum sampai ujung maka geser kanan
//            else{ // jika sudah
//                posbawah++; // geser kebawah
//                poskanan = 0;  // kembali ke 0
//            }
//        }
//        while(poskanan < keysize()-1){ // jika ada kosong di kanan, maka isi dengan random ascii a-z
//            columnar[poskanan][posbawah]=(rand()%26)+97; //isi sisanya dengan random ascii a-z
//            poskanan++; // geser ke kanan
//        }
        insertpt(plaintext, textsize); // memasukan semua plaintext kedalam susunan myzkowski
        sort(textsize); // mengsortir susunan myzkowski menjadi ciphertext

        printf("\nKey: %s", plaintext);
        printf("\nKey: %s\n", key);

        printf("Columnar prearranged:\n");
        for(int i = 0; i < keysize()-1;i++){
            printf("\t%c: ", key[i]);
            for (int j = 0; j < arraysize(textsize); j++) printf("%c", columnar[i][j]);
            printf("\n");
        }
        printf("Columnar rearranged:");
        for(int i = 0; i < keysize()-1;i++){
            for (int j = 0; j < arraysize(textsize); j++) printf("%c", resolved[i][j]);
            printf(" ");
       }
        printf("\n\n");
    }

}
