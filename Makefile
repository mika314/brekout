all: desktop

desktop: FORCE gen
	coddle
	play /usr/share/sounds/sound-icons/percussion-12.wav 2> /dev/null

web: FORCE desktop
	emcc -Wall -Wextra -std=c++20 -O3 -I.coddle/libs_src -s USE_SDL=2 -s TOTAL_MEMORY=19988480 -s ALLOW_MEMORY_GROWTH=1 `sed 's/.coddle\///g' .coddle/brekout.objs | sed 's/.cpp.o/.cpp/g'` -o brekout.html
	play /usr/share/sounds/sound-icons/percussion-12.wav 2> /dev/null

gen: FORCE make-gen
	make -f gen.make

make-gen: FORCE
	echo "make[1]: Entering directory 'make-gen'"
	cd make-gen && coddle
	echo "make[1]: Leaving directory 'make-gen'"
	make-gen/make-gen > gen.make

FORCE:
