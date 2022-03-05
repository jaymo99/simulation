//KARIUKI JAMES MWAURA - CIT-221-059/2018
#include <iostream>
#include <queue>
#include <fstream>
#include <math.h>
#include <conio.h>
#include <iomanip>
int main()
{ 
// Single server queue:

int customers=15, iat=0, serviceTime=0, startTime=0, inQueue=0;
int idleHours=0, idleMinutes=0;
int RN_arrival[] = {82, 91, 12, 77, 90, 75, 33, 61, 19, 58, 41, 54, 52, 16, 86};
int RN_service[] = {93, 59, 76, 62, 40, 41, 51, 91, 93, 38, 92, 22, 9, 7, 65};
// std::ofstream outfile("testing.txt",std::ios::out);
// outfile<<"\n Customer\t RN(arrivals)\t IAT\t Arrival time\t RN(service)\t \t Service.T\t Start.T\t End.T\t In Queue\t Idle.T\t Delay\n";
struct time { //HH:MM time structure
    int hour;
    int mins;
};
time arrivalTime;
arrivalTime.hour = 1;
arrivalTime.mins = 0;

time serviceBegin;
serviceBegin.hour = 1, serviceBegin.mins = 0;

time serviceEnd;
serviceEnd.hour = 1, serviceEnd.mins = 0;

std::queue<time> q; //declare a queue that stores end time values
q.push(serviceEnd);

std::cout<<"C\t"<<"IAT\t"<<"AT\t\t"<<"ST\t"<<"SB\t\t"<<"SE\t\t"<<"inQueue\t"<<"IT\t"<<"Delay\n";

for (int i = 0; i<customers; ++i)
{
    //Generate inter arrival time
    int x = RN_arrival[i]; 
    if(x>=0 && x<=19){
        iat = 1;
    }
    else if (x<=44){
        iat = 2;
    }
    else if (x<=74){
        iat = 3;
    }
    else if (x<=89){
        iat = 4;
    }
    else{
        iat = 5;
    }

    //Generate Arrival time (on clock)
    arrivalTime.mins += iat;
    if(arrivalTime.mins>59){
        arrivalTime.hour += arrivalTime.mins / 60;
        arrivalTime.mins = arrivalTime.mins % 60;
    }
    //Update Queue
    if(arrivalTime.hour > q.front().hour || arrivalTime.mins >= q.front().mins){
        q.pop();
    }

    inQueue = q.size();

    //Generate service time
    x = RN_service[i]; 
    if(x>=0 && x<=9){
        serviceTime = 1;
    }
    else if (x<=24){
        serviceTime = 2;
    }
    else if (x<=59){
        serviceTime = 3;
    }
    else if (x<=74){
        serviceTime = 4;
    }
    else if (x<=89){
        serviceTime = 5;
    }
    else{
        serviceTime = 6;
    }

    //Generate Start time
    if(arrivalTime.hour <= serviceEnd.hour && arrivalTime.mins <= serviceEnd.mins){
        serviceBegin.hour = serviceEnd.hour;
        serviceBegin.mins = serviceEnd.mins;
    }else{
        serviceBegin.hour = arrivalTime.hour;
        serviceBegin.mins = arrivalTime.mins;
    }

    //Calculate idle time
    time idleTime;
    idleTime.hour = serviceBegin.hour - serviceEnd.hour;
    idleTime.mins = serviceBegin.mins - serviceEnd.mins;

    //Generate End time
    int addedMins = serviceBegin.mins + (serviceTime%60);
    serviceEnd.hour = serviceBegin.hour + (addedMins/60);
    serviceEnd.mins =  addedMins % 60;

    //push to Queue
    q.push(serviceEnd);

    //Calculate Delay
    time delay;
    delay.hour = serviceBegin.hour - arrivalTime.hour;
    if(delay.hour>0 && serviceBegin.mins<arrivalTime.mins){
        delay.hour = delay.hour - 1;
        serviceBegin.mins += 60;
    }
    delay.mins = serviceBegin.mins - arrivalTime.mins; 

    std::cout<<(i+1)<<"\t"<<iat<<"\t";
    if(arrivalTime.mins<10){
        std::cout<<arrivalTime.hour<<":0"<<arrivalTime.mins<<"\t";
    }else{
        std::cout<<arrivalTime.hour<<":"<<arrivalTime.mins<<"\t";
    }
    std::cout<<serviceTime<<"\t";
    if(serviceBegin.mins<10){
        std::cout<<serviceBegin.hour<<":0"<<serviceBegin.mins<<"\t";
    }else{
        std::cout<<serviceBegin.hour<<":"<<serviceBegin.mins<<"\t";
    }
    if(serviceEnd.mins<10){
        std::cout<<serviceEnd.hour<<":0"<<serviceEnd.mins<<"\t";
    }else{
        std::cout<<serviceEnd.hour<<":"<<serviceEnd.mins<<"\t";
    }
    //////////////////////QUEUE//////////////////////
    std::cout<<inQueue<<"\t\t";
    ////////////////////////////////////////////////
    if(idleTime.hour > 0){
        std::cout<<idleTime.hour<<":"<<idleTime.mins<<"\t";
    }else{
        std::cout<<idleTime.mins<<"\t";
    }
    if(delay.hour > 0){
        std::cout<<delay.hour<<":"<<delay.mins<<"\n";
    }else{
        std::cout<<delay.mins<<"\n";
    }

}

std::cout<<"\nQueue\n";
std::cout<<q.size();

}