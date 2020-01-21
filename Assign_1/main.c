#include "course.h"
#include "student.h"

//Test cases for course
int main(){
    struct student_id id;
    id.sid_serial = 0001;
    id.sid_year = 2020;
  
    struct course *course1 = course_create(SUBJ_ECE,1020);
    struct course *course2 = course_create(SUBJ_PHYS,1001);
    struct course *course3 = course_create(SUBJ_CIV,1001);
    struct course *course4 = course_create(SUBJ_PHYS,1000);
    struct student *student1 = student_create(id, false);
    student_take(student1,course1,99);
    student_take(student1,course2,89);
    student_take(student1,course3,50);
    student_take(student1,course4,49);
    double result = student_passed_average(student1);
    printf("%.2f\n", result);
    return 0;
}