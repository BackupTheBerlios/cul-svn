CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)

# LOWER UPPER ATOM
SET(TEMPLATE_CHAR    "c C char TEMPLATE_CHAR")
SET(TEMPLATE_DOUBLE  "d D double TEMPLATE_DOUBLE")
SET(TEMPLATE_INT     "i I int TEMPLATE_INT")
SET(TEMPLATE_CUL_PTR "p P cul_ptr TEMPLATE_CUL_PTR")
SET(TEMPLATE_SIZE_T  "u U size_t TEMPLATE_SIZE_T")

SET(TEMPLATE_ALL ${TEMPLATE_CHAR} ${TEMPLATE_DOUBLE} ${TEMPLATE_INT}
    ${TEMPLATE_CUL_PTR} ${TEMPLATE_SIZE_T})
SET(TEMPLATE_BASIC ${TEMPLATE_CHAR} ${TEMPLATE_DOUBLE} ${TEMPLATE_INT}
    ${TEMPLATE_SIZE_T})

# configuration of templates
SET(TEMPLATE_FIELD      "[^ ]+")
SET(TEMPLATE_PREFIX     "cul_")
SET(TEMPLATE_BASE       "^${TEMPLATE_PREFIX}([^.]+)\\.h\\.in$")
SET(TEMPLATE_EXTENSION  ".h")

MACRO(CUL_TEMPLATE_FILE InputFile OutputFile Template)
    # extract all parts of template
    STRING(REGEX MATCHALL ${TEMPLATE_FIELD} Macros ${Template})

    LIST(GET Macros 0 LOWER)
    LIST(GET Macros 1 UPPER)
    LIST(GET Macros 2 ATOM)
    LIST(GET Macros 3 TEMPLATE)

    # set output flag
    SET(Output 1)

    # load file and clean output file
    FILE(STRINGS ${InputFile} InputContents)
    FILE(REMOVE ${OutputFile})

    # initialize loop
    SET(LineNr 0)
    LIST(LENGTH InputContents Lines)
    SET(OutputContents)

    WHILE(${LineNr} LESS ${Lines})
        LIST(GET InputContents ${LineNr} Line)

        # process output directive
        IF(Line MATCHES "^[#]cmake([^ ]+)( [A-Za-z_]+$)?$")
            IF("ifdef" STREQUAL "${CMAKE_MATCH_1}")
                MESSAGE("${CMAKE_MATCH_1}")
                IF(" ${TEMPLATE}" STREQUAL ${CMAKE_MATCH_2})
                    SET(Output 1)
                ENDIF()
            ELSEIF("ifndef" STREQUAL "${CMAKE_MATCH_1}")
                IF(" ${TEMPLATE}" STREQUAL ${CMAKE_MATCH_2})
                    SET(Output 0)
                ENDIF()
            ELSEIF("else" STREQUAL ${CMAKE_MATCH_1})
                IF(Output)
                    SET(Output 0)
                ELSE()
                    SET(Output 1)
                ENDIF()
            ELSEIF("endif" STREQUAL ${CMAKE_MATCH_1})
                SET(Output 1)
            ENDIF()
        ELSEIF(Output)
            STRING(REPLACE "\@LOWER\@" ${LOWER} Line "${Line}")
            STRING(REPLACE "\@UPPER\@" ${UPPER} Line "${Line}")
            STRING(REPLACE "\@ATOM\@" ${ATOM} Line "${Line}")
            FILE(APPEND ${OutputFile} "${Line}\n")
        ENDIF()

        MATH(EXPR LineNr "${LineNr} + 1")
    ENDWHILE()
ENDMACRO(CUL_TEMPLATE_FILE)

MACRO(CUL_TEMPLATE_HEADER InputFile OutputDir Templates)
    # extract file base
    GET_FILENAME_COMPONENT(FileName ${InputFile} NAME)

    # process type of file
    SET(FilePrefix ${TEMPLATE_PREFIX})
    SET(FileExtension ${TEMPLATE_EXTENSION})
    STRING(REGEX REPLACE ${TEMPLATE_BASE} "\\1" FileBase ${FileName})

    # write status information
    MESSAGE(STATUS "Processing template: ${FileName}")

    FOREACH(Template ${Templates})
        # extract template Id (or LOWER macro)
        STRING(REGEX MATCH ${TEMPLATE_FIELD} Id ${Template})

        # set output file name
        SET(OutputName "${FilePrefix}${Id}${FileBase}${FileExtension}")
        SET(OutputFile "${OutputDir}/${OutputName}")

        # process template
        MESSAGE(STATUS "Writing template: ${OutputName}")
        CUL_TEMPLATE_FILE(${InputFile} ${OutputFile} ${Template})
    ENDFOREACH(Template)
ENDMACRO(CUL_TEMPLATE_HEADER)

