add_definitions(-DNGINTERFACE_EXPORTS)

add_library(mymesh ${NG_LIB_TYPE}
    mymeshclass.cpp
)

if(APPLE)
    set_target_properties( mesh PROPERTIES SUFFIX ".so")
endif(APPLE)

if(NOT WIN32)
    target_link_libraries( mymesh ${ZLIB_LIBRARIES} ${MPI_CXX_LIBRARIES} ${PYTHON_LIBRARIES} ${METIS_LIBRARY})
    install( TARGETS mymesh ${NG_INSTALL_DIR})
endif(NOT WIN32)

install(FILES
    mymeshclass.hpp
    DESTINATION ${NG_INSTALL_DIR_INCLUDE}/mymesh COMPONENT netgen_devel
)
