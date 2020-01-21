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
    student_take(student1,course1,89);
    student_take(student1,course1,50);
    student_take(student1,course1,50);
    student_free(student1);
    course_refcount(course1);
    return 0;
}