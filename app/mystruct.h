#ifndef MYSTRUCT_H
#define MYSTRUCT_H

typedef struct structxy{
    double x;
    double y;
}structxy;

typedef struct structidxy{
    int id;
    double x;
    double y;
}structidxy;

typedef struct Best{
    structxy Position;
    double Cost;
}PersonalBest,GlobalBest;

typedef  struct structparticle{

    unsigned int id;

    structxy Position;
    structxy Velocity;

    double Cost;    
    PersonalBest PBest;

    bool MissionAccomplished;

    unsigned int NoBestIte;
    unsigned int NoBestIteHeu;
    bool Estancado;
    bool StateFistTime;
    char D;
    unsigned int repetividad;
}strucparticle;

typedef struct solucionTriangular{
    double W;
    double C1;
    double C2;
}solucionTring;

typedef struct struct_map{
    double x[2];
    double y[2];
}structMapa;



#endif // MYSTRUCT_H
