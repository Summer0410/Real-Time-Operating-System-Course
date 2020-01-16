#include "course.h"
#include "student.h"

//Test cases for course
int main(){
    struct course *course = course_create(SUBJ_PHYS,123);
    course_release(course);
    course_refcount(course);
    course_hold(course);
    course_refcount(course);
    return 0;
}