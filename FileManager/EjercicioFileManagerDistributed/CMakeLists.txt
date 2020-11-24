add_executable (server server.cpp FileManager.cpp FileManager.h FileManagerImp.cpp FileManagerImp.h FileManagerStub.cpp FileManagerStub.h Utils.cpp Utils.h)
target_link_libraries(server pthread)

add_executable (client client.cpp FileManager.cpp FileManager.h FileManagerImp.cpp FileManagerImp.h FileManagerStub.cpp FileManagerStub.h Utils.cpp Utils.h)
target_link_libraries(client pthread)
