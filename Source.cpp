#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream> // file streaming
#include <limits> 
#include <time.h> // for date

using namespace std;

void menu();
int log_in(int authorization);//logs in for student & manager alike .
void student_profile(int id);// menu for studnt
void manager_profile(int id); // menu for manager
void print_my_event(int id);//prints all events by ID .
void new_event(int id); // add new event to file 
int pending_events(string supervisor_manager); // print all pending event for this namager and ask if he wants to chanage 
void change_event(int event_number); // chanage event by event number because this number is unique
void print_all_events();//prints all events .
void print_by_event_number(int Event_number);//prints the event (gets event number) .
void back_to_student_profile(int id); // for back student profile
void back_to_manager_profile(int id ); // for back manage profile
int get_set_event_number(int choose, int current = 0); // to get current event number from file send choose=0 to add +1 to event number send choose=1, current = current event number(the number of last event)  
void print_closed_events(string supervisor_manager);
void print_pending_events(string supervisor_manager);// prints all pending and in progress events .of supervisor

bool is_event_exist(string description_event);
void analys_common_evnets();
void analys_pending_events_by_supervisor();
void analys_all_events_by_supervisor();
void reports();

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
			id = log_in(1);
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
            if(tempPassword==Password && authorization==tempAuthorization){
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
	int tempID = 0;
	string date_evenet, Event_Number, Subject, Event_Description, Status, Supervisor, Priority, Creator_name, Creator_ID;
	ifstream eventsDB;
	eventsDB.open("eventDB.csv");
	if (eventsDB.fail()) {
		cerr << "error copying file to inFile" << endl;
		exit(1);
	}
	eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (eventsDB.good()) {
		getline(eventsDB, date_evenet, ',');
		getline(eventsDB, Event_Number, ',');
		getline(eventsDB, Subject, ',');
		getline(eventsDB, Event_Description, ',');
		getline(eventsDB, Status, ',');
		getline(eventsDB, Supervisor, ',');
		getline(eventsDB, Priority, ',');
		getline(eventsDB, Creator_name, ',');
		getline(eventsDB, Creator_ID);
		tempID = atoi(Creator_ID.c_str());
		if (ID == tempID) 
		{
			cout << "Date: " << date_evenet << endl << "Eventer number: " << Event_Number << endl<<"Subject: " << Subject << endl
				<< "Event description: " << Event_Description << endl << "Status: " << Status << endl << "Supervisor: " <<
				Supervisor << endl << "Priority: " << Priority << endl << "Creator name: " << Creator_name << endl
				<< "Creator ID: " << Creator_ID << endl;
			cout << "-----------------------------------------------------------" << endl;
		}
	}
	cout << endl;
} //for student

// handle in manager profile
void manager_profile(int id)
{
	int choose, event_number, temp_id;
	string supervisor_manager;
	ifstream studentsDB;
	studentsDB.open("StudentsDB.txt");
	if (!studentsDB.good())
		exit(2);

	while (studentsDB >> temp_id) { // to get supervisor
		if (temp_id == id) {
			studentsDB >> temp_id;
			studentsDB >> temp_id;
			studentsDB >> supervisor_manager;
			studentsDB >> supervisor_manager;
			studentsDB >> temp_id;
			studentsDB >> temp_id;
			studentsDB >> supervisor_manager;
		}
		studentsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// skips a line
	}
	studentsDB.close();

	system("cls");
	cout << "Profile manager" << endl << endl;
	cout << "choose a number:" << endl;
	cout << "1- pending events" << endl << "2-closed events" << endl << "3- all event" << endl << "4- reports" << endl << "5- new event" << endl << "6 - back to menu" << endl;
	cout << endl << "-----------------------------------" << endl << "Enter your choice: ";
	cin >> choose;

	switch (choose)
	{
	case 1:
	{
		event_number = pending_events(supervisor_manager); //handle pending events
		change_event(event_number);
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
		cout << "choose a number:" << endl;
		cout << "1 - print all event" << endl << "2 - anount of common events" << endl << "3 - anount of all events by supervisor" << endl << "4 - anount of pending events by supervisor" << endl << "5 - back to manager profile" << endl;
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
			analys_common_evnets();
			back_to_manager_profile(id);
			break;
		}
		case 3:
		{
			system("cls");
			analys_all_events_by_supervisor();
			back_to_manager_profile(id);
			break;
		}
		case 4:
		{
			analys_pending_events_by_supervisor();
			system("cls");
			
			back_to_manager_profile(id);
			break;
		}
		case 5:
		{
			manager_profile(id);
			break;
		}

		}
	case 4:
	{
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
void print_by_event_number(int Event_number)
{
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
		if (Event_number == tempEventnumber)
		{
			cout << "Date: " << date1 << endl << "Eventer number: " << Event_number << "Subject: " << endl << Subject << endl
				<< "Event description: " << Event_Description << endl << "Status: " << Status << endl << "Supervisor: " <<
				Supervisor << endl << "Priority: " << Priority << endl << "Creator name: " << Creator_name << endl
				<< "Creator ID: " << Creator_ID << endl;
			cout << "-----------------------------------------------------------" << endl;
		}
	}
}
void new_event(int id)
{
	system("cls");
	int tempID, temp = 1;
	int event_number = get_set_event_number(0); // read form file 
	string event_description, first_name, last_name, subject;
	status status_ = In_process;
	priority pr;
	supervisor sup;
	ifstream students_DBFile;
	ofstream event_DBFile;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	char time_buffer[80];
	strftime(time_buffer, 80, "%d/%m/%Y-%I:%M",ltm);
	students_DBFile.open("StudentsDB.txt");//StudentsDB.txt location
	if (students_DBFile.fail()) {
		cerr << "error copying file to inFile" << endl;
		exit(2);
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

		students_DBFile.ignore(std::numeric_limits<std::streamsize>::max(),'\n');// skips a line
	}
	students_DBFile.close();
	cout <<  "----------------------------------------" << endl << "\t\tNew event" << endl << "----------------------------------------" << endl<<endl;
	cout << "Enter a subject: ";
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
		event_DBFile << time_buffer << "," << event_number << "," << subject << "," << event_description << "," << get_status_string(status_) << "," <<
			get_supervisor_string(sup) << "," << get_priority_string(pr) << "," << first_name << " " << last_name << "," << id ;

		system("cls");
		cout << "Thanks for the report!" << endl << "The event received in the system" << endl << "Your event number is: " << event_number << endl;
		get_set_event_number(1, event_number);
	}
	else
		cout << "Sorry!!!" << endl << "You've already opened an event about it.." << endl;

	event_DBFile.close();
}
int pending_events(string supervisor_manager)
{
	int event_num;
	print_pending_events(supervisor_manager);

	cout << endl << "-----------------------------------"<<endl << "Enter a event number for change: ";
	cin >> event_num;
	cout << "-----------------------------------" << endl;
	return event_num;
}

