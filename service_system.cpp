#include<iostream>
#include<iomanip>
#include<random>
#include<string>
#include<vector>
using namespace std;
//clinic system: 
//maximum time to (examination فحص طبي) is 10 minute 
//maximum patients number is 25 patient

int n ;
int Patient_Number=1;
string schedule[] = {"Patient Number","Arrival Time", "Examination Time", "Examination Begin",
"Examination End", "Wait", "Doctor Idle Time" , "Time Spend"};
vector <double> arrival_time; // Done
vector <double> examination_time; // Done
vector <double> examination_begin(100); //
vector <double> examination_end(100); //
vector <double> wait(100); //
vector <double> doctor_idle_time(100); //
vector <double> time_spend(100); //


double generator(int min , int max)
{
	random_device rd;                       
    mt19937 gen(rd());                      // مولد Mersenne Twister
    uniform_real_distribution<> dist(min,max); // min & max of examination
	return dist(gen);
}

void print()
{
	for(int i = 0 ; i<8 ; i++)
		cout<< schedule[i]<<" | ";
	cout<< endl;
	for(int i = 0 ; i<n ; i++)
	{
		if(i==0)
			cout<<"==============================================================================================="
			<<"================================="<<endl;
		cout<< setw(8) << Patient_Number << setw(8) << "|" ; 
		Patient_Number++;
		cout<< setw(8) << arrival_time[i] << setw(8) << "|" ;
		cout<< setw(8) << examination_time[i] << setw(8) << "|" ;
		cout<< setw(8) << examination_begin[i] << setw(8) << "|" ;
		cout<< setw(8) << examination_end[i] << setw(8) << "|" ;
		cout<< setw(8) << wait[i] << setw(8) << "|" ;
		cout<< setw(8) << doctor_idle_time[i] << setw(8) << "|" ;
		cout<< setw(8) << time_spend[i] << setw(8) << "|" << endl;
		if(i==(n-1))
			cout<<"==============================================================================================="
			<<"================================="<<endl;
	}

}

void calculate()
{
	examination_begin[0]= arrival_time[0];
	examination_end[0]= arrival_time[0] + examination_time[0];
	wait[0]= 0;
	doctor_idle_time[0]= arrival_time[0]; // sheet <3> depend on arrival time instead of 0
    time_spend[0] = examination_time[0] ;

    for (int i = 1 ; i < n ; i++)
    {
        if(arrival_time[i]<= examination_end[i-1])
        {
            examination_begin[i] = examination_end[i-1];
            wait[i] = examination_end[i-1] - arrival_time[i];
            examination_end[i] = arrival_time[i] + wait[i] + examination_time[i];
            doctor_idle_time[i]= 0;
            time_spend[i] = examination_end[i] - arrival_time[i];
        }
        else
        {
            examination_begin[i] = arrival_time[i];
            wait[i] = 0;
            examination_end[i] = examination_begin[i] + examination_time[i];
            doctor_idle_time[i]= examination_begin[i] - examination_end[i-1];
            time_spend[i] = examination_end[i] - arrival_time[i];
        }
    }
} 

void average ()
{
	double waiters=0.0; 
	double total_waiting=0.0; 
	for(double i : wait )
	{
		if(i>0)
		{
			total_waiting+=i;
			waiters++;
		}
	}
    cout<< "Average Waiting Time general: "<< total_waiting/n << " minute" << endl ;
	cout<< "Average Waiting Time For waiting patients: "<< total_waiting/waiters << " minute" << endl ;
	cout<< "Probability of waiters: "<< waiters / n * 100 << " %" << endl;

	double idle_time_defult=30.0;
	double total_idle=0.0; 
	for(double i : doctor_idle_time ) 
	{
		total_idle+=i;
	}
    cout<< "Probability Of Idle: "<< total_idle/idle_time_defult << endl ;

	total_idle=0.0;
	for(double i : doctor_idle_time ) 
	{
		total_idle+=i;
	} 
	//avg of doctor idle time depend on total simulation time:
	double total_simulation = examination_end[n-1] - arrival_time[0];
    cout<< "Total Idle Time: "<< total_idle << " minute" << endl ;
    cout<< "Average doctor Idle: "<< total_idle / total_simulation << " minute" << endl ; 


	double total_time_spend=0.0;
	for(double i : time_spend )
	{
		total_time_spend+=i;
	}
    cout<< "Total Time Spend: "<< total_time_spend << " minute" << endl ;
    cout<< "Average Time Spend: "<< total_time_spend / n << " minute" << endl ;

	double total_examination_time = 0;
	for(double i : examination_time )
	{
		total_examination_time+=i;
	}
    cout<< "Average Examination: "<< total_examination_time / n << " for each patient" << endl;
	
}

int main ()
{
	n = generator(1,25);
	double y = 0.0;
	for( int i = 0 ; i< n ; i++ ) //loop for patient arrival time
	{
		double x = generator(y,y+generator(0.0,30.0)); //time expected between two patients arrival from 0 to 30 minutes
		arrival_time.push_back(x);
		y=x;
	}
	for( int i = 0 ; i< n ; i++ ) //loop for patient examination time
	{
		double x = generator(1.0,10.0); //examination time from 1 to 10 minutes
		examination_time.push_back(x);
	}
    calculate();
	print();
	average ();
	return 0;
}
