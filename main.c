#include <stdio.h>
#include <stdlib.h>

#define POLYNOME_CRC16 0x1021
#define UINT8 unsigned char
#define UINT32 unsigned int
/* déclaration du registre de calcul de CRC en tant que variable globale
(elle conservera sa valeur d'un appel à l'autre) */

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
void calc_crc16_sur_un_octet (UINT8 nouvel_octet);
void calc_crc16_sur_la_chaine (char *string, size_t len);
int main()
{

char string[1024];
printf("Entrer une chaine (moins de 1024 caractères) : ");
fscanf(stdin, "%s", string);
printf("\tinput = \"%s\"\n", string);
int i=0;
while(string[i]!='\0'){i++;}

calc_crc16_sur_la_chaine(*string, i);
    return 0;
}

void calc_crc16_sur_un_octet (UINT8 nouvel_octet){
int bdpf;
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
void calc_crc16_sur_la_chaine (char *string, size_t len){
reg = 0;
for(size_t i= 0; i< len; i++)
{
    calc_crc16_sur_un_octet(&string[i]);
}
   calc_crc16_sur_un_octet ((UINT8) 0x0);
   calc_crc16_sur_un_octet ((UINT8) 0x0);

   printf("res: %p\n", get_reste(reg));
}
