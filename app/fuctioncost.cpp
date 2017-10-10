#include "fuctioncost.h"

FuctionCost::FuctionCost()
{
    CParticles.clear();
}

void FuctionCost::set_new_Obstacle(structxy obstaculo)
{
    Obstaculos.push_back(obstaculo);
}

void FuctionCost::set_new_Obstacle(vector<structxy> obstaculo)
{
    Obstaculos = obstaculo;
}

void FuctionCost::set_new_target(vector<structidxy> newtarget, int ntarget)
{
    this->target = newtarget;
    this->ntarget = ntarget;
}

void FuctionCost::set_new_Particles(vector<strucparticle> particle)
{
    this->Particles = particle;
}

void FuctionCost::set_new_Particles_Thread(vector<strucparticle> particle)
{
    this->CParticles = particle;
}

double FuctionCost::potential_field(structxy vector)
{
    return W1 * obstaculos(vector) + W2 * cuadratica(vector);
}

double FuctionCost::potential_field_2AB(structxy vectores, unsigned int ite)
{
    return W1 * obstaculos2AB(vectores, ite) + W2 * cuadratica(vectores);
}

double FuctionCost::cuadratica(structxy vector)
{
    return pow(vector.x - target[ntarget].x, 2.0) + pow(vector.y - target[ntarget].y, 2.0);
}

double FuctionCost::obstaculos(structxy vector)
{    
    double f_gaussian = 0;
    for( unsigned int i = 0; i < Obstaculos.size(); i++){
        f_gaussian += alfa_a*exp( - ( pow(vector.x - Obstaculos[i].x , 2.0) + pow(vector.y - Obstaculos[i].y, 2.0))/(2*pow(sigma_o, 2.0)));
    }
    return f_gaussian;
}

double FuctionCost::obstaculos2AB(structxy vectores, unsigned int ite)
{
    double f_gaussian = 0;
    for( unsigned int i = 0; i < Obstaculos.size(); i++){
        f_gaussian += alfa_a*exp( - ( pow(vectores.x - Obstaculos[i].x , 2.0) + pow(vectores.y - Obstaculos[i].y, 2.0))/(2*pow(sigma_o, 2.0)));
    }
    for( unsigned int i = 0; i < Particles.size(); i++){
        if(Particles[i].id != Particles[ite].id){
            f_gaussian += alfa_a*exp( - ( pow(vectores.x - Particles[i].Position.x , 2.0) + pow(vectores.y - Particles[i].Position.y, 2.0))/(2*pow(sigma_o, 2.0)));
        }
    }
    for( unsigned int i = 0; i < CParticles.size(); i++){
        if(CParticles[i].id != Particles[ite].id){
            f_gaussian += alfa_a*exp( - ( pow(vectores.x - CParticles[i].Position.x , 2.0) + pow(vectores.y - CParticles[i].Position.y, 2.0))/(2*pow(sigma_o, 2.0)));
        }
    }
    return f_gaussian;
}

structxy FuctionCost::obstaculosHeu(structxy vectores, unsigned int ite)
{
    structxy result;
    int kn = 0;
    double f_gaussian = 0;
    for( unsigned int i = 0; i < Obstaculos.size(); i++){
        f_gaussian += alfa_a*exp( - ( pow(vectores.x - Obstaculos[i].x , 2.0) + pow(vectores.y - Obstaculos[i].y, 2.0))/(2*pow(sigma_o, 2.0)));
    }
    for( unsigned int i = 0; i < Particles.size(); i++){
        if(ite < Particles.size()){
            if(Particles[i].id != Particles[ite].id){
                f_gaussian += alfa_a*exp( - ( pow(vectores.x - Particles[i].Position.x , 2.0) + pow(vectores.y - Particles[i].Position.y, 2.0))/(2*pow(sigma_o, 2.0)));
                kn++;
            }
        }
    }
    result.x = f_gaussian;
    result.y = kn;
    return result;
}

int FuctionCost::heuristica(int angulo, int sentido, int set)
{
    int k = angulo;
    for (int i = 1; i < 8 + set; i++){
        k = algoritmoLoop(k,sentido);
    }
    return k;
}

int FuctionCost::algoritmoLoop(int angulo, int sentido)
{
    int k;
    if (sentido == -1){
        if (angulo == 1)
            k = 32;
        else
            k = angulo - 1;
    } else {
        k = angulo + 1;
        if (k == 33)
            k = 1;
    }
    return k;
}
