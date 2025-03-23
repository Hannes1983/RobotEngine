add_library(Backend InputReader.cpp InputReader.h OutputReader.cpp OutputReader.h RobotEngine.cpp RobotEngine.hpp Constants.hpp)
message("wxWidgets ADDDDDD!" ${wxWidgets_LIBRARIES} )
target_link_libraries(Backend PUBLIC ${wxWidgets_LIBRARIES})