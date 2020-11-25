#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.c"
#include "history_payment.c"
#include "income.c"

//deklarasi fungsi
int getTotalTrx();

//deklarasi prosedur
void restartTrx();
void saveToFile();
void pemasukan();
void barang();
void run();


/*DEKLARASI STRUCT MENU*/
 struct Menu {
    int nomor;
    char *nama;
    int harga;
};

/*INISIALISASI STRUCT OF ARRAY MENU*/
struct Menu menu[10] = {
    /*Food*/
    {1, "Bakso", 25000},
    {2, "Nasi Goreng", 28000},
    {3, "Mi Goreng", 22000},
    {4, "Pizza", 45000},
    {5, "Spagetti", 25000},
    /*drink*/
    {6, "Cappucino", 27000},
    {7, "Tea", 13000},
    {8, "Juice", 17000},
    {9, "Mineral Water", 6000},
    {10, "Vietnam Drip", 27000}


};

/*deklarasi global panjang menu (untuk syarat dalam perulangan)*/
int menu_length = sizeof(menu)/sizeof(menu[0]);

/*Transaksi Struct*/
struct Transaction {
    struct Menu menu;
    int amount;
    int total;
};
/*array of struct transaksi*/
struct Transaction trx[100];

int hasil;

/*main function (fungsi dasar)*/
int main() {
    run();
    return 0;
}

/*function of Running code*/
void run() {

    awal:;
    printf("========== PAYMENT OF SALES MENU ==========\n\n");

    printf("\t1. Payment\n");
    printf("\t2. History Payment\n");
    printf("\t3. Income\n");
    printf("\t4. Exit\n");
    printf("\n\tSelect: ");

    int select;

    select = getchar();
    system("cls");

    switch (select) {
        case 1 : {barang(); break;}
        case 2 : {select = 0;
                    history_payment();
                    printf("Back\n");
                    system("pause");
                    system("cls");
                    goto awal; break;}
        case 3 : {income();
                    printf("\nBack\n");
                    system("pause");
                    system("cls");
                    run();break;}
        case 4: {exit(0); break;}
        default: {goto awal;}
    }
}

/*function rumus total(jumlah) belanja*/
int getTotalTrx() {
    int totalTrx = 0;
    int trx_length = sizeof(trx)/sizeof(trx[0]);
    for(int i=0; i<trx_length; i++) {
        if(trx[i].total == 0)
            break;
        printf("\ttrx no %d.  %s, jumlah:%d\n", i+1, trx[i].menu.nama, trx[i].total);
        totalTrx += trx[i].total;
    }

    return totalTrx;
}

/*to restart content of trx array*/
void restartTrx(){
    int trx_length = sizeof(trx)/sizeof(trx[0]);
    for (int i = 0; i<trx_length; i++){
        trx[i].total = 0;
    }
}

/*prosedur untuk memasukan history payment kedalam file*/
void saveToFile(){

    struct tm *Sys_T;

    time_t Tval;
    Tval = time(NULL);
    Sys_T = localtime(&Tval); /* Untuk mendapatkan waktu lokal komputer */
    /* Sys_T = gmtime(&Tval); */ /* Untuk mendapatkan waktu komputer berbasis GMT/UTC */

    // creating file pointer to work with files
    FILE *fptr;


    // opening file in writing mode
    fptr = fopen("program.txt", "a+");

    // exiting program
    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    char waktu_[500];
    sprintf(waktu_, "%s======================\n", asctime (Sys_T));
    fprintf(fptr, "%s", waktu_);

    int trx_length = sizeof(trx)/sizeof(trx[0]);
    for(int i=0; i<trx_length; i++) {
        if(trx[i].total == 0)
            break;
        char sentence[500];
        sprintf(sentence, "trx no %d.  %s, jumlah:%d, harga:%d\n", i+1, trx[i].menu.nama, trx[i].amount, trx[i].total);
        fprintf(fptr, "%s", sentence);
    }
    char enter[500];
    sprintf(enter, "\n");
    fprintf(fptr, "%s", enter);

    fclose(fptr);
}

/*prosedur untuk memasukan pemasukan kedalam file*/
void pemasukan(){
    FILE *income;
    int totalTrx;
    int sum = 0;



    income = fopen("Income.txt", "w");

    if (income == NULL) {
        printf("Error!");
        exit(1);
    }
     int trx_length = sizeof(trx)/sizeof(trx[0]);
        for(int i=0; i<trx_length; i++) {
            if(trx[i].total == 0)
                break;
            totalTrx += trx[i].total;
        }

    sum =+ totalTrx;
    hasil +=sum;
    int jumlah = hasil;
    char text[500];
    sprintf(text, "Total Pemasukan= %d", jumlah);
    fprintf(income, "%s", text);

    fclose(income);

}

/*function PAYMENT, BAYAR, Kembalian*/
void barang() {
    lagi:;
    daftar();
    int x;
    int y;
    int count=0;
    do{ input:;
        printf("\n\tInput Code: ");
        scanf("%d", &x);

        if(x<menu_length + 1 && x>0) {
            for(int j=0; j<menu_length; j++) {
                if(x==menu[j].nomor) {
                    trx[count].menu = menu[j];
                    printf("\t%s= ", trx[count].menu.nama);
                    scanf("%d", &x);
                    trx[count].amount = x;
                    trx[count].total = menu[j].harga * trx[count].amount;
                    break;
                }
            }
            printf("\t%s = %d  Amount: %d\n", trx[count].menu.nama, trx[count].total, trx[count].amount);
        } else if (x == 0){
            break;
        } else if(x == 99){
            run();
        }else{
            printf("\tCode Do Not Exist\n");
            goto input;
        }

        count++;
    } while(x!=0);

    int total_trx =  getTotalTrx();
    if(total_trx == 0){
        system("cls");
        goto lagi;
    }
    printf("\n\t\t\t\tSubTotal: %d\n", total_trx);
    printf("\tMasukan uang untuk bayar: ");
    int bayar;
    scanf("%d", &bayar);
    int kembalian = bayar - total_trx;
    printf("\tKembalian: %d\n", kembalian);

    pemasukan();
    saveToFile();
    restartTrx();

    printf("\tMau ngitung lagi?(1 for yes, 0 for no)\n\tSelect: ");
    scanf("%d", &x);
    if (x  == 1){
        system("cls");
        goto lagi;
    }else{
        system("cls");
        run();
    }

}
