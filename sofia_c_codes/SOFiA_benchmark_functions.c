/* F1 FUNCTION - [-100,100] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	
	for (int i = 0; i < DIMENSIONS; ++i)
	{
		result += pow(matrix[w][i],2);
	}	

	return result;
}

/* F2 FUNCTION - [-10,10] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	double arg1 = 0.0;
	double arg2 = 0.0;
	
	for (int i = 0; i < DIMENSIONS; ++i)
	{
		arg1 += fabs(matrix[w][i]);
	}	

	for (int i = 0; i < DIMENSIONS; ++i)
	{
		arg2 *= fabs(matrix[w][i]);
	}

	result = arg1 + arg2;

	return result;
}

/* F3 FUNCTION - [-100,100] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	double arg1 = 0.0;
	
	for (int i = 0; i < (DIMENSIONS+1); ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			arg1 += matrix[w][j];
		}

		arg1 = pow(arg1,2);
		result += arg1;
		arg1 = 0.0;		
	}	

	return result;
}

/* F4 FUNCTION - [-100,100] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = fabs(matrix[w][0]);	
	
	for (int i = 0; i < DIMENSIONS; ++i)
	{
		if (matrix[w][i] > result)
		{
			result = fabs(matrix[w][i]);
		}		
	}	

	return result;
}

/* F5 FUNCTION - [-30,30] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	
	for (int i = 0; i < (DIMENSIONS-1); ++i)
	{
		result += ((100*(pow((matrix[w][i+1]-pow(matrix[w][i],2)),2)))+pow((matrix[w][i]-1),2));
	}	

	return result;
}

/* F6 FUNCTION - [-100,100] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	
	for (int i = 0; i < DIMENSIONS; ++i)
	{
		result += pow((matrix[w][i]+0.5),2);
	}	

	return result;
}

/* F7 FUNCTION - [-1.28,1.28] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	double rand = random01();

	while(rand == 1.0)
	{
		rand = random01();
	}
	
	for (int i = 0; i < DIMENSIONS; ++i)
	{
		result += (i+1)*pow(matrix[w][i],4);
	}	

	return (result+rand);
}

/* F8 FUNCTION - [-500,500] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	
	for (int i = 0; i < DIMENSIONS; ++i)
	{
		result += (matrix[w][i]*sin(sqrt(fabs(matrix[w][i]))));
	}	

	return -result;
}

/* F9 FUNCTION - [-5.12,5.12] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	
	for (int i = 0; i < DIMENSIONS; ++i)
	{
		result += ((pow(matrix[w][i],2)-10*cos(2*M_PI*matrix[w][i]))+10);
	}		

	return result;
}

/* F10 FUNCTION - [-32,32] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	double arg1 = 0.0;
	double arg2 = 0.0;

	for (int i = 0; i < DIMENSIONS; ++i)
	{
		arg1 += pow(matrix[w][i],2);
	}

	arg1 = arg1/30.0;
	arg1 = sqrt(arg1);
	arg1 = -0.2*arg1;
	
	for (int i = 0; i < DIMENSIONS; ++i)
	{
		arg2 += cos(2*M_PI*matrix[w][i]);
	}		

	arg2 = (arg2/30.0);

	result = ((-20*exp(arg1))-(exp(arg2))+20+exp(1));

	return result;
}

/* F11 FUNCTION - [-600,600] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	double arg1 = 0.0;
	double arg2 = 1.0;
	
	for (int i = 0; i < DIMENSIONS; ++i)
	{
		arg1 += pow(matrix[w][i],2);
	}

	arg1 = (arg1/4000.0);

	for (int i = 0; i < DIMENSIONS; ++i)
	{
		arg2 *= cos(matrix[w][i]/sqrt(i+1));
	}

	result = arg1-arg2+1;	

	return result;
}

/* F12 FUNCTION - [-50,50] */
double uFunc(double x, int a, int k, int m)
{
	double result = 0.0;

	if (x > a)
	{
		result = (k*pow((x-a),m));
	}
	else if (x < (-a))
	{
		result = (k*pow((-x-a),m));		
	}
	else 
	{
		result = 0.0;
	}

	return result;
}
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	double arg1 = 0.0;
	double arg2 = 0.0;
	double arg3 = 0.0;
	double arg4 = 0.0;
	
	arg1 = sin(M_PI*(1+(matrix[w][0]+1)/4.0));	

	for (int i = 0; i < (DIMENSIONS-1); ++i)
	{
		arg2 += pow((((matrix[w][i]+1)/4.0)),2)*(1+(10*pow(sin(M_PI*(1+(matrix[w][i+1]+1)/4.0)),2)));
	}

	arg3 = pow((((matrix[w][DIMENSIONS-1]+1)/4.0)),2);

	for (int i = 0; i < DIMENSIONS; ++i)
	{
		arg4 += uFunc(matrix[w][i],10,100,4);
	}

	result = (3.14159265358979323846/30.0)*(10*pow(arg1,2)+arg2+arg3)+arg4;	

	return result;
	//(math.pi/dim)*(10*((numpy.sin(math.pi*(1+(x[0]+1)/4)))**2)
		//+numpy.sum((((x[1:dim-1]+1)/4)**2)*(1+10*((numpy.sin(math.pi*(1+(x[1:dim-1]+1)/4))))**2))
		//+((x[dim-1]+1)/4)**2)+numpy.sum(Ufun(x,10,100,4));   
}

