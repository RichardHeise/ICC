#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

double bisseccao (Polinomio p, double a, double b, double eps,
	       int *it, double *raiz) {

	double xm_old, xm_new, erro = 0;

	xm_new = (a + b) / 2;
	double val1, val2;

	calcPolinomio_rapido(p, a, &val1, NULL);
	calcPolinomio_rapido(p, xm_new, &val2, NULL);

	double compare = val1 * val2;

	erro = fabs((xm_new - xm_old) / xm_new) *100;

	if ( compare < 0)
		b = xm_new;
	else if ( compare > 0)
		a = xm_new;
	else {
		*raiz = xm_new;
		return erro;
	}

	(*it)++;
	
	do {
		xm_old = xm_new;
		xm_new = (a + b) / 2;

		calcPolinomio_rapido(p, a, &val1, NULL);
		calcPolinomio_rapido(p, xm_new, &val2, NULL);

		compare = val1 * val2;

		erro = fabs((xm_new - xm_old) / xm_new) *100;

		if ( compare < 0)
			b = xm_new;
		else if ( compare > 0)
			a = xm_new;
		else {
			*raiz = xm_new;
			return erro;
		}

		(*it)++;

		
	} while ( erro > eps && *it < MAXIT);

	*raiz = xm_new;
	return erro;

}


double newtonRaphson (Polinomio p, double x0, double eps,
		   int *it, double *raiz)
{
	double x_new = x0, x_old, px, dpx, dpx_old, erro = 0;
	int criteria1, criteria2, criteria3;

	do{
		x_old = x_new;
		dpx_old = dpx;

		calcPolinomio_rapido(p, x_old, &px, &dpx);

		if(fabs(dpx) < DBL_MIN)
			dpx = dpx_old;

		x_new = x_old - px / dpx;
		
		erro = fabs(x_old - x_new);
		criteria1 = erro > eps;

		calcPolinomio_rapido(p, x_new, &px, NULL);
		criteria2 = fabs(px) > eps;

		(*it)++;
		criteria3 = (*it) < MAXIT;

	} while(criteria1 && criteria2 && criteria3);

	*raiz = x_new;
	return erro;
}


double secante (Polinomio p, double x0, double x1, double eps,
	     int *it, double *raiz)
{
	double x_new = x1, x_old = x0, x_older, px, px_older, px_temp, erro;
	int criterio1, criterio2, criterio3;

	do{
		x_older = x_old;
		x_old = x_new;

		calcPolinomio_rapido(p, x_old, &px, NULL);

		px_temp = px_older;
		calcPolinomio_rapido(p, x_older, &px_older, NULL);

		if(!(fabs(px - px_older) > DBL_MIN)){
			px_older = px_temp;
		}

		x_new = x_old - (px * (x_old - x_older))/(px - px_older);
		
		erro = fabs(x_old - x_new);
		criterio1 = erro > eps;

		calcPolinomio_rapido(p, x_new, &px, NULL);
		criterio2 = fabs(px) > eps;

		(*it)++;

		criterio3 = (*it) < MAXIT;

	}while(criterio1 && criterio2 && criterio3);

	*raiz = x_new;
	return erro;
}


void calcPolinomio_rapido(Polinomio p, double x, double *px, double *dpx) {
	double b = 0;
	double c = 0;
	for (int i = p.grau; i > 0; --i) {
		b = b*x + p.p[i];
		c = c*x + b;
	}

	b = b*x + p.p[0];
	*px = b;

	if(dpx){
		*dpx = c;
	}
}


void calcPolinomio_lento(Polinomio p, double x, double *px, double *dpx) {
	
}
