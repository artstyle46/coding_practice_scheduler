#include <bits/stdc++.h>
#include <time.h>

using namespace std;


// local_current_time saved here.

int curr_time() {
	time_t t =time(0);
	struct tm *now = localtime(&t);
	int seconds_now = now->tm_sec;
	int minutes_now = now->tm_min + now->tm_hour * 60;
	seconds_now = seconds_now + minutes_now * 60;
	return seconds_now;
}

//converting string into time in seconds.

int convert_string_secs(string input_time)
{
	int days = atoi((input_time.substr(0,2)).c_str());
	int hours = atoi((input_time.substr(3,2)).c_str());
	int minutes = atoi((input_time.substr(6,2)).c_str());
	int seconds = atoi((input_time.substr(9,2)).c_str());
	hours = hours + days *24;
	minutes = minutes + hours * 60;
	seconds = seconds + minutes * 60;
	return seconds;
}

// sleep duration for program.

int calc_sleep_time(string input_time)
{
	int input_time_in_secs = convert_string_secs(input_time);
	int curr_time_in_secs = curr_time();
	return input_time_in_secs - curr_time_in_secs;
}

//scheduling the job here.

void scheduler_thread(string input_time, string time_interval, string path)
{
	int sleep_time = calc_sleep_time(input_time);
	int time_int_in_secs = convert_string_secs(time_interval);
	while(sleep_time < 0)
		sleep_time = sleep_time + time_int_in_secs;
	while(true)
	{
		sleep(sleep_time);
		const char *temp = path.c_str();
		char *args[] = {NULL};
		pid_t pid = fork();
		switch(pid)
		{
			case 0:
				execv(temp,args);
				break;
		}
		sleep_time = time_int_in_secs;
	}  
}

int main()
{
//	ofstream log_file("log.txt");
//	cout.rdbuf(log_file.rdbuf());
	ifstream in("input.txt"); // input file should be in format: [1-n] DD:HH:MM:SS DD:HH:MM:SS path/to/executable.
	cin.rdbuf(in.rdbuf());		//DD:HH:MM:SS->time to run the job, DD:HH:MM:SS-> time interval for scheduling.
	if(in.is_open())
	{
		int num;
		while(cin >> num)
		{
			string input_time, time_interval, path;
			cin >> input_time >> time_interval >> path;
			pid_t pid1 = fork();
			switch (pid1)
			{
				case 0:
					scheduler_thread(input_time, time_interval, path);
					return 0;
			}
		}
		in.close();
	}
	return 0;
}
