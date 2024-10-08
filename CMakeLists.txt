cmake_minimum_required(VERSION 3.6.0)
<<<<<<< HEAD
project(Main)
=======
project(HelloSQLite)
>>>>>>> 32d63524b593a41ef1f07f528505e3f5c751204b
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)
file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/include/*"
	"${PROJECT_SOURCE_DIR}/src/*"
)
<<<<<<< HEAD
add_executable(Main ${SRCS})
=======
add_executable(HelloSQLite ${SRCS})
find_package(SQLite3 REQUIRED)
target_link_libraries(HelloSQLite ${SQLite3_LIBRARIES})
>>>>>>> 32d63524b593a41ef1f07f528505e3f5c751204b
