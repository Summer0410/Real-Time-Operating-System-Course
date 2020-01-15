#include "course.h"

 struct course{
    enum subject subject;
    uint16_t code;
    int refcount;
};

struct course*	course_create(enum subject subject, uint16_t code){
    struct course *new_course;//declare a new variable
    new_course->subject = SUBJ_CHEM;
    new_course->code = 1234;
    new_course->refcount = 1;
    return new_course;   
};



int main(){
    struct course* new_course = course_create(SUBJ_ENGI,1234);
    return 0;
}