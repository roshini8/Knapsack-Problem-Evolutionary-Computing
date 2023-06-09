#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;
//declare constant: 
//1. What are the problem criteria that are suitable to be a constant?
//2. What are the algorithm fixed parameters?
//declare chromosomes data structure
//3. What is your chromosome structure?


const int gene = 10;
const int popsize = 30;
const int capacity = 165;
const double SUM_VALUE = 699;
const int weight[gene] = { 23, 31, 29, 44, 53, 38, 63, 85, 89, 82 };
const int value[gene] = { 92, 57, 49, 68, 60, 43, 67, 84, 87, 92 };
int chromosomes[popsize][gene];
double fitness[popsize];
int parents[2][gene];
int children[2][gene];
int newchromosomes[popsize][gene];
const double crossprob = 0.9;
const double MUT_PROBABILITY = 0.1;
int newchromosomescounter = 0;
const int maxgeneration = 20;
ofstream averageFitnessFile;
ofstream bestFitnessFile;
ofstream bestChromosomeFile;
float bestFitness = -1;
int bestChromosome[gene];

void initializePopulation() {

	for (int c = 0; c < popsize; c++) {
		int total = 0;
		for (int g = 0; g < gene; g++) {
			chromosomes[c][g] = rand() % 2;
			total += weight[g] * chromosomes[c][g];
		}

	}

	//1. For every chromosome, c
	//1.1 For every genes, g, in the chromosome, c
	//1.1.1 Generate either 0 or 1
	//1.1.2 Assign to the g of c
}

void printChromosome() {

	for (int c = 0; c < popsize; c++) {

		for (int g = 0; g < gene; g++) {
			cout << chromosomes[c][g] << "\t";


		}
		cout << endl << endl;

		//1. For every chromosome, c
		//1.1 Print Chromosome number
		//1.2 For every genes g, in the chromosome, c
		//1.2.3 Print g of c
	}
}

void evaluateChromosomes() {




	for (int c = 0; c < popsize; c++) {
		int totalWeight[popsize] = { 0 };
		int totalValue[popsize] = { 0 };

		for (int g = 0; g < gene; g++) {
			totalWeight[c] += (chromosomes[c][g] * weight[g]);
			totalValue[c] += (chromosomes[c][g] * value[g]);


		}
		cout << "Total Weight : " << totalWeight[c] << "\t";
		cout << "Total Value : " << totalValue[c] << "\t";


		double FitnessFunction = 0;

		if (totalWeight[c] > capacity) {
			fitness[c] = (totalValue[c] / SUM_VALUE) * 0.5;
			cout << "Fitness Value of c : " << fitness[c] << endl << endl;
		}
		else if (totalWeight[c] <= capacity) {
			fitness[c] = totalValue[c] / SUM_VALUE;
			cout << "Fitness Value of c : " << fitness[c] << endl << endl;
		}
	}


}

//declare parent’s data structure
void parentSelection() {
	//declare necessary variables
	//1. For both parents
	//1.1 Pick a random number to be the index for player 1
	//1.2 Pick another random number to be the index for player 2
	//1.3 Compare fitness between player 1 and 2, pick the best one to be

		//2. Repeat (1) for parent 2
		//3. Copy selected parents to array parents
		//4. Print parent 1 and 2
		//NOTE: After you are done, improve your code to avoid the same number picked for
		//player 1 and player 2, and also avoid the same chromosome picked for parent 1
		//and 2

	int player1, player2, player3;
	int indexParents[2];

	for (int p = 0; p < 2; p++) {
		player1 = rand() % popsize;
		do {
			player2 = rand() % popsize;
		} while (player2 == player1);

		do {
			player3 = rand() % popsize;
		} while ((player3 == player2) && (player3 == player1));


		if (fitness[player1] >= fitness[player2])
			indexParents[p] = player1;
		else if (fitness[player1] >= fitness[player3])
			indexParents[p] = player1;
		else if (fitness[player2] >= fitness[player3])
			indexParents[p] = player2;
		else
			indexParents[p] = player3;

		cout << "\n\tPlayer's index: " << player1 << " vs " << player2 << " vs " << player3;
		cout << "\n\tFitness " << fitness[player1] << " vs " << fitness[player2] << " vs " << fitness[player3];
		cout << "\n\t Winner " << p + 1 << ": " << indexParents[p] << endl;


	}

	for (int p = 0; p < 2; p++) {
		cout << "\tParent " << p + 1 << "\t";
		for (int g = 0; g < gene; g++) {
			parents[p][g] = chromosomes[indexParents[p]][g];
			cout << parents[p][g] << " ";

		}
		cout << endl;
	}
}

