cmake_minimum_required(VERSION 2.8)
project(kinetic-c-client C)

include(ExternalProject)

#
# External third party build
# protbuf protobuf-c socket99 jsonc-c
#
ExternalProject_Add(protobuf_ep
                    URL ${PROJECT_SOURCE_DIR}/vendor/protobuf-2.6.0
                    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>)
ExternalProject_Get_Property(protobuf_ep install_dir)
set(protobuf_ep_install_dir ${install_dir})

ExternalProject_Add(protobuf-c_ep
                    GIT_REPOSITORY ${PROJECT_SOURCE_DIR}/vendor/protobuf-c
                    GIT_TAG v1.1.0
                    UPDATE_COMMAND ""
                    CONFIGURE_COMMAND PKG_CONFIG_PATH=${protobuf_ep_install_dir}/lib/pkgconfig <SOURCE_DIR>/configure --prefix <INSTALL_DIR>)
ExternalProject_Add_Step(protobuf-c_ep autogen
                         COMMAND <SOURCE_DIR>/autogen.sh
                         DEPENDEES download
                         DEPENDERS configure
                         WORKING_DIRECTORY <SOURCE_DIR>)
ExternalProject_Get_Property(protobuf-c_ep install_dir)
include_directories(${install_dir}/include)
add_library(protobuf-c STATIC IMPORTED GLOBAL)
set_property(TARGET protobuf-c PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libprotobuf-c.a)

ExternalProject_Add(socket99_ep
                    GIT_REPOSITORY ${PROJECT_SOURCE_DIR}/vendor/socket99
                    GIT_TAG eb363130439f513fe0aec90598b53a1412cffa7c
                    URL ${PROJECT_SOURCE_DIR}/vendor/socket99
                    UPDATE_COMMAND ""
                    CONFIGURE_COMMAND ""
                    BUILD_IN_SOURCE 1
                    INSTALL_COMMAND PREFIX=<INSTALL_DIR> make install)
ExternalProject_Get_Property(socket99_ep install_dir)
include_directories(${install_dir}/include)
add_library(socket99 STATIC IMPORTED GLOBAL)
set_property(TARGET socket99 PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libsocket99.a)

ExternalProject_Add(json-c_ep
                    GIT_REPOSITORY ${PROJECT_SOURCE_DIR}/vendor/json-c
                    GIT_TAG ec4879ac5b502ae81f6b73450b960ede11ad2560
                    UPDATE_COMMAND ""
                    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix <INSTALL_DIR>
                    INSTALL_COMMAND make install)
ExternalProject_Add_Step(json-c_ep autogen
                         COMMAND <SOURCE_DIR>/autogen.sh
                         DEPENDEES download
                         DEPENDERS configure
                         WORKING_DIRECTORY <SOURCE_DIR>)
ExternalProject_Get_Property(json-c_ep install_dir)
include_directories(${install_dir}/include/json-c)
add_library(json-c STATIC IMPORTED GLOBAL)
set_property(TARGET json-c PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libjson-c.a)

add_dependencies(protobuf-c_ep protobuf_ep)

#
# Kinetic-c build
#
file(READ config/VERSION V)
string(STRIP ${V} V)
set(KINETIC_C_VERSION "${V}" CACHE INTERNAL "" FORCE)
message(STATUS "Building kinetic-c ${KINETIC_C_VERSION}")

#
# Version header generated file in source tree
# It is a kind of an build artifact,
# it should generated in the build tree with the use of a config_file command
#
execute_process(COMMAND ${PROJECT_SOURCE_DIR}/config/generate_version_info.sh)

# XXX DB we should add the -Wmissing-prototypes here
set(WARN "-Wall -Wextra -Wstrict-prototypes -Wcast-align
-Wno-missing-field-initializers -Werror=strict-prototypes -Wshadow -Werror"
    CACHE INTERNAL "" FORCE)

add_definitions(-std=c99 -pedantic -D_POSIX_C_SOURCE=199309L -D_C99_SOURCE=1 ${WARN})
include_directories(include)
add_subdirectory(src)

