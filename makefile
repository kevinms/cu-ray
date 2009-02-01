a.out: main1.o model.o list.o material.o vector.h ray.h rayfuns.h rayhdrs.h
	gcc -Wall -g *.o -lm

.c.o: $<
	-gcc -c -Wall -c -g $<  2> $(@:.o=.err)
	cat $*.err
