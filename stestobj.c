#include </mnt/d/Programming/c/oopc/shapeobj.h>

int main(void) {
  int i;
  double area;
  OBJECT *shapes[3];

  shapes[0] = new_circle(100.0, 100.0, 50.0);
  shapes[1] = new_rectangle(100., 150., 200., 100.);

  for(i = 0; i < 2; i++) {
    send_message(shapes[i], COMPUTE_AREA, &area);
    printf("Area of shape [%d] = %f\n", i, area);
  }

  for(i = 0; i < 2; i++) {
    send_message(shapes[i], DRAW);
  }

  /*

  NEW TRIAGLE LOGIC

  */

 OBJECT *t;
 t = new_triangle(100., 100., 200., 100., 150., 50.);

 send_message(t, COMPUTE_AREA, &area);
 printf("The Area of the triangle is: %f\n", area);

  return 0;
}
