#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M_PI 3.14159265358979323846

#define POP_SIZE 20
#define DIMENSIONS 30
#define INTERVAL_X 100
#define INFLUENCERS 3
#define QUITTERS 0
#define TETA 1	//probability of approximating the influencer by the mean distance
#define OMEGA 0.7

#define RUNS 30
#define ITER_MAX 500

double population[POP_SIZE][DIMENSIONS];
double fitnessValues[POP_SIZE][2];
double goodStructures[DIMENSIONS];
double A[DIMENSIONS];
int functionEvaluations = 500000;

double checking = 0.0;
int counting = 0;

double calcMean(double matrix[POP_SIZE][DIMENSIONS], int w)
{
	double mean = 0.0;
	for (int i = 0; i < 2*INFLUENCERS; ++i)
	{
		mean += matrix[i][w];
	}

	mean = mean/(2*INFLUENCERS);

	return mean;
}

double calStandardDeviation(double matrix[POP_SIZE][DIMENSIONS], int j)
{
	double mean = 0.0;
	double stdDev = 0.0;
	
	mean = calcMean(matrix,j);

	for (int i = 0; i < INFLUENCERS; ++i)
	{
		stdDev += pow((matrix[i][j] - mean),2);
	}
	stdDev = sqrt(stdDev/POP_SIZE);
	
	return stdDev;	
}

/* random number between -INTERVAL_X and INTERVAL_X*/
double randomX()
{
	double x = ((rand() % RAND_MAX)/(double)(RAND_MAX - 1));
	x = x*INTERVAL_X;
	double sign = ((rand() % RAND_MAX)/(double)(RAND_MAX - 1));
	if(sign > 0.5) {x = (-1)*x;}
	return x;
}

/* random number between 0 and 1*/
double random01()
{
	double x = ((rand() % RAND_MAX)/(double)(RAND_MAX - 1));		
	return x;
}

/* initialize all values of matrix to 0 */
void resetMatrix(double matrix[POP_SIZE][DIMENSIONS])
{
	for (int i = 0; i < POP_SIZE; ++i)
	{
		for (int j = 0; j < DIMENSIONS; ++j)
		{
			matrix[i][j] = 0.0;
		}
	}
}

/* initialize population */
void initialPop(double matrix[POP_SIZE][DIMENSIONS])
{
	for (int i = 0; i < POP_SIZE; ++i)
	{
		for (int j = 0; j < DIMENSIONS; ++j)
		{
			matrix[i][j] = randomX();
		}
	}
}
//==================================================================================================
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
//==================================================================================================

void calcFitnessValues(double levels[POP_SIZE][2], double matrix[POP_SIZE][DIMENSIONS])
{
	for (int i = 0; i < POP_SIZE; ++i)
	{
		levels[i][0] = i;		
		levels[i][1] = calcFitness(i,matrix);
		functionEvaluations--;		
	}
}

void sortByFitness(double levels[POP_SIZE][2])
{
	double temp[POP_SIZE][2];	
	double min = 10000000000000000;
	int individual = 0;
	
	for (int count = 0; count < POP_SIZE; ++count)
	{
		for (int i = 0; i < POP_SIZE; ++i)
		{
			if (levels[i][1] < min && levels[i][1] != 10000000000000000)
			{
				min = levels[i][1];
				individual = i;
			}
		}
		
		temp[count][0] = individual;
		temp[count][1] = min;
		min = 10000000000000000;
		levels[individual][1] = 10000000000000000;
	}

	for (int i = 0; i < POP_SIZE; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			levels[i][j] = temp[i][j];
		}
	}
}

void printMatrix(double matrix[POP_SIZE][DIMENSIONS])
{
	for (int i = 0; i < POP_SIZE; ++i)
	{
		for (int j = 0; j < DIMENSIONS; ++j)
		{
			printf("%.2lf ", matrix[i][j]);
		}
		printf("-> %.2lf", calcFitness(i, matrix));
		printf("\n");
	}
}

