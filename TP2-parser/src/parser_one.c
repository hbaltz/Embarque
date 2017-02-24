/**
* Aller voir la documentetion du protocole ubx : https://www.u-blox.com/sites/default/files/products/documents/u-blox6_ReceiverDescrProtSpec_%28GPS.G6-SW-10018%29_Public.pdf?utm_source=en%2Fimages%2Fdownloads%2FProduct_Docs%2Fu-blox6_ReceiverDescriptionProtocolSpec_%28GPS.G6-SW-10018%29.pdf
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Strucutre du payload correspondant à un message ubdx de class 01 et d'ID 21
struct timeUTC{
	unsigned int iTown;
	unsigned int tAcc;
	signed int nano;
	unsigned short year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
	unsigned char valid;
};

// Strucutre d'un message ubx
struct message{
	// Caractères de synchronisation
	unsigned char sync1;
	unsigned char sync2;

	// Caractères définissant la classe +ID
	unsigned char class;
	unsigned char ID;

	// Taille payload
	unsigned short length;

	// Payload content
	unsigned char payload[150];

	// Check
	unsigned char checksum1;
	unsigned char checksum2;
};

// Donnée en entrée
unsigned char data[] = {0xb5, 0x62, 0x01, 0x21, 0x14, 0x00, 0x60, 0x12, 0xe7, 0x1e, 0x0d, 0x00, 0x00, 0x00, 0x6c, 0x77, 0x00, 0x00, 0xe0, 0x07, 0x07, 0x17, 0x00, 0x00, 0x2b, 0x07, 0xd4, 0x01};

// Déclaration fonction
void afficherDonnee(struct message msg, struct timeUTC tUtc);

int main(int argc, char **argv){

	int argAff;

	if (argv[1] != NULL){
		argAff = strtod(argv[1],NULL);
	}

	// Désérialisation
	struct message msg; 
	msg = *(struct message *) data;

	// Taille data
	int sizeData = sizeof(data);

	// Récupération Checksum
	msg.checksum1 = data[sizeData-2];
	msg.checksum2 = data[sizeData-1];

	unsigned char chks1 = 0, chks2 = 0; // Checksum calculée

	for (int i = 2; i < sizeData-2; ++i){
		chks1 += data[i];
		chks2 += chks1;
	}

	// Nous ne continouns les traitements que si les checksum calculés sont égaux aux checksum contenus dans le messaga
	if(chks1 == msg.checksum1 && chks2==msg.checksum2){
		// Si le message ubdx est de class 01 et a pour ID 21, on lit la date
		if(msg.class == 0x01  && msg.ID == 0x21){
				// Lecture payload
				struct timeUTC tUtc;
				tUtc = * (struct timeUTC *) msg.payload;

				
				// Affichage des données détaillée
				if(argAff == 1){
					afficherDonnee(msg,tUtc);
				}

				// Affichage de la date d'acquisiton
				printf("Date d'acquisiton : %u/%u/%u à %u:%u:%u \n",
					tUtc.day,tUtc.month,tUtc.year,tUtc.hour,tUtc.min,tUtc.sec);
			}
	}
	return 0;
}

void afficherDonnee(struct message msg, struct timeUTC tUtc){
	// Affichage donnée général msg
		printf("Sync1: %X \n", msg.sync1);
		printf("Sync2: %X \n", msg.sync2);
		printf("Class: %X \n", msg.class);
		printf("ID: %X \n", msg.ID);
		printf("Length: %X \n", msg.length);

		// Affichage données payload
		printf("iTown: %u \n",tUtc.iTown);
		printf("tAcc: %u \n",tUtc.tAcc);
		printf("nano: %u \n",tUtc.nano);
		printf("year: %u \n",tUtc.year);
		printf("month: %u \n",tUtc.month);
		printf("day: %u \n",tUtc.day);
		printf("hour: %u \n",tUtc.hour);
		printf("min: %u \n",tUtc.min);
		printf("sec: %u \n",tUtc.sec);
		printf("valid: %u \n",tUtc.valid);

		// Affichage checkSum
		printf("Checksum1: %u \n", msg.checksum1);
		printf("Checksum2: %u \n", msg.checksum2);
}
