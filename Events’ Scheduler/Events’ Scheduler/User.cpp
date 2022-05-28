#include "User.h"
#include <iostream>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<string>
#include"Event.h"
#include <fstream>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

//this function to detect intesection between events when adding or updating events
bool User::intersect(string start_time, string end_time)
{
	bool bad = 0;
	vec.push_back(start_time);
	vec.push_back(end_time);
	sort(vec.begin(), vec.end());
	for (int i = 0; i < vec.size() - 1; i++)
	{
		if (mp[vec[i]] == 0 && mp[vec[i + 1]] == 0)
		{
			bad = 1;
			break;
		}
		else if (mp[vec[i]] == 1 && mp[vec[i + 1]] == 1)
		{
			bad = 1;
			break;
		}
	}
	return bad;
}

//this function to convert integer to string and it is a helper for intersect function
string User::fix(int x)
{
	string s = to_string(x);
	if (s.size() == 1) {
		string s2 = "0";
		s = s2 + s;
	}
	return s;
}

//this function to order events before displaying them
void User::to_order(string start_time, string end_time, string name) {
	vec_disp.push_back(start_time);
	vec_disp.push_back(end_time);
	sort(vec_disp.begin(), vec_disp.end());
	vec_disp2.push_back({start_time, name});
	vec_disp2.push_back({ end_time ,name});
}

//this function to load data from the file to the events vector
void User::load_data() {
	ifstream open_event;
	open_event.open("upcoming_events.txt");
	string name;
	string place;
	string M;
	int start_date_day;
	int start_date_month;
	int start_date_year;
	int end_date_day;
	int end_date_month;
	int end_date_year;
	int start_time;
	int start_time_min;
	int end_time;
	int end_time_min;
	bool done;
	
	getline(open_event, name);
	getline(open_event, place);
	open_event >> start_date_day;
	open_event >> start_date_month;
	open_event >> start_date_year;
	open_event >> end_date_day;
	open_event >> end_date_month;
	open_event >> end_date_year;
	open_event >> start_time;
	open_event >> start_time_min;
	open_event >> end_time;
	open_event >> end_time_min;
	getline(open_event, M);
	getline(open_event, M);
	open_event >> done;

	while (!open_event.eof())
	{
		Event eve(name, start_date_day, start_date_month, start_date_year, end_date_day, end_date_month, end_date_year, place, start_time, end_time, start_time_min, end_time_min, done, M);
		events.push_back(eve);
		getline(open_event >> ws, name);
		getline(open_event, place);
		open_event >> start_date_day;
		open_event >> start_date_month;
		open_event >> start_date_year;
		open_event >> end_date_day;
		open_event >> end_date_month;
		open_event >> end_date_year;
		open_event >> start_time;
		open_event >> start_time_min;
		open_event >> end_time;
		open_event >> end_time_min;
		getline(open_event >> ws, M);
		open_event >> done;
	}
	open_event.close();
}

