add_executable (mmlcl_server main_server.cpp Server.h Server.cpp ClientConnection.h ClientConnection.cpp   MultMatrixImp.h MultMatrixImp.cpp multmatrix.h multmatrix.cpp)
target_link_libraries(mmlcl_server pthread)

add_executable (mmlcl_client main_client.cpp MultMatrixStub.h MultMatrixStub.cpp   multmatrix.h multmatrix.cpp)
