#pragma once
#include <string>
using namespace std;

class User
{ 
	const string login_; //For create a unique login
	string name_;
	string password_;

public:
	User(const string& login, const string& name, const string& password ) : login_(login), name_(name), password_(password) {}

	const string& getLogin() const { return login_; }

	const string& getName() const { return name_; }
	void setName(const string& name) { name_ = name; }

	const string& getPassword() const { return password_; }
	void setPassword(const string& password) { password_ = password; }
};