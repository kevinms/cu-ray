CFLAGS = -DDBG_PIX -DDBG_HIT
RAYOBJS = main.o model.o camera.o list.o material.o plane.o \
          object.o sphere.o tplane.o image.o ray.o
RAYHDRS = vector.h ray.h rayfuns.h rayhdrs.h
ray: $(RAYOBJS)
	gcc -Wall -o ray -g $(RAYOBJS) -lm
$(RAYOBJS): $(RAYHDRS) makefile
.c.o: $<
	-gcc -c -Wall $(CFLAGS) -c -g $< 2> $(@:.o=.err)
	cat $*.err

clean:
	rm *.o ray *.err
