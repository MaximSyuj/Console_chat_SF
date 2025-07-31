#pragma once
#include "Message.h"
#include <memory>
#include <exception>
#include <vector>

//Exception if the login is busy
struct LoginExcept:public exception
{
	const char* what() const noexcept override 
	{ 
		return 
		"\t ----------------------\n\t| Error: Login exists. |\n\t ---------------------- \n\n"; 
	}
};

class Chat
{
	bool chatRun_ = false;
	vector<User> usersRoster_;
	vector<Message> messagesRoster_;
	shared_ptr<User> currentUser_ = nullptr;

	void login();
	void signUp();
	void viewChat() const;
	void onlineUsers() const;
	void createMessage();
	
	vector<User>& getAllUsers() { return usersRoster_; } //User container
	vector<Message>& getAllMessages() { return messagesRoster_; } //Message container

	shared_ptr<User> getUserByLogin(const string& login) const; //Description login counter
	shared_ptr<User> getUserByName(const string& name) const; //Description name counter

public:
	bool chatRun() const { return chatRun_; }

	void run();
	void mainMenu();
	void userMenu();
	shared_ptr<User> getCurrentUser() const { return currentUser_; } //Tracking current user
};