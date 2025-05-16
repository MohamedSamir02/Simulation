#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;

int n ;
string schedule[] = {"Arrival Time", "Service Time", "Service Begin",
"Service End", "Wait In Queue", "Serive Idle Time" , "Time Spend In System"};
vector <int> arrival_time; // Done
vector <int> service_time; // Done
vector <int> service_begin(100); //
vector <int> service_end(100); //
vector <int> wait_in_queue(100); //
vector <int> service_idle_time(100); //
vector <int> time_spend_in_system(100); //


void inputs()
{
    cout<< "Enter Number Of Services: ";
    cin>> n;
	cout<< "Enter The Arrival Time Of All Clients:\n";
	for( int i = 0 ; i< n ; i++ )
	{
		int x;
		cin >> x;
		arrival_time.push_back(x);
		
	}
	cout<<"==============\n";
	cout<< "Enter The Service Time Of All Clients:\n";
	for( int i = 0 ; i< n ; i++ )
	{
		int x;
		cin >> x;
		service_time.push_back(x);
	}
}

void print()
{
	for(int i = 0 ; i<7 ; i++)
		cout<< schedule[i]<<" | ";
	cout<< endl;
	for(int i = 0 ; i<n ; i++)
	{
		if(i==0)
			cout<<"-------------|"<<"--------------|"<<
			"---------------|"<<"-------------|"<<"---------------|"
			<<"------------------|"<<"----------------------|"<<endl;
		
		cout<< setw(7) << arrival_time[i] << setw(7) << "|" ;
		cout<< setw(7) << service_time[i] << setw(8) << "|" ;
		cout<< setw(8) << service_begin[i] << setw(8) << "|" ;
		cout<< setw(7) << service_end[i] << setw(7) << "|" ;
		cout<< setw(7) << wait_in_queue[i] << setw(9) << "|" ;
		cout<< setw(9) << service_idle_time[i] << setw(10) << "|" ;
		cout<< setw(11) << time_spend_in_system[i] << setw(12) << "|" << endl;
		if(i==(n-1))
			cout<<"-------------|"<<"--------------|"<<
			"---------------|"<<"-------------|"<<"---------------|"
			<<"------------------|"<<"----------------------|"<<endl;
	}

}

void calculate()
{
	service_begin[0]= arrival_time[0];
	service_end[0]= arrival_time[0] + service_time[0];
	wait_in_queue[0]= 0;
	service_idle_time[0]= arrival_time[0]; // sheet <3> depend on arrival time instead of 0
    time_spend_in_system[0] = service_time[0] ;

    for (int i = 1 ; i < n ; i++)
    {
        if(arrival_time[i]<= service_end[i-1])
        {
            service_begin[i] = service_end[i-1];
            wait_in_queue[i] = service_end[i-1] - arrival_time[i];
            service_end[i] = arrival_time[i] + wait_in_queue[i] + service_time[i];
            service_idle_time[i]= 0;
            time_spend_in_system[i] = service_end[i] - arrival_time[i];
        }
        else
        {
            service_begin[i] = arrival_time[i];
            wait_in_queue[i] = 0;
            service_end[i] = service_begin[i] + service_time[i];
            service_idle_time[i]= service_begin[i] - service_end[i-1];
            time_spend_in_system[i] = service_end[i] - arrival_time[i];
        }
    }
} 

void average ()
{
	float waiters=0; //sheet <4> print as float
	float total=0; //sheet <4> print as float
	for(int i : wait_in_queue ) // sheet <1> sum without accumlate
	{
		if(i>0)
		{
			total+=i;
			waiters++;
		}
	}
    cout<< "Average Waiting Time: "<< total/n << endl ;
    cout<< "Probability: "<< waiters / n << endl;
	cout<< "Average Waiting Time For Those Who Wait: "<< total/waiters << endl ;

	int idle_system_defult=86;
	total=0; //sheet <4> print as float
	for(int i : service_idle_time ) // sheet <1> sum without accumlate
	{
		total+=i;
	}
    cout<< "Probability Of Idle System: "<< total/idle_system_defult << endl ;

	total=0;
	for(int i : service_idle_time ) 
	{
		total+=i;
	} // sheet <2> avg of service idle time depend on total simulation time:
	int total_simulation = service_end[n-1] - arrival_time[0];
    cout<< "Average Service Idle Time: "<< total / total_simulation << endl ; 


	total=0;
	for(int i : time_spend_in_system ) // sheet <1> sum without accumlate
	{
		total+=i;
	}
    cout<< "Average Time Spend In System: "<< total / n << endl ;

	total = 0;
	for(int i : service_time ) // sheet <1> sum without accumlate
	{
		total+=i;
	}
    cout<< "Average Service Time: "<< total / n << endl;

	total=0;
	
}

int main ()
{
	inputs();
    calculate();
	print();
	average ();
	return 0;
}