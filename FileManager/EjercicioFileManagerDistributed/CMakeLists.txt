add_executable (server main_server.cpp Server.h Server.cpp ClientConnection.h ClientConnection.cpp MyConnection.h MyConnection.cpp FileManagerImp.h FileManagerImp.cpp FileManager.h FileManager.cpp)
target_link_libraries(server pthread)

add_executable (client main_client.cpp FileManagerStub.h FileManagerStub.cpp MyConnection.h MyConnection.cpp)
target_link_libraries(client pthread)
