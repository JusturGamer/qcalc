set(RESOURCES ${CMAKE_SOURCE_DIR}/resources/resources.qrc)
set(CORE parser.cpp utils.cpp qcalc.cpp)

set(SRCS ${CORE} mainwindow.cpp
                 filters.cpp
                 buttons.cpp
                 display.cpp
                 titlebar.cpp
                 basic_mode.cpp)

if(WIN32)
  set(RESOURCES ${RESOURCES} ${CMAKE_SOURCE_DIR}/resources/resources.rc)
endif()

add_library(core ${CORE})

add_executable(qcalc WIN32 main.cpp ${SRCS} ${RESOURCES})
target_link_libraries(qcalc mainwindow ${MPFR_LIBRARIES} ${MPIR_LIBRARIES})

if(MSVC)
  set_target_properties(qcalc PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()

qt5_use_modules(qcalc Core Gui Widgets)

# Copy MPIR DLLs
if(WIN32 AND MPIR_FOUND)
  # Define MPIR_ROOT if necessary
  if(DEFINED ENV{MPIR_ROOT})
    if(NOT DEFINED MPIR_ROOT)
      set(MPIR_ROOT $ENV{MPIR_ROOT})
   endif()
  endif()

  add_custom_command(TARGET qcalc POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E make_directory
                             ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/
                    )

  if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    add_custom_command(TARGET qcalc POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                               ${MPIR_ROOT}/dll/Win32/Debug/mpir.dll
                               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/
                       COMMAND ${CMAKE_COMMAND} -E copy
                               ${MPIR_ROOT}/dll/Win32/Release/mpir.dll
                               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/
                      )
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_custom_command(TARGET qcalc POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                               ${MPIR_ROOT}/dll/x64/Debug/mpir.dll
                               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/
                       COMMAND ${CMAKE_COMMAND} -E copy
                               ${MPIR_ROOT}/dll/x64/Release/mpir.dll
                               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/
                      )
  endif()
endif()

# Copy MPFR DLLs
if(WIN32 AND MPFR_FOUND)
  # Define MPFR_ROOT if necessary
  if(DEFINED ENV{MPFR_ROOT})
    if(NOT DEFINED MPFR_ROOT)
      set(MPFR_ROOT $ENV{MPFR_ROOT})
    endif()
  endif()

  add_custom_command(TARGET qcalc POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E make_directory
                             ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/
                    )

  if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    add_custom_command(TARGET qcalc POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                               ${MPFR_ROOT}/dll/Win32/Debug/mpfr.dll
                               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/
                       COMMAND ${CMAKE_COMMAND} -E copy
                               ${MPFR_ROOT}/dll/Win32/Release/mpfr.dll
                               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/
                      )
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_custom_command(TARGET qcalc POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                               ${MPFR_ROOT}/dll/x64/Debug/mpfr.dll
                               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/
                       COMMAND ${CMAKE_COMMAND} -E copy
                               ${MPFR_ROOT}/dll/x64/Release/mpfr.dll
                               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/
                      )
  endif()
endif()
