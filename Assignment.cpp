//KARIUKI JAMES MWAURA - CIT-221-059/2018
//HALIMA YUSUF GALGALO - CIT-221-058/2018
//MURIITHI CHARLES MAINA -CIT-221-053/2018
//ROBERT MUNGAI MWANGI - CIT-221-039/2018
//JUMA MICHELLE NANJALA - CIT-221-018/2018
#include <iostream>
#include <queue>
#include <fstream>
#include <math.h>
#include <conio.h>
#include <iomanip>
int main()
{ 
// Single server queue:

int customers=15, iat=0, serviceTime=0, inQueue=0;
double totalIdleTime=0, totalSimulationTime=0;
int RN_arrival[] = {82, 91, 12, 77, 90, 75, 33, 61, 19, 58, 41, 54, 52, 16, 86};
int RN_service[] = {93, 59, 76, 62, 40, 41, 51, 91, 93, 38, 92, 22, 9, 7, 65};
double sur; //server utilization rate
std::ofstream outfile("output.txt",std::ios::out);
outfile<<"\nC\tRN\tIAT\tAT\tRN\tST\tStart\tEnd\tin_Queue\t\tIT\tDelay\n";

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

time startTime; //to calculate total simulation time
time endTime; //to calculate total simulation time

std::queue<time> q; //declare a queue that stores end time values
q.push(serviceEnd);



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

    if(i==0){
        startTime = serviceBegin; //store the very first start Time (to calculate tot simulation time)
    }

    //Calculate idle time
    int a = (serviceBegin.hour*60) + serviceBegin.mins;
    int b = (serviceEnd.hour*60) + serviceEnd.mins;
    int idleTime = a-b;
    totalIdleTime += idleTime; //cumulative result for total idle time

    //Generate End time
    int addedMins = serviceBegin.mins + (serviceTime%60);
    serviceEnd.hour = serviceBegin.hour + (addedMins/60);
    serviceEnd.mins =  addedMins % 60;

    endTime = serviceEnd; // for calculating tot. simulation time

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

    outfile<<(i+1)<<"\t"<<RN_arrival[i]<<"\t"<<iat<<"\t";
    if(arrivalTime.mins<10){
        outfile<<arrivalTime.hour<<":0"<<arrivalTime.mins<<"\t";
    }else{
        outfile<<arrivalTime.hour<<":"<<arrivalTime.mins<<"\t";
    }
    outfile<<RN_service[i]<<"\t"<<serviceTime<<"\t";
    if(serviceBegin.mins<10){
        outfile<<serviceBegin.hour<<":0"<<serviceBegin.mins<<"\t";
    }else{
        outfile<<serviceBegin.hour<<":"<<serviceBegin.mins<<"\t";
    }
    if(serviceEnd.mins<10){
        outfile<<serviceEnd.hour<<":0"<<serviceEnd.mins<<"\t";
    }else{
        outfile<<serviceEnd.hour<<":"<<serviceEnd.mins<<"\t";
    }
    outfile<<inQueue<<"\t\t"<<idleTime<<"\t";
    if(delay.hour > 0){
        outfile<<delay.hour<<":"<<delay.mins<<"\n";
    }else{
        outfile<<delay.mins<<"\n";
    }

}
//calcluate total simulation time
int a = ((endTime.hour * 60) + endTime.mins); //convert to minutes
int b = ((startTime.hour * 60) + startTime.mins);
totalSimulationTime = a-b;
//calculate server utilization rate
sur = ((totalSimulationTime - totalIdleTime)/totalSimulationTime);
sur *=100; //multiply by 100 to get percentage

outfile<<"\nThe server utilization rate = "<<round(sur)<<"%";
outfile<<"\nThe average delay in the Queue = ";
outfile<<"\nThe average No. of customers queueing per hour = ";
std::cout<<"\nThe results are save on a text file called (output.txt)\nNOTE: table displays correctly on notepad";

}