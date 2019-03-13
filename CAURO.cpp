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

#define INDIVIDUAL_SIZE 100
#define RULESET_SIZE 5
#define PERTURBATION_SIZE 5
#define SIZE 3
#define MAX_POPULATION 100
#define MAX_GENERATION 200
#define NUM_OF_LETTER 6
#define NUM_OF_SAMPLE 10000

using namespace std;

static string truelabel[NUM_OF_SAMPLE];
static string result[NUM_OF_SAMPLE];
static int five_time_modify[1000];

typedef struct _modification
{
    int mod_p1;
    int mod_p2;
    int insert_p1;
    int insert_p2;
    int insert_p3;
    int del_p1;
}modification;

int dataMod1 (char individual[NUM_OF_LETTER])
{//1
    
    string out_file;
    string line;
    string array[NUM_OF_SAMPLE/2];
    string finddna = "";
    int counter = 0;
    int a = 0;
    
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
    
    
    finddna += individual[0];
    finddna += individual[1];
    for(int i=0; i < NUM_OF_SAMPLE/2; i++)
    {//2
        position = array[i].find(finddna);
        if(position != array[i].npos)
        {//3
            array[i][position] = individual[1];
            array[i][position+1] = individual[0];
            counter++;
        }//3
    }//2
    finddna = "";
    
    finddna += individual[2];
    finddna += individual[3];
    for(int i=0; i< NUM_OF_SAMPLE/2; i++)
    {//2
        position = array[i].find(finddna);
        if(position != array[i].npos)
        {//3
            finddna += individual[4];
            array[i].replace(position, 2, finddna);
            counter++;
        }//3
    }//2
    finddna = "";
    
    finddna = individual[5];
    for(int i=0; i < NUM_OF_SAMPLE/2; i++)
    {//2
        position = array[i].find(finddna);
        if(position != array[i].npos)
        {//3
            array[i].erase(position, 1);
            counter++;
        }//3
    }//2
    inf1.close();

    ofstream out1;
    out1.open("/Users/lidi/Desktop/GAtestdata/os1.neg");
    out1.flush();
    for(int i=0; i < NUM_OF_SAMPLE/2; i++)
    {//2
        out1 << array[i] << "\n";
    }//2
    out1.close();
    
    return counter;
}//1

int dataMod2 (char individual[NUM_OF_LETTER])
{//1
    
    string out_file;
    string line;
    string array[NUM_OF_SAMPLE/2];
    string finddna = "";
    int counter = 0;
    int a = 0;
    
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
    
    finddna += individual[0];
    finddna += individual[1];
    for(int i=0; i < NUM_OF_SAMPLE/2; i++)
    {//2
        position = array[i].find(finddna);
        if(position != array[i].npos)
        {//3
            array[i][position] = individual[1];
            array[i][position+1] = individual[0];
            counter++;
        }//3
    }//2
    finddna = "";
    
    finddna += individual[2];
    finddna += individual[3];
    for(int i=0; i< NUM_OF_SAMPLE/2; i++)
    {//2
        position = array[i].find(finddna);
        if(position != array[i].npos)
        {//3
            finddna += individual[4];
            array[i].replace(position, 2, finddna);
            counter++;
        }//3
    }//2
    finddna = "";
    
    finddna = individual[5];
    for(int i=0; i < NUM_OF_SAMPLE/2; i++)
    {//2
        position = array[i].find(finddna);
        if(position != array[i].npos)
        {//3
            array[i].erase(position, 1);
            counter++;
        }//3
    }//2

    inf2.close();

    ofstream out2;
    out2.open("/Users/lidi/Desktop/GAtestdata/os2.pos");
    out2.flush();
    for(int i=0; i < NUM_OF_SAMPLE/2; i++)
    {//2
        out2 << array[i] << "\n";
    }//2
    out2.close();
    
    return counter;
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

int rulesetMod1 (char dna[RULESET_SIZE][NUM_OF_LETTER], int rulesetnum)
{//1
    
    string out_file;
    string line;
    string array[NUM_OF_SAMPLE/2];
    string finddna = "";
    int counter = 0;
    int a = 0;
    int modi_time = 0;
    five_time_modify[rulesetnum] = 0;
    
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
        for(int j=0; j < RULESET_SIZE; j++)
        {//3
        
            finddna += dna[j][0];
            finddna += dna[j][1];
            position = array[i].find(finddna);
            if(position != array[i].npos)
            {//4
                array[i][position] = dna[j][1];
                array[i][position+1] = dna[j][0];
                modi_time++;
                if(modi_time < PERTURBATION_SIZE)
                {//5
                    finddna = "";
                    goto conti1;
                }//5
                else
                {//5
                    five_time_modify[rulesetnum]++;
                    goto next;
                }//5
            }//4
            else
            {//4
                finddna = "";
            }//4
            
        conti1:
            finddna += dna[j][2];
            finddna += dna[j][3];
            position = array[i].find(finddna);
            if(position != array[i].npos)
            {//4
                finddna += dna[j][4];
                array[i].replace(position, 2, finddna);
                modi_time++;
                if(modi_time < PERTURBATION_SIZE)
                {//5
                    finddna = "";
                    goto conti2;
                }//5
                else
                {//5
                    five_time_modify[rulesetnum]++;
                    goto next;
                }//5
            }//4
            else
            {//4
                finddna = "";
            }//4
            
        conti2:
            finddna += dna[j][5];
            position = array[i].find(finddna);
            if(position != array[i].npos)
            {//4
                array[i].erase(position, 1);
                if(modi_time < PERTURBATION_SIZE)
                {//5
                    goto conti3;
                }//5
                else
                {//5
                    five_time_modify[rulesetnum]++;
                    goto next;
                }//5
            }//4
            
        conti3:
            finddna = "";
            
        }//3
        
    next:
        finddna = "";
        if(modi_time > 0)
        {//3
            counter++;
            modi_time = 0;
        }//3
        
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
    
    return counter;
}//1

int rulesetMod2 (char dna[RULESET_SIZE][NUM_OF_LETTER], int rulesetnum)
{//1
    
    string out_file;
    string line;
    string array[NUM_OF_SAMPLE/2];
    string finddna = "";
    int a = 0;
    int counter = 0;
    int modi_time = 0;
    five_time_modify[rulesetnum] = 0;
    
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
        for(int j=0; j < RULESET_SIZE; j++)
        {//3
            
            finddna += dna[j][0];
            finddna += dna[j][1];
            position = array[i].find(finddna);
            if(position != array[i].npos)
            {//4
                array[i][position] = dna[j][1];
                array[i][position+1] = dna[j][0];
                modi_time++;
                if(modi_time < PERTURBATION_SIZE)
                {//5
                    finddna = "";
                    goto conti1;
                }//5
                else
                {//5
                    five_time_modify[rulesetnum]++;
                    goto next;
                }//5
            }//4
            else
            {//4
                finddna = "";
            }//4
            
        conti1:
            finddna += dna[j][2];
            finddna += dna[j][3];
            position = array[i].find(finddna);
            if(position != array[i].npos)
            {//4
                finddna += dna[j][4];
                array[i].replace(position, 2, finddna);
                modi_time++;
                if(modi_time < PERTURBATION_SIZE)
                {//5
                    finddna = "";
                    goto conti2;
                }//5
                else
                {//5
                    five_time_modify[rulesetnum]++;
                    goto next;
                }//5
            }//4
            else
            {//4
                finddna = "";
            }//4
            
        conti2:
            finddna += dna[j][5];
            position = array[i].find(finddna);
            if(position != array[i].npos)
            {//4
                array[i].erase(position, 1);
                if(modi_time < PERTURBATION_SIZE)
                {//5
                    goto conti3;
                }//5
                else
                {//5
                    five_time_modify[rulesetnum]++;
                    goto next;
                }//5
            }//4
            
        conti3:
            finddna = "";
            
        }//3
        
    next:
        finddna = "";
        if(modi_time > 0)
        {//3
            counter++;
            modi_time = 0;
        }//3
        
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
    
    return counter;
}//1

string* importResult()
{//1
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


int main()
{//1
    string* pointer;
    string tlabel[NUM_OF_SAMPLE];
    float rule_fitness[INDIVIDUAL_SIZE];
    int rule_counter[INDIVIDUAL_SIZE];
    int rule_picktime[INDIVIDUAL_SIZE];
    int rulerec[RULESET_SIZE];
    int ruleset_fitness[MAX_POPULATION];
    int ruleset_counter[MAX_POPULATION];
    int bestguy = -1;
    
    //load true label
    pointer = loadTruelabel();
    for(int i=0; i < NUM_OF_SAMPLE; i++)
    {//2
        tlabel[i] = pointer[i];
    }//2
    
    modification** population = (modification**)malloc(MAX_POPULATION * sizeof(modification*));
    for(int i=0; i < MAX_POPULATION; i++)
    {//2
        int perturbation_size = RULESET_SIZE * sizeof(modification);
        population[i] = (modification*)malloc(perturbation_size);
        
        for(int j = 0; j < RULESET_SIZE; j++)
        {//3
            population[i][j].mod_p1 = 0;
            population[i][j].mod_p2 = 0;
            population[i][j].insert_p1 = 0;
            population[i][j].insert_p2 = 0;
            population[i][j].insert_p3 = 0;
            population[i][j].del_p1 = 0;
        }//3
        
    }//2
    
    int individual_size = INDIVIDUAL_SIZE;
    int rule_size = RULESET_SIZE;
    int counters[RULESET_SIZE];
    
    srand((unsigned)time(NULL));
    
    //allocation and initialization
    modification* individual = (modification*)malloc(individual_size * sizeof(modification));
    for(int i=0; i < individual_size; i++)
    {//2
        individual[i].mod_p1 = 'a' + rand()%26;
        individual[i].mod_p2 = 'a' + rand()%26;
        individual[i].insert_p1 = 'a' + rand()%26;
        individual[i].insert_p2 = 'a' + rand()%26;
        individual[i].insert_p3 = 'a' + rand()%26;
        individual[i].del_p1 = 'a' + rand()%26;
    }//2
    
    modification* ruleset = (modification*)malloc(rule_size * sizeof(modification));
    for(int i=0; i < rule_size; i++)
    {//2
        ruleset[i].mod_p1 = 0;
        ruleset[i].mod_p2 = 0;
        ruleset[i].insert_p1 = 0;
        ruleset[i].insert_p2 = 0;
        ruleset[i].insert_p3 = 0;
        ruleset[i].del_p1 = 0;
    }//2
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    for(int i=0; i < MAX_GENERATION; i++)
    {//2
        for(int num_of_ruleset=0; num_of_ruleset < MAX_POPULATION; num_of_ruleset++)
        {//3
            
            //////////////////////////////////////// rule fitness calculation ///////////////////////////////////////////
            
            char perturbation[NUM_OF_LETTER];
            char dna[rule_size][NUM_OF_LETTER];
            string classresult[NUM_OF_SAMPLE];
            int count1 = 0;
            
            //import result and calculate fitness
            //pointer = importResult();
            
            //randomly select individuals
            for(int i=0; i < rule_size; i++)
            {//4
                int random_index = rand()%(individual_size - 1);
                
                perturbation[0] = (char)individual[random_index].mod_p1;
                perturbation[1] = (char)individual[random_index].mod_p2;
                perturbation[2] = (char)individual[random_index].insert_p1;
                perturbation[3] = (char)individual[random_index].insert_p2;
                perturbation[4] = (char)individual[random_index].insert_p3;
                perturbation[5] = (char)individual[random_index].del_p1;
                
                rule_counter[random_index] = dataMod1(perturbation) + dataMod2(perturbation);
                
                for(int i=0; i < MAX_GENERATION; i++){//2
                    for(int num_of_ruleset=0; num_of_ruleset < MAX_POPULATION; num_of_ruleset++){//3
                        // rule fitness calculation
                        char perturbation[NUM_OF_LETTER];
                        char dna[rule_size][NUM_OF_LETTER];
                        string classresult[NUM_OF_SAMPLE];
                        int count1 = 0;("calling python neural network\n");
                
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
                
                /*pointer = importResult();
                
                for(int i=0; i < NUM_OF_SAMPLE; i++)
                {//5
                    classresult[i] = pointer[i];
                }//5
                
                for(int i=0; i < NUM_OF_SAMPLE; i++)
                {//5
                    if(classresult[i] != tlabel[i])
                    {//6
                        count1++;
                    }//6
                }//5
                rule_fitness[random_index] = count1;*/
                
                ruleset[i].mod_p1 = individual[random_index].mod_p1;
                ruleset[i].mod_p2 = individual[random_index].mod_p2;
                ruleset[i].insert_p1 = individual[random_index].insert_p1;
                ruleset[i].insert_p2 = individual[random_index].insert_p2;
                ruleset[i].insert_p3 = individual[random_index].insert_p3;
                ruleset[i].del_p1 = individual[random_index].del_p1;
                
                rule_picktime[random_index]++;
                rulerec[i] = random_index;
            }//4
            
            //////////////////////////////////////// counter calculation ///////////////////////////////////////////
            
            //////////////////////////////////////// fitness calculation ///////////////////////////////////////////
            
            for(int i=0; i < rule_size; i++)
            {//4
                population[num_of_ruleset][i].mod_p1 = ruleset[i].mod_p1;
                population[num_of_ruleset][i].mod_p2 = ruleset[i].mod_p2;
                population[num_of_ruleset][i].insert_p1 = ruleset[i].insert_p1;
                population[num_of_ruleset][i].insert_p2 = ruleset[i].insert_p2;
                population[num_of_ruleset][i].insert_p3 = ruleset[i].insert_p3;
                population[num_of_ruleset][i].del_p1 = ruleset[i].del_p1;
            }//4
            
            for(int i=0; i < rule_size; i++)
            {//4
                dna[i][0] = (char)ruleset[i].mod_p1;
                dna[i][1] = (char)ruleset[i].mod_p2;
                dna[i][2] = (char)ruleset[i].insert_p1;
                dna[i][3] = (char)ruleset[i].insert_p2;
                dna[i][4] = (char)ruleset[i].insert_p3;
                dna[i][5] = (char)ruleset[i].del_p1;
            }//4
            
            //modify samples
            ruleset_counter[num_of_ruleset] = rulesetMod1(dna, num_of_ruleset) + rulesetMod2(dna, num_of_ruleset);
            
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
            
            pointer = importResult();
            
            for(int i=0; i < NUM_OF_SAMPLE; i++)
            {//4
                classresult[i] = pointer[i];
            }//4
            
            for(int i=0; i < NUM_OF_SAMPLE; i++)
            {//4
                if(classresult[i] != tlabel[i])
                {//5
                    count1++;
                }//5
            }//4
            ruleset_fitness[num_of_ruleset] = count1;
            
            //individual fitness calculate
            for(int i=0; i<rule_size; i++)
            {
                rule_fitness[rulerec[i]] += ruleset_fitness[num_of_ruleset];
            }
            
            count1 = 0;
            printf("ruleset counter and fitness calculated\n");
            
            if(bestguy < 0)
            {//4
                bestguy = num_of_ruleset;
            }//4
            else
            {//4
                if(ruleset_fitness[num_of_ruleset] > ruleset_fitness[bestguy])
                {//5
                    bestguy = num_of_ruleset;
                }//5
            }//4
            
            //////////////////////////////////////// fitness calculation ///////////////////////////////////////////
            
        }//3
        
        
        ofstream outbest;
        outbest.open("/Users/lidi/Desktop/GAtestdata/Bestguy.txt", ios::app);
        
        outbest << "For the " << i << "th generation the best-guy is the " << bestguy << "th ruleset with fitness: " << ruleset_fitness[bestguy] << " and counter: " << ruleset_counter[bestguy] << " five-time-modify: " << five_time_modify[bestguy] << "\n";
        outbest << "Best ruleset: \n";
        for(int i=0; i < rule_size; i++)
        {//3
            outbest << "[" << (char)population[bestguy][i].mod_p1 << " , " << (char)population[bestguy][i].mod_p2 << " , " << (char)population[bestguy][i].insert_p1 << " , " << (char)population[bestguy][i].insert_p2 << " , " << (char)population[bestguy][i].insert_p3 << " , " << (char)population[bestguy][i].del_p1 << "]   ";
        }//3
        outbest << "\n";
        
        //individuals evaluation
        float midcon;
        for(int i=0; i<MAX_POPULATION; i++)
        {
            if(rule_picktime[i] > 0)
            {
                midcon = rule_fitness[i]/rule_picktime[i];
                rule_fitness[i] = midcon;
            }
        }
        
        int x, y[6];
        for(int i=0; i < MAX_POPULATION; i++)
        {//3
            for(int j=1; j < MAX_POPULATION-i; j++)
            {//4
                if(rule_fitness[j-1] > rule_fitness[j])
                {//5
                    x = rule_fitness[j];
                    rule_fitness[j] = rule_fitness[j-1];
                    rule_fitness[j-1] = x;
                    
                    x = rule_counter[j];
                    rule_counter[j] = rule_counter[j-1];
                    rule_counter[j-1] = x;
                    
                    y[0] = individual[j].mod_p1;
                    y[1] = individual[j].mod_p2;
                    y[2] = individual[j].insert_p1;
                    y[3] = individual[j].insert_p2;
                    y[4] = individual[j].insert_p3;
                    y[5] = individual[j].del_p1;
                    
                    individual[j].mod_p1 = individual[j-1].mod_p1;
                    individual[j].mod_p2 = individual[j-1].mod_p2;
                    individual[j].insert_p1 = individual[j-1].insert_p1;
                    individual[j].insert_p2 = individual[j-1].insert_p2;
                    individual[j].insert_p3 = individual[j-1].insert_p3;
                    individual[j].del_p1 = individual[j-1].del_p1;
                    
                    individual[j-1].mod_p1 = y[0];
                    individual[j-1].mod_p2 = y[1];
                    individual[j-1].insert_p1 = y[2];
                    individual[j-1].insert_p2 = y[3];
                    individual[j-1].insert_p3 = y[4];
                    individual[j-1].del_p1 = y[5];
                }//5
            }//4
        }//3
        
        for(int i=0; i < 10; i++)
        {//3
            individual[i].mod_p1 = 'a' + rand()%26;
            individual[i].mod_p2 = 'a' + rand()%26;
            individual[i].insert_p1 = 'a' + rand()%26;
            individual[i].insert_p2 = 'a' + rand()%26;
            individual[i].insert_p3 = 'a' + rand()%26;
            individual[i].del_p1 = 'a' + rand()%26;
            rule_fitness[i] = 0;
            rule_counter[i] = 0;
        }//3
        
        for(int i=10; i < MAX_POPULATION; i++)
        {//3
            for(int j=11; j < MAX_POPULATION-i; j++)
            {//4
                if(rule_counter[j-1] > rule_counter[j])
                {//5
                    x = rule_fitness[j];
                    rule_fitness[j] = rule_fitness[j-1];
                    rule_fitness[j-1] = x;
                    
                    x = rule_counter[j];
                    rule_counter[j] = rule_counter[j-1];
                    rule_counter[j-1] = x;
                    
                    y[0] = individual[j].mod_p1;
                    y[1] = individual[j].mod_p2;
                    y[2] = individual[j].insert_p1;
                    y[3] = individual[j].insert_p2;
                    y[4] = individual[j].insert_p3;
                    y[5] = individual[j].del_p1;
                    
                    individual[j].mod_p1 = individual[j-1].mod_p1;
                    individual[j].mod_p2 = individual[j-1].mod_p2;
                    individual[j].insert_p1 = individual[j-1].insert_p1;
                    individual[j].insert_p2 = individual[j-1].insert_p2;
                    individual[j].insert_p3 = individual[j-1].insert_p3;
                    individual[j].del_p1 = individual[j-1].del_p1;
                    
                    individual[j-1].mod_p1 = y[0];
                    individual[j-1].mod_p2 = y[1];
                    individual[j-1].insert_p1 = y[2];
                    individual[j-1].insert_p2 = y[3];
                    individual[j-1].insert_p3 = y[4];
                    individual[j-1].del_p1 = y[5];
                }//5
            }//4
        }//3
        
        for(int i=10; i < 20; i++)
        {//3
            individual[i].mod_p1 = 'a' + rand()%26;
            individual[i].mod_p2 = 'a' + rand()%26;
            individual[i].insert_p1 = 'a' + rand()%26;
            individual[i].insert_p2 = 'a' + rand()%26;
            individual[i].insert_p3 = 'a' + rand()%26;
            individual[i].del_p1 = 'a' + rand()%26;
            rule_fitness[i] = 0;
            rule_counter[i] = 0;
        }//3
        
        cout << "New individuals are created!\n";
    }//2
    
    return 0;
}//1
