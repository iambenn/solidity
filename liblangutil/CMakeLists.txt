# Solidity Commons Library (Solidity related sharing bits between libsolidity and libyul)
file(GLOB sources
	CharStream.cpp
	ErrorReporter.cpp
	Exceptions.cpp
	ParserBase.cpp
	Scanner.cpp
	Token.cpp
)

file(GLOB headers
	CharStream.h
	EVMVersion.h
	ErrorReporter.h
	Exceptions.h
	ParserBase.h
	Scanner.h
	SourceLocation.h
	Token.h
	UndefMacros.h
)

add_library(langutil ${sources} ${headers})
target_link_libraries(langutil PUBLIC devcore)