void printTable(double matrix[POP_SIZE][2])
{
	for (int i = 0; i < POP_SIZE; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			printf("%.3lf ", matrix[i][j]);
		}
		printf("\n");
	}
}

void sortPopulation(double vector[POP_SIZE][2], double matrix[POP_SIZE][DIMENSIONS])
{
	double temp[POP_SIZE][DIMENSIONS];
	int id = 0;

	for (int x = 0; x < POP_SIZE; ++x)
	{
		id = vector[x][0];

		for (int i = 0; i < DIMENSIONS; ++i)
		{
			temp[x][i] = matrix[id][i];
		}
	}

	for (int i = 0; i < POP_SIZE; ++i)
	{
		for (int j = 0; j < DIMENSIONS; ++j)
		{
			matrix[i][j] = temp[i][j];
		}
	}
}

double calcDistance(double matrix[POP_SIZE][DIMENSIONS], int x, int y)
{
	double distance = 0.0;

	for (int i = 0; i < DIMENSIONS; ++i)
	{
		distance += pow((matrix[y][i] - matrix[x][i]),2);
	}

	return sqrt(distance);
}

double calcInfluence(double matrix[POP_SIZE][DIMENSIONS], int x, int y)
{
	double oppinionNormalized = 0.0;
	double distance = 0.0;
	double infuence = 0.0;

	oppinionNormalized = abs(calcFitness(x, matrix)-calcFitness(y, matrix))/calcFitness(y, matrix);	
	distance = (1/calcDistance(matrix,x,y))*0.2;

	//printf("Fitness: %lf\n", calcFitness(y, matrix));	
	//printf("Distance: %lf\n", calcDistance(matrix,x,y));	
	//printf("Influence: %lf\n", infuence);
	//printf("---------------------------------------------\n");

	infuence = oppinionNormalized+distance;	

	return infuence;
}

int decideInfluencer(double matrix[POP_SIZE][DIMENSIONS], int y)
{
	double total = 0.0;
	double influence1 = calcInfluence(matrix, 0, y);
	double influence2 = calcInfluence(matrix, 1, y);
	double influence3 = calcInfluence(matrix, 2, y);
	double randomNum = 0.0;

	total = influence1 + influence2 + influence3;
	influence1 = ((100*influence1)/total)/100;
	influence2 = ((100*influence2)/total)/100;
	influence3 = ((100*influence3)/total)/100;

	//printf("%lf\n", influence1);
	//printf("%lf\n", influence2);
	//printf("%lf\n", influence3);
	
	randomNum = random01();

	if (randomNum <= influence1)
	{
		return 1;
	}
	else if (randomNum > influence1 && randomNum <= influence1+influence2)
	{
		return 2;
	}
	else
	{
		return 3;
	}	
}

