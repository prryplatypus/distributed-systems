add_executable (fmmain_server main_server.cpp Server.h Server.cpp ClientConnection.h ClientConnection.cpp MyConnection.h MyConnection.cpp FileManagerImp.h FileManagerImp.cpp FileManager.h FileManager.cpp)
target_link_libraries(fmmain_server pthread)

add_executable (fmmain_client main_client.cpp FileManagerStub.h FileManagerStub.cpp MyConnection.h MyConnection.cpp FileManager.h FileManager.cpp)