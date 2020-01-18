#include "course.h"
#include "stdio.h"
#include "stdlib.h"

 struct course{
    enum subject subject;
    uint16_t code;
    uint8_t refcount;
    int grade;
};

struct course*	course_create(enum subject subject, uint16_t code){
    struct course * course_ptr = (struct course *)malloc(sizeof(struct course));
    course_ptr->code = code;
    course_ptr->subject  = subject;
    course_ptr->refcount = 1;
    course_ptr->grade = 0;
    return course_ptr;
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
    //printf("\n%d\n", course->refcount);
}

/** Decrement a course's refcount (optionally freeing it). */
void		course_release(struct course* course){
    (course->refcount)--;
    printf("\n%d\n", course->refcount);
};
/** Retrieve the current reference count of a course. */
int		course_refcount(const struct course* course){
    printf("\n%d\n", course->refcount);
    return course->refcount;
}


