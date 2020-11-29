add_executable (fm_server main_server.cpp Server.h Server.cpp ClientConnection.h ClientConnection.cpp MyConnection.h MyConnection.cpp FileManagerImp.h FileManagerImp.cpp FileManager.h FileManager.cpp)
target_link_libraries(fm_server pthread)

add_executable (fm_client main_client.cpp FileManagerStub.h FileManagerStub.cpp MyConnection.h MyConnection.cpp)
