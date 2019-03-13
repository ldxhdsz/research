//
//  main.cpp
//  Evaluation
//
//  Created by リディ on 25/12/2017.
//  Copyright © 2017 リディ. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "time.h"
#include "unistd.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <Python/Python.h>

#define POPULATION_SIZE 200
#define MUTATION_RATE 80.0
#define SIZE 100
#define NUM_OF_CLS 2
#define MAX_GENERATION 100
#define NUM_OF_TARGETS 1000
#define LETTER_NUM 2
#define NUM_OF_SAMPLE 10000

using namespace std;

static string truelabel[NUM_OF_SAMPLE];
static string result[NUM_OF_SAMPLE];

typedef struct _modification
{
    int perturbation_s1;
    int perturbation_s2;
}modification;

void dataMod1 (char dna[SIZE][2])
{//1
    
    string out_file;
    string line;
    string array[NUM_OF_SAMPLE/2];
    string finddna;
    int a = 0;
    int count = 0;
    
    //load dataset
    ifstream inf1;
    inf1.open("/Users/lidi/Desktop/GAtestdata/original_sample1.txt");

    printf("loading dataset\n");
    if(inf1)
    {//2
        while(getline(inf1, line))
        {//3
            array[a] = line;
            a++;
        }//3
    }//2
    else
    {//2
        cout << "can't find original sample" << endl;
    }//2
    
    printf("modifying text samples....\n");
    
    string::size_type position;
    
    for(int i=0; i < NUM_OF_SAMPLE/2; i++)
    {//2
        for(int j=0; j<SIZE; j++)
        {//3
            finddna += dna[j][0];
            finddna += dna[j][1];
            
        conti:
            position = array[i].find(finddna);
            if(position != array[i].npos)
            {//4
                array[i][position] = dna[j][1];
                array[i][position+1] = dna[j][0];
                count ++;
                if(count == 3)
                {//5
                    goto next;
                }//5
                else
                {//5
                    goto conti;
                }//5
            }//4
            else
            {//4
                finddna = "";
            }//4
        }//3
    next:
        finddna = "";
        count = 0;
        
    }//2
    inf1.close();
    printf("modification finished\n");
    
    //output modified dataset
    ofstream out1;
    out1.open("/Users/lidi/Desktop/GAtestdata/os1.neg");
    out1.flush();
    for(int i=0; i < NUM_OF_SAMPLE/2; i++)
    {//2
        out1 << array[i] << "\n";
    }//2
    out1.close();
    printf("new sample saved\n");
}//1

void dataMod2 (char dna[SIZE][2])
{//1
    
    string out_file;
    string line;
    string array[NUM_OF_SAMPLE/2];
    string finddna;
    int a = 0;
    int count = 0;
    
    //load dataset
    ifstream inf2;
    inf2.open("/Users/lidi/Desktop/GAtestdata/original_sample2.txt");
    
    printf("loading dataset\n");
    if(inf2)
    {//2
        while(getline(inf2, line))
        {//3
            array[a] = line;
            a++;
        }//3
    }//2
    else
    {//2
        cout << "can't find original sample" << endl;
    }//2
    
    printf("modifying text samples....\n");
    
    string::size_type position;
    
    for(int i=0; i < NUM_OF_SAMPLE/2; i++)
    {//2
        for(int j=0; j<SIZE; j++)
        {//3
            finddna += dna[j][0];
            finddna += dna[j][1];
            
        conti:
            position = array[i].find(finddna);
            if(position != array[i].npos)
            {//4
                array[i][position] = dna[j][1];
                array[i][position+1] = dna[j][0];
                count++;
                if(count == 3)
                {//5
                    goto next;
                }//5
                else
                {//5
                    goto conti;
                }//5
            }//4
            else
            {//4
                finddna = "";
            }//4
        }//3
    next:
        finddna = "";
        count = 0;
        
    }//2
    inf2.close();
    printf("modification finished\n");
    
    //output modified dataset
    ofstream out2;
    out2.open("/Users/lidi/Desktop/GAtestdata/os2.pos");
    out2.flush();
    for(int i=0; i < NUM_OF_SAMPLE/2; i++)
    {//2
        out2 << array[i] << "\n";
    }//2
    out2.close();
    printf("new sample saved\n");
}//1

string* loadTruelabel ()
{//1
    //string truelabel[NUM_OF_SAMPLE];
    string line;
    int a = 0;
    
    ifstream infile;
    infile.open("/Users/lidi/Desktop/GAtestdata/Truelabel.txt");
    
    printf("loading label\n");
    if(infile)
    {//2
        while(getline(infile, line))
        {//3
            truelabel[a] = line;
            a++;
        }//3
    }//2
    else
    {//2
        printf("loading label failed\n");
    }//2
    printf("label loaded\n");
    
    return truelabel;
}//1

