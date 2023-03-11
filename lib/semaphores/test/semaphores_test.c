#include <assert.h> /* assert */
#include <stdio.h> /* i/o */
#include <stdlib.h> /* atoi */
#include <string.h> /* string operations */

#include "semaphores.h"

#define MAX_INPUT (10)
#define ASCII_MAX (128)

typedef void (*intput_handler_t)(semid_t, char*);

static intput_handler_t g_handlers[ASCII_MAX] = {NULL};

static int IsUndo(char *action);
static int ExtractNum(char *str);
static void DHandler(semid_t id, char *action);
static void IHandler(semid_t id, char *action);
static void VHandler(semid_t id, char *action);
static void NothingHandler(semid_t id, char *action);
static void LUTify(void);

int main(int argc, char *argv[])
{
    semid_t id = 0;
    char action[MAX_INPUT];
    int num = 0;

    id = SemCreate(argv[1], 0, 1);
    LUTify();

    do
    {
        fgets(action, MAX_INPUT, stdin);
        action[strcspn(action, "\n")] = '\0';

        g_handlers[*action](id, action);
        
    }while('X' != *action && 'x' != *action);

    SemDestroy(id);

	return 0;
}

static int IsUndo(char *action)
{
    assert(NULL != action);
    
    return (NULL != strstr(action, "UNDO") && NULL != strstr(action, "undo"));
}

static int ExtractNum(char *str)
{
    char *runner = NULL;

    assert(NULL != str);

    runner = str;

    while('0' >= *runner || '9' <= *runner)
    {
        ++runner;
    }

    return atoi(runner);
}

static void DHandler(semid_t id, char *action)
{
    assert(NULL != action);

    SemDecrement(id, ExtractNum(action), IsUndo(action));
}

static void IHandler(semid_t id, char *action)
{
    assert(NULL != action);

    SemIncrement(id, ExtractNum(action), IsUndo(action));
}

static void VHandler(semid_t id, char *action)
{
    printf("%d\n",SemGetVal(id));
}

static void NothingHandler(semid_t id, char *action)
{
    (void)id;
    (void)action;
}

static void LUTify(void)
{
    size_t i = 0;
    
    for(i = 0; i < ASCII_MAX; ++i)
    {
        g_handlers[i] = &NothingHandler;
    }

    g_handlers['D'] = &DHandler;
    g_handlers['I'] = &IHandler;
    g_handlers['V'] = &VHandler;
    g_handlers['d'] = &DHandler;
    g_handlers['i'] = &IHandler;
    g_handlers['v'] = &VHandler;
}


