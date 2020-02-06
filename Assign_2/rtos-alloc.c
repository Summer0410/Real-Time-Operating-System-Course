#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> 
#include <fcntl.h>
#include "rtos-alloc.h"

/**
 * Allocate @b size bytes of memory for the exclusive use of the caller,
 * as `malloc(3)` would.
 */
typedef struct allocation {
	void	*a_base;
	size_t	a_len;
	struct allocation *a_prev;
	struct allocation *a_next;
} alloc_t;
size_t total_size = 0;
static struct allocation *first_alloc, *last_alloc = NULL;//Pointers to an allocation struct

struct allocation* alloc_init(){
	return first_alloc = last_alloc = mmap(0,sizeof(struct allocation),PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);//First node and the last node point to the same addr
}


void*	rtos_malloc(size_t size){
        alloc_t *ap;
        if (first_alloc == NULL){
                printf("%s\n","The first node is NULL");
		ap = alloc_init();
		if (ap == NULL){
			return NULL;
		}
	}
	else{   printf("%s", "First node is not NULL\n");
		ap = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);//Allocate the memory
		last_alloc->a_next = ap;
		ap->a_prev = last_alloc;
		last_alloc = ap;
	}
	ap->a_base = ap;
	ap->a_len = size;
        total_size += ap->a_len;
        printf("%d\n",ap->a_len);
        printf("%d\n", ap);
	return ap;
}
struct allocation* alloc_find(void *p)
{       printf("%s","I came to find" );
	for (alloc_t *ap = first_alloc; ap != NULL; ap = ap->a_next)
	{
		if (ap->a_base == p)
		{       printf("%s\n","I found the ptr");
                        printf("%d",ap->a_base);
			return ap;
		}
                printf("%s\n","I did not find the ptr");
	}

	return NULL;
}
/**
 * Change the size of the allocation starting at @b ptr to be @b size bytes,
 * as `realloc(3)` would.
 */
void*	rtos_realloc(void *ptr, size_t size){
        int *addr = mmap(NULL, size, PROT_READ,MAP_SHARED,0,0);
        return addr;
}

/**
 * Release the memory allocation starting at @b ptr for general use,
 * as `free(3)` would.
 */
void	rtos_free(void *ptr){
        alloc_t *ap = alloc_find(ptr);
        if (ap != NULL){
                printf("%s", "not NULL\n");
                alloc_t *prevp = ap->a_prev;
	        alloc_t *nextp = ap->a_next;

	        alloc_t **prevnextp = (prevp ? &prevp->a_next : &first_alloc);
	        *prevnextp = nextp;

	        alloc_t **nextprevp = (nextp ? &nextp->a_prev : &last_alloc);
	        *nextprevp = prevp;
                int unmap = munmap(ptr, ap->a_len);
                printf("%d\n", ptr);
                ptr=NULL;
        }

}

/*
 * The following functions will help our test code inspect your allocator's
 * internal state:
 */

/**
 * How large is the allocation pointed at by this pointer?
 *
 * @pre   @b ptr points at a valid allocation (according to `rtos_allocated`)
 */
size_t	rtos_alloc_size(void *ptr){
        alloc_t *ap = alloc_find(ptr);
        if(ap!=NULL)
                return ap->a_len;
}

/**
 * Does this pointer point at the beginning of a valid allocation?
 *
 * @param   ptr    any virtual address
 *
 * @returns whether or not @b ptr is a currently-allocated address returned
 *          from @b my_{m,re}alloc
 */
bool	rtos_allocated(void *ptr){
        alloc_t *ap = alloc_find(ptr);
        if(ap!=NULL)
                return true;
        return false;
}

/**
 * How much memory has been allocated by this allocator?
 *
 * @returns the number of bytes that have been allocated to user code,
 *          **not** including any allocator overhead
 */
size_t	rtos_total_allocated(void){
        //Loop through the list to add up the size
        return total_size;
}

bool rtos_is_valid(void *ptr){
        if(ptr==NULL || ptr<0){
                printf("%s\n", "It's not valid");
                return false;
        }
        else{
                alloc_t *ap = alloc_find(ptr);
                if(ap == NULL)
                        return false;
                return true;
                
        }
             
}






