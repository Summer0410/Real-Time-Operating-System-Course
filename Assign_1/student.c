#include "student.h"
#include "course.h"
#include "stdio.h"

// /** Opaque type representing a student. */
struct student{
    struct student_id id;
    bool grad;
    int *course_ptr[20];
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
    free(student);
};

/**
 * Note that a student has taken a course.
 *
 * This student will now take a reference to (i.e., increment the refcount of)
 * the course that is passed in.
 */
void    student_take(struct student *s, struct course *course, uint8_t grade){
            bool found_course = false;
            for(int i = 0; i< s->course_count; i++){
                struct course * current_course_ptr = (s->course_ptr)[i];
                if(current_course_ptr->code == course->code && current_course_ptr->subject == course->subject){
                    found_course = true;
                    current_course_ptr->grade = grade;
                }       
            } 
            if(found_course == false){
                struct course * added_course_ptr = course_create(course->subject, course->code);
                added_course_ptr->grade = grade;
                (s->course_ptr)[s->course_count] = added_course_ptr;
                (s->course_count)++;
            }
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
            for(int i = 0; i< s->course_count; i++){
                struct course * current_course_ptr = (s->course_ptr)[i];
                if(current_course_ptr->code == course->code && current_course_ptr->subject == course->subject){
                    printf("%d\n",current_course_ptr->grade);
                    return current_course_ptr->grade;
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
        int passed_course = 0;
        int sum = 0;
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
            printf("%d\n", sum);
            printf("%d\n", passed_course);
            printf("%d", sum/passed_course);
            return sum/passed_course;
        }
            else{//grades
                for (int i = 0; i< s->course_count; i++){
                    printf("%s", "hello");
                struct course * current_course_ptr = (s->course_ptr)[i];
                    if (current_course_ptr->grade>=65){
                        sum += current_course_ptr->grade;
                        passed_course ++;
                } 
            }     
        }
         return sum/passed_course; 
    }
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
    
    if(s->grad == 0){
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
        double sum, average = 0;
        for(int i = 0; i<s->course_count; i++){
            struct course * current_course_ptr = (s->course_ptr)[i];
            sum += current_course_ptr->grade;
            average = sum/s->course_count;
        }
        if(average<60)
            return false;
    }
    return true;
}

