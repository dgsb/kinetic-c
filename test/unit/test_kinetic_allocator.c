/*
* kinetic-c
* Copyright (C) 2014 Seagate Technology.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

#include "kinetic_allocator.h"
#include "mock_kinetic_types_internal.h"
#include "kinetic_logger.h"
#include "kinetic_proto.h"
#include "byte_array.h"
#include "protobuf-c/protobuf-c.h"
#include "unity.h"
#include "unity_helper.h"
#include "mock_memory_stubs.h"
#include <stdlib.h>
#include <pthread.h>

KineticConnection Connection;
KineticSession Session;

void setUp(void)
{
    KineticLogger_Init("stdout", 3);
}

void tearDown(void)
{
    KineticLogger_Close();
}

void test_KineticAllocator_NewConnection_should_return_null_if_calloc_returns_null(void)
{
    calloc_ExpectAndReturn(1, sizeof(KineticConnection), NULL);
    KineticConnection* connection =  KineticAllocator_NewConnection();
    TEST_ASSERT_NULL(connection);
}

void test_KineticAllocator_NewConnection_should_return_a_connection_with_connected_flag_set_to_false(void)
{
    calloc_ExpectAndReturn(1, sizeof(KineticConnection), &Connection);
    KineticConnection* connection =  KineticAllocator_NewConnection();
    TEST_ASSERT_NOT_NULL(connection);
    TEST_ASSERT_FALSE(connection->connected);
}

void test_KineticAllocator_NewPDU_should_return_null_if_calloc_returns_null(void)
{
    calloc_ExpectAndReturn(1, sizeof(KineticPDU), NULL);
    KineticPDU * pdu = KineticAllocator_NewPDU(&Connection);
    TEST_ASSERT_NULL(pdu);
}

void test_KineticAllocator_NewPDU_should_initialize_pdu(void)
{
    KineticPDU pdu;
    calloc_ExpectAndReturn(1, sizeof(KineticPDU), &pdu);
    KineticPDU_Init_Expect(&pdu, &Connection);
    KineticPDU * pdu_pointer = KineticAllocator_NewPDU(&Connection);
    TEST_ASSERT_NOT_NULL(pdu_pointer);
}

void test_KineticAllocator_NewKineticResponse_should_return_null_if_calloc_return_null(void)
{
    calloc_ExpectAndReturn(1, sizeof(KineticResponse) + 1234, NULL);
    KineticResponse * response = KineticAllocator_NewKineticResponse(1234);
    TEST_ASSERT_NULL(response);
}
