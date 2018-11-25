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
void student_profile(int id);
void manager_profile(int id);
void print_my_event(int id);//prints all events by ID .
void new_event(int id);
int pending_events();
void change_event(int event_number);
void print_closed_events(); //prints all closed events .
void reports();
void print_common_evnets_stat();
void print_all_events();//prints all events .
void print_pending_events();// prints all pending and in progress events .
void print_by_event_number(int Event_number);//prints the event (gets event number) .
void print_events_by_supervisor();
bool is_event_exist(string description_event);
void back_to_student_profile(int id);
void back_to_manager_profile(int id );


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
	cout << "Welcome to SCE" << endl<<endl;
	cout << "Choose a number: " << endl;
	cout << "1- student" << endl << "2 - manager" << endl<< "3 - EXIT"<<endl;
	cout << endl << "-----------------------------------" << endl << "Enter your choice: ";
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

void manager_profile(int id)
{
	int choose, event_number;
	system("cls");

	cout << "Profile manager" << endl<<endl;
	cout << "choose a number:" << endl;
	cout << "1- pending events" << endl << "2-closed events" << endl << "3- all event" << endl << "4- reports" << endl<<"5- new event"<<endl << "6 - back to menu" << endl;
	cout << endl << "-----------------------------------" << endl << "Enter your choice: ";
	cin >> choose;

	switch (choose)
	{
	case 1:
	{
		event_number = pending_events(); // print all pending event and choose event number for change and return that
		change_event(event_number);
		back_to_manager_profile(id);
		break;
	}
	case 2:
	{
		print_closed_events();
		back_to_manager_profile(id);
		break;
	}
	case 3:
	{
		cout << "choose a number:" << endl;
		cout <<"1- show all event"<<endl << "2- common events" << endl << "3- events by supervisor" << endl << "4- pending events by supervisor" << "5-print events by event number"<<endl<<"6 - back to manager profile"<<endl;
		cout << endl << "-----------------------------------" << endl << "Enter your choice: ";
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			system("cls");
			print_all_events();
			back_to_manager_profile(id);
			break;
		}
		case 2:
		{
			system("cls");
			print_common_evnets_stat();
			back_to_manager_profile(id);
			break;
		}
		case 3:
		{
			system("cls");
			print_events_by_supervisor();
			back_to_manager_profile(id);
			break;
		}
		case 4:
		{
			system("cls");
			print_pending_events();
			back_to_manager_profile(id);
			break;
		}
        case 5:
        {
            system("cls");
            int eventNo;
            cout<<"Enter the Event number: ";
            cin>>eventNo;
            cout<<endl;
            print_by_event_number(eventNo);
            back_to_manager_profile(id);
            
        }
		case 6:
		{
		    manager_profile(id);
			break;
		}
		case 7:
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
void print_by_event_number(int Event_number){
    int tempEventnumber=0;
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
        getline(eventsDB,Creator_ID,',');
        tempEventnumber=stoi(Event_Number);
        if(Event_number==tempEventnumber){
            cout<<date1<<endl<<"priority: "<<priority<<endl<<"Subject: "<<Subject<<endl<<"supervisor: "<<Supervisor<<endl<<"Status: "<<Status<<endl<<"name: "<<Creator_name<<endl<<"ID: "<<Creator_ID<<endl<<"Event no: "<<Event_Number<<endl<<"Description: "<<Event_Description<<endl;
            return;
        }
    }
    cout<<endl;
}
void print_my_event(int ID){
    int tempID=0;
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
        getline(eventsDB,Creator_ID,',');
        tempID=stoi(Creator_ID);
        if(ID==tempID){
            cout<<date1<<endl<<"priority: "<<priority<<endl<<"Subject: "<<Subject<<endl<<"supervisor: "<<Supervisor<<endl<<"Status: "<<Status<<endl<<"name: "<<Creator_name<<endl<<"ID: "<<Creator_ID<<endl<<"Event no: "<<Event_Number<<endl<<"Description: "<<Event_Description<<endl;
        }
    }
    cout<<endl;
}
void new_event(int id)
{
	system("cls");
	int tempID, temp = 1;
	static int event_number = 4; // add file 
	string event_description, first_name, last_name, subject;
	status st(In_process);
	priority pr;
	supervisor sup;
	ifstream students_DBFile;
	ofstream event_DBFile;
	//add time!!!
	time_t now = time(0);
	tm *ltm = localtime(&now);
	char time_buffer[80];
	strftime(time_buffer, 80, "%d/%m/%Y-%I:%M",ltm);
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

		students_DBFile.ignore(std::numeric_limits<std::streamsize>::max(),'\n');// skips a line
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
		event_DBFile << time_buffer <<"," << event_number << "," << subject << "," << event_description << "," << get_status_string(st) << ","<<
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
	int event_num;
	// print all event is not done

	cout << endl << "-----------------------------------"<<endl << "Enter a event number for change: ";
	cin >> event_num;
	cout << "-----------------------------------" << endl;
	return event_num;
}

void change_event(int event_number)
{
}

void print_closed_events()
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
        getline(eventsDB,Creator_ID,',');
        if(Status=="closed"){
            cout<<date1<<endl<<"priority: "<<priority<<endl<<"Subject: "<<Subject<<endl<<"supervisor: "<<Supervisor<<endl<<"Status: "<<Status<<endl<<"name: "<<Creator_name<<endl<<"ID: "<<Creator_ID<<endl<<"Event no: "<<Event_Number<<endl<<"Description: "<<Event_Description<<endl;
        }
    }
    cout<<endl;
}

void all_event()
{
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
        getline(eventsDB,Creator_ID,',');
        cout<<date1<<endl<<"priority: "<<priority<<endl<<"Subject: "<<Subject<<endl<<"supervisor: "<<Supervisor<<endl<<"Status: "<<Status<<endl<<"name: "<<Creator_name<<endl<<"ID: "<<Creator_ID<<endl<<"Event no: "<<Event_Number<<endl<<"Description: "<<Event_Description<<endl;
    }
    cout<<endl;
}

void print_pending_events()// prints all pending and in progress events
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
        getline(eventsDB,Creator_ID,',');
        if(Status=="pending" || Status=="In treatment"){
            cout<<date1<<endl<<"priority: "<<priority<<endl<<"Subject: "<<Subject<<endl<<"supervisor: "<<Supervisor<<endl<<"Status: "<<Status<<endl<<"name: "<<Creator_name<<endl<<"ID: "<<Creator_ID<<endl<<"Event no: "<<Event_Number<<endl<<"Description: "<<Event_Description<<endl;
        }
    }
    cout<<endl;
}


void print_events_by_supervisor()
{
}

bool is_event_exist(string description_event)
{
	return true;
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









