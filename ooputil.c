#include </mnt/d/Programming/c/oopc/shapeobj.h>

int send_message(OBJECT *p_obj, int msgid, ...) {
  int status;
  va_list argp;
  va_start(argp, msgid);
  status = class_message(p_obj->p_class, p_obj, msgid, argp);
  va_end(argp);
  return(status);
}

int class_message(CLASS *p_class, OBJECT *p_obj, int msgid, va_list argp) {
  int i, status;
  if(p_class == NULL) return 0;

  if(p_class->messages != NULL) {
    for(i = 0; i < p_class->num_messages; i++) {
      if(p_class->messages[i].message_id == msgid) {
        return ((*p_class->messages[i].message_handler)(p_obj, argp));
      }
    }
    status = class_message(p_class->base_class, p_obj, msgid, argp);
  }
  return(status);
}

void *allocate_memory(size_t numbytes) {
  void *ptr;
  if((ptr = calloc(1, numbytes)) == NULL) {
    fprintf(stderr, "Error allocating %d bytes of memory. Exiting...", numbytes);
    exit(1);
  }
  return(ptr);
}

int get_offset(CLASS *p_class) {
  CLASS *p_ct;
  int size = 0;

  for(p_class = p_class->base_class; p_class != NULL; p_class = p_class->base_class) {
    size += p_class->data_size;
  }
  return size;
}
