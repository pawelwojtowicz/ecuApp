project ( deployConfigurationFiles )


if (DEFINED ECUAPP_INSTALL_ROOT )
SET( ECUAPP_CONFIGURATION_PATH /etc/opt )
SET( ECUAPP_SERVER_DIR /srv/www )

# create directories
install ( DIRECTORY DESTINATION ${ECUAPP_CONFIGURATION_PATH} )
install ( DIRECTORY DESTINATION ${ECUAPP_SERVER_DIR}/cgi-bin )

install ( DIRECTORY ${ECUAPP_ROOT_DIR}/Configuration/ DESTINATION ${ECUAPP_CONFIGURATION_PATH} )
install ( DIRECTORY ${ECUAPP_ROOT_DIR}/HTMLSource/ DESTINATION ${ECUAPP_SERVER_DIR} )
else ()
	message ("Configuration and HTTP sources are not installed (ECUAPP_INSTALL_ROOT not defined)")
endif ()
