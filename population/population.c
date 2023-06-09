#include <cs50.h>
#include <stdio.h>

int startingPopulation, endingPopulation;
void Years(void);
int main(void)
{
    do{
        startingPopulation = get_int("Start size: ");
    }while(startingPopulation < 9);

    do{
        endingPopulation = get_int("End Size: ");
    }while(endingPopulation < startingPopulation);

    Years();
}


void Years(void)
{
    int new, dead, years, population;

    population = startingPopulation;
    for(int i = 1; population < endingPopulation; i++){
        new = population / 3;
        dead = population / 4;
        population = population + new - dead;
        years = i;
    }

    printf("Years: %i\n", years);
}