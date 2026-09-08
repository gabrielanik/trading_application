cmake_minimum_required(VERSION 3.19)
project(trading_application LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql Network)

qt_standard_project_setup()

qt_add_executable(trading_application
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h

    account.h account.cpp
    mainwindow.ui
    loginwindow.h
    main.h
    loginwindow.cpp
    loginwindow.ui

    .gitignore
    appflow.h appflow.cpp
    dbmanager.h dbmanager.cpp
    stockmanager.h stockmanager.cpp
    orderdialog.ui

)

target_link_libraries(trading_application
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
        Qt6::Network
)

install(TARGETS trading_application
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET trading_application
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
