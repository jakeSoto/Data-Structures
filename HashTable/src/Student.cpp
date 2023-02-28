#include "Student.h"

template <typename Comparable>
Student<Comparable>::Student()
{
}

template <typename Comparable>
string Student<Comparable>::getFirstName()
{
    return fname;
}

template <typename Comparable>
string Student<Comparable>::getLastName()
{
    return lname;
}

template <typename Comparable>
string Student<Comparable>::getDepartment()
{
    return department;
}

template <typename Comparable>
string Student<Comparable>::getGPA()
{
    return gpa;
}

template <typename Comparable>
void Student<Comparable>::setFirstName(Comparable name)
{
    fname = name;
}

template <typename Comparable>
void Student<Comparable>::setLastName(Comparable name)
{
    lname = name;
}
template <typename Comparable>
void Student<Comparable>::setDepartment(Comparable dept)
{
    department = dept;
}

template <typename Comparable>
void Student<Comparable>::setGPA(Comparable grade)
{
    gpa = grade;
}