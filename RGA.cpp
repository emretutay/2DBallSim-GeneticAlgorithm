#include "RGA.h"





/* 
    Initialize a random chromosome as a binary string

    @return individual   Returns created individual

    Time Complexity : O(1) Constant Time
    Space Complexity : O(1) Constant Space
*/
RGA::chrom RGA::initializeRandomIndividual()
{
    chrom individual;
    individual.Vx = ((double)rand() / RAND_MAX) * (UB - LB) + LB;
    individual.Vy = ((double)rand() / RAND_MAX) * (UB - LB) + LB;

    return individual;
}

/*
    Initialize the entire population of individuals

    @param  &pop   Reference of a vector of individuals

    Time Complexity : O(n) Linear Time
    Space Complexity : O(n) Linear Space
*/ 
void RGA::initializeRandomPop(vector<chrom> &pop)
{
    for (int i = 0; i < N; i++)
    {
        pop.push_back(initializeRandomIndividual());
    }
}



/*
    Evaluate a single chromosome

    @param  &pop   Reference of a vector of individuals
    @return end    True if user closes app, else false

    Time Complexity : O(n) Linear Time
    Space Complexity : O(n) Linear Space
*/ 
bool RGA::evaluate(vector<chrom> &pop)
{  
    float totalFitness = 0.0f; 
     vector<Ball> ballsPop;
    for (int i = 0; i < N; i++)
    {   
        // Setting the values of the balls
        float Vx = pop[i].Vx;
        float Vy = pop[i].Vy;
        float sPosX = 400.0f;
        float sPosY = 50.0f;
        float radius = 8.0f;
        float mass = 100.0f;
        Ball ballPop(sPosX,sPosY,Vx,Vy,0,0,radius,mass);
        ballsPop.push_back(ballPop);
        
       
    }
    Init_Game game = Init_Game(ballsPop); // Initializing the game with the balls
    ballsPop.clear();

    vector<Ball> return_pop = game.returnBalls(); // Return the balls in their final position
    bool end = game.returnEnd();        // Checking if the user wants to close the app

    int i = 0;
    for(auto& ball : return_pop){ 
        
        float ePosX = ball.getX(); // Getting final position
        float ePosY = ball.getY();

        float goalX = 400;  // Goal position
	    float goalY = 600;

        // Fitness is the distance to the goal position
        float Dist = sqrtf((ePosX - goalX)*(ePosX - goalX) + (ePosY - goalY)*(ePosY - goalY)); 

        pop[i].fitness = Dist;
        
        i++;

    }

    for(int i = 0; i < N; i++){ // Calculating total fitness
        float fit = pop[i].fitness;
        totalFitness += fit;
    }

    float averageFitness = totalFitness / N;  // Calculating average fitness
    cout << "average fitness : " << averageFitness << endl;
    return end;
    
}

/* Binary Tournament Selection operator

    @param  &pop   Reference of a vector of individuals
    @return  Returns vector of selected individuals

    Time Complexity : O(n) Linear Time
    Space Complexity : O(n) Linear Space
*/
vector<RGA::chrom> RGA::selection(vector<chrom> &pop)
{
    vector<chrom> mat; // Maring pool will contain copies of individuals from the population (you could also use references, I chose to have copies such that the mating pool and the offspring population are the same objects)

    for (int i = 0; i < N; i++)
    {
        unsigned int i1 = rand() % N;
        unsigned int i2 = rand() % N;
        if (pop[i1].fitness < pop[i2].fitness)
            mat.push_back(pop[i1]);
        else
            mat.push_back(pop[i2]);
    }

    return mat;
}



/*  
    BLX-alpha crossover

    @param x_p1  Parent 1
    @param x_p1  Parent 2

    @return  off  Offspring


    Time Complexity : O(1) Constant Time
    Space Complexity : O(1) Constant Space
*/ 
double RGA::blxaOnDecisionVariable(double x_p1, double x_p2)
{
    double off = 0.0;
    if (x_p1 > x_p2)
    {
        // Swap if parent 1 bigger
        double temp = x_p1;
        x_p1 = x_p2;
        x_p2 = temp;
    }

    double u = (rand() % 100) / 100.0;
    double gamma = ((1.0 + 2.0 * ALPHA) * u) - ALPHA;
    off = ((1.0 - gamma) * x_p1) + (gamma * x_p2);
    off = max(min(off, UB), LB);
    return off;
}


