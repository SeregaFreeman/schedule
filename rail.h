#ifndef RAIL_H
#define RAIL_H
#include <iostream>
#include <cstdlib>
using namespace std;

struct Time
{
    int hour;
    int minute;
};

class SchedFunc
{
    string unit;
    string name;
    int price;
    int order;
    int number;
    int type;
    Time departure_time;
    Time travel_time;

public:

    int kurs;
    void generate(SchedFunc *timegen, int number);
    void write(SchedFunc *timegen, int number);
    void read(SchedFunc *&timegen, int number);
    void output(SchedFunc *timegen, int number, int type);
    void set_name(string name);
    int get_price();
    Time get_deptime();
    Time get_travel_time();
    int price_convertion();

};


int part(SchedFunc A[],int l,int r,int (*cmp)(SchedFunc,SchedFunc),int order);
void sort(SchedFunc A[],int l,int r,int (*cmp)(SchedFunc,SchedFunc),int order);
int cmp_price(SchedFunc a, SchedFunc b);
int cmp_deptime(SchedFunc a, SchedFunc b);
int cmp_traveltime(SchedFunc a, SchedFunc b);
int time_to_int(Time a);

#endif
