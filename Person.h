#ifndef PERSON_H
#define PERSON_H
#include<string>
#include <iostream>
using namespace std;

class Person
{
public:
	string name;
	virtual void displayName() = 0;
};

class Student : public Person
{
public:
	Student(string nm) { Person::name = nm; };
	~Student() {};
	virtual void displayName() {cout << "	Student: " << Person::name;};
};

class Teacher : public Person
{
public:
	Teacher(string nm) {Person::name = nm;};
	~Teacher() {};
	virtual void displayName() { cout << "Teacher: " << Person::name; };
};

#endif
