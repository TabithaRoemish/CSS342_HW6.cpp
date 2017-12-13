//structure.h
// Programmer: Tabitha Roemish
// Date: November 20, 2017
// File Includes: school and element definitions and declarations

#ifndef STRUCTURE_H
#define STRUCTURE_H
#define LOWERLIMIT 5
#define UPPERLIMIT 8
#include <iostream>
#include <string>
#include <list>
#include "Person.h"

using namespace std;

class element
{
public:
	element() : save(false) {};
	Person* pt;
	list<element> lst;
	bool operator<(const element &elm) const { return lst.size() < elm.lst.size(); };
	bool operator==(const element &elm) const { return pt->name == elm.pt->name; };
	bool save;

};
//shool structure consists of a root list of elements that contain "teachers
// and each teacher element contains an element list of students
class school
{ 
public:
	school() : studentsTotal(0), teachersTotal(0) {};
	~school() {};
	void insertTeacher(string nm);
	void insertStudentFor(string teachName, string stuName);
	void insertStudent(string nm);
	
	void removeTeacher(string nm);
	void removeStudent(string nm);
	void printSchoolList();
	void displayTeacherTotals();
	bool findTeacher(string nm, element& pt);
	string findStudentsTeacher(string nm);
	list<element> findStudentsFor(string nm);
	void clearTree();

private:
	list<element> root;
	int studentsTotal;
	int teachersTotal;
	void distributeStudents();
};

// school definitions
void school::printSchoolList()
{
	if (root.size() == 0)
		cout << "Empty List";
	else
	{
		list<element>::iterator it = root.begin();
		while (it != root.end())
		{
			it->pt->displayName();
			cout << ": " << it->lst.size();
			cout << endl;
			if (it->lst.size() != 0)
			{
				list<element>::iterator x = it->lst.begin();
				while (x != it->lst.end())
				{
					x->pt->displayName();
					cout << endl;
					x++;
				}
			}
			it++;
		}
	}
	cout << endl;
}

void school::displayTeacherTotals()
{
	if (root.size() == 0)
		cout << "Empty List";
	else
	{
		list<element>::iterator it = root.begin();
		while (it != root.end())
		{
			it->pt->displayName();
			cout << ": " << it->lst.size();
			cout << endl;
			it++;
		}
	}
	cout << endl;
}

void school::distributeStudents()
{
	if (studentsTotal > 0 && teachersTotal > 1)
	{
		int evenDist = studentsTotal / teachersTotal;
		root.sort();
		list<element>::iterator teachListHead = root.begin();
		list<element>::iterator teachListTail = root.end();
		while (teachListTail->lst.size() < evenDist)
		{
			while (teachListHead != teachListTail)
			{
				if (teachListHead->lst.size() > evenDist)
				{
					list<element>::iterator studentList = teachListHead->lst.begin();
					while (studentList != teachListHead->lst.end())
					{
						if (teachListHead->lst.front().save != true)
						{
							teachListTail->lst.push_front(teachListHead->lst.front());
							teachListHead->lst.pop_front();
							break;
						}
						else
							studentList++;
					}
					teachListHead++;
				}
			}
			root.sort();
		}
	}
}

void school::insertTeacher(string nm)
{
	element * spot = new element; // create the element
	Teacher * teach = new Teacher(nm); // create the teacher
	spot->pt = teach; // assign eleent pointer to new teacher
	root.push_front(*spot); // insert element to root list
	teachersTotal++;

	distributeStudents();
}

void school::insertStudent(string nm)
{
	root.sort();
	root.reverse();
	studentsTotal++;
	//create new element with new student pointer
	element * insert = new element;
	Student * stud = new Student(nm);
	insert->pt = stud;
	
	list<element>::iterator teachListHead = root.begin();
	
		if (root.back().lst.size() < LOWERLIMIT || root.back().lst.size() >= UPPERLIMIT)
		{
			root.back().lst.push_front(*insert);
		}
		else //5-8
		{
			while (teachListHead != root.end())
			{
				if (teachListHead->lst.size() >= LOWERLIMIT && teachListHead->lst.size() < UPPERLIMIT)
				{
					teachListHead->lst.push_front(*insert);
					break;
				}
				else
					teachListHead++;
			}
		}
	
}


bool school::findTeacher(string nm, element& pt)
{
	bool found = false;
	list<element>::iterator teachListHead = root.begin();
	while (teachListHead != root.end())
	{
		if (teachListHead->pt->name == nm)
		{
			found = true;
			pt = *teachListHead;
		}
		teachListHead++;
	}
	return found;
}

list<element> school::findStudentsFor(string nm)
{
	element  teacher;
	
	bool found = findTeacher(nm, teacher);
	list<element> temp;
	if (found)
	{
		temp = teacher.lst;
	}
	return temp;
}

//returns blank string if student not found
string school::findStudentsTeacher(string nm)
{
	string teachername = "";
	list<element>::iterator teachListHead = root.begin();
	while (teachListHead != root.end())
	{
		list<element>::iterator studentList = teachListHead->lst.begin();
		while (studentList != teachListHead->lst.end())
		{
			if (studentList->pt->name == nm)
			{
				teachername = teachListHead->pt->name;
				break;
			}
			studentList++;
		}
		teachListHead++;
	}
	return teachername;
}

void school::insertStudentFor(string teachName, string stuName)
{
	element teacher;
	
	bool found = findTeacher(teachName, teacher);
	if (found)
	{
		element * insert = new element;
		Student * stud = new Student(stuName);
		insert->pt = stud;
		teacher.lst.push_front(*insert);
		teacher.lst.front().save = true;
		distributeStudents();
		studentsTotal++;
	}
	else
		cout << "Teacher not found, Student has not been added to roster";
	
}

void school::removeTeacher(string nm)
{
	element teacher;
	
	bool found = findTeacher(nm, teacher);
	list<element> holder(teacher.lst); // get student list
	root.remove(teacher); // delete teacher from root list
	
	//iterate through holder adding each element with insertstudent
	list<element>::iterator it = holder.begin();
	while (it != holder.end())
	{
		insertStudent(it->pt->name);
		it++;
	}
	teachersTotal--;
}

void school::removeStudent(string nm)
{
	//find student element
	//when found, delete from list
	list<element>::iterator teachListHead = root.begin();
	while (teachListHead != root.end())
	{
		list<element>::iterator studentList = teachListHead->lst.begin();
		while (studentList != teachListHead->lst.end())
		{
			if (studentList->pt->name == nm)
			{
				teachListHead->lst.remove(*studentList);
				break;
			}
			studentList++;
		}
		teachListHead++;
	}
	distributeStudents();
	studentsTotal--;
}

void school::clearTree()
{
	root.clear();
	studentsTotal = 0;
	teachersTotal = 0;
}

#endif
