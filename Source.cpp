#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream> // file streaming
#include <limits> 
#include <time.h> // for date

using namespace std;

void menu();
int log_in(int authorization);
void student_profile(int id);
void manager_profile(int id);
void print_my_event(int id);
void new_event(int id);
int pending_events();
void change_event(int event_number);
void print_closed_events();
void reports();
void print_common_evnets();
void print_all_event();
void print_pending_events_by_supervisor();
void print_events_by_supervisor();
bool is_event_exist(string description_event);

enum status
{
	Done=0
	,In_treatment=1
	,In_process=2 


};

enum priority
{
	High = 0
	, Low = 1
};

enum supervisor
{
	Securing=0
	, Cleaning=1
	, Dean=2
	, Maintenance=3
	, Students_Association=4
};

//enum string
string get_status_string(status st)
{
	switch (st)
	{
	case Done: {return "Done"; break; }
	case In_treatment: {return "In treatment";  break; }
	case In_process: {return "In process"; break; }
	default: break;
	}
	return string();
}
string get_priority_string(priority pr)
{
	switch (pr)
	{
	case High: {return "High"; break; }
	case Low: {return "Low"; break; }
	default:
		break;
	}

	return string();
}

string get_supervisor_string(supervisor sup)
{
	switch (sup)
	{
	case Securing: {return "Securing"; break; }
	case Cleaning: {return "Cleaning"; break; }
	case Dean: {return "Dean"; break; }
	case Maintenance: {return "Maintenance"; break; }
	case Students_Association: {return "Students Association"; break; }

	default:
		break;
	}
	return string();
}

int main()
{
	menu();
	return 0;
}

void menu()
{
	int user_type, id;
	bool is_log_in = true;

	system("cls");
	cout << "Welcome to SCE" << endl;
	cout << "Choose a number: " << endl;
	cout << "1- student" << endl << "2 - manager" << endl<< "3 - EXIT"<<endl;
	cin >> user_type;
	system("cls");
	do
	{
		switch (user_type)
		{
		case 1: // student 
		{
			id = log_in(1);
			if (id == -1)
			{
				is_log_in = false;
				break;
			}
			student_profile(id);

			break;
		}
		case 2: // manager
		{

			id = log_in(2);
			if (id == -1)
			{
				is_log_in = false;
				break;
			}

			manager_profile(id);
			break;
		}
		case 3:
			cout << "Bye Bye...." << endl;
		default:
			exit(1);
			break;
		}
	} while (!is_log_in);

}

int log_in(int authorization) // return ID otherwise return -1
{
    int ID, Password;
    int tempID, tempPassword,tempAuthorization;
    ifstream StudentsDBFile;
    StudentsDBFile.open("StudentsDB.txt");//StudentsDB.txt location
    if(StudentsDBFile.fail()){
        cerr<<"error copying file to inFile"<<endl;
		StudentsDBFile.close();
        exit(1);
    }
    cout << "Enter id: "<<endl;
    cin >> ID;
    cout << "Enter Password: "<<endl;
    cin >> Password;
    while(StudentsDBFile>>tempID){
        if(tempID==ID){
            StudentsDBFile >> tempPassword;
            StudentsDBFile >> tempAuthorization;
            if(tempPassword==Password && authorization-1==tempAuthorization){
                return ID;
            }
        }
        StudentsDBFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// skips a line
    }
	StudentsDBFile.close();
    
    return -1;
}

// handle in student profile
void student_profile(int id)
{
	int choose;
	system("cls");

	cout << "Student profile!" << endl;
	cout << "choose a number:" << endl;
	cout << "1 - show my event" << endl << "2 - new event" << endl << "3 - back to menu" << endl;
	cin >> choose;

	switch (choose)
	{
	case 1:
	{
		print_my_event(id);
		
		cout << endl << "Enter 3 - back to student profile";
		cin >> choose;
		if(choose == 3)
		   student_profile(id);
		break;
	}
	case 2:
	{
		new_event(id);
		cout << endl << "Enter 3 - back to student profile";
		cin >> choose;
		if (choose == 3)
			student_profile(id);
		break;
	}
	case 3:
	{
		menu();
		break;
	}
	default:
		exit(2);
		break;
	}
}

