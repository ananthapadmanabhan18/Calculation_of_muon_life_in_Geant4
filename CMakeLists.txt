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


add_executable(simulation simulation.cc ${sources} ${headers})
target_link_libraries(simulation ${Geant4_LIBRARIES})



set(SIMULATION_SCRIPTS
  init_vis.mac
  run.mac
  vis.mac
  energy_dist.root
  )

foreach(_script ${SIMULATION_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/Release/${_script}
    COPYONLY
    )
endforeach()

add_custom_target(MUON_LIFE_TIME DEPENDS simulation)


install(TARGETS simulation DESTINATION bin)
