#include "course.h"
#include "student.h"

//Test cases for course
int main(){
    struct student_id id;
    id.sid_serial = 0001;
    id.sid_year = 2020;
  
    struct course *course1 = course_create(SUBJ_MATH,1000);
    struct course *course2 = course_create(SUBJ_PHYS,1001);
    struct student *student1 = student_create(id, false);
    course_code(course1);
    course_subject(course1);
    course_code(course2);
    course_subject(course2);
    return 0;
}