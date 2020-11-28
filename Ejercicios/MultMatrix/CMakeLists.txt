add_executable (multmatrix_server main_server.cpp Server.h Server.cpp ClientConnection.h ClientConnection.cpp MyConnection.h MyConnection.cpp MultMatrixImp.h MultMatrixImp.cpp multmatrix.h multmatrix.cpp)
target_link_libraries(multmatrix_server pthread)

add_executable (multmatrix_client main_client.cpp MultMatrixStub.h MultMatrixStub.cpp MyConnection.h MyConnection.cpp multmatrix.h multmatrix.cpp)
