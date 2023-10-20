cmake_minimum_required(VERSION 3.26)
project(BatteryHistory C)

set(CMAKE_C_STANDARD 11)

add_executable(BatteryHistory main.c
        consts.h)

if(UNIX)
    # On Unix-like systems (Linux, macOS), use the HOME environment variable
    execute_process(
            COMMAND echo $ENV{HOME}
            OUTPUT_VARIABLE USER_HOME
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

message("USER_HOME_DIR=${USER_HOME}")

add_compile_definitions(
        BATTERY_LOG_PATH="${USER_HOME}/batterylog.csv"
)

set(systemd_path "${USER_HOME}/.config/systemd/user/")

set(local_bin_path "${USER_HOME}/.local/bin/")

file(COPY ${CMAKE_SOURCE_DIR}/systemd DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/install.sh DESTINATION ${CMAKE_BINARY_DIR})
file(CHMOD ${CMAKE_BINARY_DIR}/install.sh PERMISSIONS
        OWNER_READ
        OWNER_EXECUTE

)

install(
        DIRECTORY ${CMAKE_BINARY_DIR}/systemd
        DESTINATION ${systemd_path}
)

install(
        FILES ${CMAKE_BINARY_DIR}/BatteryHistory
        DESTINATION ${local_bin_path}
)

install(CODE "message(\"Configuring services\")")

install(CODE "execute_process(COMMAND systemctl --user daemon-reload)")

install(CODE "execute_process(COMMAND systemctl --user enable battery-logger.timer)")

install(CODE "execute_process(COMMAND systemctl --user enable battery-logger.service)")

install(CODE "execute_process(COMMAND systemctl --user start battery-logger.timer)")