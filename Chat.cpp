#include <iostream>
#include "Chat.h"

/*Start and Menu*/
void Chat::run()
{
	chatRun_ = true;
	cout << "\t\t\t\t\t\t  Welcome to the chat! "<<endl;
 }

void Chat::mainMenu()
{
	currentUser_ = nullptr;
	int oper;

	do
	{
		cout << "\t\t\t\t\t\t  ===== MAIN MENU ===== " << endl;
		cout << "\t\t\t\t\t\t |                     |" << endl;
		cout << "\t\t\t\t\t\t |     1 - Log in      |" << endl;     
		cout << "\t\t\t\t\t\t |     2 - Sign up     |" << endl;
		cout << "\t\t\t\t\t\t |                     |" << endl;
		cout << "\t\t\t\t\t\t |      3 - Quit       |" << endl;
		cout << "\t\t\t\t\t\t |                     |" << endl;
		cout << "\t\t\t\t\t\t  =====================\n\n\n\n" << endl;
		cin >> oper;

		switch (oper)
		{
		case 1:
			login();
			break;
			
		case 2:
			//Verification of login uniqueness
			try
			{
				signUp();
			}
			catch (const exception& exp)
			{
				cout << exp.what() << endl;
			}
			break;

		case 3:
			chatRun_ = false;
			break;

		default:
			cout << "\t ----------------------------- " << endl;
			cout << "\t| Error: Incorrect operation! |" << endl;
			cout << "\t ----------------------------- \n\n" << endl;
			break;
		}
	} while (!currentUser_ && chatRun_);
}

void Chat::userMenu()
{
	int op;

	cout << "\t\t\t\t\t\t Welcome to the chat " << currentUser_->getName() << "!\n" << endl;

	while (currentUser_)
	{
		cout << "\t\t\t\t\t\t ~~~~~~~ USER MENU ~~~~~~~ " << endl;
		cout << "\t\t\t\t\t\t|                         |" << endl;
		cout << "\t\t\t\t\t\t|   1 - View the chat     |" << endl;
		cout << "\t\t\t\t\t\t|   2 - Create message    |" << endl;
		cout << "\t\t\t\t\t\t|   3 - Online Users      |" << endl;
		cout << "\t\t\t\t\t\t|                         |" << endl;
		cout << "\t\t\t\t\t\t|        0 - Exit         |" << endl;
		cout << "\t\t\t\t\t\t|                         |" << endl;
		cout << "\t\t\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~ \n\n\n\n" << endl;

		cin >> op;

		switch (op)
		{
		case 1:
			viewChat();
			break;

		case 2:
			createMessage();
			break;

		case 3:
			onlineUsers();
			break;

		case 0:
			currentUser_ = nullptr;
			break;

		default:
			cout << "\t ----------------------------- " << endl;
			cout << "\t| Error: Incorrect operation! |" << endl;
			cout << "\t ----------------------------- \n\n" << endl;
			break;
		}

	}
}


/*User function*/
void Chat::login()
{
	string login, password;
	int operation;

	do
	{
		cout << "\tEnter your login:\n" << endl;
		cin >> login;
		cout << "\tEnter your password:\n" << endl;
		cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getPassword()))
		{
			currentUser_ = nullptr;

			cout << "\t ------------------------ " << endl;
			cout << "\t| Error: User not found. |" << endl;
			cout << "\t|                        |" << endl;
			cout << "\t|       0 - exit         |" << endl;
			cout << "\t ------------------------ \n\n" << endl;
			cin >> operation;

			if (operation == 0)
			{
				break;
			}
		}
	} while (!currentUser_);
}

void Chat::signUp()
{
	string login, password, name;

	cout << "\tEnter your login:\n" << endl;
	cin >> login;
	cout << "\tEnter your password:\n" << endl;
	cin >> password;
	cout << "\tEnter your name:\n" << endl;
	cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw LoginExcept(); //try{} and catch(){} in the mainMenu()
	}

	User user = User(login, name, password);
	usersRoster_.push_back(user); //Add a new user to the end of the container
	currentUser_ = make_shared<User>(user); //Pointed the new user as the current
}

void Chat::viewChat() const
{
	string from, to;

	cout << "\n CHAT" << endl;

	for (auto& mess : messagesRoster_) //Range-based messages
	{	
		//Message from me
		if ((currentUser_->getLogin() == mess.getFrom()) || (currentUser_->getLogin() == mess.getTo()) || mess.getTo() == "all")
		{
			from = (currentUser_->getLogin() == mess.getFrom()) ? "me" : getUserByLogin(mess.getFrom())->getName();

			if (mess.getTo() == "all")
			{
				to = " all users ";
			}
			else
			{
				to = (currentUser_->getLogin() == mess.getTo()) ? "me" : getUserByLogin(mess.getTo())->getName();
			}
			cout << "|_______________________________________________________________________________________________________________________" << endl;
			cout << "| From: " << from << "\n| To: " << to << "\n|" << endl;
			cout << "| Message:\n| " << mess.getText() << endl;
		}
	}
	cout << "!_______________________________________________________________________________________________________________________\n\n\n" << endl;
}

void Chat::onlineUsers() const
{
	cout << "\t\t\t\t\t\t ******** ONLINE ********" << endl;

	for (auto& user : usersRoster_) //Range-based users
	{
		cout << "\n\t\t\t\t\t\t> " << user.getName();

		//Pointer to the current user
		if (currentUser_->getLogin() == user.getLogin()) 
		{
			cout << " [ Me ] " << endl;
		}
	}

	cout << "\n\t\t\t\t\t\t *************************\n\n\n" << endl;
}

void Chat::createMessage()
{
	string to, text;

	cout << "\n\tTo(name or 'all'):" << endl;
	cin >> to;
	cout << "\n\tMessage:" << endl;
	cin.ignore();
	getline(cin, text); //Ignoring spaces to avoid an error

	if (!(to == "all" || getUserByName(to)))
	{	
		cout << "\t -------------------------------------- " << endl;
		cout << "\t| Error send message: can't find user. | " << endl;
		cout << "\t -------------------------------------- \n\n" << endl;
		return;
	}

	//Add a new message to the end of the container
	if (to == "all")
	{
		messagesRoster_.push_back(Message{ currentUser_->getLogin(), "all", text });
	}
	else
	{
		messagesRoster_.push_back(Message{ currentUser_->getLogin(), getUserByName(to)->getLogin(), text });
	}
}

//Definition login counter
shared_ptr<User> Chat::getUserByLogin(const string& login) const
{
	for (auto& user : usersRoster_)
	{
		if (login == user.getLogin())
		{
			return make_shared<User>(user);
		}
	}

	return nullptr;
}

//Definition name counter
shared_ptr<User> Chat::getUserByName(const string& name) const
{
	for (auto& user : usersRoster_)
	{
		if (name == user.getName())
		{
			return make_shared<User>(user);
		}
	}

	return nullptr;
}