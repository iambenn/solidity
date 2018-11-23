file(GLOB sources
	Assembly.cpp
	AssemblyItem.cpp
	BlockDeduplicator.cpp
	CommonSubexpressionEliminator.cpp
	ConstantOptimiser.cpp
	ControlFlowGraph.cpp
	ExpressionClasses.cpp
	GasMeter.cpp
	Instruction.cpp
	JumpdestRemover.cpp
	KnownState.cpp
	LinkerObject.cpp
	PathGasMeter.cpp
	PeepholeOptimiser.cpp
	SemanticInformation.cpp
	SimplificationRules.cpp
)

file(GLOB headers
	Assembly.h
	AssemblyItem.h
	BlockDeduplicator.h
	CommonSubexpressionEliminator.h
	ConstantOptimiser.h
	ControlFlowGraph.h
	Exceptions.h
	ExpressionClasses.h
	GasMeter.h
	Instruction.h
	JumpdestRemover.h
	KnownState.h
	LinkerObject.h
	PathGasMeter.h
	PeepholeOptimiser.h
	RuleList.h
	SemanticInformation.h
	SimplificationRule.h
	SimplificationRules.h
)

add_library(evmasm ${sources} ${headers})
target_link_libraries(evmasm PUBLIC devcore)
