cmake_minimum_required(VERSION 3.6.0)
project(HelloSQLite)
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)
file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/include/*"
	"${PROJECT_SOURCE_DIR}/src/*"
)
add_executable(HelloSQLite ${SRCS})
find_package(SQLite3 REQUIRED)
target_link_libraries(HelloSQLite ${SQLite3_LIBRARIES})