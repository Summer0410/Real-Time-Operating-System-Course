#include "student.h"
#include "course.h"

/** Opaque type representing a student. */
struct student{
    struct student_id id;
    bool grad;
    struct course_code[20];
    int course_total;
};

 struct course{
    enum subject subject;
    uint16_t code;
    int refcount;
};
struct student*	student_create(struct student_id id, bool grad_student){
    struct student *new_student;
    new_student->grad = grad_student;
    new_student->id = id;
    new_student->course_total = 0;
    return new_student;
};

/**
 * Note that a student has taken a course.
 *
 * This student will now take a reference to (i.e., increment the refcount of)
 * the course that is passed in.
 */
void		student_take(struct student *s, struct course *course, uint8_t grade){
            grade = 0;
            s->course_code[s->course_total][0] = course->code;
            s->course_code[s->course_total][1] = grade;
            s->course_total++;
};
