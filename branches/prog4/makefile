a.out: model.o camera.o list.o material.o plane.o object.o sphere.o image.o ray.o tplane.o \
                 vector.h ray.h rayfuns.h rayhdrs.h	
	gcc -Wall -g *.o -lm

.c.o: $<
	-gcc -c -Wall -c -g $<  2> $(@:.o=.err)
	cat $*.err
	
clean:
	rm *.o a.out *.err
