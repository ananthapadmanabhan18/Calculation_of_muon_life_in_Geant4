cmake_minimum_required(VERSION 3.16...3.28)
project(MUON_LIFE_TIME)


option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# find_package(ROOT REQUIRED COMPONENTS RIO Net)
# include(${ROOT_USE_FILE})

add_executable(simulation simulation.cc ${sources} ${headers})
target_link_libraries(simulation PRIVATE ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})




set(SIMULATION_SCRIPTS
  init_vis.mac
  run.mac
  vis.mac
  )

foreach(_script ${SIMULATION_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/Macros/${_script}
    ${PROJECT_BINARY_DIR}/Release/${_script}
    COPYONLY
    )
endforeach()

add_custom_target(MUON_LIFE_TIME DEPENDS simulation)


install(TARGETS simulation DESTINATION bin)
