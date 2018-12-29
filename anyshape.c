#include </mnt/d/Programming/c/oopc/shapeobj.h>

static int allocate_data(OBJECT *p_obj, va_list argp);

static MESSAGE messages[] = {
  ALLOCATE_DATA, allocate_data
};

CLASS generic_shape = {
  NULL,
  0,
  sizeof(messages)/sizeof(MESSAGE),
  messages
};

static int allocate_data(OBJECT *p_obj, va_list argp) {
  CLASS *p_class;
  int size = 0;

  for(p_class = p_obj->p_class, size = 0; p_class != NULL; p_class = p_class->base_class) {
    size += p_class->data_size;
  }

  p_obj->p_data = allocate_memory(size);
  return 1;
}
