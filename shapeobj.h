#if !defined(SHAPEOBJ_H)
#define SHAPEOBJ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef struct MESSAGE {
  int message_id;
  int (*message_handler)();
} MESSAGE;

typedef struct CLASS {
  struct CLASS *base_class;
  int data_size;
  int num_messages;
  MESSAGE *messages;
} CLASS;

typedef struct OBJECT {
  void *p_data;
  CLASS *p_class;
} OBJECT;

#define ALLOCATE_DATA 1
#define DRAW 2
#define COMPUTE_AREA 3

OBJECT *new_circle(double x, double y, double radious);
OBJECT *new_rectangle(double x1, double y1, double x2, double y2);
OBJECT *new_triangle(double x1, double y1, double x2, double y2, double x3, double y3);

int send_message(OBJECT *p_obj, int msgid, ...);
int class_message(CLASS *p_class, OBJECT *p_obj, int msgid, va_list argp);
void *allocate_memory(size_t bytes);
int get_offset(CLASS *p_class);

#endif
