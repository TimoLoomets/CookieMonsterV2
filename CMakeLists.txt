# v3.14 required for FetchContent_MakeAvailable
cmake_minimum_required(VERSION 3.14)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)

if (DEFINED MCU)
  include(FetchContent)
	FetchContent_Declare(
		mcu_support
		GIT_REPOSITORY https://github.com/bolderflight/mcu-support.git
		GIT_TAG v1.1.0
	)
	FetchContent_MakeAvailable(mcu_support)
  # Setting up the toolchain
  set(CMAKE_TOOLCHAIN_FILE "${mcu_support_SOURCE_DIR}/cmake/cortex.cmake")
  # Project information
  project(GenericFolk
    LANGUAGES C CXX
  )
  # Grab the processor and set up definitions and compile options
  include(${mcu_support_SOURCE_DIR}/cmake/config_mcu.cmake)
  configMcu(${MCU} ${mcu_support_SOURCE_DIR})
  # Add the library target
  if (MCU STREQUAL "MK20DX128" OR MCU STREQUAL "MK20DX256" OR MCU STREQUAL "MK64FX512" OR MCU STREQUAL "MK66FX1M0" OR MCU STREQUAL "MKL26Z64")
    add_library(core
      core/src/teensy3x/analog.c
      core/src/teensy3x/DMAChannel.cpp
      core/src/teensy3x/eeprom.c
      core/src/teensy3x/hardware_serial.cc
      core/src/teensy3x/IntervalTimer.cpp
      core/src/teensy3x/mk20dx128.c
      core/src/teensy3x/nonstd.c
      core/src/teensy3x/pins_teensy.c
      core/src/teensy3x/Print.cpp
      core/src/teensy3x/serial1.c
      core/src/teensy3x/serial2.c
      core/src/teensy3x/serial3.c
      core/src/teensy3x/serial4.c
      core/src/teensy3x/serial5.c
      core/src/teensy3x/serial6.c
      core/src/teensy3x/serial6_lpuart.c
      core/src/teensy3x/Stream.cpp
      core/src/teensy3x/usb_desc.c
      core/src/teensy3x/usb_dev.c
      core/src/teensy3x/usb_inst.cpp
      core/src/teensy3x/usb_mem.c
      core/src/teensy3x/usb_serial.c
      core/src/teensy3x/systick_isr.c
      core/src/teensy3x/yield.c
      core/src/teensy3x/SPI.cpp
      core/src/teensy3x/micros64.c
      core/src/teensy3x/WireKinetis.cpp
      core/include/teensy3x/core.h
      core/include/teensy3x/avr_emulation.h
      core/include/teensy3x/avr_functions.h
      core/include/teensy3x/core_pins.h
      core/include/teensy3x/DMAChannel.h
      core/include/teensy3x/eeprom.h
      core/include/teensy3x/elapsedMillis.h
      core/include/teensy3x/HardwareSerial.h
      core/include/teensy3x/IntervalTimer.h
      core/include/teensy3x/kinetis.h
      core/include/teensy3x/mk20dx128.h
      core/include/teensy3x/pins_arduino.h
      core/include/teensy3x/Print.h
      core/include/teensy3x/Stream.h
      core/include/teensy3x/usb_desc.h
      core/include/teensy3x/usb_dev.h
      core/include/teensy3x/usb_mem.h
      core/include/teensy3x/usb_names.h
      core/include/teensy3x/usb_serial.h
      core/include/teensy3x/SPI.h
      core/include/teensy3x/EEPROMclass.h
      core/include/teensy3x/micros64.h
      core/include/teensy3x/WireKinetis.h
    )
  else ()
    add_library(core
      core/src/teensy4x/bootdata.c
      core/src/teensy4x/clockspeed.c
      core/src/teensy4x/delay.c
      core/src/teensy4x/analog.c
      core/src/teensy4x/DMAChannel.cpp
      core/src/teensy4x/eeprom.c
      core/src/teensy4x/HardwareSerial.cpp
      core/src/teensy4x/HardwareSerial1.cpp
      core/src/teensy4x/HardwareSerial2.cpp
      core/src/teensy4x/HardwareSerial3.cpp
      core/src/teensy4x/HardwareSerial4.cpp
      core/src/teensy4x/HardwareSerial5.cpp
      core/src/teensy4x/HardwareSerial6.cpp
      core/src/teensy4x/HardwareSerial7.cpp
      core/src/teensy4x/HardwareSerial8.cpp
      core/src/teensy4x/interrupt.c
      core/src/teensy4x/IntervalTimer.cpp
      core/src/teensy4x/nonstd.c
      core/src/teensy4x/Print.cpp
      core/src/teensy4x/pwm.c
      core/src/teensy4x/rtc.c
      core/src/teensy4x/startup.c
      core/src/teensy4x/Stream.cpp
      core/src/teensy4x/tempmon.c
      core/src/teensy4x/usb.c
      core/src/teensy4x/usb_desc.c
      core/src/teensy4x/usb_inst.cpp
      core/src/teensy4x/usb_serial.c
      core/src/teensy4x/yield.cpp
      core/src/teensy4x/digital.c
      core/src/teensy4x/debugprintf.c
      core/src/teensy4x/EventResponder.cpp
      core/src/teensy4x/serialEvent.cpp
      core/src/teensy4x/serialEvent1.cpp
      core/src/teensy4x/serialEvent2.cpp
      core/src/teensy4x/serialEvent3.cpp
      core/src/teensy4x/serialEvent4.cpp
      core/src/teensy4x/serialEvent5.cpp
      core/src/teensy4x/serialEvent6.cpp
      core/src/teensy4x/serialEvent7.cpp
      core/src/teensy4x/serialEvent8.cpp
      core/src/teensy4x/serialEventUSB1.cpp
      core/src/teensy4x/serialEventUSB2.cpp
      core/src/teensy4x/SPI.cpp
      core/src/teensy4x/WireIMXRT.cpp
      core/src/teensy4x/micros64.c
      core/include/teensy4x/core.h
      core/include/teensy4x/arm_math.h
      core/include/teensy4x/avr_emulation.h
      core/include/teensy4x/avr_functions.h
      core/include/teensy4x/core_cmInstr.h
      core/include/teensy4x/core_pins.h
      core/include/teensy4x/DMAChannel.h
      core/include/teensy4x/eeprom.h
      core/include/teensy4x/elapsedMillis.h
      core/include/teensy4x/HardwareSerial.h
      core/include/teensy4x/IntervalTimer.h
      core/include/teensy4x/imxrt.h
      core/include/teensy4x/pins_arduino.h
      core/include/teensy4x/Print.h
      core/include/teensy4x/printf.h
      core/include/teensy4x/Stream.h
      core/include/teensy4x/usb_desc.h
      core/include/teensy4x/usb_dev.h
      core/include/teensy4x/usb_names.h
      core/include/teensy4x/usb_serial.h
      core/include/teensy4x/EEPROMclass.h
      core/include/teensy4x/core_id.h
      core/include/teensy4x/EventResponder.h
      core/include/teensy4x/SPI.h
      core/include/teensy4x/WireIMXRT.h
      core/include/teensy4x/micros64.h
    )
  endif()
  # Setup include directories 
  target_include_directories(core PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/include>
    $<INSTALL_INTERFACE:include>
  )

  #VL53L1XExtended
  file(GLOB_RECURSE LIB_VL53L1XEXTENDED ${CMAKE_CURRENT_SOURCE_DIR}/libraries/VL53L1XExtended/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/libraries/VL53L1XExtended/include/*.hpp)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/VL53L1XExtended/include $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  add_library(VL53L1XExtended STATIC ${LIB_VL53L1XEXTENDED})
  target_link_libraries(VL53L1XExtended
    PRIVATE
    core
  )

  #VL53L5CXExtended
  file(GLOB_RECURSE LIB_VL53L5CXEXTENDED ${CMAKE_CURRENT_SOURCE_DIR}/libraries/VL53L5CXExtended/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/libraries/VL53L5CXExtended/include/*.hpp)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/VL53L5CXExtended/include $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  add_library(VL53L5CXExtended STATIC ${LIB_VL53L5CXEXTENDED})
  target_link_libraries(VL53L5CXExtended
    PRIVATE
    core
  )

  #PWMServo
  file(GLOB_RECURSE LIB_PWMSERVO ${CMAKE_CURRENT_SOURCE_DIR}/libraries/PWMServo/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/libraries/PWMServo/include/*.hpp)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/PWMServo/include $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  add_library(PWMServo STATIC ${LIB_PWMSERVO})
  target_link_libraries(PWMServo
    PRIVATE
    core
  )

  #Encoder
  file(GLOB_RECURSE LIB_ENCODER ${CMAKE_CURRENT_SOURCE_DIR}/libraries/Encoder/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/libraries/Encoder/include/*.hpp)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/Encoder/include $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  add_library(Encoder STATIC ${LIB_ENCODER})
  target_link_libraries(Encoder
    PRIVATE
    core
  )

  #CookieMonsterDrive
  file(GLOB_RECURSE LIB_COOKIEMONSTERDRIVE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/CookieMonsterDrive/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/libraries/CookieMonsterDrive/include/*.hpp)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/CookieMonsterDrive/include $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  add_library(CookieMonsterDrive STATIC ${LIB_COOKIEMONSTERDRIVE})
  target_link_libraries(CookieMonsterDrive
    PRIVATE
    core
    PWMServo
    Encoder
  )

  #TeensyDebug
  file(GLOB_RECURSE LIB_TEENSYDEBUG ${CMAKE_CURRENT_SOURCE_DIR}/libraries/TeensyDebug/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/libraries/TeensyDebug/include/*.hpp)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/TeensyDebug/include $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  add_library(TeensyDebug STATIC ${LIB_TEENSYDEBUG})
  target_link_libraries(TeensyDebug
    PRIVATE
    core
  )

  #Interaction
  file(GLOB_RECURSE LIB_INTERACTION ${CMAKE_CURRENT_SOURCE_DIR}/libraries/Interaction/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/libraries/Interaction/include/*.hpp)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/Interaction/include $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  add_library(Interaction STATIC ${LIB_INTERACTION})
  target_link_libraries(Interaction
    PRIVATE
    core
  )

  #Util
  file(GLOB_RECURSE LIB_UTIL ${CMAKE_CURRENT_SOURCE_DIR}/libraries/Util/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/libraries/Util/include/*.hpp)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/Util/include $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  add_library(Util STATIC ${LIB_UTIL})
  target_link_libraries(Util
    PRIVATE
    core
  )

  #IMU
  file(GLOB_RECURSE LIB_IMU ${CMAKE_CURRENT_SOURCE_DIR}/libraries/IMU/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/libraries/IMU/include/*.hpp)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/IMU/include $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  add_library(IMU STATIC ${LIB_IMU})
  target_link_libraries(IMU
    PRIVATE
    core
    Util
  )

  #Navigation
  file(GLOB_RECURSE LIB_NAVIGATION ${CMAKE_CURRENT_SOURCE_DIR}/libraries/Navigation/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/libraries/Navigation/include/*.hpp)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/Navigation/include $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  add_library(Navigation STATIC ${LIB_NAVIGATION})
  target_link_libraries(Navigation
    PRIVATE
    core
    CookieMonsterDrive
    Interaction
    VL53L1XExtended
    IMU
  )

  # Example if this project is built separately
  if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
    include(${mcu_support_SOURCE_DIR}/cmake/flash_mcu.cmake)

    # Add the example target
    add_executable(TOF_test main/TOF_test.cpp)
    # Add the includes
    target_include_directories(TOF_test PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main>
      $<INSTALL_INTERFACE:include>
    )
    # Link libraries to the test target
    target_link_libraries(TOF_test
      PRIVATE 
      core
      VL53L1XExtended
    )
    # Add hex and upload targets
    FlashMcu(TOF_test ${MCU} ${mcu_support_SOURCE_DIR})

    add_executable(blink main/blink.cpp)
    # Add the includes
    target_include_directories(blink PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main>
      $<INSTALL_INTERFACE:include>
    )
    # Link libraries to the test target
    target_link_libraries(blink
      PRIVATE
      core
      Interaction
    )
    # Add hex and upload targets
    FlashMcu(blink ${MCU} ${mcu_support_SOURCE_DIR})

    add_executable(servo_test main/servo.cpp)
    # Add the includes
    target_include_directories(servo_test PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main>
      $<INSTALL_INTERFACE:include>
    )
    # Link libraries to the test target
    target_link_libraries(servo_test
      PRIVATE
      core
      PWMServo
    )
    # Add hex and upload targets
    FlashMcu(servo_test ${MCU} ${mcu_support_SOURCE_DIR})

    add_executable(encoder_test main/encoder_test.cpp)
    # Add the includes
    target_include_directories(encoder_test PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main>
      $<INSTALL_INTERFACE:include>
    )
    # Link libraries to the test target
    target_link_libraries(encoder_test
      PRIVATE
      core
      CookieMonsterDrive
    )
    # Add hex and upload targets
    FlashMcu(encoder_test ${MCU} ${mcu_support_SOURCE_DIR})

    add_executable(speed_control_test main/speed_control_test.cpp)
    # Add the includes
    target_include_directories(speed_control_test PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main>
      $<INSTALL_INTERFACE:include>
    )
    # Link libraries to the test target
    target_link_libraries(speed_control_test
      PRIVATE
      core
      CookieMonsterDrive
    )
    # Add hex and upload targets
    FlashMcu(speed_control_test ${MCU} ${mcu_support_SOURCE_DIR})

    add_executable(ackermann_test main/ackermann_test.cpp)
    # Add the includes
    target_include_directories(ackermann_test PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main>
      $<INSTALL_INTERFACE:include>
    )
    # Link libraries to the test target
    target_link_libraries(ackermann_test
      PRIVATE
      core
      CookieMonsterDrive
      TeensyDebug
    )
    # Add hex and upload targets
    FlashMcu(ackermann_test ${MCU} ${mcu_support_SOURCE_DIR})

    add_executable(slip_test main/slip_test.cpp)
    # Add the includes
    target_include_directories(slip_test PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main>
      $<INSTALL_INTERFACE:include>
    )
    # Link libraries to the test target
    target_link_libraries(slip_test
      PRIVATE
      core
      CookieMonsterDrive
      TeensyDebug
    )
    # Add hex and upload targets
    FlashMcu(slip_test ${MCU} ${mcu_support_SOURCE_DIR})

    add_executable(IMU_test main/IMU_test.cpp)
    # Add the includes
    target_include_directories(IMU_test PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main>
      $<INSTALL_INTERFACE:include>
    )
    # Link libraries to the test target
    target_link_libraries(IMU_test
      PRIVATE
      IMU
      TeensyDebug
    )
    # Add hex and upload targets
    FlashMcu(IMU_test ${MCU} ${mcu_support_SOURCE_DIR})

    add_executable(driving main/driving.cpp)
    # Add the includes
    target_include_directories(driving PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main>
      $<INSTALL_INTERFACE:include>
    )
    # Link libraries to the test target
    target_link_libraries(driving
      PRIVATE
      core
      Navigation
      IMU
      TeensyDebug
    )
    # Add hex and upload targets
    FlashMcu(driving ${MCU} ${mcu_support_SOURCE_DIR})

    add_executable(VL53L5CX_test main/VL53L5CX_test.cpp)
    # Add the includes
    target_include_directories(VL53L5CX_test PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main>
      $<INSTALL_INTERFACE:include>
    )
    # Link libraries to the test target
    target_link_libraries(VL53L5CX_test
      PRIVATE
      core
      VL53L5CXExtended
      TeensyDebug
    )
    # Add hex and upload targets
    FlashMcu(VL53L5CX_test ${MCU} ${mcu_support_SOURCE_DIR})
  endif()
endif()