//Add event function
bool User::add_event() {
	ifstream open_event;
	open_event.open("upcoming_events.txt");
	string name;
	string place;
	string M;
	int start_date_day;
	int start_date_month;
	int start_date_year;
	int end_date_day;
	int end_date_month;
	int end_date_year;
	int start_time;
	int start_time_min;
	int end_time;
	int end_time_min;
	bool done;
	
	//load data from the file to the events vector
	if (open_event) {
		events.clear();
		vec.clear();
		open_event.close();
		load_data();
	}
	
	//get time now
	time_t t = std::time(0);  
	tm* now = std::localtime(&t);
	int year = now->tm_year + 1900;
	int day = now->tm_mday;
	int month = (now->tm_mon + 1);

label:
	//take event name
again:cout << "\n\t\t\t\tEnter event name: ";
	getline(cin>>ws, name);
	cout << endl;

	// check if the name already exists
	if (!events.empty()) {
		int choice;
		for (int i = 0; i < events.size(); i++)
		{
			if (events[i].name.compare(name) == 0) {
				cout << "\t\t\t\tThis event name already exists\n";
				goto again;
			}
		}
	}

	//take event place
	cout << "\t\t\t\tEnter event place: ";
	getline(cin, place);
	cout << endl;
	
	//take event start date
l1:cout << "\t\t\t\tEnter event start date:" << endl;
	cout << "\t\t\t\tday: ";
	while (cin >> start_date_day && (start_date_day < 1 || start_date_day >31)) {
		cout << "\t\t\t\tRange is [1-31]" << endl;
		cout << "\t\t\t\tday: ";
	}

	cout << "\t\t\t\tmonth: ";
	while (cin >> start_date_month && (start_date_month < 1 || start_date_month > 12)) {
		cout << "\t\t\t\tRange is [1-12]" << endl;
		cout << "\t\t\t\tmonth: ";
	}

	if ((start_date_month < month) || ((start_date_day <= day) && (start_date_month == month))) {
		cout << "\n\t\t\t\tPlease enter coming date"<<endl;
		goto l1;
	}
cout << "\t\t\t\tyear: ";
	while (cin >> start_date_year && (start_date_year > 2022 || start_date_year < 2022)) {
		cout << "\t\t\t\tYear should be 2022" << endl;
		cout << "\t\t\t\tyear: ";
	}
	cout << endl;
	
	//take event end date
	l4:cout << "\t\t\t\tEnter event end date:" << endl;
	cout << "\t\t\t\tday: ";
	while (cin >> end_date_day && (end_date_day < 1 || end_date_day >31)) {
		cout << "\t\t\t\tRange is [1-31]" << endl;
		cout << "\t\t\t\tday: ";
	}

	cout << "\t\t\t\tmonth: ";
	while (cin >> end_date_month && (end_date_month < 1 || end_date_month > 12)) {
		cout << "\t\t\t\tRange is [1-12]" << endl;
		cout << "\t\t\t\tmonth: ";
	}

	if ((end_date_month < month) || (end_date_day <= day) && (end_date_month == month)) {
		cout << "\n\t\t\t\t Please enter coming date\n";
		goto l4;
	}
	
	cout << "\t\t\t\tyear: ";
	while (cin >> end_date_year && (end_date_year > 2022 || end_date_year < 2022))
	{
		cout << "\t\t\t\tYear should be 2022" << endl;
		cout << "\t\t\t\tyear: ";
	}
	
	if ((end_date_day == start_date_day && end_date_month == start_date_month) || (end_date_day < start_date_day && end_date_month == start_date_month) || (end_date_month < start_date_month)) {
		cout << "\n\t\t\t\tEnd date is before start date or the event length is less than one day!!";
		cout << endl;
		goto l4;
	}
	cout << endl;

	//take event start time
	t:cout << "\t\t\t\tEnter event start time (Hours): ";
	while (cin >> start_time && (start_time > 12 || start_time < 1)) {
		cout << "\t\t\t\tRange is[1-12] ";
		cout << endl;
		cout << "\t\t\t\tEnter event start time (Hours): ";
	}
	cout << endl;

	cout << "\t\t\t\tEnter event start time (Minutes): ";
	while (cin >> start_time_min && (start_time_min > 59 || start_time_min < 0)) {
		cout << "\t\t\t\tRange is[0-59] ";
		cout << endl;
		cout << "\t\t\t\tEnter event start time (Minutes): ";
	}
	cout << endl;

	//take event end time
	cout << "\t\t\t\tEnter event end time (Hours): ";
	while (cin >> end_time && (end_time > 12 || end_time < 1)) {
		cout << "\t\t\t\tRange is[1-12] ";
		cout << endl;
		cout << "\t\t\t\tEnter event end time (Hours): ";
	}
	cout << endl;

	cout << "\t\t\t\tEnter event end time (Minutes): ";
	while (cin >> end_time_min && (end_time_min > 59 || end_time_min < 0)) {
		cout << "\t\t\t\tRange is[0-59] ";
		cout << "\t\t\t\tEnter event end time (Minutes): ";
	}

	//pm or am
yet2:cout << "\n\t\t\t\tEnter pm or am: ";
	cin >> M;
	transform(M.begin(), M.end(), M.begin(), ::toupper);
	if (M == "PM" || M == "AM")
		goto yet;
	else
		goto yet2;
yet:cout << endl;
	
	if (start_time != 12 && (start_time > end_time)) {
			cout << "\t\t\t\tstart time should be before end time\n\n";
			goto t;
	}
	
	string s1, s2, s3, s4, s5, s6, s7, s8, start_time_s, end_time_s;
	
	//load events from the file to the intersection vector
	for (int i = 0; i < events.size(); i++)
	{
		 s1 = fix(events[i].start_date_year);
		 s2 = fix(events[i].start_date_month);
		 s3 = fix(events[i].start_date_day);
		 s4 = fix(events[i].start_time);
		 start_time_s = s1 + s2 + s3 + s4;
		 s5 = fix(events[i].end_date_year);
		 s6 = fix(events[i].end_date_month);
		 s7 = fix(events[i].end_date_day);
		 s8 = fix(events[i].end_time);
		 end_time_s = s5 + s6 + s7 + s8;
		mp[start_time_s] = 1;
		mp[end_time_s] = 0;
		intersect(start_time_s, end_time_s);
	}
	
	//check the intersect between events
	s1 = fix(start_date_year); 
	s2 = fix(start_date_month); 
	s3 = fix(start_date_day);
	s4 = fix(start_time);
	start_time_s = s1 + s2 + s3 + s4;
	s5 = fix(end_date_year);
	s6 = fix(end_date_month); 
	s7 = fix(end_date_day);
	s8 = fix(end_time);
	end_time_s = s5 + s6 + s7 + s8;
	mp[start_time_s] = 1;
	mp[end_time_s] = 0;
	if (intersect(start_time_s, end_time_s))
	{
		int choice;
		for (int j = 0; j < vec.size(); j++)
		{
			if (vec[j] == start_time_s || vec[j] == end_time_s)
			{
				vec.erase(vec.begin() + j);
				j -= 1;
			}
		}
		cout << "\t\t\t\tThere is an intersect!!" << endl;
		again2:cout << "\t\t\t\tpress 1 to enter data again or 0 to go to main page: ";
		cin >> choice;
		if (choice == 0) {
			return false;
		}
		else if(choice == 1) {
			goto label;
		}
		else {
			cout << "\t\t\t\tThis choice is invalid!\n";
			goto again2;
		}
	}

	else
	{
		Event eve(name, start_date_day, start_date_month, start_date_year, end_date_day, end_date_month, end_date_year, place, start_time, end_time, start_time_min, end_time_min,M);
		events.push_back(eve);
		insert_file(eve);
		
		cout << "\t\t\t\tYour event is being added";
		for (int i = 0; i < 6; i++)
		{
			cout << ".";
			this_thread::sleep_for(chrono::milliseconds(300));
		}
		cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t-:Your event is successfully added:-\n\n";
		
		return true;
	}
}

