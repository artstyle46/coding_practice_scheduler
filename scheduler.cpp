#include <bits/stdc++.h>
#include <time.h>

using namespace std;

class time {
private:
	struct tm *input_time;
	time(struct tm *input);
public:
	void getInput(struct tm *input_time);
};

time :: time(struct tm *input){
	input->tm_sec = 0;
	input->tm_min = 0;
	input->tm_hour = 0;
	input->tm_mday = 1;
	input->tm_mon = 0;
	input->tm_year = 1900;
	input->tm_wday = 0;
	input->tm_yday = 0;
	input->tm_isdst = NULL;
}

void time :: getInput(struct tm *input){
	string str;
	cout << "please enter the time in the only given format:\n HH:MM:SS\n";
	cin >> str;
	if(str.length() != 8)
		cout << "please enter time in only given format" << endl;
	else{
		int temp = stoi(str.substr(0,2));
		if(temp >23 || temp < 0)
			cout << "Invalid time hour can only be from 0 to 23" << endl;
		else
			input->tm_hour = temp;
		temp = stoi(str.substr(3,2));
		if(temp >59 || temp < 0)
			cout << "Invalid time minute can only be from 0 to 59" << endl;
		else
			input->tm_min = temp;
		temp = stoi(str.substr(5,2));
		if(temp > 59 || temp < 0)
			cout << "Invalid time second can only be from 0 to 59" << endl;
		else
			input->tm_sec = temp;
	}
}