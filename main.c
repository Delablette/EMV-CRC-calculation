#include <stdio.h>
#include <stdlib.h>
#define POLYNOME_CRC16 0x1021
#define UINT8 unsigned char
#define UINT32 unsigned int

UINT32 reg = 0;
/* retourne le champ excedant de la variable */
#define get_excedant(reg) (((reg) & 0xFF000000) >> 24)
/* retourne le champ reste de la variable */
#define get_reste(reg) (((reg) & 0x00FFFF00) >> 8)
/* retourne le champ octet de la variable */
#define get_octet(reg) ((reg) & 0x000000FF)
/* stocke "val" (tronqué à 8 bits si besoin) dans le champ octet */
#define set_octet(reg, val) ((reg) = ((reg) & 0xFFFFFF00) | ((val) & 0xFF))
/* stocke "val" (tronqué sur 16 bits si besoin) dans le champ reste */
#define set_reste(reg, val) ((reg) = ((reg) & 0xFF0000FF) | (((val) & 0xFFFF) <<8))

void afficher_tableau_charac(char tableau[], int taille);
UINT8 conversion_character (char var1, char var2);
void calc_crc16_sur_un_octet (UINT8 nouvel_octet);
void calc_crc16_sur_la_chaine (UINT8 string3[], int len);

int main()
{
    char TableauChar[1024];
    UINT8 TableauHexadecimal[1024];
    int taille_tableau = 0;
    int character_courant=0;
    int character_intermediaire=0;
    printf("inserez votre chaine de caracteres: ");
    scanf("%s", TableauChar);

    while (TableauChar[taille_tableau] != '\0'){
         printf("%c", TableauChar[taille_tableau]);
         taille_tableau++;
    }
       printf("\n le tableau a une taille de %d caracteres", taille_tableau);
    afficher_tableau_charac(TableauChar, taille_tableau);

    while(character_courant < taille_tableau/2){
        TableauHexadecimal[character_courant] = conversion_character(TableauChar[character_intermediaire], TableauChar[character_intermediaire+1]);
        character_courant +=1;
        character_intermediaire+=2;
    }
    printf("\naffichage du tableau hexadecimal: ");
    for(int i = 0; i< taille_tableau/2; i++){
        printf("%p", TableauHexadecimal[i]);
    }
    printf("\n");

    calc_crc16_sur_la_chaine(TableauHexadecimal, taille_tableau/2);

    return 0;
}

void afficher_tableau_charac(char tableau[], int taille){
printf("\n\n******affiche de la chaine dans la fonction******\n");
for(int i=0; i<taille;i++){
    printf("%c", tableau[i]);
}
}

UINT8 conversion_character (char var1, char var2){
    UINT8 hexadecimal=0;
    if ('0'<=var1 && var1<='9'){
            hexadecimal = 0xFF &((var1 - '0')<<4);

    }
    else if ('A'<= var1 && var1 <='F'){
        hexadecimal = (var1 - 55)<<4;
    }
    else{
         fprintf(stderr, "erreur de nombre saisi\n");
         return 1;
    }
   if ('0'<=var2 && var2<='9'){
            hexadecimal += (var2 - '0');
   }
    else if ('A'<= var2 && var2<='F'){
        hexadecimal += (var2 - 55);
    }
    else{
         fprintf(stderr, "erreur de nombre saisi\n");
         return 1;void calc_crc16_sur_la_chaine (UINT8 string3[], int len){
reg = 6363;
for(int i= 0; i< len; i++)
{
    printf("l'octet dans la fonction chaine: %p\n", string3[i]);
    calc_crc16_sur_un_octet(string3[i]);
}
   calc_crc16_sur_un_octet ((UINT8) 0x0);
   calc_crc16_sur_un_octet ((UINT8) 0x0);

   printf("res: %p\n", get_reste(reg));
}
    }
    return hexadecimal;
}

void calc_crc16_sur_la_chaine (UINT8 string3[], int len){
reg = 0xFFFF;
for(int i= 0; i< len; i++)
{
    printf("l'octet dans la fonction chaine: %p\n", string3[i]);
    calc_crc16_sur_un_octet(string3[i]);
}
   calc_crc16_sur_un_octet ((UINT8) 0x0);
   calc_crc16_sur_un_octet ((UINT8) 0x0);

   printf("res: %p\n", get_reste(reg));
}

void calc_crc16_sur_un_octet (UINT8 nouvel_octet){
int bdpf;
printf("octet dans la chaine: %p\n", nouvel_octet);
set_octet(reg, nouvel_octet);
for(int i=0; i<8;i++){
reg = reg <<1;

if((get_excedant(reg) & 0x01) == 1){
    bdpf = 1;
}
else
    bdpf = 0;
if (bdpf== 1){
    set_reste(reg, (get_reste(reg)^ POLYNOME_CRC16));
}
}
}