//this function to insert event's data in a file
void User::insert_file(Event eve) {
	ofstream event_data;
	event_data.open("upcoming_events.txt", ios::app);
	event_data << eve.name;
	event_data << endl;
	event_data << eve.place;
	event_data << endl;
	event_data << eve.start_date_day;
	event_data << endl;
	event_data << eve.start_date_month;
	event_data << endl;
	event_data << eve.start_date_year;
	event_data << endl;
	event_data << eve.end_date_day;
	event_data << endl;
	event_data << eve.end_date_month;
	event_data << endl;
	event_data << eve.end_date_year;
	event_data << endl;
	event_data << eve.start_time;
	event_data << endl;
	event_data << eve.start_time_min;
	event_data << endl;
	event_data << eve.end_time;
	event_data << endl;
	event_data << eve.end_time_min;
	event_data << endl;
	event_data << eve.M;
	event_data << endl;
	event_data << eve.done;
	event_data << endl;
	event_data.close();
}

//Update event function
bool User::update_event(string name) {
	events.clear();
	vec.clear();
	ifstream open_event;
	open_event.open("upcoming_events.txt");
	
	//check if there are events or not
	if (!open_event) {
		cout << "\t\t\t\tThere are no events yet!!" << endl;
		return false;
	}
	load_data();
	open_event.close();
	int indicator;
	string s1, s2, s3, s4, s5, s6, s7, s8, start_time_s, end_time_s;
	int choice;
	bool found = false;
	
	// get time now
	time_t t = std::time(0);
	tm* now = std::localtime(&t);
	int year = now->tm_year + 1900;
	int day = now->tm_mday;
	int month = (now->tm_mon + 1);

	for (int i = 0; i < events.size(); i++)
	{
		if (events[i].name.compare(name) == 0) {
			found = true;
		wrong:cout << "\t\t\t\tEnter the attribute number you want to update: " << endl;
			cout << "\t\t\t\t1- Event name\n";
			cout << "\t\t\t\t2- Event date and time\n";
			cout << "\t\t\t\t3- Event place\n";
			cout << "\t\t\t\t4- Change the case of event to done event\n";
			cout << "\t\t\t\tChoice: ";
			cin >> indicator;
			cout << endl;
			
			switch (indicator) {
			//to updaate event name
			case 1:
			label1:cout << "\t\t\t\tEnter event name: ";
				getline(cin, events[i].name);
				getline(cin, events[i].name);
				for (int i = 0; i < events.size(); i++)
				{
					if (events[i].name.compare(name) == 0) {
						cout << "\t\t\t\tThis event name already exists\n";
						goto label1;
					}
				}
				break;
			
			//to update Event date and time
			case 2:
			l1:
			label2:cout << "\t\t\t\tEnter event start date:" << endl;
				cout << "\t\t\t\tday: ";
				while (cin >> events[i].start_date_day && (events[i].start_date_day < 1 || events[i].start_date_day >31)) {
					cout << endl;
					cout << "\t\t\t\tRange is [1-31]" << endl;
					cout << "\t\t\t\tday: ";
				}

				cout << "\t\t\t\tmonth: ";
				while (cin >> events[i].start_date_month && (events[i].start_date_month < 1 || events[i].start_date_month > 12)) {
					cout << endl;
					cout << "\t\t\t\tRange is [1-12]" << endl;
					cout << "\t\t\t\tmonth: ";
				}

				if ((events[i].start_date_month < month) || ((events[i].start_date_day <= day) && (events[i].start_date_month == month))) {
					cout << "\n\t\t\t\tPlease enter coming date\n";
					goto l1;
				}
				
				cout << "\t\t\t\tyear: ";
				while (cin >> events[i].start_date_year && (events[i].start_date_year > 2022 || events[i].start_date_year < 2022)) {
					cout << endl;
					cout << "\t\t\t\tYear should be 2022" << endl;
					cout << "\t\t\t\tyear: ";
				}
				cout << endl;

			l4:cout << "\t\t\t\tEnter event end date:" << endl;
				cout << "\t\t\t\tday: ";
				while (cin >> events[i].end_date_day && (events[i].end_date_day < 1 || events[i].end_date_day >31)) {
					cout << endl;
					cout << "\t\t\t\tRange is [1-31]" << endl;
					cout << "\t\t\t\tday: ";
				}

				cout << "\t\t\t\tmonth: ";
				while (cin >> events[i].end_date_month && (events[i].end_date_month < 1 || events[i].end_date_month > 12)) {
					cout << endl;
					cout << "\t\t\t\tRange is [1-12]" << endl;
					cout << "\t\t\t\tmonth: ";
				}
				if ((events[i].end_date_month < month) || (events[i].end_date_day <= day) && (events[i].end_date_month == month)) {
					cout << "\n\t\t\t\t Please enter coming date\n";
					goto l4;
				}

				cout << "\t\t\t\tyear: ";
				while (cin >> events[i].end_date_year && (events[i].end_date_year > 2022 || events[i].end_date_year < 2022)) {
					cout << endl;
					cout << "\t\t\t\tYear should be 2022" << endl;
					cout << "\t\t\t\tyear: ";
				}

				if ((events[i].end_date_day == events[i].start_date_day && events[i].end_date_month == events[i].start_date_month) || (events[i].end_date_day < events[i].start_date_day && events[i].end_date_month == events[i].start_date_month) || (events[i].end_date_month < events[i].start_date_month)) {
					cout << "\n\t\t\t\tEnd date is before start date or the event length is less than one day!!";
					cout << endl;
					goto l4;
				}
				cout << endl;

				t:cout << "\t\t\t\tEnter event start time (Hours): ";
				while (cin >> events[i].start_time && (events[i].start_time > 12 || events[i].start_time < 1)) {
					cout << "\t\t\t\tRange is[1-12] ";
					cout << endl;
					cout << "\t\t\t\tEnter event start time (Hours): ";
				}
				cout << endl;

				cout << "\t\t\t\tEnter event start time (Minutes): ";
				while (cin >> events[i].start_time_min && (events[i].start_time_min > 59 || events[i].start_time_min < 0)) {
					cout << "\t\t\t\tRange is[0-59] ";
					cout << endl;
					cout << "\t\t\t\tEnter event start time (Minutes): ";
				}
				cout << endl;

				cout << "\t\t\t\tEnter event end time (Hours): ";
				while (cin >> events[i].end_time && (events[i].end_time > 12 || events[i].end_time < 1)) {
					cout << "\t\t\t\tRange is[1-12] ";
					cout << endl;
					cout << "\t\t\t\tEnter event end time (Hours): ";
				}
				cout << endl;

				cout << "\t\t\t\tEnter event end time (Minutes): ";
				cin >> events[i].end_time_min;
				while (cin >> events[i].end_time_min && (events[i].end_time_min > 59 || events[i].end_time_min < 0)) {
					cout << "\t\t\t\tRange is[0-59] ";
					cout << endl;
					cout << "\t\t\t\tEnter event end time (Minutes): ";
				}
				cout << endl;

			yet2:cout << "\n\t\t\t\tEnter PM or AM: ";
				cin >> events[i].M;
				transform(events[i].M.begin(), events[i].M.end(), events[i].M.begin(), ::toupper);
				if (events[i].M == "PM" || events[i].M == "AM")
					goto yet;
				else
					goto yet2;
			yet:cout << endl;
				if (events[i].start_time != 12 && (events[i].start_time > events[i].end_time)) {
					cout << "\t\t\t\tstart time should be before end time\n\n";
					goto t;
				}
				
				//load events from file to intesection vector
				for (int i = 0; i < events.size(); i++)
				{
					s1 = fix(events[i].start_date_year);
					s2 = fix(events[i].start_date_month);
					s3 = fix(events[i].start_date_day);
					s4 = fix(events[i].start_time);
					start_time_s = s1 + s2 + s3 + s4;
					s5 = fix(events[i].end_date_year);
					s6 = fix(events[i].end_date_month);
					s7 = fix(events[i].end_date_day);
					s8 = fix(events[i].end_time);
					end_time_s = s5 + s6 + s7 + s8;
					intersect(start_time_s, end_time_s);
				}
				
				//to check the intersection
				s1 = fix(events[i].start_date_year);
				s2 = fix(events[i].start_date_month);
				s3 = fix(events[i].start_date_day);
				s4 = fix(events[i].start_time);
				start_time_s = s1 + s2 + s3 + s4;
				s5 = fix(events[i].end_date_year);
				s6 = fix(events[i].end_date_month);
				s7 = fix(events[i].end_date_day);
				s8 = fix(events[i].end_time);
				end_time_s = s5 + s6 + s7 + s8;
				mp[start_time_s] = 1;
				mp[end_time_s] = 0;
				if (intersect(start_time_s, end_time_s))
				{
					for (int j = 0; j < vec.size(); j++)
					{
						if (vec[j] == start_time_s || vec[j] == end_time_s)
						{
							vec.erase(vec.begin() + j);
							j -= 1;
						}
					}
					cout << "\t\t\t\tThere is an intersect!!" << endl;
					goto label2;
				}
				break;
				
			//to update event place
			case 3:
				cout << "\t\t\t\tEnter event palce: ";
				getline(cin, events[i].place);
				getline(cin, events[i].place);
				break;

			case 4:
				label_done:cout << "\t\t\t\tEnter 1 to change the event case to done: ";
				cin >> choice;
				if (choice == 1) {
					events[i].done = true;
					delete_event(events[i].name,true,"u");
				}
				else {
					cout << "\t\t\t\tThis choice is invalid!\n";
					goto label_done;
				}
				break;

			default:
				cout << "\t\t\t\tThis choice is invalid!\n";
				goto wrong;
			}
		}
	}
	if (name == "") {
		return true;
	}
		
	if (!found) {
		cout << "\t\t\t\tThere is no event with this name to update\n\n";
	}
	update_file(events);
	return found;
}

