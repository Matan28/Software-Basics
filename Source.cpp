#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream> // file streaming
#include <limits> 
#include <time.h> // for date 


using namespace std;

// Declaration function
void menu();
int log_in(int authorization);//logs in for student & manager alike .
void student_profile(int id);// menu for studnt
void manager_profile(int id); // menu for manager
void print_my_event(int id);//prints all events by ID .
void new_event(int id); // add new event to file 
int pending_events(int id,string supervisor_manager); // print all pending event for this namager and ask if he wants to chanage 
void change_event(int event_number, string supervisor_manager); // chanage event by event number because this number is unique
void print_all_events();//prints all events .
bool print_by_event_number(int Event_number, string super);//prints the event (gets event number) .
void back_to_student_profile(int id); // for back student profile
void back_to_manager_profile(int id ); // for back manage profile
int get_set_event_number(int choose, int current = 0); // to get current event number from file send choose=0 to add +1 to event number send choose=1, current = current event number(the number of last event)  
void print_closed_events(string supervisor_manager); // print events are status done
int print_pending_events(string supervisor_manager);// prints all pending and in progress events .of supervisor
bool is_event_exist(int id, string subject_event, string supervisor_event, string description_event); //check if event exist to this user
void analytics_pending_events_by_supervisor(int id);
void analytics_all_events_by_supervisor(int id);
void reports();
string replace_comma_to_point(string str); // if the user enter , so replace this in .
void analytics_menu(int id);
void back_to_analytics_menu(int id);
string lower_string(string str);

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
	system("Color 2");
	menu();
	return 0;
}

