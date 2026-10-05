/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "5team",
    /* First member's full name */
    "Mingi Kim",
    /* First member's email address */
    "alsrl6710@gmail.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

// 싱글 워드 크기, 4바이트
#define WSIZE             4
// 더블 워드 크기, 8바이트
#define DSIZE             8
// mm_init 호출 시 최초로 할당하는 크기, 4096바이트
#define CHUNKSIZE         (1<<12)

// 둘 중에 더 큰 값
#define MAX(x, y)         ((x) > (y) ? (x) : (y))

// 헤더를 구성, alloc은 0 또는 1
#define PACK(size, alloc) ((size) | (alloc))

// 이 포인터의 헤더 정보를 구함
#define GET(p)            (*(unsigned int *)(p))
// 이 포인터의 헤더 정보를 덮어씀, 보통 PACK과 같이 쓰임
#define PUT(p, val)       (*(unsigned int *)(p) = val)

// 헤더에서 블록 크기를 구함
#define GET_SIZE(p)       (GET(p) & ~0x7)
// 헤더에서 할당 바이트를 구함
#define GET_ALLOC(p)      (GET(p) & 0x1)

// 블록 포인터로부터 헤더 포인터를 구함
#define HDRP(bp)          ((char *)(bp) - WSIZE)
// 블록 포인터로부터 풋터 포인터를 구함
#define FTRP(bp)          ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

// 블록 포인터로부터 다음 블록의 위치를 구함
#define NEXT_BLKP(bp)     ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
// 블록 포인터로부터 이전 블록의 위치를 구함
#define PREV_BLKP(bp)     ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

// 824페이지에서 나온 "한 개의 정적(static) 전역변수"
static char *heap_listp = 0;

/* 
 * mm_init - initialize the malloc package.
 */
// F9.44
// 묵시적 가용 리스트의 불변하는 형식 초기화
int mm_init(void)
{
    if (heap_listp = mem_sbrk(4*WSIZE) == (void*)-1) {
        return -1;
    }
    PUT(heap_listp, 0);
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (3*WSIZE), PACK(0, 1));
    heap_listp += (2*WSIZE);

    if (extend_heap(CHUNKSIZE / WSIZE) == NULL) {
        return -1;
    }
    return 0;
}

// F9.45
// mm_init에서 가용 공간을 늘리려고 호출하는 그 함수
static void *extend_heap(size_t words)
{
    char *bp;
    size_t size;

    size = (words%2) ? (words+1) * WSIZE : words * WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1L) {
        return NULL;
    }

    PUT(HDRP(bp), PACK(size, 1));
    PUT(FTRP(bp), PACK(size, 1));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));
    
    return coalesce(bp);
}

/*
 * mm_free - Freeing a block does nothing.
 */

// naive 방식에서는 아무것도 안하는 이 함수를
// 할당 비트를 0으로 맞추고 경계태그 연결 함수(coalesce)를 써서 가용 공간을 최대한 늘려야 함
void mm_free(void *bp)
{
    
}

// 경계태그 연결 함수, 사실상 묵시적 가용 리스트 방식의 하이라이트
static void *coalesce(void *bp)
{

}

// 연습문제 9.8, first fit 검색을 수행하는 함수
static void *find_fit(size_t asize)
{

}

// 연습문제 9.9, 블록을 실제로 배치하는 함수
// 요청한 블록을 가용 블록의 시작 부분에 배치해야 하며, 남은 부분의 크기가 최소 블록 크기와 같거나 큰 경우에만 분할
static void *place(void *bp, size_t asize)
{

}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */

// naive 방식에서는 단순히 mem_sbrk 함수를 호출하는 이 함수를
// 가용 블록을 찾고 여기를 할당했다고 표시해야 함
void *mm_malloc(size_t size)
{
    // int newsize = ALIGN(size + SIZE_T_SIZE);
    // void *p = mem_sbrk(newsize);
    // if (p == (void *)-1)
	// return NULL;
    // else {
    //     *(size_t *)p = size;
    //     return (void *)((char *)p + SIZE_T_SIZE);
    // }
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;
    
    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}