//this function to update events in the file
void User::update_file(vector<Event> update) {
	ofstream updated_events("upcoming_events.txt", ios::out | ios::trunc);
	updated_events.close();
	for (int i = 0; i < update.size(); i++)
	{
		insert_file(update[i]);
	}
}

//Delete event function
bool User::delete_event(string name, bool is_done,string delete_or_update) {
	events.clear();
	done_events.clear();
	ifstream open_event;
	open_event.open("upcoming_events.txt");
	
	//check if there are events or not
	if (!open_event) {
		cout << "\n\t\t\t\tThere are no events yet!!" << endl;
		return false;
	}
	open_event.close();
	load_data();
	
	bool flag = false;

	for (int i = 0; i < events.size(); i++)
	{
		
		if (events[i].name.compare(name) == 0) {
			if (delete_or_update == "d") {
				string is_done1;
			aga:cout << "\n\t\t\t\tIs this event done? [Yes/No]: ";
				cin >> is_done1;
				cout << endl;
				if (is_done1 == "yes" || is_done1 == "Yes") {
					is_done = true;
				}
				else if (is_done1 == "no" || is_done1 == "No") {
					is_done = false;
				}
				else {
					cout << "This choice is invalid!\n";
					goto aga;
				}
				cout << "\n\t\t\t\tYour event is being deleted";
				for (int i = 0; i < 6; i++)
				{
					cout << ".";
					this_thread::sleep_for(chrono::milliseconds(400));
				}
				cout << "\n\t\t\t\t\t\t\t\t\t\t\t-:Your event is successfully deleted:-\n\n";
			}
			
			flag = true;
			if (is_done) {
				done_events.push_back(events[i]);
				events.erase(events.begin() + i);
			}
			else {
				events.erase(events.begin() + i);
			}
		}
	}
	
	if (name == "") {
		return true;
	}
	
	if (!flag) {
		cout << "\n\t\t\t\tThere is no event with this name to delete\n\n";
	}
	delete_file(events);
	insert_done_events(done_events);
	return flag;
}

