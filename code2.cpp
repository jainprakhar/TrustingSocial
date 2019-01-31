#include <bits/stdc++.h>
using namespace std;

typedef struct meeting{
	string name;
	int duration;
	int start_time;
	int track_id;
};

meeting* getMeeting(string nm,int durn,int st_time,int tid)
{
	meeting* m = new meeting();
	m->name = nm;
	m->duration = durn;
	m->start_time = st_time;
	m->track_id = tid;
	return m;
}

meeting* processLine(string str)
{
	int prev_sp = -1;
	for(int i=0;i<str.length();i++)
	{
		if(str[i] == ' ')
		{
			prev_sp = i;
		}
	}

	//assuming always in mins
	int end = str.length() - 3;//removing mins
	int durn = stoi(str.substr(prev_sp+1,end-(prev_sp+1)));
	meeting* m = getMeeting(str,durn,0,0);
	return m;
}

int actual(int ctime,int durn)
{
	int mins = ctime - (ctime/100)*100;//mins in ctime
	int hrs = (ctime/100);//hrs in ctime

	int totalmins = mins + durn;
	int add_hrs = hrs + (mins+durn)/60;
	int add_mins = mins + durn - ((totalmins)/60)*60;

	return (100*(add_hrs) + add_mins);
}

string formatTime(int ctime)
{
	int mins = ctime - (ctime/100)*100;//mins in ctime
	int hrs = (ctime/100);//hrs in ctime
	string am_pm = "AM";

	string ret = "";
	if(hrs >= 10) 
	{
		if(hrs >= 13)
		{
			ret += to_string(hrs-12);
		}
		else ret += to_string(hrs); 
	}
	else ret += "0" + to_string(hrs);

	ret += ":";

	if(mins >= 10)ret += to_string(mins);
	else ret += "0" + to_string(mins);

	if(hrs > 12)
	{
		am_pm = "PM";
	}

	ret += am_pm;
	return ret;
}


vector<string> fillMeetings(vector<meeting*> allM,int tracks)
{
	vector<string> ans; 
	int ctracks = 1;//current track id
	int ctime = 900;//current time
	bool lunch = false;

	ans.push_back("Track no. " + to_string(ctracks));
	for(int i=0;i<allM.size();i++)
	{
		meeting* curr = allM[i];
		int actual_time = actual(ctime,curr->duration);
		if(actual_time > 1200)//lunch time exceeded
		{
			if(actual_time > 1700)//start new track
			{
				ctracks++;
				ctime = 900;
				lunch = false;
				ans.push_back("05:00PM Networking Event");
				ans.push_back("\n*************\n");
				ans.push_back("Track no. " + to_string(ctracks));
			}
			else//schedule after lunch
			{
				if(!lunch)
				{
					ans.push_back("12:00PM Lunch");
					lunch = true;
					curr->start_time = 1300;
					curr->track_id = ctracks;
					ans.push_back("01:00PM " + curr->name);
					ctime = actual(1300,curr->duration);
				}
				else// lunch taken
				{
					curr->start_time = ctime;
					curr->track_id = ctracks;
					ans.push_back(formatTime(ctime) + "	" + curr->name);
					ctime = actual(ctime,curr->duration);				
				}

			}
		}
		else//schedule before lunch
		{
			curr->start_time = ctime;
			curr->track_id = ctracks;
			ans.push_back(formatTime(ctime) + "	" + curr->name);
			ctime = actual(ctime,curr->duration);	
		}

	}

	// events are finished then networking event for last track
	ans.push_back("05:00PM Networking Event");
	return ans;

}


int main()
{	
	//input
	ifstream fid;
	fid.open("input2.txt");
	char line[256];
	
	//file read
	vector<meeting*> allMeeting;// track of all the meetings
	int total_duration = 0;// total time in mins for all meetings
	while(fid.peek()!=EOF)
	{
		fid.getline(line,256);
		//cout << strlen(line) << endl;
		string ln = line;
		//cout << ln << endl;
		allMeeting.push_back(processLine(ln));
		total_duration += float(allMeeting[allMeeting.size()-1]->duration);
	}


	// utility
	int req_tracks = ceil(total_duration/(8*60.0));//no of hours in a day

	//output
	vector<string> ans = fillMeetings(allMeeting,req_tracks);
	for(int i=0;i<ans.size();i++)
		cout << ans[i] << endl;

	return 0;
}