#ifndef FUCTIONCOST_H
#define FUCTIONCOST_H

#include <cmath>
#include <vector>
#include "mystruct.h"
#include <algorithm>
#include <iostream>

using namespace std;

static const double PI  = 3.14159265;
static const double sigma_o_2 = 0.007;
static const double sigma_o   = sqrt(sigma_o_2);
static const double alfa_a    = 1/(2*PI*pow(sigma_o,2));

static const double W1 = 1;
static const double W2 = 0.01;

class FuctionCost
{
public:
    FuctionCost();
    void set_new_Obstacle(structxy obstaculo);
    void set_new_Obstacle(vector<structxy> obstaculo);
    void set_new_target(vector<structidxy> newtarget,int ntarget);
    void set_new_Particles(vector<strucparticle> particle);
    void set_new_Particles_Thread(vector<strucparticle> particle);

    double potential_field(structxy vector);
    double potential_field_2AB(structxy vectores, unsigned int ite );
    double obstaculos2AB(structxy vectores, unsigned int ite);
    structxy obstaculosHeu(structxy vectores, unsigned int ite);
    int heuristica(int angulo, int sentido, int set);

private:
    double cuadratica(structxy vector);
    double obstaculos(structxy vector);    
    int algoritmoLoop(int angulo, int sentido);

    vector<structxy> Obstaculos;
    vector<strucparticle> Particles;
    vector<strucparticle> CParticles;
    vector<structidxy> target;
    int ntarget;

    bool match;


};

#endif // FUCTIONCOST_H

