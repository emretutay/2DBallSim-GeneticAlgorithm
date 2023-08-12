#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>

#include "Ball.h"
#include "Init_Game.h"


using namespace std;

// Constants-Parameters of the BGA
#define N 100    // size of population
#define T 100     // max number of generations
#define UB 3000.0   // upper bound (same for both decision variables)
#define LB -3000.0  // lower bound (same for both decision variables)
#define PC 1.0    // probability of crossover
#define PM 0.3    // probability of mutation
#define ALPHA 0.5 // alpha parameter for BLX-a crossover
#define ETA_M 5.0 // eta parameter for polynomial mutation




class RGA{



public:
    // Data Structure of Chromosome
    struct chrom
    {
        double Vx;        // decision variable 1 (real value)
        double Vy;        // decision variable 1 (real value)
        double objF_val;  // value of the objective function
        double fitness;   // fitness of the individual
    };

    // Utility to compare chromosomes in terms of their fitness (for sorting function)
    struct compareChroms
    {
        inline bool operator()(const chrom &obj1, const chrom &obj2)
        {
            return (obj1.fitness < obj2.fitness);
        }
    };





    // Function prototypes
    void initializeRandomPop(vector<chrom> &);
    chrom initializeRandomIndividual();
    bool evaluate(vector<chrom> &);
    vector<chrom> selection(vector<chrom> &);
    void variation(vector<chrom> &);
    double blxaOnDecisionVariable(double, double);
    void crossover(chrom &, chrom &);
    void polynomialMutation(double &);
    void mutation(chrom &);
    void survival_nonElitist(vector<chrom> &, vector<chrom> &);
    void survival_elitist(vector<chrom> &, vector<chrom> &);
    



};
