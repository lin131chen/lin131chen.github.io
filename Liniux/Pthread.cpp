#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
#include<unistd.h>

using namespace std;

void* dispatcher(void* arg);
void* producer(void* arg);

int total = 0;
int Pnum[4] = {};
int Inum[4] = {};
int battery = 0;
int aircraft = 0;
int propeller = 0;

pthread_mutex_t init;

int main(int argc, char* argv[])
{
	pthread_mutex_init(&init, NULL);
	srand(atoi(argv[2]));
	if (atoi(argv[1]) == 0)
	{
		pthread_t dispatcher1;
		pthread_t producer1;
		pthread_t producer2;
		pthread_t producer3;
		pthread_create(&dispatcher1, NULL, dispatcher, NULL);
		pthread_create(&producer1, NULL, producer, (void*)(intptr_t)1);
		pthread_create(&producer2, NULL, producer, (void*)(intptr_t)2);
		pthread_create(&producer3, NULL, producer, (void*)(intptr_t)3);

		pthread_join(dispatcher1, NULL);
		pthread_join(producer1, NULL);
		pthread_join(producer2, NULL);
		pthread_join(producer3, NULL);

		cout << "Num of battery" << battery << endl;
		cout << "Num of aircraft" << aircraft << endl;
		cout << "Num of propeller" << propeller << endl;
		int max = (Pnum[1] >= Pnum[2] && Pnum[1] >= Pnum[3]) ? Pnum[1] : (Pnum[2] >= Pnum[1] && Pnum[2] >= Pnum[3]) ? Pnum[2] : Pnum[3];
		int min = (Pnum[1] <= Pnum[2] && Pnum[1] <= Pnum[3]) ? Pnum[1] : (Pnum[2] <= Pnum[1] && Pnum[2] <= Pnum[3]) ? Pnum[2] : Pnum[3];
		for (int k = 1; k <= 3; k++)
		{
			if (Pnum[k] == max)
			{
				cout << "Producer " << k << ": " << Pnum[k] << "drone(s)" << endl;
			}
		}
		for (int k = 1; k <= 3; k++)
		{
			if (Pnum[k] < max&&Pnum[k]>min)
			{
				cout << "Producer " << k << ": " << Pnum[k] << "drone(s)" << endl;
			}
		}
		for (int k = 1; k <= 3; k++)
		{
			if (Pnum[k] == min)
			{
				cout << "Producer " << k << ": " << Pnum[k] << "drone(s)" << endl;
			}
		}


	}
	return 0;
}

void* dispatcher(void* arg)
{
	while (total < 50)
	{
		int choice = -1;
		do {
			choice = rand() % 3 + 1;
			//cout<<".";
			usleep(10);
		} while (Inum[choice] != 0);
		if (total >= 50)
		{
			return 0;
		}
		cout << "Dispatcher:";
		if (choice == 1)
		{
			cout << "battery" << endl;
			Inum[1]++;
			battery++;
		}
		else if (choice == 2)
		{
			cout << "aircraft" << endl;
			Inum[2]++;
			aircraft++;
		}
		else if (choice == 3)
		{
			cout << "propeller" << endl;
			Inum[3]++;
			propeller++;
		}
	}
	pthread_exit(0);
}

void* producer(void* arg)
{
	int prog = (intptr_t)arg;
	int buf_battery = 0;
	int buf_aircraft = 0;
	int buf_propeller = 0;//item have got;
	string producer;
	if (total > 50)
	{
		return 0;
	}
	if (prog == 1)
	{
		producer = "Producer 1 (aircraft):";
	}
	else if (prog == 2)
	{
		producer = "Producer 2: ";
	}
	else if (prog == 3)
	{
		producer = "Producer 3: ";
	}
	while (total < 50)
	{
		pthread_mutex_lock(&init);
		if (Inum[1] > 0 && buf_battery == 0)
		{
			Inum[1]--;
			buf_battery++;
			cout << producer << "get battery" << endl;
		}
		else if (Inum[2] > 0 && buf_aircraft == 0 && prog != 1)
		{
			Inum[2]--;
			buf_aircraft++;
			cout << producer << "get atrcraft" << endl;
		}
		else if (Inum[3] > 0 && buf_propeller == 0)
		{
			Inum[3]--;
			buf_propeller++;
			cout << producer << "get propeller" << endl;
		}
		if (buf_battery != 0 && buf_aircraft != 0 && buf_propeller != 0 && prog != 1)
		{
			buf_battery--;
			buf_aircraft--;
			buf_propeller--;
			total++;
			Pnum[prog]++;
			cout << producer << "OK, " << Pnum[prog] << " drone(s)" << endl;
		}

		else if (prog == 1 && buf_battery != 0 && buf_propeller != 0)
		{
			buf_battery--;
			buf_propeller--;
			total++;
			Pnum[prog]++;
			cout << producer << "OK, " << Pnum[prog] << " drone(s)" << endl;
		}
		pthread_mutex_unlock(&init);
	}

	pthread_exit(0);

}