void newInfluencedPoint(double matrix[POP_SIZE][DIMENSIONS], int influencer, int influenced)
{
	double add = random01();
	double choose = random01();
	double intervalToAdd = 0.0;
	double approache = random01();
	double sign = random01();		

	if (approache < 0.5)
	{
		approache = 0.5;
	}

	if (choose <= TETA)
	{		
		for (int i = 0; i < DIMENSIONS; ++i)
		{			

			if (matrix[influenced][i] > 0 && matrix[influencer][i] > 0)
			{
				intervalToAdd = matrix[influencer][i]-matrix[influenced][i];
				if (intervalToAdd == 0)
				{
					intervalToAdd = 1.0;
				}
				intervalToAdd = intervalToAdd*approache;
				if (sign > OMEGA)
				{
					matrix[influenced][i] = -(matrix[influenced][i]+intervalToAdd);					
					//printf("%lf\n", matrix[influenced][i]);
				}
				else
				{
					matrix[influenced][i] = matrix[influenced][i]+intervalToAdd;
					//printf("%lf\n", matrix[influenced][i]);
				}
				
			}
			else if (matrix[influenced][i] < 0 && matrix[influencer][i] < 0)
			{
				intervalToAdd = matrix[influencer][i]+((-1)*matrix[influenced][i]);
				if (intervalToAdd == 0)
				{
					intervalToAdd = 1.0;
				}	
				intervalToAdd = intervalToAdd*approache;
				if (sign > OMEGA)
				{
					matrix[influenced][i] = -(matrix[influenced][i]+intervalToAdd);
					//printf("%lf\n", matrix[influenced][i]);
				}
				else
				{
					matrix[influenced][i] = matrix[influenced][i]+intervalToAdd;
					//printf("%lf\n", matrix[influenced][i]);

				}
			}
			else if (matrix[influenced][i] < 0 && matrix[influencer][i] > 0)
			{
				intervalToAdd = matrix[influencer][i]+((-1)*matrix[influenced][i]);
				if (intervalToAdd == 0)
				{
					intervalToAdd = 1.0;
				}	
				intervalToAdd = intervalToAdd*approache;
				if (sign > OMEGA)
				{
					matrix[influenced][i] = -(matrix[influenced][i]+intervalToAdd);
					//printf("%lf\n", matrix[influenced][i]);
				}
				else
				{
					matrix[influenced][i] = matrix[influenced][i]+intervalToAdd;
					//printf("%lf\n", matrix[influenced][i]);
				}
			}
			else if (matrix[influenced][i] > 0 && matrix[influencer][i] < 0)
			{
				intervalToAdd = matrix[influencer][i]-matrix[influenced][i];
				if (intervalToAdd == 0)
				{
					intervalToAdd = 1.0;
				}
				intervalToAdd = intervalToAdd*approache;
				if (sign > OMEGA)
				{
					matrix[influenced][i] = -(matrix[influenced][i]+intervalToAdd);
					//printf("%lf\n", matrix[influenced][i]);
				}
				else
				{
					matrix[influenced][i] = matrix[influenced][i]+intervalToAdd;
					//printf("%lf\n", matrix[influenced][i]);
				}	
			}
			//intervalToAdd = fabs(matrix[influenced][i])
			//matrix[influenced][i] = (matrix[influencer][i]+matrix[influenced][i])/2;
			//printf("%lf\n", intervalToAdd);
			
			checking += intervalToAdd;
			counting++;					
		}		
	}	
	else
	{		
		for (int i = 0; i < DIMENSIONS; ++i)
		{
			if (random01() > 0.5)
			{			
				if (matrix[influencer][i] > 0)
				{
					matrix[influenced][i] = matrix[influencer][i]+add;
				}
				else
				{
					matrix[influenced][i] = matrix[influencer][i]-add;
				}
			}
			else
			{
				if (matrix[influencer][i] < 0)
				{
					matrix[influenced][i] = matrix[influencer][i]+add;
				}
				else
				{
					matrix[influenced][i] = matrix[influencer][i]-add;
				}
			}			
		}		
	}
}

int pause = 0;

void crossover01(double matrix[POP_SIZE][DIMENSIONS])
{
	int parent1 = rand() % 5;
	int parent2 = rand() % (POP_SIZE-5);
	int crossPoint = rand() % (DIMENSIONS-1);

	if (crossPoint < 0)
	{
		crossPoint = 1;
	}

	if (parent2 <= 4)
	{
		parent2 = parent2+5;
	}

	for (int i = 0; i < crossPoint; ++i)
	{
		matrix[16][i] = matrix[parent1][i];
	}

	for (int i = crossPoint; i < DIMENSIONS; ++i)
	{
		matrix[16][i] = matrix[parent2][i];
	}

	for (int i = 0; i < crossPoint; ++i)
	{
		matrix[17][i] = matrix[parent2][i];
	}

	for (int i = crossPoint; i < DIMENSIONS; ++i)
	{
		matrix[17][i] = matrix[parent1][i];
	}

	int parent3 = rand() % 5;
	int parent4 = rand() % (POP_SIZE-5);
	crossPoint = rand() % (DIMENSIONS-1);

	while (parent3 == parent1 || parent3 == parent2)
	{
		parent3 = rand() % 5;
	}

	if (crossPoint == 0)
	{
		crossPoint = 1;
	}

	if (parent4 <= 4)
	{
		parent4 = parent4+5;
	}

	while (parent4 == parent1 || parent4 == parent2 || parent4 == parent3)
	{
		parent4 = rand() % (POP_SIZE-5);
		if (parent4 <= 4)
		{
			parent4 = parent4+5;
		}				
	}	

	for (int i = 0; i < crossPoint; ++i)
	{
		matrix[18][i] = matrix[parent3][i];
	}

	for (int i = crossPoint; i < DIMENSIONS; ++i)
	{
		matrix[18][i] = matrix[parent4][i];
	}

	for (int i = 0; i < crossPoint; ++i)
	{
		matrix[19][i] = matrix[parent4][i];
	}

	for (int i = crossPoint; i < DIMENSIONS; ++i)
	{
		matrix[19][i] = matrix[parent3][i];
	}		
}

