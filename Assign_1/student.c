#include "student.h"
#include "course.h"
#include "stdio.h"
#include "stdlib.h"

// /** Opaque type representing a student. */
struct student{
    struct student_id id;
    bool grad;
    int *course_ptr[20];
    int *course_catalog_ptr[20];
    int course_count;
};

 struct course{
    enum subject subject;
    uint16_t code;
    int grade;
};

struct student*	student_create(struct student_id id, bool grad_student){
    struct student * student_ptr =   (struct student *)malloc(sizeof(struct student));
    student_ptr->grad = grad_student;
    student_ptr->id = id;
    student_ptr->course_count = 0;
    return student_ptr;
};

/**
 * Release a student object.
 */
void student_free(struct student* student){
    int * current_ptr;
    for(int i = 0; i<(student->course_count); i++){
        current_ptr = (student->course_catalog_ptr)[i];
        course_release(current_ptr);
    }
    free(student);
};

/**
 * Note that a student has taken a course.
 *
 * This student will now take a reference to (i.e., increment the refcount of)
 * the course that is passed in.
 */
void    student_take(struct student *s, struct course *course, uint8_t grade){
            struct course * added_course_ptr = course_create(course->subject, course->code);
            added_course_ptr->grade = grade;
            (s->course_ptr)[s->course_count] = added_course_ptr;
            (s->course_catalog_ptr)[s->course_count] = course;
            (s->course_count)++;
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
int     student_grade(struct student* s, struct course* course){
            int latest_grade = -1;
            for(int i = 0; i< s->course_count; i++){
                struct course * current_course_ptr = (s->course_ptr)[i];
                if(current_course_ptr->code == course->code && current_course_ptr->subject == course->subject)
                    latest_grade = current_course_ptr->grade;     
                }  
            return latest_grade;     
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
        int passed_course = 0;
        int sum  = 0;
        double average;
        if(s->course_count == 0){
            return 0;
        }
        else{
            if (s->grad == 0){//Undergrads
                for (int i = 0; i< s->course_count; i++){
                    struct course * current_course_ptr = (s->course_ptr)[i];
                    if (current_course_ptr->grade>=50){
                        sum += (current_course_ptr->grade);
                        passed_course ++;
                }
            }
        }
            else{//grades
                for (int i = 0; i< s->course_count; i++){
                    struct course * current_course_ptr = (s->course_ptr)[i];
                    if (current_course_ptr->grade>=65){
                        sum += current_course_ptr->grade;
                        passed_course ++;
                } 
            }     
        }
         if (passed_course>0){
            average = (double)sum/passed_course;
            return (double)sum/passed_course;
         }
                
        else{
            return 0;
        }          
    }
}


bool		student_promotable(const struct student* s){
    if(s->grad == 1){
        int failed = 0;
        for(int i = 0; i<s->course_count; i++){
            struct course * current_course_ptr = (s->course_ptr)[i];
            if (current_course_ptr->grade<65)
                failed++;
            if (failed>1)
                return false;
        }
    }
    else{
        double sum = 0;
        for(int i = 0; i<s->course_count; i++){
            struct course * current_course_ptr = (s->course_ptr)[i];
            sum += (current_course_ptr->grade);
        }
        if(sum/(s->course_count)<60)
            return false;
            
    }
    return true;
}