/*

    Crossover Operator

    @param &p1  Parent 1
    @param &p2  Parent 2

    Time Complexity : O(1) Constant Time
    Space Complexity : O(1) Constant Space


*/
void RGA::crossover(RGA::chrom &p1, RGA::chrom &p2)
{
    float r = (rand() % 100) / 100.0f; // Generates a number between 0.0 and 0.99
    if (r <= PC)
    {
        double off1_Vx = blxaOnDecisionVariable(p1.Vx, p2.Vx);
        double off2_Vx = blxaOnDecisionVariable(p1.Vx, p2.Vx);
        double off1_Vy = blxaOnDecisionVariable(p1.Vy, p2.Vy);
        double off2_Vy = blxaOnDecisionVariable(p1.Vy, p2.Vy);
        p1.Vx = off1_Vx;
        p2.Vx = off2_Vx;
        p1.Vy = off1_Vy;
        p2.Vy = off2_Vy;
    }
}


/*
    Polynomial Mutation

    @param &x   Gene to be mutated

    Time Complexity : O(1) Constant Time
    Space Complexity : O(1) Constant Space



*/
void RGA::polynomialMutation(double &x)
{
    double delta = 0.0;
    float r = (rand() % 100) / 100.0f; // Generates a number between 0.0 and 0.99
    if (r < 0.5)
    {
        // formula 1
        delta = pow((2.0 * r), (1.0 / (ETA_M + 1.0))) - 1.0;
    }
    else
    {
        // formula 2
        delta = 1.0 - pow((2.0 - 2.0 * r), (1.0 / (ETA_M + 1.0)));
    }
    x = x + (UB - LB) * delta;
    x = max(min(x, UB), LB);
}



/*
    Mutation Operator

    @param   &ind     Reference of the individual

    Time Complexity : O(1) Constant Time
    Space Complexity : O(1) Constant Space


*/

void RGA::mutation(RGA::chrom &ind)
{
    float r = (rand() % 100) / 100.0f; // Generates a number between 0.0 and 0.99
    if (r <= PM)
    {
        polynomialMutation(ind.Vx);
        polynomialMutation(ind.Vy);
    }
}
/*
    Variation is crossover+mutation, will create the population of offspring

    @param   &off  The reference of the vector that contains offspring

    Time Complexity : O(n)  Linear Time
    Space Complexity : O(n) Linear Space

*/
void RGA::variation(vector<RGA::chrom> &off)
{

    random_shuffle(off.begin(), off.end()); // This is to create random pairs of parents. Somehow it didn't work on my compiler, that's why it's commented...

    for (int i = 0; i < N; i += 2)
    {
        crossover(off[i], off[i + 1]); // Perform crossover on the pair
        mutation(off[i]);              // Mutate first child
        mutation(off[i + 1]);          // Mutate second child
    }
}


/* Non-elitist survival method

   @param  &pop   Reference of a vector of individuals 
   @param   &off  The reference of the vector that contains offspring

   Time Complexity : O(1) Constant Time
   Space Complexity : O(n) Linear Space


*/
void survival_nonElitist(vector<RGA::chrom> &pop, vector<RGA::chrom> &off)
{
    pop = off;
    sort(pop.begin(), pop.end(), RGA::compareChroms()); // Sort population from smallest to largest fitness
}

/*  Elitist survival method (mu+lambda scheme)

    @param  &pop   Reference of a vector of individuals 
    @param   &off  The reference of the vector that contains offspring

    Time Complexity : O(n) Linear Time
    Space Complexity : O(n) Linear Space

*/ 
void survival_elitist(vector<RGA::chrom> &pop, vector<RGA::chrom> &off)
{

    for (int i = 0; i < N; i++)
    {
        pop.push_back(off[i]);
    }

    sort(pop.begin(), pop.end(), RGA::compareChroms()); // Sort population from smallest to largest fitness

    for (int i = 0; i < N; i++)
    {
        pop.pop_back();
    }
}




int main(int argc, char *argv[])
{
    RGA rga;
    srand(time(NULL)); // used to generate pseudo-random numbers based on time of the execution
    vector<RGA::chrom> pop;
    rga.initializeRandomPop(pop);
    bool endApp = rga.evaluate(pop);
    if (endApp == 1)
        {   
            cout << " \n ***** \n ***** \n Application quit \n \n ***** \n ***** " << endl;
            return 0;
        }
    cout << 0 << ") Best: " << pop[0].fitness << " <" << pop[0].Vx << ", " << pop[0].Vy << "> \n";    
    for (int i = 0; i < T; i++)
    {
        vector<RGA::chrom> off = rga.selection(pop); // Node: selection should return a mating pool (possible with references rather than copies); however, I decided to have copies and create offspring directly.
        rga.variation(off);
        endApp = rga.evaluate(off);
        if (endApp == 1)
        {   
            cout << " \n ***** \n ***** \n Application quit \n \n ***** \n ***** " << endl;
            return 0;
        }
        
        // survival_nonElitist(pop,off);
        survival_elitist(pop, off);
        cout << i + 1 << ") Best: " << pop[0].fitness << " <" << pop[0].Vx << ", " << pop[0].Vy << "> \n";
        cout << endl;

    }
    cout << " \n ***** \n ***** \n Application ended \n \n ***** \n ***** " << endl;
    return 0;
}