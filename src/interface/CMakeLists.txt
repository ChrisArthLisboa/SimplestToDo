
file(GLOB SOURCES_C "*.c")
file(GLOB SOURCES_H "*.h")
add_library(

    interface

    ${SOURCES_C}
    ${SOURCES_H}

)