/* F13 FUNCTION - [-50,50] */
double uFunc(double x, int a, int k, int m)
{
	double result = 0.0;

	if (x > a)
	{
		result = (k*pow((x-a),m));
	}
	else if (x < (-a))
	{
		result = (k*pow((-x-a),m));		
	}
	else 
	{
		result = 0.0;
	}

	return result;
}
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	double arg1 = 0.0;
	double arg2 = 0.0;
	double arg3 = 0.0;
	double arg4 = 0.0;
	
	arg1 = pow(sin(3*M_PI*matrix[w][0]),2);	

	for (int i = 0; i < (DIMENSIONS-1); ++i)
	{
		arg2 += (pow((matrix[w][i]-1),2))*(1+pow(sin(3*M_PI*matrix[w][i+1]),2));
	}

	arg3 = pow((matrix[w][DIMENSIONS-1]-1),2)*(1+pow(sin(2*M_PI*matrix[w][DIMENSIONS-1]),2));

	for (int i = 0; i < DIMENSIONS; ++i)
	{
		arg4 += uFunc(matrix[w][i],5,100,4);
	}

	result = 0.1*(arg1+arg2+arg3)+arg4;	

	return result;	
}

/* F14 FUNCTION - [-65.536,65.536] */
double aS[2][25] = {
{-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32},
{-32,-32,-32,-32,-32,-16,-16,-16,-16,-16,0,0,0,0,0,16,16,16,16,16,32,32,32,32,32}
};

double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	double arg1 = 0.002;
	double arg2 = 0.0;
	double arg2_aux = 0.0;
	
	for (int j = 0; j < 25; ++j)
	{
		for (int i = 0; i < 2; ++i)
		{
			arg2_aux += pow((matrix[w][i] - aS[i][j]),6);
		}

		arg2 += (1.0)/((j+1)+arg2_aux);
		arg2_aux = 0.0;
	}

	result = pow((arg1+arg2),(-1));

	return result;
}

/* F15 FUNCTION - [-5,5] */
double ak[11] = {0.1957,0.1947,0.1735,0.1600,0.0844,0.0627,0.0456,0.0342,0.0323,0.0235,0.0246};
double bk[11] = {4,2,1,0.5,0.25,0.166666666,0.125,0.1,0.083333333,0.071428571,0.0625};
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	
	for (int i = 0; i < 11; ++i)
	{
		result += pow((ak[i] - ((matrix[w][0]*(pow(bk[i],2) + bk[i]*matrix[w][1]))/(pow(bk[i],2)+bk[i]*matrix[w][2]+matrix[w][3]))),2);
	}	

	return result;
}

/* F16 FUNCTION - [-5,5] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	
	result = 4*pow(matrix[w][0],2)-2.1*pow(matrix[w][0],4)+0.333333333*pow(matrix[w][0],6)+matrix[w][0]*matrix[w][1]-4*pow(matrix[w][1],2)+4*pow(matrix[w][1],4);
	

	return result;
}

/* F17 FUNCTION - [-5,5] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	
	result = pow((matrix[w][1] - 5.1*pow(matrix[w][0],2)/(pow(M_PI,2)*4.0) + (5.0*matrix[w][0]/3.14159265358979323846) - 6.0),2) + 10.0*0.960211264*cos(matrix[w][0]) + 10.0;	

	return result;
}

/* F18 FUNCTION - [-2,2] */
double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	double arg1 = 0.0;
	double arg2 = 0.0;	

	arg1 = (pow((matrix[w][0]+matrix[w][1]+1.0),2))*(19.0-(14.0*matrix[w][0])+(3.0*pow(matrix[w][0],2))-(14.0*matrix[w][1])+(6.0*matrix[w][0]*matrix[w][1])+(3.0*pow(matrix[w][1],2)));
	arg2 = (pow((2.0*matrix[w][0]-3.0*matrix[w][1]),2))*(18.0-(32.0*matrix[w][0])+(12.0*pow(matrix[w][0],2))+(48.0*matrix[w][1])-(36.0*matrix[w][0]*matrix[w][1])+(27.0*pow(matrix[w][1],2)));
	
	result = (1.0+arg1)*(30.0+arg2);

	return result;
}

/* F19 FUNCTION - [0,1] */
double aH[4][3] = {{3,10,30},{0.1,10,35},{3,10,30},{0.1,10,35}};
double cH[4] = {1,1.2,3,3.2};
double pH[4][3] = {{0.3689,0.117,0.2673},{0.4699,0.4387,0.747},{0.1091,0.8732,0.5547},{0.03815,0.5743,0.8828}};

double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	double arg1 = 0.0;	

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < DIMENSIONS; ++j)
		{
			arg1 += aH[i][j]*pow((matrix[w][j]-pH[i][j]),2);
		}

		arg1 = exp(-arg1);
		result += cH[i]*arg1;
		arg1 = 0.0;
	}

	result = -result;	

	return result;
}

/* F20 FUNCTION - [0,1] */
double aH[4][6] = {{10,3,17,3.5,1.7,8},{0.05,10,17,0.1,8,14},{3,3.5,1.7,10,17,8},{17,8,0.05,10,0.1,14}};
double cH[4] = {1,1.2,3,3.2};
double pH[4][6] = {{0.1312,0.1696,0.5569,0.0124,0.8283,0.5886},{0.2329,0.4135,0.8307,0.3736,0.1004,0.9991},{0.2348,0.1415,0.3522,0.2883,0.3047,0.6650},{0.4047,0.8828,0.8732,0.5743,0.1091,0.0381}};

double calcFitness(int w, double matrix[POP_SIZE][DIMENSIONS])
{
	double result = 0.0;
	double arg1 = 0.0;	

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < DIMENSIONS; ++j)
		{
			arg1 += aH[i][j]*pow((matrix[w][j]-pH[i][j]),2);
		}

		arg1 = exp(-arg1);
		result += cH[i]*arg1;
		arg1 = 0.0;
	}

	result = -result;	

	return result;
}





















