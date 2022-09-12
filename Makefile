.PHONY: help
$(VERBOSE).SILENT:



# Self-Documented Makefile
# https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
help:
	@grep -E '^(\w|-)+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
.DEFAULT_GOAL := help


run:
	tar -xzvf irrKlang.tar.gz irrKlang
	g++ src/main.cpp --std=c++17 -framework OpenGL -framework GLUT -L./irrKlang/bin/macosx-gcc -pthread -o checkers
	rm -rf irrKlang
