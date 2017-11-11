#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "Map.hpp"
#include "Population.hpp"
#include "ImportData.hpp"
#include "GPX2.hpp"

using std::cout;
using std::endl;
using std::stoi;
using std::invalid_argument;
using std::random_shuffle;
using std::srand;

void GA(string,unsigned);
bool stop(Population);
double compareDouble(const double,const double,const double = 0.000001);
Population generateNewPopulation(Population);


//primeiro argumento tour_name, segundo tamanho da pop
int main(int argc, char *argv[]){
    string name{""};
    unsigned popSize{0};
    
    srand(time(NULL));

    if(argc == 3){
        try{
            name = argv[1];
            popSize = stoi(argv[2]);
        }catch(invalid_argument &i_a){
            cout<<"Invalid population size! "<<i_a.what()<<endl;
            return(0);
        }
    }else if(argc == 0){
        cout<<"Please specify the arguments: tour name and population size."<<endl;
        return(0);
    }else{
        cout<<"Invalid argument number. Expecting two arguments."<<endl;
        return(0);
    }

    GA(name,popSize);

    return 0;
}

void GA(string name,unsigned popSize){

    Map map;
    Population pop;

    {
        ImportData dataFile(name);
        //carrega o mapa
        map.setCityList(dataFile.getCitiesCoord());

        //carrega a primeira população
        pop = dataFile.importFirstPopulation(map,name,popSize);
    }

    

    int i{0};
    while(stop(pop)){
        pop = generateNewPopulation(pop);
        if(i%10 == 0){
            for(Tour t : pop.getPopulation()){
                cout<<t<<endl;
            }
            cout<<"gen "<<i<<" best fitness "<<pop.bestFitness()<<endl;
        }
        i++;
    }
    cout<<"THE END"<<endl;
    cout<<"gen "<<i<<" best fitness "<<pop.bestFitness()<<endl;

}

bool stop(Population pop){

    int static generationsWithoutChange{0};
    int static bestFitness{0};
    int currentFitness{pop.bestFitness()};

    if(bestFitness > currentFitness){
        bestFitness = currentFitness;
        generationsWithoutChange = 0;
        cout<<"new best fitness: "<<bestFitness<<endl;
    }else{
        generationsWithoutChange++;
    }

    if(generationsWithoutChange == 100){
        return(false);
    }else{
        return(true);
    }
}

Population generateNewPopulation(Population pop){
    unsigned size = pop.getPopulation().size();
    Population newPop;

    std::random_shuffle(pop.getPopulation().begin(),pop.getPopulation().end());
    
    for(unsigned i=0;i<size;i++){
        if(i==(size-1)){
            newPop.addNewTour(GPX2::crossover(pop.getPopulation().at(i),pop.getPopulation().at(0)));
        }else{
            newPop.addNewTour(GPX2::crossover(pop.getPopulation().at(i),pop.getPopulation().at(i+1)));
        }
    }

    return newPop;
}

double compareDouble(const double a,const double b,const double delta){
    return(abs(a-b)<delta);
}