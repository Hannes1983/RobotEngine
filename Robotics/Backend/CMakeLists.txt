set(sources_cpp ${sources_cpp} 
    InputReader.cpp 
	OutputReader.cpp
	RobotEngine.cpp
	BaseReader.cpp
	SimReader.cpp
)
set(headers_hpp ${headers_hpp} 
    InputReader.h 
	OutputReader.h
	RobotEngine.hpp
	Constants.hpp
	BaseReader.h
	SimReader.h
)


add_library(Backend ${headers_hpp} ${sources_cpp})

target_link_libraries(Backend PUBLIC ${wxWidgets_LIBRARIES})