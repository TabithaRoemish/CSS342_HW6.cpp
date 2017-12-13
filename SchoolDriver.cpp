//SchoolDriver.cpp
//	Programmer: Tabitha Roemish
//	Date: November 20, 2017
#include <iostream>
#include "structure.h"
#include "Person.h"
#include <sstream>
using namespace std;

int main()
{
	school skiSchool;
	// First Example, 5 teachers, 5 students
	cout << "5 Teachers, 5 students: " << endl;
	skiSchool.insertTeacher("TeacherA");
	skiSchool.insertTeacher("TeacherB");
	skiSchool.insertTeacher("TeacherC");
	skiSchool.insertTeacher("TeacherD");
	skiSchool.insertTeacher("TeacherE");
	for (int i = 1; i <= 5; i++)
	{
		ostringstream ss;
		ss << i;
		skiSchool.insertStudent(ss.str());
	}
	skiSchool.displayTeacherTotals();
	skiSchool.clearTree();

	// Second Example: 3 Teachers, 20 students
	skiSchool.insertTeacher("TeacherA");
	skiSchool.insertTeacher("TeacherB");
	skiSchool.insertTeacher("TeacherC");
	cout << "3 Teachers, 20 students: " << endl;
	for (int i = 1; i <= 20; i++)
	{
		ostringstream ss;
		ss << i;
		skiSchool.insertStudent(ss.str());
	}
	skiSchool.displayTeacherTotals(); 
	skiSchool.clearTree();
	
	//Third Example: 3 Teachers, 28 students
	skiSchool.insertTeacher("TeacherA");
	skiSchool.insertTeacher("TeacherB");
	skiSchool.insertTeacher("TeacherC");
	cout << "3 Teachers, 28 students: " << endl;
	for (int i = 1; i <= 28; i++)
	{
		ostringstream ss;
		ss << i;
		skiSchool.insertStudent(ss.str());
	}
	skiSchool.displayTeacherTotals();
	skiSchool.clearTree();

	//Demonstration
		// 3 teachers, 19 students
	cout << "3 Teachers, 19 students: " << endl;
	skiSchool.insertTeacher("Cathy");
	skiSchool.insertTeacher("Rebecca");
	skiSchool.insertTeacher("David");
	char name = 'A';
	for (int i = 1; i <= 19; i++)
	{
		string str(1, name);
		skiSchool.insertStudent(str);
		name++;
	}
	skiSchool.printSchoolList();
		
	// remove teacher
	cout << "Remove 'Cathy': " << endl;
	skiSchool.removeTeacher("Cathy");
	skiSchool.printSchoolList();

		//try insert
	cout << "Try to insert student for Cathy: " << endl;
	skiSchool.insertStudentFor("Cathy", "New Student");
	
	// test find students teacher
	cout << endl;
	cout << "Test find teacher for a given student, 'D': " << endl;
	string tempName = skiSchool.findStudentsTeacher("D");
	cout << tempName;

	cin.get();
	return 0;
}