void crossover() {
	int co_point = 0;
	//1. Copy both parent’s chromosome to children chromosomes
	//2. Generate a random number from 0-1. Make sure it is real value data

		//3. If (2) less than crossover probability
		//2.1 generate a random crossover point
		//2.2 Crossover parent 1 and parent 2 to produce the children
		//4. Print children 1 & 2
	cout << "\n\tChildren before Crossover " << endl;
	for (int ch = 0; ch < 2; ch++) {
		cout << "Children " << ch << "\t";
		for (int g = 0; g < gene; g++) {
			children[ch][g] = parents[ch][g];
			cout << children[ch][g] << " ";

		}
		cout << endl;
	}
	srand(time(NULL));
	int randNum = (rand() % 11) / 10.0;
	cout << "\n\t randNum : " << randNum;
	if (randNum <= crossprob) {
		co_point = (rand() % gene);
		cout << "\n\t CO happned at Cross Over Point " << co_point;
	}

	for (int g = co_point; g < gene; g++) {
		children[0][g] = parents[1][g];
		children[1][g] = parents[0][g];
	}

	cout << "\n\t Children after Crossover : ";
	for (int c = 0; c < 2; c++) {
		cout << "\n\tChildren " << c << "\t";
		for (int g = 0; g < gene; g++) {
			cout << children[c][g] << " ";
		}
	}
	cout << endl;
}

//declare MUTATION_PROBABILITY as a constant
void mutation() {
	//1. Declare necessary variables
	//2. Declare mutation bit
	//3. For both children
	//3.1. Generate number from 0-1 (real values)
	//3.2. If 3.1 less than mutation probability
	//3.2.1. generate a mutation bit
	//3.2.2. Print the mutation bit
	//3.2.3. Flip the mutation bit (if condition)
	//End if
	//End for
	//5. Print the mutated chromosomes
	double randNumber;
	int mutIndex;
	for (int ch = 0; ch < 2; ch++) {
		randNumber = double(rand() % 11) / 10.0;
		cout << "\n\t randNum " << randNumber;
		if (randNumber < MUT_PROBABILITY) {
			mutIndex = rand() % gene;
			cout << "\n\t Mutation will happen at index : " << mutIndex;

			if (children[ch][mutIndex] == 0)
				children[ch][mutIndex] = 1;
			else
				children[ch][mutIndex] = 0;
		}
	}
	cout << "\n\t Children after Mutation: ";
	for (int c = 0; c < 2; c++) {
		cout << "\n\t Children " << c << "\t";
		for (int g = 0; g < gene; g++) {
			cout << children[c][g] << " ";
		}
	}



	cout << endl << endl;

}

void survivalSelection() {
	//1. For each chromosome
	//1.2. For each gene
	//1.3 Copy children to the survival chromosome array
	//2. Update array counter
	//3. Print chromosomes in the new population so far
	for (int c = 0; c < 2; c++) {
		for (int g = 0; g < gene; g++) {
			newchromosomes[newchromosomescounter][g] = children[c][g];

		}
		newchromosomescounter++;
	}





	cout << "\n\t New chromosomes so far : ";
	for (int c = 0; c < popsize; c++) {
		cout << "\n\t Children " << c << "\t";
		for (int g = 0; g < gene; g++) {
			cout << newchromosomes[c][g] << " ";
		}
	}
	cout << endl;
}

//copy chromosome to the original data structure
void copyChromosome() {
	for (int c = 0; c < popsize; c++) {
		for (int g = 0; g < gene; g++) {
			chromosomes[c][g] = newchromosomes[c][g];
		}
	}

}

void calculateAverageFitness()
{
	float totalFitness = 0;
	float avgFitness;

	for (int c = 0; c < popsize; c++) {
		totalFitness = totalFitness + fitness[c];
	}
	avgFitness = totalFitness / popsize;

	cout << "\n\t Average Fitness : " << avgFitness;
	averageFitnessFile << avgFitness << endl;

}

void recordBestFitness() {
	for (int c = 0; c < popsize; c++) {
		if (fitness[c] >= bestFitness) {
			bestFitness = fitness[c];
		}
		for (int g = 0; g < gene; g++) {
			bestChromosome[g] = chromosomes[c][g];
		}
	}
	cout << "\n\t Best Fitness = " << bestFitness;
	cout << "\n\t Best Chromosome = ";
	for (int g = 0; g < gene; g++) {
		cout << bestChromosome[g];
	}
	cout << endl;
	bestFitnessFile << bestFitness << endl;
	for (int g = 0; g < gene; g++) {
		bestChromosomeFile << bestChromosome[g];
	}
	bestChromosomeFile << endl;
}


int main() {

	averageFitnessFile.open("AverageFitness.txt");
	bestFitnessFile.open("BestFitness.txt");

	cout << "INITIALIZE POPULATION :" << endl;
	initializePopulation();

	for (int generation = 0; generation < maxgeneration; generation++) {
		cout << "\n\nGeneration : " << generation + 1 << endl << endl;
		newchromosomescounter = 0;


		printChromosome();
		cout << "\n\nEVALUATE CHROMOSOMES " << endl;
		evaluateChromosomes();
		calculateAverageFitness();
		recordBestFitness();

		for (int c = 0; c < popsize / 2; c++) {


			cout << "\n\nPARENT SELECTION " << endl;
			parentSelection();

			cout << "\n\n Crossover " << endl;
			crossover();

			cout << "\n\n Mutation " << endl;
			mutation();

			cout << "\n\n Survival Selection " << endl;
			survivalSelection();
		}

		cout << "\n\n Copy Chromosomes : DONE" << endl;
		copyChromosome();
	}

	averageFitnessFile.close();
	bestFitnessFile.close();
	system("pause");
}