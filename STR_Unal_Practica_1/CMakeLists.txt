cmake_minimum_required(VERSION 3.5.0)
project(Train C)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c controllers/doors.c controllers/doors.h controllers/brake.c controllers/brake.h controllers/hvac.c controllers/hvac.h controllers/lighting.c controllers/lighting.h controllers.h managers/ticket.c managers/ticket.h managers/emergency_alarm.c managers/emergency_alarm.h managers.h controllers/velocity.c controllers/velocity.h)