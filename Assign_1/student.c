#include "student.h"
#include "course.h"
#include "stdio.h"

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
    struct student * student_ptr =   (struct student *)malloc(sizeof(struct student));
    student_ptr->grad = grad_student;
    student_ptr->id = id;
    student_ptr->course_count = 0;
    for(int i = 0; i<100; i++){
        for(int j=0;j<2;j++){
            student_ptr->course_taken[i][j] = 0;
        }
    }
    return student_ptr;
};

/**
 * Release a student object.
 */
void		student_free(struct student* student){
    // course_release()
    free(student);
};

/**
 * Note that a student has taken a course.
 *
 * This student will now take a reference to (i.e., increment the refcount of)
 * the course that is passed in.
 */
void		student_take(struct student *s, struct course *course, uint8_t grade){
            int old_grade  = student_grade(s, course);
            printf("%d\n",old_grade);
            if(old_grade == -1){//if the course has not been taken, added the course to the list
                s->course_taken[s->course_count][0] = course->code;
                s->course_taken[s->course_count][1] = grade;
                course_hold(course);
            }
            else if(grade>old_grade)
                    s->course_taken[s->course_count][1] = grade;       
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
        printf("%d\n",s->course_count);
        for (int i = 0; i< s->course_count; i++){
            // printf("%d\n",grade);
            // printf("%d\n",grade);

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
        double sum = 0;
        int passed_course = 0;
        if (s->grad == 0){
            for (int i = 0; i< s->course_count; i++){
            if (s->course_taken[i][1]>=50){
                sum += s->course_taken[i][1];
                passed_course ++;
            }
        }
    }
        else{
            for (int i = 0; i< s->course_count; i++){
            if (s->course_taken[i][1]>=65){
                sum += s->course_taken[i][1];
                passed_course ++;
            }
        } 
    }
        return sum/passed_course;       
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
            if (s->course_taken[i][1]<65)
                failed++;
            if (failed>1)
                return false;
        }
    }
    else{
        double sum, average = 0;
        for(int i = 0; i<s->course_count; i++){
            sum += s->course_taken[i][1];
            average = sum/s->course_count;
        }
        if(average<60)
            return false;
    }
    return true;
}

