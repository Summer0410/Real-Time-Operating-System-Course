#include "student.h"
#include "course.h"

// /** Opaque type representing a student. */
struct student{
    struct student_id id;
    bool grad;
    int course_taken [100][2];
    int course_count;
};

 struct course{
    enum subject subject;
    uint16_t code;
    int refcount;
};
struct student*	student_create(struct student_id id, bool grad_student){
    struct student new_student;
    new_student.grad = grad_student;
    new_student.id = id;
    new_student.course_count = 0;
    return &new_student;
};

/**
 * Release a student object.
 */
void		student_free(struct student* student){
    free(student);
};

/**
 * Note that a student has taken a course.
 *
 * This student will now take a reference to (i.e., increment the refcount of)
 * the course that is passed in.
 */
void		student_take(struct student *s, struct course *course, uint8_t grade){
            s->course_taken[s->course_count][0] = course->code;
            s->course_taken[s->course_count][1] = grade;
            course_hold(course);
};


/**
 * Retrieve a student's mark in a course.
 *
 * This will retrieve the most recent grade that a student achieved in a
 * particular course.
 *
 * @returns    a grade, or -1 if the student has not taken the course
 */
int		student_grade(struct student* s, struct course* course){
        for (int i = 0; i< s->course_count; i++){
            if (s->course_taken[i][0] == course->code){
                return s->course_taken[i][1];
            }
        }
        return -1;
}

/**
 * Determine the average grade in the courses this student has passed.
 *
 * This will average the grades in courses that the student has passed, meaning
 * that they scored at least 50 (if undergraduate) or 65 (if graduate).
 *
 * @returns     the average, or 0 if no courses have been passed
 */
double		student_passed_average(const struct student* s){
        // int sum = 0;
        // int passed_course = 0;
        // for (int i = 0; i< s->course_count; i++){
        //     if (s->course_taken[i][1]>=50){
        //         sum += s->course_taken[i][1]>=50;
        //         passed_course ++;
        //     }
        // }
        // double average = sum/passed_course;
        // if(average>=60)
        //     return average;
        // else
        //     return 0;     
}

/**
 * Determine whether or not this student is promotable.
 *
 * (note: this is not how promotion really works... simplified for assignment)
 *
 * For graduate students, determine whether they have passed all of their
 * courses apart from (up to) one.
 *
 * For undergraduate students, determine whether or not the cumulative average
 * of all courses is at least 60%.
 */
bool		student_promotable(const struct student* s){
            double average = stu

}