//this function to delete events from the file
void User::delete_file(vector<Event> deleted) {
	ofstream updated_events("upcoming_events.txt", ios::out | ios::trunc);
	updated_events.close();
	for (int i = 0; i < deleted.size(); i++)
	{
		insert_file(deleted[i]);
	}
}

//this functions to display events ordered by start date and reminder time
bool User::display_in_order() {
	bool flag = false;
	ifstream display_event;
	display_event.open("upcoming_events.txt");
	if (!display_event) {
		return flag;
	}
	vector <Event> displayed_events;
	displayed_events.clear();
	vec_disp.clear();
	vec_disp2.clear();
	string name;
	string place;
	string s1, s2, s3, s4, s5, s6, s7, s8, start_time_s, end_time_s;
	string M;
	int start_date_day;
	int start_date_month;
	int start_date_year;
	int end_date_day;
	int end_date_month;
	int end_date_year;
	int start_time;
	int end_time;
	int start_time_min;
	int end_time_min;
	bool done;

	//load events from the file to the vector displayed_events
	getline(display_event, name);
	getline(display_event, place);
	display_event >> start_date_day;
	display_event >> start_date_month;
	display_event >> start_date_year;
	display_event >> end_date_day;
	display_event >> end_date_month;
	display_event >> end_date_year;
	display_event >> start_time;
	display_event >> start_time_min;
	display_event >> end_time;
	display_event >> end_time_min;
	getline(display_event, M);
	getline(display_event, M);
	display_event >> done;
	while (!display_event.eof())
	{
		Event eve(name, start_date_day, start_date_month, start_date_year, end_date_day, end_date_month, end_date_year, place, start_time, end_time, start_time_min, end_time_min, done, M);
		displayed_events.push_back(eve);
		getline(display_event >> ws, name);
		getline(display_event, place);
		display_event >> start_date_day;
		display_event >> start_date_month;
		display_event >> start_date_year;
		display_event >> end_date_day;
		display_event >> end_date_month;
		display_event >> end_date_year;
		display_event >> start_time;
		display_event >> start_time_min;
		display_event >> end_time;
		display_event >> end_time_min;
		getline(display_event >> ws, M);
		display_event >> done;
	}
	display_event.close();
	
	//load events from the file to the intersection vector
	for (int i = 0; i < displayed_events.size(); i++)
	{
		s1 = fix(displayed_events[i].start_date_year);
		s2 = fix(displayed_events[i].start_date_month);
		s3 = fix(displayed_events[i].start_date_day);
		s4 = fix(displayed_events[i].start_time);
		start_time_s = s1 + s2 + s3 + s4;
		s5 = fix(displayed_events[i].end_date_year);
		s6 = fix(displayed_events[i].end_date_month);
		s7 = fix(displayed_events[i].end_date_day);
		s8 = fix(displayed_events[i].end_time);
		end_time_s = s5 + s6 + s7 + s8;
		to_order(start_time_s, end_time_s, displayed_events[i].name);
	}
	
	//to display events
	int it = 0;
	for (int i = 0; i < vec_disp.size(); i += 2)
	{
		for (int j = 0; j < vec_disp2.size(); j+=2)
		{
			if (vec_disp2[j].first == vec_disp[i] && vec_disp2[j+1].first == vec_disp[i+1]) {
				for (int k = 0; k < displayed_events.size(); k++)
				{
					if (displayed_events[k].name.compare(vec_disp2[j].second) == 0) {
						flag = true;
						displayed_events[k].reminder_time(displayed_events[k].start_time, displayed_events[k].start_time_min, displayed_events[k].M);
						displayed_events[k].reminder_date(displayed_events[k].start_date_month, displayed_events[k].start_date_day);
						cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t  -: Event" << it + 1 << " :-" << endl << endl;
						cout << "\t\t\t\t\t\tName: " << displayed_events[k].name << endl;
						cout << "\t\t\t\t\t\tPlace: " << displayed_events[k].place << endl;
						cout << "\t\t\t\t\t\tStart Date: " << displayed_events[k].start_date_day << "/" << displayed_events[k].start_date_month << "/" << displayed_events[k].start_date_year << endl;
						cout << "\t\t\t\t\t\tEnd Date: " << displayed_events[k].end_date_day << "/" << displayed_events[k].end_date_month << "/" << displayed_events[k].end_date_year << endl;
						cout << "\t\t\t\t\t\tStart Time: " << displayed_events[k].start_time << ":" << displayed_events[k].start_time_min << endl;
						cout << "\t\t\t\t\t\tEnd Time: " << displayed_events[k].end_time << ":" << displayed_events[k].end_time_min << endl;
						cout << "\t\t\t\t\t\tReminder Time: " << displayed_events[k].r.month_count << " months, " << displayed_events[k].r.day_count << " days, " << displayed_events[k].r.hour_count << " hours, " << displayed_events[k].r.minute_count << " minutes" << endl;
						cout << "\t\t\t\t\t\t-->===================================================<-----" << endl << endl;
						it++;
					}
					
				}
			}
		}
	}
	return flag;
}

