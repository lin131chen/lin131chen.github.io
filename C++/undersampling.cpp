#include <iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct merge1
{
	int x;
	int y;
};

vector<float> height;
vector<int>label;
vector<merge1>comparenum;
vector<int>answer;
vector<int>result;

int main(int argc, char* argv[])
{
	ifstream fin1("2_merge.txt", ios::in);
	ifstream fin2("2_labels.txt", ios::in);
	ifstream fin3("2_height.txt", ios::in);
	fin1.open(argv[1]);
	fin2.open(argv[2]);
	fin3.open(argv[3]);


	string temp_str;
	float temp_num;
	while (!fin1.eof())
	{
		string temp;//merge
		getline(fin1, temp_str);
		int i = temp_str.find(',');
		merge1 merge;
		temp.assign(temp_str, 0, i);
		merge.x = atoi(temp.c_str());
		temp.assign(temp_str, i + 1, temp_str.size() - i);
		merge.y = atoi(temp.c_str());
		comparenum.push_back(merge);
	}

	while (!fin2.eof())//label
	{
		getline(fin2, temp_str);
		while (temp_str.find('"') != -1)
		{
			int ch = temp_str.find('"');
			temp_str.erase(ch, 1);
		}
		temp_num = atof(temp_str.c_str());
		label.push_back(temp_num);
	}

	while (!fin3.eof())//height
	{
		getline(fin3, temp_str);
		temp_num = atof(temp_str.c_str());
		height.push_back(temp_num);
	}

	int num = label.size() - 1;
	int i = 0;
	while (num > 10)
	{
		if (comparenum[i].x < 0 && comparenum[i].y < 0)
		{
			if (label[(0 - (comparenum[i].x)) - 1] > label[(0 - (comparenum[i].y)) - 1])//變y
			{
				label[(0 - (comparenum[i].x)) - 1] = label[0 - (comparenum[i].y) - 1];
				result.push_back(label[0 - (comparenum[i].y) - 1]);
			}
			else//變x
			{
				label[0 - (comparenum[i].y) - 1] = label[0 - (comparenum[i].x) - 1];
				result.push_back(label[0 - (comparenum[i].x) - 1]);
			}

		}
		else if (comparenum[i].x < 0 && comparenum[i].y > 0)
		{
			if (label[0 - (comparenum[i].x) - 1] > result[(comparenum[i].y) - 1])//變y
			{
				label[0 - (comparenum[i].x) - 1] = result[(comparenum[i].y) - 1];
				result.push_back(result[(comparenum[i].y) - 1]);
			}
			else//變x
			{
				for (int j = 0; j < label.size(); j++)
				{
					if (label[j] == result[(comparenum[i].y) - 1])
					{
						label[j] = label[0 - (comparenum[i].x) - 1];
					}
				}
				result.push_back(label[0 - (comparenum[i].x) - 1]);
			}
		}
		else if (comparenum[i].x > 0 && comparenum[i].y > 0)
		{
			if (result[(comparenum[i].x) - 1] > result[(comparenum[i].y) - 1])//變y
			{
				for (int j = 0; j < label.size(); j++)
				{
					if (label[j] == result[(comparenum[i].x) - 1])
					{
						label[j] = result[comparenum[i].y - 1];
					}
				}
				result.push_back(result[comparenum[i].y - 1]);
			}
			else//變x
			{
				for (int j = 0; j < label.size(); j++)
				{
					if (label[j] == result[(comparenum[i].y) - 1])
					{
						label[j] = result[comparenum[i].x - 1];
					}
				}
				result.push_back(result[(comparenum[i].x) - 1]);
			}
		}
		else if (comparenum[i].x > 0 && comparenum[i].y < 0)
		{
			if (result[(comparenum[i].x) - 1] > label[0 - (comparenum[i].y) - 1])//變y
			{
				for (int j = 0; j < label.size(); j++)
				{
					if (label[j] == result[comparenum[i].x] - 1);
					{
						label[j] = label[0 - (comparenum[i].y) - 1];
					}
				}
				result.push_back(label[0 - (comparenum[i].y) - 1]);
			}
			else//變x
			{
				label[0 - (comparenum[i].y) - 1] = result[(comparenum[i].x) - 1];
				result.push_back(label[(comparenum[i].x) - 1]);
			}
		}
		i++;
		num--;
	}

	answer.push_back(label[0]);
	/*for (int i = 0; i < label.size(); i++)
	{
		cout << i << "label:" << label[i] << " ";
	}*/

	for (int i = 0; i < label.size(); i++)
	{
		int k = 0;
		for (; k < answer.size(); k++)
		{
			if (answer[k] == label[i])
			{
				break;
			}
		}
		if (k == answer.size())
		{
			answer.push_back(label[i]);
		}
	}
	std::sort(answer.begin(), answer.end());
	for (int i = 1; i < answer.size(); i++)
	{
		cout << answer[i] << " ";
	}
}
