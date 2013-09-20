#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "rail.h"

using namespace std;

int main()
{
    srand(time(NULL));
    SchedFunc var;
    int number;
    int choice;
    int type;
    cout<<"Вас приветствует программа распиания поездов. Выберите направление:\n 1 - На Брест\n 2 - На Минск\n";
    cin>>choice;
    number=rand()%11+5;
    SchedFunc *timegen=new SchedFunc[number]; //выделение памяти под number элементов массива
    system("clear");
    var.generate(timegen, number);
    cout<<"По какому курсу выводить цену? 1 - в белорусских рублях, 2 - в у.е.";
    cin>>type;
    var.output(timegen, number, type);
    cout<<"Что вы хотите сделать?\n1.Записать и прочитать файл\n2.Сортировать\n0.Exit\n";
    cin>>choice;

    switch(choice)
    {
    case 1: //генерация, запись и чтение
        system("clear");
        var.generate(timegen, number);   //генерим
        var.write(timegen, number);      // пишем сгенеренное
        var.read(timegen, number);       //открываем сгенеренное
        cout<<"Everything is ok! Look through timegen.txt"<<endl;
        break;

    case 2: //генерация и сортировка

        cout<<"Выберите сортировку:\n1.Сортировка по времени отправления\n2.Сортировка по цене (по убывванию)\n3. Сортировка по цене (по возрастанию)";
        cin>>choice;
        switch(choice)
        {
            int order;
        case 1: //сортировка по времени отправления (по возрастанию)
            system("clear");
            sort(timegen, 0, number-1, cmp_deptime, order=1);
            var.output(timegen, number, type);
            break;
        case 2:
            system("clear");
            var.output(timegen, number, type);
            sort(timegen, 0, number-1, cmp_traveltime, order=1);
            var.output(timegen, number, type);
            break;
        case 3: //сортировка по цене (возр)
            system("clear");
            var.output(timegen, number, type);
            sort(timegen, 0, number-1, cmp_price, order=1);
            var.output(timegen, number, type);
            break;
        case 4: //сортировка по цене (убыв)
            system("clear");
            var.output(timegen, number, type);
            sort(timegen, 0, number-1, cmp_price, order=-1);
            var.output(timegen,number, type);
            break;


        }
        break;


    case 0:
        break;
    }
    delete [] timegen; //очистка памяти массива
    return 0;
}
