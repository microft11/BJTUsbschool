#ifndef _123456_2_H_
#define _123456_2_H_

#include<iostream>
using namespace std;

namespace N123456
{
	struct STUDENT
    {
	    long int number;
	    char name[20];
	    char major[20];
    	double score;
    };
	
	extern STUDENT * gStu;
    extern int count;
    extern int available;
    void add_student(STUDENT & stu);
    void display();
}

#endif



