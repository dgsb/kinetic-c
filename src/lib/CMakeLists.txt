set(KINETIC_LIB_SRCS
#            socket99.c
#            protobuf-c.c
            kinetic_allocator.c
            kinetic_nbo.c
            kinetic_operation.c
            kinetic_callbacks.c
            kinetic_builder.c
            kinetic_request.c
            kinetic_response.c
            kinetic_bus.c
            kinetic_auth.c
            kinetic_pdu_unpack.c
            kinetic.pb-c.c
            kinetic_socket.c
            kinetic_message.c
            kinetic_logger.c
            kinetic_hmac.c
            kinetic_controller.c
            kinetic_device_info.c
            kinetic_session.c
            kinetic_types_internal.c
            kinetic_types.c
            kinetic_memory.c
            kinetic_semaphore.c
            kinetic_countingsemaphore.c
            kinetic_resourcewaiter.c
            kinetic_acl.c
            byte_array.c
            kinetic_client.c
            kinetic_admin_client.c
            threadpool/threadpool.c
            bus/bus.c
            bus/bus_poll.c
            bus/bus_ssl.c
            bus/listener.c
            bus/listener_cmd.c
            bus/listener_helper.c
            bus/listener_io.c
            bus/listener_task.c
            bus/send.c
            bus/send_helper.c
            bus/syscall.c
            bus/util.c
            bus/yacht.c
            )

include_directories(. bus threadpool)
add_library(kinetic-c-client STATIC ${KINETIC_LIB_SRCS})
#add_library(kinetic-c-client_shared SHARED ${KINETIC_LIB_SRCS})
add_dependencies(kinetic-c-client protobuf-c_ep)
add_subdirectory(threadpool)

