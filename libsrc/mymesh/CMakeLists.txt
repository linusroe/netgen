add_definitions(-DNGINTERFACE_EXPORTS)
if(NOT WIN32)
    set(mymesh_object_libs 
        $<TARGET_OBJECTS:la>
        $<TARGET_OBJECTS:gprim>
        $<TARGET_OBJECTS:gen>
        )
endif(NOT WIN32)

add_library(mymesh ${NG_LIB_TYPE}
    mymeshclass.cpp
    ${mymesh_object_libs}

)

if(APPLE)
    set_target_properties( mymesh PROPERTIES SUFFIX ".so")
endif(APPLE)

if(NOT WIN32)
    target_link_libraries( mymesh ${ZLIB_LIBRARIES} ${MPI_CXX_LIBRARIES} ${PYTHON_LIBRARIES} ${METIS_LIBRARY})
    install( TARGETS mymesh ${NG_INSTALL_DIR})
endif(NOT WIN32)

install(FILES
    mymeshclass.hpp
    DESTINATION ${NG_INSTALL_DIR_INCLUDE}/mymesh COMPONENT netgen_devel
)
