#include <stdio.h>
/* #include <stdlib.h> */
#include <stdbool.h>

// int main(){
// // printf("my name is ali\n");
// // printf("my adress is Sollentunaroad 305\n");
// // printf("my age is 31\n");
//     printf("my name is ali\nSollentunaroad 305\nmy age is 31" );

// int main(){
//     printf("Name of user: %s so now you know\n" , getenv ("USERNAME") ) ;
//     printf("Pathen %s\n", getenv("PATH") );

// int main() {
//     int days=5;
//     int pricePerNight=2500;
//     int totalPrice=25000;

//     printf("What does the hotel cost per night? ");
//     scanf("%d", &pricePerNight);
    
//     printf("How many nights? ");
//     scanf("%d", &days);
//     if (days > 5) {
//         printf("you are staying more then 5 nights");
//     }

//     totalPrice = days * pricePerNight;
//     printf("It will be %dkr\n", totalPrice ); 
//     printf("It will be %dkr\n", days * pricePerNight);


// int main() {
// // create a program that writes out 1-10 on the screen.
// for(int i = 0; i <= 10; i++) {
//     printf("%d\n",i);
// }

// int i = 0;
// while(i <= 10){
//     printf("%d\n",i);
//     i++;
// }

// for(int i = 10; i >= 0; i = i -4 ) {
//     printf("%d\n",i);
// }

//     return 0;
// }


// int main() {
//     int activate; // after int is a variable, can have any name.
//     int end; // after int is ia variable
//     printf("Activate");
//     scanf("%d", &activate); // can not have space after &
//     printf("End");
//     scanf("%d", &end);

//     if (activate < end) {
//         for(int i=activate; i <=end; i ++){// ++ means 1 nr will be added so for example : if you press 6 it will become 7
//             printf("%d\n",i);
//         }

//         int i=activate;
//         while(i <=end){
//             printf("%d\n",i);
//             i++;

//         }
//     }else { //activate >= end
//         //    20          15 
//         for(int i=activate; i >=end; i--){ // likewise like we wrote on the + part it will become -1 less    
//             printf("%d\n",i);
//         }

//         int i=activate;
//         while(i >= end){
//             printf("%d\n",i);
//             i--;
//         }
//     }
// }
    


/* int main(){ // need curly braces after int main(){ ALWAYS!
    while(1){
    int NR1;
    int NR2;  // what comes after int is a variable.
    printf("NR1: ");
    scanf("%d",& NR1);
    printf("NR2: ");
    scanf("%d",& NR2);
    // NR1 + NR2 =

    printf("if number comes %d\n", NR1 + NR2); // so the NR 1 & 2 we dont put ""
    int keepGoing;
    scanf("%d", &keepGoing);
    if(keepGoing == 0)
    break;
// } */
// }

// int main(){
//     int total= 0;
//     for(int cat=0; cat < 10; cat++ ){
//     int nr;
//     printf("Nr %d ", cat + 1);
//     scanf("%d",&nr);
//     total += nr;
// }
// printf("Total %d", total);
// return 0;

// }
int main(){
    while(true){
        printf("Admin menu\n");
        printf("1. Remote open door\n");
        printf("2. List all cards in system\n");
        printf("3. Add/remove access\n");
        printf("4. Exit\n");
        printf("9. FAKE TEST SCAN CARD\n");
        printf("Select option: ");
        int option;
        scanf("%d", &option);
        if(option ==4){
        }
    }
}