void menu()
{
	int user_type, id, back;
	bool is_log_in = true;

	system("cls");
	cout << "Welcome to SCE" << endl << endl;
	cout << "Choose a number: " << endl;
	cout << "1 - student" << endl << "2 - manager" << endl << "3 - EXIT" << endl;
	cout << endl << "-----------------------------------" << endl << "Enter your choose: ";
	cin >> user_type;

	system("cls");
	do
	{
		system("cls");
		switch (user_type)
		{
		case 1: // student 
		{
			id = log_in(1);
			if (id == -1)
			{
				is_log_in = false;
				cout << "------------------------------" << endl <<
					"Sorry!!" << endl << "Your login information is incorrect!! " << endl << "Please try again" << endl;
				cout << "-----------------------------" << endl << "Enter 3 - for back to menu or anything number for try again: ";
				cin >> back;

				if (back == 3)
					menu();
			}
			else
				student_profile(id);

			break;
		}
		case 2: // manager
		{
			id = log_in(2);
			if (id == -1)
			{
				system("cls");
				is_log_in = false;
				cout << "------------------------------" << endl << "------------------------------" << endl <<
					"Sorry!!" << endl << "Your login information is incorrect!! " << endl << "Please try again" << endl;
				cout << "-----------------------------" << endl << "Enter 3 - for back to menu or anything number for try again: ";
				cin >> back;

				if (back == 3)
					menu();
			}

			else
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
    string ID, Password,tempID, tempPassword,tempAuthorization;
    ifstream StudentsDBFile;
    StudentsDBFile.open("StudentsDB.csv");//StudentsDB.csv location

    if(StudentsDBFile.fail()){
        cerr<<"error copying file to inFile"<<endl;
		StudentsDBFile.close();
        exit(1);
    }
    cout << "Enter id: "<<endl;
    cin >> ID;
    cout << "Enter Password: "<<endl;
    cin >> Password;

	StudentsDBFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// skips a line
    
	while(StudentsDBFile.good())
	{
		getline(StudentsDBFile,tempID,',');

        if(tempID == ID)
		{
			getline(StudentsDBFile, tempPassword, ',');
			getline(StudentsDBFile, tempAuthorization, ',');

            if(tempPassword==Password && authorization == stoi(tempAuthorization))
                return stoi(ID);
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

	cout << "Student profile!" << endl<<endl;
	cout << "choose a number:" << endl;
	cout << "1 - show my event" << endl << "2 - new event" << endl << "3 - back to menu" << endl;
	cout << endl << "-----------------------------------" << endl << "Enter your choice: ";
	cin >> choose;

	switch (choose)
	{
	case 1:
	{
		print_my_event(id);
		back_to_student_profile(id);
		break;
	}
	case 2:
	{
		new_event(id);
		back_to_student_profile(id);
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
void print_my_event(int ID) {
	system("cls");
	int tempID = 0, count_all_events = get_set_event_number(0) - 1;
	string date_evenet, Event_Number, Subject, Event_Description, Status, Supervisor, Priority, Creator_name, Creator_ID,remarks;
	ifstream eventsDB;
	eventsDB.open("eventDB.csv");
	if (eventsDB.fail()) {
		cerr << "error copying file to inFile" << endl;
		exit(1);
	}
	eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	for(int i=0;i<count_all_events;i++)
	{
		getline(eventsDB, date_evenet, ',');
		getline(eventsDB, Event_Number, ',');
		getline(eventsDB, Subject, ',');
		getline(eventsDB, Event_Description, ',');
		getline(eventsDB, Status, ',');
		getline(eventsDB, Supervisor, ',');
		getline(eventsDB, Priority, ',');
		getline(eventsDB, Creator_name, ',');
		getline(eventsDB, Creator_ID,',');
		tempID = stoi(Creator_ID);
		getline(eventsDB, remarks);

		if (ID == tempID) 
		{
			cout << "Date: " << date_evenet << endl << "Eventer number: " << Event_Number << endl<<"Subject: " << Subject << endl
				<< "Event description: " << Event_Description << endl << "Status: " << Status << endl << "Supervisor: " <<
				Supervisor << endl << "Priority: " << Priority << endl << "Creator name: " << Creator_name << endl
				<< "Creator ID: " << Creator_ID << endl<<"Remarks: "<<remarks<<endl;
			cout << "-----------------------------------------------------------" << endl;
		}
	}
	cout << endl;
} //for student

// handle in manager profile
void manager_profile(int id)
{
	int choose,event_number;
	string temp, temp_id;
	string supervisor_manager;
	ifstream StudentsDBFile;
	StudentsDBFile.open("StudentsDB.csv");
	if (StudentsDBFile.fail())
	{
		cerr << "error copying file to inFile" << endl;
		StudentsDBFile.close();
		exit(1);
	}
	
	StudentsDBFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// skips a first line

	while (StudentsDBFile.good())
	{
		getline(StudentsDBFile, temp_id, ',');

		if (stoi(temp_id) == id)
		{
			getline(StudentsDBFile, temp, ',');
			getline(StudentsDBFile, temp, ',');
			getline(StudentsDBFile, temp, ',');
			getline(StudentsDBFile, temp);

			supervisor_manager = get_supervisor_string(supervisor(stoi(temp)));
			break;
		}
		StudentsDBFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// skips a first line
	}
	StudentsDBFile.close();

	system("cls");
	cout << "Profile manager" << endl << endl;
	cout << "choose a number:" << endl;
	cout << "1 - pending events" << endl << "2 - closed events" << endl << "3 - all events" << endl << "4 - reports" << endl << "5 - new event" << endl << "6 - back to menu" << endl;
	cout << endl << "-----------------------------------" << endl << "Enter your choice: ";
	cin >> choose;

	switch (choose)
	{
	case 1:
	{
		event_number = pending_events(id,supervisor_manager); //handle pending events
		
		if (event_number != -1)
			change_event(event_number, supervisor_manager);
		else
			cout << "Sorry!!" << endl << "You don't have any closed event" << endl;

		back_to_manager_profile(id);
		break;
	}
	case 2:
	{
		print_closed_events(supervisor_manager);
		back_to_manager_profile(id);
		break;
	}
	case 3:
	{
		system("cls");
		cout << "--------------------------------------" << endl<< "             All events" << endl << "--------------------------------------" << endl << endl;

		cout << "choose a number:" << endl;
		cout << "1 - print all events" << endl << "2 - analytics" << endl << "3 - back to manager profile" << endl;
		cout << endl << "-----------------------------------" << endl << "Enter your choice: ";
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			system("cls");
			print_all_events(); // print all events
			back_to_manager_profile(id);
			break;
		}
		case 2:
		{
			system("cls");
			analytics_menu(id);
			back_to_manager_profile(id);
			break;
		}
		case 3:
		{
			manager_profile(id);
			break;
		}

		}
	
		case 4:
		{
			system("cls"); // clean screen
			reports();
			back_to_manager_profile(id);
			break;
		}
		case 5:
		{
			new_event(id);
			back_to_manager_profile(id);
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
	}
bool print_by_event_number(int Event_number,string super)
{
	bool is_exist = false;
	int tempEventnumber = 0;
	string date1, Event_Number, Subject, Event_Description, Status, Supervisor, Priority, Creator_name, Creator_ID;
	ifstream eventsDB;
	eventsDB.open("eventDB.csv");
	if (eventsDB.fail()) {
		cerr << "error copying file to inFile" << endl;
		exit(1);
	}
	eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (eventsDB.good()) {
		getline(eventsDB, date1, ',');
		getline(eventsDB, Event_Number, ',');
		getline(eventsDB, Subject, ',');
		getline(eventsDB, Event_Description, ',');
		getline(eventsDB, Status, ',');
		getline(eventsDB, Supervisor, ',');
		getline(eventsDB, Priority, ',');
		getline(eventsDB, Creator_name, ',');
		getline(eventsDB, Creator_ID);
		tempEventnumber = atoi(Event_Number.c_str());
		if (Event_number == tempEventnumber && Supervisor == super) // also check if this event belongs to this supervisor
		{
			cout << "Date: " << date1 << endl << "Eventer number: " << Event_number <<endl<< "Subject: " << Subject << endl
				<< "Event description: " << Event_Description << endl << "Status: " << Status << endl << "Supervisor: " <<
				Supervisor << endl << "Priority: " << Priority << endl << "Creator name: " << Creator_name << endl
				<< "Creator ID: " << Creator_ID << endl;
			cout << "-----------------------------------------------------------" << endl;
			is_exist = true;
			break;
		}
	}
	eventsDB.close();
	return is_exist;
}
void new_event(int id)// add new event ->working!
{
	system("cls");
	int  temp = 1;
	int event_number = get_set_event_number(0); // read form file 
	string temp_id, event_description, full_name, subject,super;
	status status_ = In_process;
	priority pr;
	supervisor sup;
	ifstream StudentsDBFile;
	ofstream event_DBFile;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	char time_buffer[80];
	strftime(time_buffer, 80, "%d/%m/%Y %R",ltm);
	
	StudentsDBFile.open("StudentsDB.csv");
	if (StudentsDBFile.fail())
	{
		cerr << "error copying file to inFile" << endl;
		StudentsDBFile.close();
		exit(1);
	}

	StudentsDBFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// skips a first line

	while (StudentsDBFile.good())
	{
		getline(StudentsDBFile, temp_id, ',');

		if (stoi(temp_id) == id)
		{
			getline(StudentsDBFile, full_name, ',');
			getline(StudentsDBFile, full_name, ',');
			getline(StudentsDBFile, full_name, ',');
			StudentsDBFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// skips a first line
			break;
		}
		StudentsDBFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// skips a first line
	}
	StudentsDBFile.close();
	
	cout <<  "----------------------------------------" << endl << "\t\tNew event" << endl << "----------------------------------------" << endl<<endl;
	cout << "Enter a subject: ";
	getchar();
	getline(cin, subject, '\n');
	
	cout << "----------------------------------------";
	cout <<endl<< "Enter a event description: ";
	getline(cin,event_description,'\n');
	cout << "----------------------------------------" <<endl;
	cout << "Choose priority: " << endl;
	cout << endl << "Enter 0 - high"<<endl<<"Enter 1 - low"<<endl<<endl<<"Enter your choose: ";
	cin >> temp;
	pr = priority(temp);
	cout << "----------------------------------------";
	cout << endl << "Choose supervisor:" << endl << endl << "Enter 0 - Securing" << endl << "Enter 1 - Cleaning" << endl
		<< "Enter 2 - Dean" << endl << "Enter 3 - Maintenance" << endl << "Enter 4 - Students Association" << endl << endl << "Enter your choose: ";
	cin >> temp;
	sup =  supervisor(temp);
	super = get_supervisor_string(sup);

	if (!is_event_exist(id,subject, super, event_description))
	{
		event_DBFile.open("eventDB.csv", fstream::in | fstream::out | fstream::app);

		if (event_DBFile.fail())
		{
			cerr << "error copying file to inFile" << endl;
			exit(1);
		}

		//////->>> replace , to .
		subject = replace_comma_to_point(subject);
		event_description = replace_comma_to_point(event_description);

		//////->>> write to file!!
		event_DBFile << time_buffer << "," << event_number << "," << subject << "," << event_description << "," << get_status_string(status_) << "," <<
			super << "," << get_priority_string(pr) << "," << full_name << "," << id << "," << " " << endl;

		system("cls");
		cout << "Thanks for the report!" << endl << "The event received in the system" << endl << "Your event number is: " << event_number << endl;
		get_set_event_number(1, event_number);
	}
	else
	{
		system("cls");
		cout << "Sorry!!!" << endl << "You've already opened an event about it.." << endl;
	}

	event_DBFile.close();
}

int pending_events(int id ,string supervisor_manager) // return -1 if this manager has not pending events
{
	system("cls");
	int choose, event_num = -1, count_pending_events;
	cout << "------------------------------------------------" << endl << "\tPending events for your supervisor" << endl
		<< "------------------------------------------------"<<endl;

	count_pending_events = print_pending_events(supervisor_manager);

	if (count_pending_events != 0)
	{
		cout << endl << "-----------------------------------" << endl << "Choose a number: " << endl
			<< "1 - choose event number for change" << endl << "2 - back to your profile manager" << endl
			<< "-----------------------------------" << endl;
		cout << "Your choose is: ";
		cin >> choose;

		switch (choose)
		{
		case 1:
		{
			cout << endl << "-----------------------------------" << endl << "Enter event number: ";
			cin >> event_num;
			break;
		}
		case 2:
		{
			manager_profile(id);
			break;
		}
		default:
			break;
		}
	}
	else
		return event_num = -1;

	return event_num;
}

void change_event(int event_number, string supervisor_manager)
{
	system("cls");
	cout << "----------------------------------" << endl << "\tChange event"<<endl << "----------------------------------" << endl<<endl;
	ifstream eventsDB;
	ofstream write_eventsDB;
	int temp, count_event_number = get_set_event_number(0); // for count all event +1 for title DB
	string* array_events = new string[count_event_number];
	
	
	priority pr;
	status st;
	string priority_new, status_new, remarks,temp_string;
	string event_date, event_num, event_subject, event_description, event_supervistor, event_id, event_name, event_status, event_priority, event_remarks;

	if (print_by_event_number(event_number, supervisor_manager)) // the event number for this manager is exist
	{
		cout << "----------------------------------" << endl << "\tEnter your chanages" << endl << "----------------------------------" << endl;
		cout << endl << "Priority:" << endl << "Enter 0 - high" << endl << "Enter 1 - low" << endl << endl << "Enter your choose: ";
		cin >> temp;
		pr = priority(temp);
		cout << endl << "Status: " << endl << "Enter 0 - Done" << endl << "Enter 1 - In treatment" << endl << endl << "Enter your choose: ";
		cin >> temp;
		st = status(temp);
		cout << endl << "Enter your remarks for this event: ";
		getchar();
		getline(cin, remarks);

		remarks = replace_comma_to_point(remarks); // replace if user enter , to .
		priority_new = get_priority_string(pr);
		status_new = get_status_string(st);

		eventsDB.open("eventDB.csv"); // to read
		if (eventsDB.fail())
		{
			cerr << "error copying file to inFile" << endl;
			exit(1);
		}

		for (int i = 0; i < count_event_number; i++)
		{
			getline(eventsDB, event_date, ',');
			getline(eventsDB, event_num, ',');
			getline(eventsDB, event_subject, ',');
			getline(eventsDB, event_description, ',');
			getline(eventsDB, event_status, ',');
			getline(eventsDB, event_supervistor, ',');
			getline(eventsDB, event_priority, ',');
			getline(eventsDB, event_name, ',');
			getline(eventsDB, event_id, ',');
			getline(eventsDB, event_remarks);

			if (i == event_number)
				array_events[i] = event_date + ',' + event_num + ',' + event_subject + ',' + event_description + ','
				+ status_new + ',' + event_supervistor + ',' + priority_new + ',' + event_name + ',' + event_id + ',' + remarks + '\n';
			else
				array_events[i] = event_date + ',' + event_num + ',' + event_subject + ',' + event_description + ','
				+ event_status + ',' + event_supervistor + ',' + event_priority + ',' + event_name + ',' + event_id + ',' + event_remarks + '\n';
		}

		eventsDB.close();

		write_eventsDB.open("eventDB.csv", ios::trunc); // to write new
		if (eventsDB.fail())
		{
			cerr << "error copying file to inFile" << endl;
			exit(1);
		}

		for (int i = 0; i < count_event_number; i++)
			write_eventsDB << array_events[i];

		write_eventsDB.close();
	}
	else
		cout << "The event number you entered is incorrect!!! " << endl;
}

void print_closed_events(string supervisor_manager) // ->> working!!
{
	system("cls");
    string date1,Event_Number,Subject,Event_Description,Status ,Supervisor ,Priority,Creator_name,Creator_ID,remarks;
    ifstream eventsDB;
	int count_closed_events = 0;
    eventsDB.open("eventDB.csv");
    if(eventsDB.fail()){
        cerr<<"error copying file to inFile"<<endl;
        exit(1);
    }
	cout << "----------------------------------" << endl << "\tClosed events" << endl << "----------------------------------" << endl << endl;
    eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(eventsDB.good())
	{
        getline(eventsDB,date1,',');
        getline(eventsDB,Event_Number,',');
        getline(eventsDB,Subject,',');
        getline(eventsDB,Event_Description,',');
        getline(eventsDB,Status,',');
        getline(eventsDB,Supervisor,',');
        getline(eventsDB,Priority,',');
        getline(eventsDB,Creator_name,',');
		getline(eventsDB, Creator_ID,',');
		getline(eventsDB, remarks);
        if(Status=="Done" && Supervisor== supervisor_manager)
		{
			cout << "Date: " << date1 << endl << "Eventer number: " << Event_Number << endl << "Subject: " << Subject << endl
				<< "Event description: " << Event_Description << endl << "Status: " << Status << endl << "Supervisor: " <<
				Supervisor << endl << "Priority: " << Priority << endl << "Creator name: " << Creator_name << endl
				<< "Creator ID: " << Creator_ID << endl << "Remarks:" << remarks << endl;
			cout << "-----------------------------------------------------------" << endl;
			++count_closed_events;
        }
    }
	eventsDB.close();
	if (count_closed_events == 0)
		cout << "You don't have closed events now!" << endl;

    cout<<endl;
}

void print_all_events() // ->>working!!
{
	system("cls");
    string date1,Event_Number,Subject,Event_Description,Status ,Supervisor ,Priority,Creator_name,Creator_ID, remarks;
    ifstream eventsDB;
	int event_number = get_set_event_number(0)-1; // this is the count of events number 
    eventsDB.open("eventDB.csv");
    if(eventsDB.fail()){
        cerr<<"error copying file to inFile"<<endl;
        exit(1);
    }
	cout << "------------------------------------" << endl << "\t\tAll events" << endl << "------------------------------------" << endl<<endl;
    eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (eventsDB.good() && event_number > 0)
	{
        getline(eventsDB,date1,',');
        getline(eventsDB,Event_Number,',');
        getline(eventsDB,Subject,',');
        getline(eventsDB,Event_Description,',');
        getline(eventsDB,Status,',');
        getline(eventsDB,Supervisor,',');
        getline(eventsDB,Priority,',');
        getline(eventsDB,Creator_name,',');
		getline(eventsDB, Creator_ID,',');
		getline(eventsDB, remarks);

		cout << "Date: " << date1 << endl << "Eventer number: " << Event_Number << endl << "Subject: " << Subject << endl
			<< "Event description: " << Event_Description << endl << "Status: " << Status << endl << "Supervisor: " <<
			Supervisor << endl << "Priority: " << Priority << endl << "Creator name: " << Creator_name << endl
			<< "Creator ID: " << Creator_ID << endl << "Remarks: " << remarks << endl;
		cout << "-----------------------------------------------------------" << endl<<endl;
		--event_number;
    }
    cout<<endl;
	eventsDB.close();
}

int print_pending_events(string supervisor_manager)// prints all pending and in progress events. return the number of pending events because if 0 not print the change
{
    string date1,Event_Number,Subject,Event_Description,Status ,Supervisor ,Priority,Creator_name,Creator_ID, remarks;
    ifstream eventsDB;
	int count_pending_events = 0,count_events = get_set_event_number(0)-1;
    eventsDB.open("eventDB.csv");
    if(eventsDB.fail()){
        cerr<<"error copying file to inFile"<<endl;
        exit(1);
    }
    eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(eventsDB.good() && count_events>0){
        getline(eventsDB,date1,',');
        getline(eventsDB,Event_Number,',');
        getline(eventsDB,Subject,',');
        getline(eventsDB,Event_Description,',');
        getline(eventsDB,Status,',');
        getline(eventsDB,Supervisor,',');
        getline(eventsDB,Priority,',');
        getline(eventsDB,Creator_name,',');
        getline(eventsDB,Creator_ID,',');
		getline(eventsDB, remarks);
        if((Status=="In process" || Status=="In treatment") && Supervisor== supervisor_manager )
		{
			cout << "Date: " << date1 << endl << "Eventer number: " << Event_Number << endl << "Subject: " << Subject << endl
				<< "Event description: " << Event_Description << endl << "Status: " << Status << endl << "Supervisor: " <<
				Supervisor << endl << "Priority: " << Priority << endl << "Creator name: " << Creator_name << endl
				<< "Creator ID: " << Creator_ID << endl << "Remarks: " << remarks << endl;
			cout << "-----------------------------------------------------------" << endl;
			++count_pending_events;
			--count_events;
        }
    }
	eventsDB.close();
	if (count_pending_events == 0)
		cout << "You don't have pending events now!" << endl;
    cout<<endl;
	return count_pending_events;
}

void back_to_student_profile(int id)
{
	cout << endl << "-----------------------------------" << endl;
	cout <<  "Enter for back to student profile";
	cout << endl << "-----------------------------------" << endl;
	getchar();
	getchar();
	student_profile(id);
}

void back_to_manager_profile(int id)
{

	cout << endl << "-----------------------------------" << endl;
	cout <<  "Enter for back to manager profile";
	cout << endl << "-----------------------------------" << endl;
	getchar();
	getchar();
	manager_profile(id);
}

void back_to_analytics_menu(int id)
{
	cout << endl << "-----------------------------------" << endl;
	cout << "Enter for back to analytics menu";
	cout << endl << "-----------------------------------" << endl;
	getchar();
	getchar();
	analytics_menu(id);
}

int get_set_event_number(int choose, int current) // 0- write event number, 1- read event number
{
	ifstream read_evenet_number;
	ofstream write_evenet_number;
	int temp = -1;
	switch (choose)
	{
	case 0://read
	{
		read_evenet_number.open("event_number.txt");
		if (read_evenet_number.good())
			read_evenet_number >> temp;
		else
			exit(1);
		read_evenet_number.close();
		break;
	}
	case 1://write
		write_evenet_number.open("event_number.txt");
		if (write_evenet_number.good())
			write_evenet_number << current + 1;
		else
			exit(1);
	default:
		break;
	}
	return temp;
}

void reports()
{
	int count_events_number = get_set_event_number(0) - 1;
	string the_status_entered, the_priorty_entered, the_supervisor_entered,the_events_number_entered, the_date_entered;
	ifstream event_DBFile;
	string event_date, Event_number,subject;
	string Event_Description,Status, Supervisor, Priority, creator_name,creator_ID, remarks;

	event_DBFile.open("eventDB.csv");
	if (event_DBFile.fail())
	{
		cout << "error while opening the database of the events " << endl;
		exit(2);
	}
	cout << "--------------------------------------" << endl << "\t\tReports" << endl << "--------------------------------------" << endl << endl;
	cout << "Enter the details of the report you searching for"<<endl<<
		"If you don't have the information enter char word" << endl<<endl;
	cout << "Enter the status of the event [Done, In treatment, In process]: " ;
	getchar();
	getline(cin,the_status_entered);
	cout << "Enter the priorty of the event [High, Low]: ";
	cin >> the_priorty_entered;
	cout << "Enter the supervisor of the event [Securing, Cleaning, Dean, Maintenance, Students Association]: ";
	getchar();
	getline(cin, the_supervisor_entered); 
	cout << "Enter the number of the event: ";
	cin >> the_events_number_entered;
	cout << "Enter the date of the event [formt date and time: dd/mm/yyyy 00:00]: ";
	getchar();
	getline(cin, the_date_entered);
	cout << endl << "--------------------------------------" << endl;


	event_DBFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // not include the first line because it's title
	while (event_DBFile.good() && count_events_number>0)
	{
		getline(event_DBFile, event_date, ',');
		getline(event_DBFile, Event_number, ',');
		getline(event_DBFile, subject, ',');
		getline(event_DBFile, Event_Description, ',');
		getline(event_DBFile, Status, ',');
		getline(event_DBFile, Supervisor, ',');
		getline(event_DBFile, Priority, ',');
		getline(event_DBFile, creator_name, ',');
		getline(event_DBFile, creator_ID,',');
		getline(event_DBFile, remarks);
		if (Status == the_status_entered || Supervisor == the_supervisor_entered || Event_number == the_events_number_entered || event_date == the_date_entered || the_priorty_entered == Priority)
		{
			cout << "Date: " << event_date << endl << "Eventer number: " << Event_number << endl << "Subject: " << subject << endl
				<< "Event description: " << Event_Description << endl << "Status: " << Status << endl << "Supervisor: " <<
				Supervisor << endl << "Priority: " << Priority << endl << "Creator name: " << creator_name << endl
				<< "Creator ID: " << creator_ID << endl << "Remarks: " << remarks << endl;
			cout << "-----------------------------------------------------------" << endl;
		}
		--count_events_number;
	}

	event_DBFile.close();
	cout << endl;
}

void analytics_pending_events_by_supervisor(int id)
{
	system("cls");
	double count_securing = 0, count_cleaning = 0, count_maintenance = 0, count_Students_Association = 0, count_dean = 0;
	ifstream eventsDB;
	int count_events = get_set_event_number(0) - 1, count_events_pending =0;
	string event_date, Event_number, subject;
	string Event_Description, Status, Supervisor;

	cout << "-------------------------------------" << endl << "  Analytics pending events by supervisor" << endl << "-------------------------------------" << endl;

	eventsDB.open("eventDB.csv");
	if (eventsDB.fail())
	{
		cout << "error while opening the database of the events " << endl;
		exit(2);
	}
	
	eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // not include the first line because it's title
	
	while (eventsDB.good() && count_events > 0)
	{
		getline(eventsDB, event_date, ',');
		getline(eventsDB, Event_number, ',');
		getline(eventsDB, subject, ',');
		getline(eventsDB, Event_Description, ',');
		getline(eventsDB, Status, ',');
		getline(eventsDB, Supervisor, ',');
		eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 

		if (Status == get_status_string(status::In_process) || Status == get_status_string(status::In_treatment))
		{
			count_events_pending++;

			if (Supervisor == get_supervisor_string(supervisor::Cleaning))
				count_cleaning++;
			else if (Supervisor == get_supervisor_string(supervisor::Dean))
				count_dean++;
			else if (Supervisor == get_supervisor_string(supervisor::Maintenance))
				count_maintenance++;
			else if (Supervisor == get_supervisor_string(supervisor::Securing))
				count_securing++;
			else if (Supervisor == get_supervisor_string(supervisor::Students_Association))
				count_Students_Association++;
		}

		--count_events;
	}
	eventsDB.close();

	cout << "Cleaning: " << (count_cleaning / count_events_pending) * 100 << " %" << endl;
	cout << "Dean: " << (count_dean / count_events_pending) * 100 << " %" << endl;
	cout << "Maintenance: " << (count_maintenance / count_events_pending) * 100 << " %" << endl;
	cout << "Securing: " << (count_securing / count_events_pending) * 100 << " %" << endl;
	cout << "Students association: " << (count_Students_Association / count_events_pending) * 100 << " %" << endl;

	back_to_analytics_menu(id);
}

void analytics_all_events_by_supervisor(int id)
{
	system("cls");
	double count_securing = 0, count_cleaning = 0, count_maintenance = 0, count_Students_Association = 0, count_dean = 0;
	ifstream eventsDB;
	int count_events = get_set_event_number(0) - 1,counter=0;
	string event_date, Event_number, subject;
	string Event_Description, Status, Supervisor;

	cout << "-------------------------------------" << endl << "  Analytics all events by supervisor" << endl << "-------------------------------------" << endl;

	eventsDB.open("eventDB.csv");
	if (eventsDB.fail())
	{
		cout << "error while opening the database of the events " << endl;
		exit(2);
	}
	eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // not include the first line because it's title
	while (eventsDB.good() && counter<count_events)
	{
		getline(eventsDB, event_date, ',');
		getline(eventsDB, Event_number, ',');
		getline(eventsDB, subject, ',');
		getline(eventsDB, Event_Description, ',');
		getline(eventsDB, Status, ',');
		getline(eventsDB, Supervisor, ',');
		eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 

		if (Supervisor.compare(get_supervisor_string(supervisor::Cleaning)) == 0)
			count_cleaning++;
		else if (Supervisor.compare(get_supervisor_string(supervisor::Dean)) == 0)
			count_dean++;
		else if (Supervisor.compare(get_supervisor_string(supervisor::Maintenance)) == 0)
			count_maintenance++;
		else if (Supervisor.compare(get_supervisor_string(supervisor::Securing)) == 0)
			count_securing++;
		else if (Supervisor.compare(get_supervisor_string(supervisor::Students_Association)) == 0)
			count_Students_Association++;

		++counter;
	}
	eventsDB.close();

	cout << "Cleaning: " << (count_cleaning / count_events) * 100 << " %" << endl;
	cout << "Dean: " <<  (count_dean / count_events) * 100 << " %" << endl;
	cout << "Maintenance: " << (count_maintenance / count_events) * 100 << " %" << endl;
	cout << "Securing: " << (count_securing / count_events) * 100 << " %" << endl;
	cout << "Students association: " << (count_Students_Association / count_events) * 100 << " %" << endl;

	back_to_analytics_menu(id);
}

string replace_comma_to_point(string str)
{
	for (int i = 0; i< (int)str.length(); i++)
	{
		if (str[i] == ',')
			str[i] = '.';
	}

	return str;
}

void analytics_menu(int id)
{
	system("cls");
	int choose;
	cout << "--------------------------------------" << endl << "              Analytics" << endl << "--------------------------------------" << endl << endl;

	cout << "choose a number:" << endl;
	cout <<  "1 - Events By supervisor" << endl <<"2 - Pending Events By Supervisor"<<endl
		<< "2 - back to manager profile" << endl;
	cout << endl << "-----------------------------------" << endl << "Enter your choice: ";
	cin >> choose;

	switch (choose)
	{
	case 1:
	{
		analytics_all_events_by_supervisor(id);
		break;
	}
	case 2:
	{
		analytics_pending_events_by_supervisor(id);
		break;
	}
	case 3:
	{
		manager_profile(id);
		break;
	}
	default:
		break;
	}
}

bool is_event_exist(int id,string subject_event, string supervisor_event, string description_event)
{
	ifstream eventsDB;
	int count_events = get_set_event_number(0) - 1;
	string event_date, Event_number, subject;
	string Event_Description, Status, Supervisor,Priority,name,ID;

	eventsDB.open("eventDB.csv");
	if (eventsDB.fail())
	{
		cout << "error while opening the database of the events " << endl;
		exit(2);
	}
	eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // not include the first line because it's title
	while (eventsDB.good() && count_events > 0)
	{
		getline(eventsDB, event_date, ',');
		getline(eventsDB, Event_number, ',');
		getline(eventsDB, subject, ',');
		getline(eventsDB, Event_Description, ',');
		getline(eventsDB, Status, ',');
		getline(eventsDB, Supervisor, ',');
		getline(eventsDB, Priority, ',');
		getline(eventsDB, name, ',');
		getline(eventsDB, ID, ',');
		eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

		if (id == id && supervisor_event == Supervisor) // if this equal so check the other
		{
			// ignore lowercass or upercass so convert all the lowercass
			subject = lower_string(subject);
			subject_event = lower_string(subject_event);
			Event_Description = lower_string(Event_Description);
			description_event = lower_string(description_event);
			if (subject.compare(subject_event) == 0 &&Event_Description.compare(description_event))
				return true;
		}

		--count_events;
	}
	eventsDB.close();

	return false;
}

string lower_string(string str)
{
	int  length_str = str.length();
	for (int i = 0; i < length_str; i++)
		str[i] = tolower(str[i]);
	return str;
}
