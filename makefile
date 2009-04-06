RAYOBJS = main.o camera.o list.o  model.o material.o object.o plane.o \
          parser.o  image.o raytrace.o sphere.o light.o tri.o
#         illum.o tplane.o ellipse.o

INCLUDE = ray.h rayhdrs.h rayfuns.h vector.h

CFLAGS = -DAA_SAMPLES=1
# -DDBG_PIX -DDBG_DRGB  -DAA_SAMPLES=4
# -DSOFT_SHADOWS

ray: $(RAYOBJS)
	g++ -Wall -o ray -g  $(RAYOBJS) -lm

$(RAYOBJS): $(INCLUDE) makefile

.c.o: $<
	-g++ -c -Wall $(CFLAGS) -c -g $<  2> $(@:.o=.err)
	cat $*.err

.cpp.o: $<
	-g++ -c -Wall $(CFLAGS) -c -g $<  2> $(@:.o=.err)
	cat $*.err

clean:
	rm *.o *.err


