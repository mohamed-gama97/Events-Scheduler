#include<iostream>
#include<fstream>
#include "User.h"
#include "Event.h"
#include <chrono>
#include <thread>
using namespace std;

int main() {
	int choice;
	User user;
	string updated_name;
	string deleted_name;
	bool done;
	int del;
	string is_done;
	string yes;
	system("color fc");
	cout << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t Events Scheduler\n";
	cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
label:cout << "\t\t\t\t\t\t\t\t\t -: Hi this application allows you to add,delete,or update an event :-\n";
	cout << endl;
	cout << "\t\t\t\tplease choose the number of the operation you want to perform:\n";
	cout << "\t\t\t\t1- Add Event:-\n";
	cout << "\t\t\t\t2- Delete Event:-\n";
	cout << "\t\t\t\t3- Update Event:-\n";
	cout << "\t\t\t\t4- Display Upcoming Events:-\n";
	cout << "\t\t\t\t5- Display Done Events:-\n";
	cout << "\t\t\t\t6- Exit:-\n\n";
cho:cout << "\t\t\t\tChoice: ";
	cin >> choice;
	
	switch (choice) {
	//add event choice
	case 1:
		system("cls");
		cout << endl; 
		cout<< "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
		cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t -: Add Event :-";
		add:if(user.add_event()){
			while (true) {
				string yes_or_no;
			yes:cout << "\t\t\t\tDo you want to add another event [Yes/No]: ";
				cin >> yes_or_no;
				transform(yes_or_no.begin(), yes_or_no.end(), yes_or_no.begin(), ::toupper);
				if (yes_or_no == "YES") {
					goto add;
				}
				else if (yes_or_no == "NO") {
						system("cls");
						cout << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
						cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
						goto label;
				}
				else {
					cout << "\t\t\t\tThis choice is invalid!\n";
					goto yes;
				}
			}
		}
		else {
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
			cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
			goto label;
		}
		break;
	
	//delete event choice
	case 2:
		system("cls");
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
		cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t -: Delete Event :-\n\n";
		
		if (!user.delete_event("",false,"d")) {
			z:cout << "\n\t\t\t\tPress 0 to go to main page: ";
			cin >> del;
			if (del != 0) {
				goto z;
			}
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
			cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
			goto label;
		}
	
	del:cout << "\n\t\t\t\tEnter event name you want to delete: ";
		getline(cin, deleted_name);
		getline(cin, deleted_name);
		user.delete_event(deleted_name, false,"d");
			con2:cout << "\t\t\t\tDo you want to continue deleteing? [Yes/No]: ";
			cin>> yes;
			transform(yes.begin(), yes.end(), yes.begin(), ::toupper);
			if (yes == "YES") {
				goto del;
			}
			else if(yes == "NO") {
				system("cls");
				cout << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
				cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
				goto label;
			}
			else{
				cout << "\t\t\t\tThis choice is invalid!\n";
				goto con2;
			}
		break;
	
	//update event choice
	case 3:
		system("cls");
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
		cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t -: Update Event :-\n\n";
		if (!user.update_event("")) {
		zz:cout << "\n\t\t\t\tPress 0 to go to main page: ";
			cin >> del;
			if (del != 0) {
				goto zz;
			}
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
			cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
			goto label;
		}
	up:cout << "\n\t\t\t\tEnter event name you want to update: ";
		getline(cin, updated_name);
		getline(cin, updated_name);
		cout << endl;
		if (!user.update_event(updated_name)) {
			con:cout << "\t\t\t\tDo you want to continue updating? [Yes/No]: ";
			cin >> yes;
			transform(yes.begin(), yes.end(), yes.begin(), ::toupper);
			if (yes == "YES") {
				goto up;
			}
			else if(yes == "NO") {
				system("cls");
				cout << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
				cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
				goto label;
			}
			else {
				cout << "\t\t\t\tThis choice is invalid!\n";
				goto con;
			}
		}
		while (true) {
			string yes_or_no;
			cout << "\n\t\t\t\tYour event is being updated";
			for (int i = 0; i < 6; i++)
			{
				cout << ".";
				this_thread::sleep_for(chrono::milliseconds(300));
			}
			cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t-:Your event is successfully updated:-\n\n";
			ag2:cout << "\t\t\t\tDo you want to update another event [Yes/No]: ";
			cin >> yes_or_no;
			transform(yes.begin(), yes.end(), yes.begin(), ::toupper);
			if (yes_or_no == "YES") {
				goto up;
			}
			else if (yes_or_no == "NO") {
				system("cls");
				cout << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
				cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
				goto label;
			}
			else {
				cout << "\t\t\t\tThis choice is invalid!\n";
				goto ag2;
			}
		}
		break;
	
	//display upcoming events choice
	case 4:
		system("cls");
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
		cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t -: Upcoming Events :-\n\n";
		if (!user.display_in_order()) {
			cout << "\t\t\t\tNo upcoming events yet!!\n";
		}

		p:cout << "\n\t\t\t\tPress 0 to go to main page: ";
		cin >> del;
		if (del != 0) {
			goto p;
		}
		
		else {
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
			cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
			goto label;
		}
		break;
	
	//display done events choice
	case 5:
		system("cls");
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
		cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t -: Done Events :-\n\n";
		user.display_done_events();
		
		pp2:cout << "\n\t\t\t\tPress 0 to go to main page or 1 to clear them: ";
			cin >> del;
			if (del == 1) {
				cout << "\n\t\t\t\tEvents are being deleted";
				for (int i = 0; i < 6; i++)
				{
					cout << ".";
					this_thread::sleep_for(chrono::milliseconds(500));
				}
				remove("done_events.txt");
				system("cls");
				cout << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
				cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
				goto label;
			}
			else if (del == 0) {
				system("cls");
				cout << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tEvents Scheduler\n";
				cout << "\t\t\t\t-----------------------------------------------------**************************************-----------------------------------------------------\n\n";
				goto label;
			}
			else {
				goto pp2;
			}
		break;
	
	//exit choice
	case 6:
		cout << "\t\t\t\t\t\t\t\t\t\t\t-: Thanks for using our application :-\n\n";
		break;
	
	default:
		cout << "\t\t\t\tThis choice is invalid!\n";
		goto cho;
	}

	return 0;
}