//to display done events
void User::display_done_events() {
	ifstream displayed_done;
	displayed_done.open("done_events.txt");
	
	//check if there are done events in the file or not
	if (!displayed_done) {
		cout << endl;
		cout << "\t\t\t\tNo done events yet!!\n";
		return;
	}
	string name;
	string place;
	string M;
	int start_date_day;
	int start_date_month;
	int start_date_year;
	int end_date_day;
	int end_date_month;
	int end_date_year;
	int start_time;
	int end_time;
	int start_time_min;
	int end_time_min;
	bool done;

	//load done events from the file to display them
	getline(displayed_done, name);
	getline(displayed_done, place);
	displayed_done >> start_date_day;
	displayed_done >> start_date_month;
	displayed_done >> start_date_year;
	displayed_done >> end_date_day;
	displayed_done >> end_date_month;
	displayed_done >> end_date_year;
	displayed_done >> start_time;
	displayed_done >> start_time_min;
	displayed_done >> end_time;
	displayed_done >> end_time_min;
	getline(displayed_done, M);
	getline(displayed_done, M);
	displayed_done >> done;
	int it = 0;
	while (!displayed_done.eof())
	{
		cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\t  -: Event" << it + 1 << " :-" << endl << endl;
		cout << "\t\t\t\t\t\tName: " << name << endl;
		cout << "\t\t\t\t\t\tPlace: " << place << endl;
		cout << "\t\t\t\t\t\tStart Date: " << start_date_day << "/" << start_date_month << "/" << start_date_year << endl;
		cout << "\t\t\t\t\t\tEnd Date: " <<end_date_day << "/" << end_date_month << "/" << end_date_year << endl;
		cout << "\t\t\t\t\t\tDone: |Yes|" << endl;
		cout << "\t\t\t\t\t\t-->===================================================<-----" << endl << endl;
		it++;
		getline(displayed_done >> ws, name);
		getline(displayed_done, place);
		displayed_done >> start_date_day;
		displayed_done >> start_date_month;
		displayed_done >> start_date_year;
		displayed_done >> end_date_day;
		displayed_done >> end_date_month;
		displayed_done >> end_date_year;
		displayed_done >> start_time;
		displayed_done >> start_time_min;
		displayed_done >> end_time;
		displayed_done >> end_time_min;
		getline(displayed_done >> ws, M);
		displayed_done >> done;
	}
	displayed_done.close();
}