string* importResult()
{//1
    //string result[NUM_OF_SAMPLE];
    string line;
    int a = 0;
    
    ifstream infile;
    infile.open("/Users/lidi/Desktop/GAtestdata/Classifiedresult.txt");
    
    printf("importing classified result\n");
    if(infile)
    {//2
        while(getline(infile, line))
        {//3
            result[a] = line;
            a++;
        }//3
    }//2
    else
    {//2
        printf("importing failed\n");
    }//21
    printf("result imported\n");
    
    return result;
}//1

int main(int argc, const char * argv[])
{//1
    // insert code here...
    
    for(int num_of_targets = 999; num_of_targets < NUM_OF_TARGETS; num_of_targets++)
    {//2
        int number_of_perturbations = SIZE;
        int population_size = POPULATION_SIZE;
        int old_fitness[POPULATION_SIZE];
        int new_fitness[POPULATION_SIZE];
        string* pointer;
        string tlabel[NUM_OF_SAMPLE];
        srand((unsigned)time(NULL));
        
    //loading true label
        pointer = loadTruelabel();
        for(int i=0; i < NUM_OF_SAMPLE; i++)
        {//3
            tlabel[i] = pointer[i];
        }//3
        
    //allocation and initialization
        modification** population = (modification**)malloc(population_size * sizeof(modification*));
        for(int i = 0; i < population_size; ++i)
        {//3
            int dna_size = number_of_perturbations * sizeof(modification);
            population[i] = (modification*)malloc(dna_size);
            
            //initialize
            for(int j = 0; j < number_of_perturbations; ++j)
            {//4
                population[i][j].perturbation_s1 = 'a' + rand()%26;
                population[i][j].perturbation_s2 = 'a' + rand()%26;
            }//4
        }//3
        
////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        modification** new_population = (modification**)malloc(population_size * sizeof(modification*));
        for(int i = 0; i < population_size; ++i)
        {//3
            int dna_size = number_of_perturbations * sizeof(modification);
            new_population[i] = (modification*)malloc(dna_size);
            
            //initialize
            for(int j = 0; j<number_of_perturbations; ++j)
            {//4
                new_population[i][j].perturbation_s1 = 0;
                new_population[i][j].perturbation_s2 = 0;
            }//4
        }//3
        
////////////////////////////////////////////////////////////////////////////////////////////////////////
        
////////////////////////////////////////// Father Test /////////////////////////////////////////////////
        
        char dna[SIZE][LETTER_NUM];
        string fatherresult[NUM_OF_SAMPLE];
        string childresult[NUM_OF_SAMPLE];
        int count = 0;
        
        
        
        ofstream outacc;
        outacc.open("/Users/lidi/Desktop/GAtestdata/Accuracy.txt", ios::app);
        outacc << "First father accuracy: " << "\n";
        outacc.close();
        
        //father evaluation
        for(int i=0; i < population_size; i++)
        {//3
            outacc.open("/Users/lidi/Desktop/GAtestdata/Accuracy.txt", ios::app);
            outacc << i << ". accuracy: ";
            outacc.close();
            
            for(int j=0; j < number_of_perturbations; j++)
            {//4
                dna[j][0] = (char)population[i][j].perturbation_s1;
                dna[j][1] = (char)population[i][j].perturbation_s2;
            }//4
            
            //modify samples
            dataMod1(dna);
            dataMod2(dna);
            
            //using python to classify
            printf("calling python neural network\n");
            
            std:: ofstream outfile("/Users/lidi/Desktop/GAtestdata/indicator1.txt");
            
            while(1)
            {//4
                sleep(1);
                ifstream fin("/Users/lidi/Desktop/GAtestdata/indicator2.txt");
                if(fin)
                {//5
                    fin.close();
                    break;
                }//5
            }//4
            remove("/Users/lidi/Desktop/GAtestdata/indicator2.txt");
            printf("called python neural network\n");
            
            //import result and calculate fitness
            pointer = importResult();
            
            for(int i=0; i < NUM_OF_SAMPLE; i++)
            {//4
                fatherresult[i] = pointer[i];
            }//4
            
            for(int i=0; i < NUM_OF_SAMPLE; i++)
            {//4
                if(fatherresult[i] != tlabel[i])
                {//5
                    count++;
                }//5
            }//4
            old_fitness[i] = count;
            count = 0;
        }//3
        printf("father fitness calculated\n");
        
////////////////////////////////////////// Father Test /////////////////////////////////////////////////
        
/////////////reproduce the mutated samples first so that can only call python program once//////////////
        
        for(int generation = 0; generation < MAX_GENERATION; generation++)
        {//3
            printf("Now is the %dth generation\n", generation);
            
            for(int i=0; i < POPULATION_SIZE; i++)
            {//4
    //the child new_individual is based on his father population[i]
                for(int j=0; j < number_of_perturbations; j++)
                {//5
    //with some random mutation
                    
                    int r1 = rand()%(POPULATION_SIZE - 1);
                    int r2 = rand()%(POPULATION_SIZE - 1);
                    int r3 = rand()%(POPULATION_SIZE - 1);
                    int random_index = rand()%(SIZE - 1);

                    
                    float F = 0.5;
                    
                    new_population[i][j].perturbation_s1 = population[r1][random_index].perturbation_s1 + F * (population[r2][random_index].perturbation_s1 - population[r3][random_index].perturbation_s1);
                    
                    if(new_population[i][j].perturbation_s1 < 97 || new_population[i][j].perturbation_s1 > 122)
                    {//6
                        //new_population[i][j].perturbation_s1 = random -> uniform(1.0, 26.0);
                        new_population[i][j].perturbation_s1 = 'a' + rand()%26;
                        
                    }//6
                    
                    new_population[i][j].perturbation_s2 = population[r1][random_index].perturbation_s2 + F * (population[r2][random_index].perturbation_s2 - population[r3][random_index].perturbation_s2);
                    
                    if(new_population[i][j].perturbation_s2 < 97 || new_population[i][j].perturbation_s2 > 122)
                    {//6
                        //new_population[i][j].perturbation_s2 = random -> uniform(1.0, 26.0);
                        new_population[i][j].perturbation_s2 = 'a' + rand()%26;
                    }//6
                    
                }//5
            }//4
/////////////reproduce the mutated samples first so that can only call python program once//////////////
            
///////////////////////////////////////////  reading text  /////////////////////////////////////////////
            
            outacc.open("/Users/lidi/Desktop/GAtestdata/Accuracy.txt", ios::app);
            outacc << generation << "th Generation child accuracy: " << "\n";
            outacc.close();
            
    //child evalutation
            for(int i=0; i < population_size; i++)
            {//4
                outacc.open("/Users/lidi/Desktop/GAtestdata/Accuracy.txt", ios::app);
                outacc << i << ". accuracy: ";
                outacc.close();
                
                for(int j=0; j < number_of_perturbations; j++)
                {//5
                    dna[j][0] = (char)new_population[i][j].perturbation_s1;
                    dna[j][1] = (char)new_population[i][j].perturbation_s2;
                }//5
                
    //modify samples
                dataMod1(dna);
                dataMod2(dna);
                
    //using python to classify
                printf("calling python neural network\n");
                
                std:: ofstream outfile("/Users/lidi/Desktop/GAtestdata/indicator1.txt");
                while(1)
                {//5
                    sleep(1);
                    ifstream fin("/Users/lidi/Desktop/GAtestdata/indicator2.txt");
                    if(fin)
                    {//6
                        fin.close();
                        break;
                    }//6
                }//5
                remove("/Users/lidi/Desktop/GAtestdata/indicator2.txt");
                printf("called python neural network\n");
                
    //import result and calculate fitness
                pointer = importResult();
                
                for(int i=0; i < NUM_OF_SAMPLE; i++)
                {//5
                    childresult[i] = pointer[i];
                }//5
                
                for(int i=0; i < NUM_OF_SAMPLE; i++)
                {//5
                    if(childresult[i] != tlabel[i])
                    {//6
                        count++;
                    }//6
                }//5
                new_fitness[i] = count;
                count = 0;
            }//4
            printf("child fitness calculated\n");
            
///////////////////////////////////////////  reading text  /////////////////////////////////////////////

    //evaluation and selection and reproduction together
            for(int i = 0; i < population_size; ++i)
            {//4
                if(new_fitness[i] > old_fitness[i])
                {//5
                    for(int j = 0; j < number_of_perturbations; ++j)
                    {//6
                        population[i][j].perturbation_s1 = new_population[i][j].perturbation_s1;
                        population[i][j].perturbation_s2 = new_population[i][j].perturbation_s2;
                    }//6
                    old_fitness[i] = new_fitness[i];
                }//5
            }//4
            
            printf("New population generated\n");
            
            printf("After %d generation, evolved!\n", generation);
            
//////////////////////////////////////// print best guy ////////////////////////////////////////////////
            
            int best_guy = 0;
            double best_score = old_fitness[0];
            
            for(int i=0; i < population_size; i++)
            {//4
                
                if(best_score < old_fitness[i])
                {//5
                    best_score = old_fitness[i];
                    best_guy = i;
                }//5
            }//4

    //output to file
            ofstream outbest;
            outbest.open("/Users/lidi/Desktop/GAtestdata/Bestguy.txt", ios::app);
            
            outbest << "After " << generation << "th generation evolved, the bestguy is " << best_guy << " with miscls_prob: " << best_score/100 << "% !\n";
            
            outbest << "Best DNA: \n";
            for(int j=0; j < SIZE; j++)
            {//4
                outbest << "[" << (char)population[best_guy][j].perturbation_s1 << " , " << (char)population[best_guy][j].perturbation_s2 << "]   ";
            }//4
            
            outbest << "\n";
            outbest.close();
            
////////////////////////////////////////////////////////////////////////////////////////////////////////
            
            
        }//3
        
        
////////////////////////////////////////////////////////////////////////////////////////////////////////

    }//2*/

    
    return 0;
}
