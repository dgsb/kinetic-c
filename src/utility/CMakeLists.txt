find_package(OpenSSL REQUIRED)
add_executable(kinetic-c-util main.c)
target_link_libraries(kinetic-c-util
                      kinetic-c-client
                      m
                      json-c
                      socket99
                      protobuf-c
                      ${OPENSSL_LIBRARIES}
                      pthread)
add_executable(kinetic-c-discovery discovery.c)
target_link_libraries(kinetic-c-discovery
                      kinetic-c-client
                      m
                      json-c
                      socket99
                      protobuf-c
                      ${OPENSSL_LIBRARIES}
                      pthread)