//to insert done events in the file
void User::insert_done_events(vector <Event> done_eve) {
	if (done_eve.empty()) {
		return;
	}
	
	else {
		ofstream done_data;
		done_data.open("done_events.txt", ios::app);
		for (int i = 0; i < done_eve.size(); i++)
		{
			done_data << done_eve[i].name;
			done_data << endl;
			done_data << done_eve[i].place;
			done_data << endl;
			done_data << done_eve[i].start_date_day;
			done_data << endl;
			done_data << done_eve[i].start_date_month;
			done_data << endl;
			done_data << done_eve[i].start_date_year;
			done_data << endl;
			done_data << done_eve[i].end_date_day;
			done_data << endl;
			done_data << done_eve[i].end_date_month;
			done_data << endl;
			done_data << done_eve[i].end_date_year;
			done_data << endl;
			done_data << done_eve[i].start_time;
			done_data << endl;
			done_data << done_eve[i].start_time_min;
			done_data << endl;
			done_data << done_eve[i].end_time;
			done_data << endl;
			done_data << done_eve[i].end_time_min;
			done_data << endl;
			done_data << done_eve[i].M;
			done_data << endl;
			done_data << done_eve[i].done;
			done_data << endl;
		}
		done_data.close();
	}
}
User::~User() {};
