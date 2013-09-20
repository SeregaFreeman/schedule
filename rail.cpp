#include "rail.h"
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;
SchedFunc a;
SchedFunc b;

void SchedFunc::set_name(string name)
{
    unit=name;
}
void SchedFunc::setPrice(int pricen)
{
    price=pricen;
}


int SchedFunc::get_price()
{
    return price;
}

Time SchedFunc::get_deptime()
{
    return departure_time;
}

Time SchedFunc::get_travel_time()
{
    return travel_time;
}

int time_to_int(Time a)
{
    int integer_time = a.hour*60+a.minute;
    return integer_time;
}

int cmp_price (SchedFunc a, SchedFunc b) //сравнение цен
{

    return a.get_price()-b.get_price();
}

int cmp_deptime (SchedFunc a, SchedFunc b) //сравнение времени отправления
{
    int a1=time_to_int(a.get_deptime());
    int a2=time_to_int(b.get_deptime());
    return a1-a2;
}

int cmp_traveltime (SchedFunc a, SchedFunc b) //сравнение времени отправления
{
    int a1=time_to_int(a.get_travel_time());
    int a2=time_to_int(b.get_travel_time());
    return a1-a2;
}


void SchedFunc::generate(SchedFunc *timegen, int number) //генерирование цены и даты
{
    for(int i=0; i<number; ++i)
    {
        bool ch=rand()%2;
        if (ch==0)
        {
            unit="Электричка";
            timegen[i].set_name(unit);
            timegen[i].price=rand()%3000+20000;
            timegen[i].travel_time.hour=rand()%6+4;
            timegen[i].travel_time.minute=rand()%60;
        }
        else
        {
            unit="Поезд     ";
            timegen[i].set_name(unit);
            timegen[i].price=rand()%3000+30000;
            timegen[i].travel_time.hour=rand()%4+2;
            timegen[i].travel_time.minute=rand()%60;

        }

        timegen[i].departure_time.hour=rand()%23+1;
        timegen[i].departure_time.minute=rand()%60;


    }
}

void SchedFunc::write(SchedFunc *timegen, int number) //запись файла архив
{
    fstream io;
    io.open ("time.txt", ios::out|ios::binary|ios::trunc);
    io.write((char *)&number,sizeof(number));//
    io.write((char *)timegen,number*sizeof(SchedFunc));
    io.close();
}

void SchedFunc::read(SchedFunc *&timegen, int number) //чтение файла time
{
    fstream io;
    io.open ("time.txt",ios::in|ios::binary);
    io.read((char *)&number,sizeof(int));
    timegen=new SchedFunc[number];
    io.read((char *)timegen,number*sizeof(SchedFunc));
    io.close();
}


int price_convertion(int pricen)
{
    int kurs=9000;
    return pricen=pricen/kurs;
}


void SchedFunc::output(SchedFunc *timegen, int number, int type) //функция вывода
{
    cout<<"Тип поезда"<<"    Цена билета"<<"     Время отправления"<<"    Время в пути"<<endl;
    cout<<"=================================================================="<<endl;
    for (int i=0; i<number; ++i)
    {
        cout<<endl;
        cout.width(10);
        cout<<timegen[i].unit;
        if (type==1)
        {
            cout.width(10);
            cout<<timegen[i].price<<" BYR";
        }
        else if (type==2)
        {

            cout.width(10);
            cout<<price_convertion(timegen[i].price)<<" USD";

        }
        cout<<"          ";
        if (timegen[i].departure_time.hour<10)
            cout<<'0';
        cout<<timegen[i].departure_time.hour;
        cout<<':';

        if (timegen[i].departure_time.minute<10)
            cout<<'0';
        cout<<timegen[i].departure_time.minute;


        cout<<"          ";
        if (timegen[i].travel_time.hour<10)
            cout<<'0';
        cout<<timegen[i].travel_time.hour;
        cout<<':';
        if (timegen[i].travel_time.minute<10)
            cout<<'0';
        cout<<timegen[i].travel_time.minute;

    }
    cout<<endl;
}

int Part(SchedFunc A[],int l,int r,int (*cmp)(SchedFunc,SchedFunc),int order) //функция разбиения
{
    int i,j;
    SchedFunc temp;
    i=l;
    while((order*cmp(A[i],A[r]))<0.0) ++i;
    for(j=i; j<r; ++j)
    {
        if((order*cmp(A[j],A[r]))<0.0)
        {
            temp=A[j];
            A[j]=A[i];
            A[i]=temp;
            ++i;
        }

    }
    temp=A[i];
    A[i]=A[r];
    A[r]=temp;
    return i;
}

void sort(SchedFunc A[],int l,int r,int (*cmp)(SchedFunc,SchedFunc),int order) //функция сортировки
{
    int m;
    if(l<r)
    {
        m=Part(A,l,r,cmp,order);
        sort(A,l,m-1,cmp,order);
        sort(A,m+1,r,cmp,order);
    }
}