void change_event(int event_number)
{
	system("cls");
	print_by_event_number(event_number);
	//write file for chanage!!!
}

void print_closed_events(string supervisor_manager)
{
    string date1,Event_Number,Subject,Event_Description,Status ,Supervisor ,priority,Creator_name,Creator_ID;
    ifstream eventsDB;
    eventsDB.open("eventDB.csv");
    if(eventsDB.fail()){
        cerr<<"error copying file to inFile"<<endl;
        exit(1);
    }
    eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(eventsDB.good()){
        getline(eventsDB,date1,',');
        getline(eventsDB,Event_Number,',');
        getline(eventsDB,Subject,',');
        getline(eventsDB,Event_Description,',');
        getline(eventsDB,Status,',');
        getline(eventsDB,Supervisor,',');
        getline(eventsDB,priority,',');
        getline(eventsDB,Creator_name,',');
        getline(eventsDB,Creator_ID);
        if(Status=="closed" && Supervisor== supervisor_manager){
            cout<<date1<<endl<<"priority: "<<priority<<endl<<"Subject: "<<Subject<<endl<<"supervisor: "<<Supervisor<<endl<<"Status: "<<Status<<endl<<"name: "<<Creator_name<<endl<<"ID: "<<Creator_ID<<endl<<"Event no: "<<Event_Number<<endl<<"Description: "<<Event_Description<<endl;
        }
    }
    cout<<endl;
}

void reports()
{
}

void print_common_evnets_stat()
{
}

void print_all_events()
{
    string date1,Event_Number,Subject,Event_Description,Status ,Supervisor ,priority,Creator_name,Creator_ID;
    ifstream eventsDB;
    eventsDB.open("/Users/adamyahnin/Documents/SoftwareBasics1/SoftwareBasics/events test nonbool/events test nonbool/eventDB.csv");
    if(eventsDB.fail()){
        cerr<<"error copying file to inFile"<<endl;
        exit(1);
    }
    eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(eventsDB.good()){
        getline(eventsDB,date1,',');
        getline(eventsDB,Event_Number,',');
        getline(eventsDB,Subject,',');
        getline(eventsDB,Event_Description,',');
        getline(eventsDB,Status,',');
        getline(eventsDB,Supervisor,',');
        getline(eventsDB,priority,',');
        getline(eventsDB,Creator_name,',');
        getline(eventsDB,Creator_ID);
        cout<<date1<<endl<<"priority: "<<priority<<endl<<"Subject: "<<Subject<<endl<<"supervisor: "<<Supervisor<<endl<<"Status: "<<Status<<endl<<"name: "<<Creator_name<<endl<<"ID: "<<Creator_ID<<endl<<"Event no: "<<Event_Number<<endl<<"Description: "<<Event_Description<<endl;
    }
    cout<<endl;
}

void print_pending_events(string supervisor_manager)// prints all pending and in progress events
{
    string date1,Event_Number,Subject,Event_Description,Status ,Supervisor ,priority,Creator_name,Creator_ID;
    ifstream eventsDB;
    eventsDB.open("eventDB.csv");
    if(eventsDB.fail()){
        cerr<<"error copying file to inFile"<<endl;
        exit(1);
    }
    eventsDB.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(eventsDB.good()){
        getline(eventsDB,date1,',');
        getline(eventsDB,Event_Number,',');
        getline(eventsDB,Subject,',');
        getline(eventsDB,Event_Description,',');
        getline(eventsDB,Status,',');
        getline(eventsDB,Supervisor,',');
        getline(eventsDB,priority,',');
        getline(eventsDB,Creator_name,',');
        getline(eventsDB,Creator_ID);
        if(Status=="pending" || Status=="In treatment" && Supervisor== supervisor_manager){
            cout<<date1<<endl<<"priority: "<<priority<<endl<<"Subject: "<<Subject<<endl<<"supervisor: "<<Supervisor<<endl<<"Status: "<<Status<<endl<<"name: "<<Creator_name<<endl<<"ID: "<<Creator_ID<<endl<<"Event no: "<<Event_Number<<endl<<"Description: "<<Event_Description<<endl;
        }
    }
    cout<<endl;
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
		read_evenet_number.close();
		break;
	}
	case 1://write
		write_evenet_number.open("event_number.txt");
		if (write_evenet_number.good())
			write_evenet_number << current + 1;
	default:
		break;
	}
	return temp;
}

void analys_common_evnets()
{
}

void analys_pending_events_by_supervisor()
{
}

void analys_all_events_by_supervisor()
{
}

bool is_event_exist(string description_event)
{
	return true;
}









