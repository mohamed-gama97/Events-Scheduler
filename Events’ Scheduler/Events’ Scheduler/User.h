#pragma once
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<string>
#include"Event.h"
#include<iostream>
using namespace std;

class User
{
private:
	vector<Event> events;//upcoming events
	vector<Event> done_events;//done events
	vector<string>vec;//for intersect function
	unordered_map<string, bool>mp;//for intersect function
	vector<string>vec_disp;//for display in order function
	vector<pair<string, string>>vec_disp2;//for display in order function
public:
	bool intersect(string, string);
	string fix(int);
	void to_order(string, string,string);
	void load_data();
	bool add_event();
	void insert_file(Event);
	bool update_event(string);
	void update_file(vector<Event>);
	bool delete_event(string,bool,string);
	void delete_file(vector<Event>);
	bool display_in_order();
	void display_done_events();
	void insert_done_events(vector<Event>);
	~User();
};

