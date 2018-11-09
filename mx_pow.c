// mx_pow.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include "stdafx.h"
#include "matrix.h"
int main()
{
	TMatrix *m,*e;
	m = mx_custom_identify(3,3);
	mx_print(m);
	e = mx_pow(m, 2);
	mx_print(e);
    return 0;
}

