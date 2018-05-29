#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "methodes.h"
#include "fonctions.h"

#define A(i,j) A[(i)*taille+(j)]
#define L(i,j) L[(i)*taille+(j)]
#define U(i,j) U[(i)*taille+(j)]

void LU(double* A, double* B, double* X, int* O, unsigned int taille){
	int i,j,k, idx;
	double val;
	double *L = (double*)malloc((taille*taille)*sizeof(double));
	double *U = (double*)malloc((taille*taille)*sizeof(double));
	double *Y = (double*)malloc((taille*taille)*sizeof(double));

	for(i=0; i<taille; i++){
		O[i]=i;
	}

	//Premiere colone de L
	for(i=0; i<taille; i++){
		L(i,0) = A(i,0);
	}

	meilleur_pivot(A,L,O, taille, 0);

	//Premiere ligne de U
	for(i=1; i<taille; i++){
		U(0,i) = A(0,i)/A(0,0);
	}

	//Complete L et U (sauf la valeur en bas a droite de L)
	for(i=1; i<taille-1; i++){
		val = 0;
		for(k=0; k<i; k++){
			val += (L(i,k)*U(k,i));
		}
		L(i,i) = A(i,i) - val;

		for(j=i+1; j<taille; j++){
			val = 0;
			for(k=0; k<i; k++){
				val +=L(j,k)*U(k,i);
			}
			L(j,i) = A(j,i) - val;
		}

		meilleur_pivot(A,L,O, taille, i);

		for(j=i+1; j<taille; j++){
			val = 0;
			for(k=0; k<i; k++){
				val +=L(i,k)*U(k,j);
			}
			U(i,j) = (A(i,j)-val)/L(i,i);
		}
	}

	//Derniere valeur de L
	val = 0;
	for(k=0; k<taille-1; k++){
		val +=L(taille-1,k)*U(k,taille-1);
	}
	L(taille-1, taille-1) = A(taille-1, taille-1) - val;

	//Diagonale de U
	for(i=0; i<taille; i++){
		U(i,i) = 1;
	}

	//Descente triangulaire
	Y[0] = B[O[0]]/L(0,0);
	for(i=1; i<taille; i++){
		val = 0;
		for(k=0; k<i; k++){
			val +=L(i,k)*Y[k];
		}
		Y[i] = (B[O[i]]-val)/L(i,i);
	}
	
	//Remontee triangulaire
	X[taille-1] = Y[taille-1];
	for(i=taille-2; i>-1; i--){
		val = 0;
		for(k=i+1; k<taille+1; k++){
			val +=U(i,k)*X[k];
		}
		X[i] = Y[i] - val;
	}
	free(L); free(U); free(Y);
}
