#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h> 
#include "rtos-alloc.h"

typedef struct allocation {
	void	*a_base;
	size_t	a_len;
	struct allocation *a_prev;
	struct allocation *a_next;
} alloc_t;

size_t total_size = 0;
void alloc_print(struct allocation *ap);
static struct allocation *first_alloc, *last_alloc = NULL;//Pointers to an allocation struct

struct allocation* alloc_init(){
	return first_alloc = last_alloc = mmap(0,sizeof(struct allocation),PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);//First node and the last node point to the same addr
}


void*	rtos_malloc(size_t size){
        alloc_t *ap;
        if (first_alloc == NULL){
		ap = alloc_init();
		if (ap == NULL){
			return NULL;
		}
	}
	else{   
		ap = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);//Allocate the memory
                if(ap == 0){
                }
		last_alloc->a_next = ap;
		ap->a_prev = last_alloc;
		last_alloc = ap;
	}
	ap->a_base = ap;
	ap->a_len = size;
        total_size += ap->a_len;
	return ap;
}
struct allocation* alloc_find(void *p)
{      
	for (alloc_t *ap = first_alloc; ap != NULL; ap = ap->a_next)
	{
		if (ap->a_base == p)
		{       
			return ap;
		}
	}

	return NULL;
}

void*	rtos_realloc(void *ptr, size_t size){
        rtos_free(ptr);
        void *addr = mmap(NULL, size, PROT_READ,MAP_SHARED,0,0);
        return addr;
}

void	rtos_free(void *ptr){

        alloc_t *ap = alloc_find(ptr);
        if (ap != NULL){
                alloc_t *prevp = ap->a_prev;
	        alloc_t *nextp = ap->a_next;

	        alloc_t **prevnextp = (prevp ? &prevp->a_next : &first_alloc);
	        *prevnextp = nextp;

	        alloc_t **nextprevp = (nextp ? &nextp->a_prev : &last_alloc);
	        *nextprevp = prevp;
                int unmap = munmap(ptr, ap->a_len);
                ptr=NULL;
        }
}

size_t	rtos_alloc_size(void *ptr){
        alloc_t *ap = alloc_find(ptr);
        if(ap!=NULL)
                return ap->a_len;
        return 0;
}

bool	rtos_allocated(void *ptr){
        alloc_t *ap = alloc_find(ptr);
        if(ap!=NULL)
                return true;
        return false;
}

size_t	rtos_total_allocated(void){
        //Loop through the list to add up the size
        return total_size;
}

bool rtos_is_valid(void *ptr){
        if(ptr==NULL || ptr<0){
                return false;
        }
        else{
                alloc_t *ap = alloc_find(ptr);
                if(ap == NULL)
                        return false;
                return true;
                
        }
             
}






