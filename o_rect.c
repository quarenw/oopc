#include </mnt/d/Programming/c/oopc/shapeobj.h>

typedef double *P_DOUBLE;

typedef struct RECTANGLE_DATA {
  double x1, y1;
  double x2, y2;
} RECTANGLE_DATA;

extern CLASS generic_shape;

static int compute_area(OBJECT *p_obj, va_list argp);
static int draw(OBJECT *p_obj, va_list argp);

static MESSAGE messages[] = {
  COMPUTE_AREA, compute_area,
  DRAW, draw
};

CLASS rectangle_class = {
  &generic_shape,
  sizeof(RECTANGLE_DATA),
  sizeof(messages)/sizeof(MESSAGE),
  messages
};

static int rectangle_offset = -1;

OBJECT *new_rectangle(double x1, double y1, double x2, double y2) {
  OBJECT *p_obj;
  RECTANGLE_DATA *p_data;

  p_obj = (OBJECT *) allocate_memory(sizeof(OBJECT));
  p_obj->p_class = &rectangle_class;

  send_message(p_obj, ALLOCATE_DATA, 0);

  if(rectangle_offset < 0) {
    rectangle_offset = get_offset(&rectangle_class);
  }
  p_data = (RECTANGLE_DATA *)((char *)p_obj->p_data + rectangle_offset);

  p_data->x1 = x1;
  p_data->y1 = y1;
  p_data->x2 = x2;
  p_data->y2 = y2;

  return(p_obj);
}

static int compute_area(OBJECT *p_obj, va_list argp) {
  int status = 0;
  double *p_area;
  RECTANGLE_DATA *p_data;

  p_data = (RECTANGLE_DATA *)((char *)p_obj->p_data + rectangle_offset);

  p_area = va_arg(argp, P_DOUBLE);
  if(p_area != NULL) {
    *p_area = fabs((p_data->x2 - p_data->x1) * (p_data->y2 - p_data->y1));
    status = 1;
  }
  return(status);
}

static int draw(OBJECT *p_obj, va_list argp) {
  RECTANGLE_DATA *p_data;

  p_data = (RECTANGLE_DATA *)((char *) p_obj->p_data + rectangle_offset);

  printf("Draw: Rectangle with corners: (%f, %f) at (%f, %f)\n", p_data->x1, p_data->y1, p_data->x2, p_data->y2);

  return 1;
}