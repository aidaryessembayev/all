#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int rain;
	double temp;
	double wind;
}weather;

int totalRain(weather *data)
{
	int total = 0;
	int i = 0;
	for (i = 0; i < 12; i++)
	{
		total += (data + i)->rain;
	}
	return total;
}

double lowAver(weather *data)
{
	double min = data->temp;
	int i;

	for (i = 0; i < 12; i++)
	{
		if (min > (data + i)->temp)
		{
			min = (data + i)->temp;
		}
	}

	return min;
}

void printTable(weather *data)
{
	int i;
	printf("Rain     Avg.Temp     Avg.Wind\n");
	for (i = 0; i < 12; i++)
	{
		printf("%2i %11lg %11lg\n", (data + i)->rain, (data + i)->temp, (data + i)->wind);
	}
}

double averOfAverOfWind(weather *data)
{
	double average = 0;
	int i;

	for (i = 0; i < 12; i++)
	{
		average += (data + i)->wind;
	}

	average = average / 12;

	return average;
}

void main()
{
	setvbuf(stdout, NULL, _IONBF, 0);

	weather *data = malloc(12 * sizeof(weather));


	FILE *input = fopen("data.txt", "r");

	int i = 0;

	while (i < 12)
	{
		fscanf(input, "%i %lf %lf", &((data + i)->rain), &((data + i)->temp), &((data + i) ->wind));
		i++;

	}

	fclose(input);

	printf("Total of rainfall: %i\n", totalRain(data));
	printf("Lower average of temperatures: %lg\n", lowAver(data));
	printf("Average of wind speed averages: %lg\n", averOfAverOfWind(data));
	printf("\n");
	printTable(data);
}
