#include "course.h"
#include "stdio.h"

 struct course{
    enum subject subject;
    uint16_t code;
    uint8_t refcount;
};

struct course*	course_create(enum subject subject, uint16_t code){
    struct course new_course;
    new_course.code = code;
    new_course.subject  = subject;
    new_course.refcount = 1;
    struct course *course_pointer = &new_course;
    return course_pointer;
};

/** Retrieve a course's subject. */
enum subject	course_subject(const struct course* course){
    printf("\n%d\n", course->subject);
    return course->subject;
}

/** Retrieve a course's course code. */
uint16_t	course_code(const struct course* course){
    printf("\n%d\n", course->code);
    return course->code;
}

/** Increment a course's refcount. */
void		course_hold(struct course* course){
    (course->refcount)++;
}

/** Decrement a course's refcount (optionally freeing it). */
void		course_release(struct course* course){
    (course->refcount)--;
}
;
/** Retrieve the current reference count of a course. */
int		course_refcount(const struct course* course){
    printf("\n%d\n", course->refcount);
    return course->refcount;
}




int main(){
    struct course *course = course_create(SUBJ_PHYS,123);
    course_release(course);
    course_refcount(course);
    course_hold(course);
    course_refcount(course);
    return 0;
}