int main ()
{
	srand(time(0));

	double avgBest = 0.0;
	double bestSol = 0.0;
	double tBest = 0.0;
	double tWorst = 0.0;
	double first = 0.0;	

	for (int y = 0; y < RUNS; ++y)
	{		
		int influencer = 0.0;	

		//scanf("%d",&pause);

		/* generates random initial population */
		initialPop(population);
		/* stores in a table the id of the individual and its fitness value */
		calcFitnessValues(fitnessValues,population);
		/* sorts table with id and fitness values by fitness */
		sortByFitness(fitnessValues);
		/* sorts the matrix of individuals by their fitness */	
		sortPopulation(fitnessValues, population);		

		bestSol = calcFitness(0, population);			
		first = calcFitness(0, population);

		//printMatrix(population);
		//scanf("%d",&pause);

		//printf("%d %.58lf\n", 1, first);


		/*-----------------------------------------------------------------------*/

		//while(functionEvaluations > 0)
		for (int will = 1; will < ITER_MAX; ++will)		
		{				
			//for (int i = INFLUENCERS; i < POP_SIZE; ++i)
			for (int i = INFLUENCERS; i < POP_SIZE; ++i)		
			{
				/* decides wich one of the best ones will be the influencer */
				influencer = decideInfluencer(population, i);
				/* changes the opinion of the influenced based on the influencer's opinion */
				newInfluencedPoint(population,influencer,i);		
			}			

			/* stores in a table the id of the individual and its fitness value */
			calcFitnessValues(fitnessValues,population);
			/* sorts table with id and fitness values by fitness */
			sortByFitness(fitnessValues);
			/* sorts the matrix of individuals by their fitness */	
			sortPopulation(fitnessValues, population);
			/* operates single point crossover in a given pair of individuals */
			crossover01(population);

			calcFitnessValues(fitnessValues,population);		
			sortByFitness(fitnessValues);		
			sortPopulation(fitnessValues, population);

			if (calcFitness(0,population) < bestSol)
			{
				bestSol = calcFitness(0, population);
				//printf("Best solution: %.5lf\n", bestSol);
			}

			//printMatrix(population);
			//scanf("%d",&pause);		
			//printf("%d %.58lf\n", will+1, bestSol);
		}		   							

		avgBest += bestSol;
		printf("RUN: %d\n", y);				
		//printMatrix(population);				

		if (y == 0)
		{
			tWorst = bestSol;
			tBest = bestSol;
		}
		else
		{
			if (bestSol > tWorst)
			{
				tWorst = bestSol;
			}
			if (bestSol < tBest)
			{
				tBest = bestSol;
			}
		}
	}

	printf("Ave: %.57lf\n", (avgBest/RUNS));
	printf("Best: %.60lf\n", tBest);
	printf("Worst: %.60lf\n", tWorst);
	printf("Checking: %.10lf\n", (checking/counting));
	printf("First: %.1lf\n", first);


	int t = 1;
	double b = 0.75;

	printf("%lf\n", (sqrt(1)));


	return 0;
}



