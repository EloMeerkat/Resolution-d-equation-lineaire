#define _CRT_SECURE_NO_WARNINGS

#define A(i,j) A[(i)*taille+(j)]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methodes.h"

int main(int argc, char **argv){
	printf("Debut de l'algorithme\n");
	printf("*********************\n");
	printf("Lecture des donnees\n");

	FILE *in = fopen("matriceA.txt", "rt");
	FILE *out = fopen("reponse.txt", "wt");

	char ligne[255];
	fgets(ligne, 255, in);
	int taille;
	sscanf(ligne, "%d", &taille);

	//Definition des matrices
	double *A = (double*)malloc((taille*taille)*sizeof(double));
	double *B = (double*)malloc((taille)*sizeof(double));
	double *X = (double*)malloc((taille)*sizeof(double));
	int *O = (int*)malloc((taille)*sizeof(int));

	double valeur;
	char chaine[5000];
	fgets(chaine, 5000, in);
	char* p = chaine;

	for(int i=0; i<taille; i++){
		for(int j=0; j<taille; j++){
			sscanf(p, "%lf", &valeur);
			A(i,j)=valeur;
			p = strchr(p, (unsigned int)' ')+1;
		}
		fgets(chaine, 5000, in);
		p = chaine;
	}

	fclose(in);
	in = fopen("matriceB.txt", "rt");

	for(int i=0; i<taille; i++){
		fgets(chaine, 5000, in);
		p = chaine;
		sscanf(p, "%lf", &valeur);
		B[i]=valeur;
	}

	LU(A, B, X, O, taille);
	printf("Racine : \n");
	fprintf(out, "Racine : \n");

	for(int i=0; i<taille; i++){
		printf("%lf\n", X[i]);
		fprintf(out, "%lf\n", X[i]);
	}

	fclose(out);
	free(A); free(B); free(X); free(O);
	printf("Fin\nAppuyer sur entrer pour quitter.\n");
	getchar();

	return 0;
}
