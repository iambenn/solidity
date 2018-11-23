file(GLOB sources
	CodeFragment.cpp
	Compiler.cpp
	CompilerState.cpp
	Parser.cpp
)

file(GLOB headers
	CodeFragment.h
	Compiler.h
	CompilerState.h
	Exceptions.h
	Parser.h
)

add_library(lll ${sources} ${headers})
target_link_libraries(lll PUBLIC evmasm devcore)
