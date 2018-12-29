#include </mnt/d/Programming/c/oopc/shapeobj.h>

typedef double *P_DOUBLE;

typedef struct TRIANGLE_DATA {
  double x1, y1;
  double x2, y2;
  double x3, y3;
} TRIANGLE_DATA;

extern CLASS generic_shape;

static int compute_area(OBJECT *p_obj, va_list argp);
static int draw(OBJECT *p_obj, va_list argp);

static MESSAGE messages[] = {
  COMPUTE_AREA, compute_area,
  DRAW, draw
};

CLASS triangle_class = {
  &generic_shape,
  sizeof(TRIANGLE_DATA),
  sizeof(messages)/sizeof(MESSAGE),
  messages
};

static int triangle_offset = -1;

OBJECT *new_triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
  OBJECT *p_obj;
  TRIANGLE_DATA *p_data;

  p_obj = (OBJECT *) allocate_memory(sizeof(OBJECT));
  p_obj->p_class = &triangle_class;

  send_message(p_obj, ALLOCATE_DATA, 0);

  if(triangle_offset < 0) {
    triangle_offset = get_offset(&triangle_class);
    p_data = (TRIANGLE_DATA *)((char *)p_obj->p_data + triangle_offset);
  }

  p_data->x1 = x1;
  p_data->y1 = y1;
  p_data->x2 = x2;
  p_data->y2 = y2;
  p_data->x3 = x3;
  p_data->y3 = y3;

  return(p_obj);
}

static int compute_area(OBJECT *p_obj, va_list argp) {
  int status = 0;
  double *p_area;
  TRIANGLE_DATA *p_data;

  p_data = (TRIANGLE_DATA *)((char *)p_obj->p_data + triangle_offset);
  p_area = va_arg(argp, P_DOUBLE);
  if(p_area != NULL) {
    double x21, y21, x31, y31;

    x21 = p_data->x2 - p_data->x1;
    y21 = p_data->y2 - p_data->y1;
    x31 = p_data->x3 - p_data->x1;
    y31 = p_data->y3 - p_data->y1;

    *p_area = fabs(y21 * x31 - x21 * y31) / 2,0;
    status = 1;
  }
  return(status);
}

static int draw(OBJECT *p_obj, va_list argp) {
  TRIANGLE_DATA *p_data;

  p_data = (TRIANGLE_DATA *)((char *)p_obj->p_data + triangle_offset);
  printf("Draw: Triangle with vertices: (%f, %f) (%f, %f) (%f, %f)\n", p_data->x1, p_data->y1, p_data->x2, p_data->y2, p_data->x3, p_data->y3);

  return 1;
}
