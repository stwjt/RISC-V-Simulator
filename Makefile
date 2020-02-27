root_dir := $(PWD)
bld_dir  := ./build
src_dir  := ./main ./sys ./dev ./cpu ./bus ./mem ./disk ./util
sim_dir  := ./sim
sim_file := sim
obj_path  = $(src_dir:=/*.o)

CC      := g++
CFLAGS  := 
OBJ      = $(wildcard ${obj_path})

.PHONY: all

all: build_obj build_elf | ${bld_dir}

build_elf: | ${bld_dir}
	${CC} ${OBJ} ${CFLAGS} -o ${bld_dir}/main

build_obj:
	for dir in ${src_dir}; do \
	    make -C $${dir} root_dir=${root_dir}; \
	done

${bld_dir}:
	mkdir -p ${bld_dir}

sim: all
	make -C ${sim_dir} prog=${prog}
	${sim_dir}/${sim_file} ${bld_dir} ${sim_dir}/prog${prog}

copy-make:
	@for dir in ${src_dir}; do \
	    cp .Makefile $${dir}/Makefile; \
	done

auto-format:
	@for dir in ${src_dir}; do \
	    make -C $${dir} auto-format; \
	done
	@make -C ${sim_dir} auto-format;

clean:
	rm -rf ./build .*.swo .*.swp .*.bin
	@for dir in ${src_dir}; do \
	    make -C $${dir} clean; \
	done
	@make -C ${sim_dir} clean;