void manager_profile(int id)
{
	int choose, event_number;
	system("cls");

	cout << "Profile manager" << endl;
	cout << "choose a number:" << endl;
	cout << "1- pending events" << endl << "2-closed events" << endl << "3- all event" << endl << "4- reports" << endl<<"5- new event"<<endl << "6 - back to menu" << endl;
	cin >> choose;

	switch (choose)
	{
	case 1:
	{
		event_number = pending_events(); // print all pending event and choose event number for change and return that
		change_event(event_number);
		cout << endl << "Enter 3 - back to student profile";
		cin >> choose;
		if (choose == 3)
			manager_profile(id);
		break;
	}
	case 2:
	{
		print_closed_events();
		cout << endl << "Enter 3 - back to student profile";
		cin >> choose;
		if (choose == 3)
			manager_profile(id);
		break;
	}
	case 3:
	{
		cout << "choose a number:" << endl;
		cout <<"1- show all event"<<endl << "2- common events" << endl << "3- events by supervisor" << endl << "4- pending events by supervisor" << endl<<"5 - back to manager profile"<<endl;
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			system("cls");
			print_all_event();
			cout << endl << "Enter 3 - back to student profile: ";
			cin >> choose;
			if (choose == 3)
				manager_profile(id);
			break;
		}
		case 2:
		{
			system("cls");
			print_common_evnets();
			cout << endl << "Enter 3 - back to student profile: ";
			cin >> choose;
			if (choose == 3)
				manager_profile(id);
			break;
		}
		case 3:
		{
			system("cls");
			print_events_by_supervisor();
			cout << endl << "Enter 3 - back to student profile: ";
			cin >> choose;
			if (choose == 3)
				manager_profile(id);
			break;
		}
		case 4:
		{
			system("cls");
			print_pending_events_by_supervisor();
			cout << endl << "Enter 3 - back to student profile: ";
			cin >> choose;
			if (choose == 3)
				manager_profile(id);
			break;
		}
		case 5:
		{
			
		    manager_profile(id);
			break;
		}
		case 6:
		{
			menu();
			break;
		}
		default:
			exit(2);
			break;
		}
	}
	case 4:
	{
		reports();
		break;
	}
	case 5:
	{
		new_event(id);
		cout << endl << "Enter 3 - back to student profile";
		cin >> choose;
		if (choose == 3)
			student_profile(id);
		break;
	}
	case 6:
	{
		menu();
		break;
	}
	default:
		exit(2);
		break;
	}
}

void print_my_event(int id)
{
}

void new_event(int id)
{
	system("cls");
	int tempID, temp = 1;
	static int event_number = 1;
	string event_description, subject, first_name, last_name;
	status st(In_process);
	priority pr;
	supervisor sup;
	ifstream students_DBFile;
	ofstream event_DBFile;
	//add time!!!
	students_DBFile.open("StudentsDB.txt");//StudentsDB.txt location
	if (students_DBFile.fail()) {
		cerr << "error copying file to inFile" << endl;
		exit(1);
	}
	while (students_DBFile >> tempID)
	{
		if (tempID == id)
		{
			students_DBFile >> temp;
			students_DBFile >> temp;
			students_DBFile >> first_name;
			students_DBFile >> last_name;
		}

		students_DBFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// skips a line
	}
	students_DBFile.close();

	cout << "Enter a subject: " << endl;
	cin >> subject;
	cout << "Enter a event description: " << endl;
	cin >> event_description;
	cout << "choose a number: 0- for high priority or 1 - for low priority: ";
	cin >> temp;
	pr = priority(temp);
	cout << endl << "choose a number: 0 - for Securing, 1- for Cleaning, 2- for Dean, 3- for Maintenance, 4- for Students Association:";
	cin >> temp;
	sup = supervisor(temp);

	if (is_event_exist(event_description))
	{
		event_DBFile.open("eventDB.csv", fstream::in | fstream::out | fstream::app);

		if (event_DBFile.fail())
		{
			cerr << "error copying file to inFile" << endl;
			exit(1);
		}

		//////->>> write to file!!
		// date first!!!!!!->chenage
		event_DBFile << "24/12/2018," << event_number << "," << subject << "," << event_description << "," << get_status_string(st) << ","<<
			get_supervisor_string(sup) <<","<< get_priority_string(pr) << "," << first_name << " " << last_name << "," << id;

		system("cls");
		cout << "Thanks for the report!" << endl << "The event received in the system" << endl << "Your event number is: " << event_number << endl;
		event_number++;
	}
	else
		cout << "Sorry!!!" << endl << "You've already opened an event about it.." << endl;

	event_DBFile.close();
}

int pending_events()
{
	return 0;
}

void change_event(int event_number)
{
}

void print_closed_events()
{
}

void all_event()
{
}

void reports()
{
}

void print_common_evnets()
{
}

void print_all_event()
{
}

void print_pending_events_by_supervisor()
{
}

void print_events_by_supervisor()
{
}

bool is_event_exist(string description_event)
{
	return true;
}









