#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream> // file streaming
#include <limits> 
using namespace std;

void menu();
int log_in(int i);
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

int main()
{
	menu();
	return 0;
}

void menu()
{
	int user_type, id;
	bool is_log_in = true;
	cout << "Welcome to SCE" << endl;

	cout << "Choose a number: " << endl;
	cout << "1- student" << endl << "2 - manager" << endl;
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
		default:
			exit(1);
			break;
		}
	} while (!is_log_in);

}

int log_in(int i) // return ID otherwise return -1
{
    int ID, Password;
    int tempID, tempPassword;
    ifstream inFile;
    inFile.open("/Users/adamyahnin/Documents/projects/test basics/test basics/StudentsDB.txt");//StudentsDB.txt location
    if(inFile.fail()){
        cerr<<"error copying file to inFile"<<endl;
        exit(1);
    }
    cout << "Enter id: "<<endl;
    cin >> ID;
    cout << "Enter Password";
    cin >>Password;
    while(inFile>>tempID){
        if(tempID==ID){
            inFile >> tempPassword;
            if(tempPassword==Password){
                return ID;
            }
        }
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// skips a line
    }
    
    
    return -1;
}

// handle in student profile
void student_profile(int id)
{
	int choose;
	system("cls");

	cout << "Profile student" << endl;
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
			cout << endl << "Enter 3 - back to student profile";
			cin >> choose;
			if (choose == 3)
				manager_profile(id);
			break;
		}
		case 2:
		{
			system("cls");
			print_common_evnets();
			cout << endl << "Enter 3 - back to student profile";
			cin >> choose;
			if (choose == 3)
				manager_profile(id);
			break;
		}
		case 3:
		{
			system("cls");
			print_events_by_supervisor();
			cout << endl << "Enter 3 - back to student profile";
			cin >> choose;
			if (choose == 3)
				manager_profile(id);
			break;
		}
		case 4:
		{
			system("cls");
			print_pending_events_by_supervisor();
			cout << endl << "Enter 3 - back to student profile";
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







