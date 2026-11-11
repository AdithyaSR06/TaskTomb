#include <iostream>
#include <string>
#include <vector>

using namespace std;

//class for goal
//stores all the information linked to each individual goal
class Goal {
private:
	string description;
	bool completed;
	int priority;
public:
	Goal(string desc, bool comp, int prio)
		: description(desc), completed(comp), priority(prio)
	{

	}; //constructor

	string getdescription() const {
		return description;
	}

	bool getcompleted() const {
		return completed;
	}

	int getpriority() const {
		return priority;
	}

	void setcompleted(bool status) {
		completed = status;
	}
};


//function to display the title screen
void displayTitle() {
	cout << "===================" << endl;
	cout << "  TASKTOMB  " << endl;
	cout << "===================" << endl;
	cout << " Your Personal Task Manager" << endl;
}

//function to display all the goals stored in the vector
//uses a const reference so the original vector isn't copied or changed
void displayGoals(const vector<Goal>& GoalList) {
	//loop through the vector and display each goal and its information
	for (size_t i = 0; i < GoalList.size(); ++i) {
		cout << "\nGoal: " << GoalList[i].getdescription() << "\n";
		cout << "\nCompleted: " << boolalpha << GoalList[i].getcompleted() << "\n";
		cout << "\nPriority: " << GoalList[i].getpriority() << "\n";
	}
}

//function to display the username
void displayUsername(string username) {
	cout << "\n your username is : " << username << endl;
}

//function to return the total number of goals currently stored in the vector
int getGoalCount(const vector<Goal>& GoalList) {
	return GoalList.size();
}

//function to check whether the user has entered a valid integer
//passes the variable by reference so the function can store the input in it
bool getIntegerInput(int& number) {
	//attempt to read an integer from the user
	cin >> number;

	//check whether the input extraction has failed
	if (cin.fail()) {
		//reset the error state of cin so it can be used again
		cin.clear();

		//discard the invalid input from the input buffer
		cin.ignore(1000, '\n');

		cout << "Invalid Input.Please enter a number";

		//return false to tell the calling code that the input failed
		return false;
	}

	//return true if the integer was successfully read
	return true;
}

//main function
int main() {
	//initialise the vector goal list
	vector<Goal> GoalList;

	//display the title screen
	displayTitle();

	//name input
	string username;
	cout << "\nWhat is your name?\n";

	//getline allows the user to enter a name containing spaces
	getline(cin, username);

	cout << "\nWelcome to TaskTomb " << username << "!\n";

	//goal setting
	//loop twice to allow the user to enter their first two goals
	for (int i = 0; i < 2; ++i) {
		
		string description; //create temporary string to hold user input
		 
		cout << "\nWhat would you like to work on today?\n";
		
		getline(cin, description); //put description into string

		Goal goal(description, false, 1); //create goal objext using constructor

		GoalList.push_back(goal); //store the object in the vector
	}

	//selection statement
	//ask the user whether they want to start working on their goal
	string goalselection;
	cout << "\n Would you like to start working on your goal?(Yes or No)";
	cin >> goalselection;

	//display a different message depending on the user's answer
	if (goalselection == "Yes")
		cout << "\nGood luck! Time to get things done.\n";
	else if (goalselection == "No")
		cout << "\nNo worries. Your goal is saved for later\n";
	else
		cout << "\nplease enter either 'Yes' or 'No'\n";

	//main menu
	int choice = 0;

	//keep displaying the menu until the user chooses option 2
	while (choice != 2) {
		cout << "\n===================\n";
		cout << "\n1.View goals\n";
		cout << "\n2.Exit\n";
		cout << "\n3.View Username\n";
		cout << "\n4.View Goal Count\n";
		cout << "\n5.Change Goal status\n";
		cout << "\n6.Add a new goal\n";
		cout << "\n===================\n";

		cout << "\nEnter a choice(1 , 2 , 3 , 4 , 5 or 6)\n";

		//check the menu input is a valid integer before continuing
		//if input fails, skip the rest of this loop iteration and show the menu again
		if (getIntegerInput(choice) == false) {
			continue;
		}

		//use a switch statement to run the option selected by the user
		switch (choice) {
		case 1: // used to print out the contents of the vector 
			displayGoals(GoalList);
			break;

		case 2:
			//break out of the switch; the while condition will now end the menu loop
			break;

		case 3:
			//call the function to display the username
			displayUsername(username);
			break;

		case 4:
		{
			//call the function to get the number of goals stored in the vector
			int goalcountdisplay = getGoalCount(GoalList);

			//display the returned goal count
			cout << "\n You currently have " << goalcountdisplay << " goals saved.\n";
			break;
		}

		case 5:
		{
			//this part of the code checks the status of a selected goal
			int selectedGoal = 0;

			//display all goals with numbers so the user can select one
			for (size_t i = 0; i < GoalList.size(); ++i) {
				//add 1 because vector indexes start at 0 but user selections start at 1
				cout << i + 1 << "\nGoal: " << GoalList[i].getdescription() << "\n";
			}

			//check that the selected number is within the range of goals in the vector
			while (selectedGoal < 1 || selectedGoal > GoalList.size()) {
				cout << "\nPlease select a goal(eg 1 ,2 etc)";


				//check that the selected goal number is a valid integer
				if (getIntegerInput(selectedGoal) == false) {
					continue;

				}
				if (selectedGoal < 1 || selectedGoal > GoalList.size()) {
					cout << "\nnumber is outside valid range";
				}


			}



			//subtract 1 to convert the user's selection into the correct vector index
			int goalIndex = selectedGoal - 1;

			string goalStatus;

			//keep asking until the user enters either Yes or No
			do {
				cout << "Have you completed the goal(enter 'Yes' or 'No'?";
				cin >> goalStatus;

			} while (goalStatus != "Yes" && goalStatus != "No");

			//update the completed status of the selected goal depending on the answer
			if (goalStatus == "Yes") {
				GoalList[goalIndex].setcompleted(true);
			}
			else if (goalStatus == "No") {
				GoalList[goalIndex].setcompleted(false);
			}
		
        break;
		}

		case 6:
		{


			//remove the leftover newline from the previous cin input
			cin.ignore();

			string description;

			cout << "Please enter a new goal";

			//get the full goal description, including spaces
			getline(cin, description);

			//set the default values for the new goal
			Goal newgoal(description, false, 1);

			//add the new goal to the existing vector
			GoalList.push_back(newgoal);

			break;
		}

		default:
			//display an error if the user enters a number that isn't one of the menu options
			cout << "\nenter either 1 ,2 , 3 , 4 or 5 or 6\n ";
			break;
		}
	}
}
