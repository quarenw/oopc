#include </mnt/d/Programming/c/oopc/shapeobj.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

typedef double *P_DOUBLE;

typedef struct CIRCLE_DATA {
  double x, y;
  double radius;
} CIRCLE_DATA;

extern CLASS generic_shape;

static int compute_area(OBJECT *p_obj, va_list argp);
static int draw(OBJECT *p_obj, va_list argp);

static MESSAGE messages[] = {
  COMPUTE_AREA, compute_area,
  DRAW, draw
};

CLASS circle_class = {
  &generic_shape,
  sizeof(CIRCLE_DATA),
  sizeof(messages)/sizeof(MESSAGE),
  messages
};

static int circle_offset = -1;

OBJECT *new_circle(double x, double y, double radius) {
  OBJECT *p_obj;
  CIRCLE_DATA *p_data;
  p_obj = (OBJECT *) allocate_memory(sizeof(OBJECT));
  p_obj->p_class = &circle_class;

  send_message(p_obj, ALLOCATE_DATA, 0);

  if(circle_offset < 0) {
    circle_offset = get_offset(&circle_class);
  }
  p_data = (CIRCLE_DATA *)((char *)p_obj->p_data + circle_offset);
  p_data->x = x;
  p_data->y = y;
  p_data->radius = radius;

  return(p_obj);
}

static int compute_area(OBJECT *p_obj,  va_list argp) {
  int status = 0;
  double *p_area;
  CIRCLE_DATA *p_data;

  p_data = (CIRCLE_DATA *)((char *)p_obj->p_data + circle_offset);

  p_area = va_arg(argp, P_DOUBLE);
  if(p_area != NULL) {
    *p_area = M_PI *p_data->radius * p_data->radius;
    status = 1;
  }
  return(status);
}

static int draw(OBJECT *p_obj, va_list argp) {
  CIRCLE_DATA *p_data;

  p_data = (CIRCLE_DATA *)((char *)p_obj->p_data + circle_offset);

  printf("Draw: Circle of radius %f at (%f, %f)\n", p_data->radius, p_data->x, p_data->y);

  return 1;
}
