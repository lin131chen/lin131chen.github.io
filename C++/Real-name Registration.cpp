#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iterator>
//#include<cstdlib>
#include <algorithm>

using namespace std;

struct Date
{
	int Year = 0;
	int Month = 0;
	int Day = 0;
	int count = 0;
};

struct Time
{
	int Hour = 0;
	int Minute = 0;
	int Second = 0;
};

struct People_Inf
{
	int count = 0;
	Date date;
	Time time;
	string ID;
	string Place;
};

int month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

bool leapyear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

int counting(Date date, Time time)
{

	int betweenyear = 0;
	for (int i = 2021; i < date.Year; i++)
	{
		if (leapyear(i))
		{
			betweenyear += 366;
		}
		else
		{
			betweenyear += 365;
		}
	}
	int betweenmonth = 0;
	if (leapyear(date.Year))
	{
		month[2] = 29;
	}
	else
	{
		month[2] = 28;
	}
	for (int i = 1; i < date.Month; i++)
	{
		int pos = month[i];
		betweenmonth += pos;
	}

	return (betweenyear + betweenmonth + date.Day - 1) * 24 * 60 * 60 + time.Hour * 60 * 60 + time.Minute * 60 + time.Second;

}

int counting(Date date)
{
	int betweenyear = 0;
	for (int i = 2021; i < date.Year; i++)
	{
		if (leapyear(i))
		{
			betweenyear += 366;
		}
		else
		{
			betweenyear += 365;
		}
	}

	if (leapyear(date.Year))
	{
		month[2] = 29;
	}
	else
	{
		month[2] = 28;
	}

	int betweenmonth = 0;
	for (int i = 1; i < date.Month; i++)
	{
		int pos = month[i];
		betweenmonth += pos;
	}
	return (betweenyear + betweenmonth + (date.Day - 1)) * 24 * 60 * 60;
}


bool date_earlier(Date data, Date get)
{
	if (data.Year < get.Year)
		return true;
	if (data.Year > get.Year)
		return false;

	if (data.Month < get.Month)
		return true;
	if (data.Month > get.Month)
		return false;

	if (data.Day < get.Day)
		return true;

	return false;
}


int main(int argc, char* argv[])
{
	ifstream fin1;
	fin1.open(argv[1]);
	//ifstream fin1("in2.txt", ios::in);
	string order;

	Date begin;
	Date end;
	vector<People_Inf>PatientData;
	vector<People_Inf>Data;
	vector<People_Inf>First_layer;
	vector<People_Inf>compare;
	vector<People_Inf>Second_layer;
	string People_ID;

	getline(fin1, People_ID);

	getline(fin1, order, '-');
	begin.Year = atoi(order.c_str());

	getline(fin1, order, '-');
	begin.Month = atoi(order.c_str());

	getline(fin1, order);
	begin.Day = atoi(order.c_str());

	getline(fin1, order, '-');
	end.Year = atoi(order.c_str());

	getline(fin1, order, '-');
	end.Month = atoi(order.c_str());

	getline(fin1, order);
	end.Day = atoi(order.c_str());

	while (!fin1.eof())
	{
		string order;
		People_Inf all;

		getline(fin1, order, ',');
		all.ID = order;

		getline(fin1, order, ',');
		all.Place = order;

		getline(fin1, order, '-');
		all.date.Year = atoi(order.c_str());

		getline(fin1, order, '-');
		all.date.Month = atoi(order.c_str());

		getline(fin1, order, ' ');
		all.date.Day = atoi(order.c_str());

		getline(fin1, order, ':');
		all.time.Hour = atoi(order.c_str());

		getline(fin1, order, ':');
		all.time.Minute = atoi(order.c_str());

		getline(fin1, order, ',');
		all.time.Second = atoi(order.c_str());

		all.count = counting(all.date, all.time);

		Data.push_back(all);
		getline(fin1, order);
	}
	int rangebegin = counting(begin);
	int rangeend = counting(end) + 24 * 60 * 59;

	for (int i = 0; i < Data.size(); i++)//留在疫調範圍資料
	{
		if (Data[i].ID == People_ID && rangebegin <= Data[i].count && Data[i].count <= rangeend)
		{
			PatientData.push_back(Data[i]);
		}
	}

	for (int j = 0; j < PatientData.size(); j++)
	{
		for (int i = 0; i < Data.size(); i++)//找到第一層
		{
			if (Data[i].Place == PatientData[j].Place && Data[i].ID != PatientData[j].ID && PatientData[j].count <= Data[i].count && Data[i].count <= PatientData[j].count + 30 * 60)
			{
				First_layer.push_back(Data[i]);
			}
		}
	}

	for (int j = 0; j < First_layer.size(); j++)//第一層三天足跡
	{
		for (int i = 0; i < Data.size(); i++)
		{
			if (Data[i].ID == First_layer[j].ID && First_layer[j].count <= Data[i].count && Data[i].count <= First_layer[j].count + 3 * 24 * 60 * 59)
			{
				compare.push_back(Data[i]);
			}
		}
	}


	for (int i = 0; i < Data.size(); i++)//第二層
	{
		for (int j = 0; j < compare.size(); j++)
		{
			if (Data[i].Place == compare[j].Place && Data[i].ID != compare[j].ID && compare[j].count <= Data[i].count && Data[i].count <= compare[j].count + 30 * 60)
			{
				Second_layer.push_back(Data[i]);
			}
		}
	}

	vector<string>answer;
	answer.push_back(People_ID);
	for (int i = 0; i < First_layer.size(); i++)
	{
		answer.push_back(First_layer[i].ID);
	}
	for (int i = 0; i < Second_layer.size(); i++)
	{
		answer.push_back(Second_layer[i].ID);
	}

	sort(answer.begin(), answer.end());

	for (int i = 0; i < answer.size(); i++)
	{
		int correct = true;
		for (int j = i+1; j < answer.size(); j++)
		{
			if (answer[i] == answer[j])
			{
				correct = false;
				break;
			}
		}
		if (correct)
		{
			cout << answer[i] << endl;
		}
		
	}



}
