# Translations

SET(translated_languages ru)

FIND_PACKAGE(Gettext REQUIRED)

FILE(GLOB gettext_source_files ${CMAKE_SOURCE_DIR}/src/*.c)
FIND_PROGRAM(XGETTEXT xgettext)
IF(NOT "${XGETTEXT}" STREQUAL "XGETTEXT-NOTFOUND")
	ADD_CUSTOM_COMMAND(OUTPUT po/messages.pot
		COMMAND ${XGETTEXT}
			--directory="${CMAKE_SOURCE_DIR}"
			--keyword=_
			--language=C
			--add-comments
			--sort-output
			--from-code=UTF-8
			--package-name="${PROJECT_NAME}"
			--package-version="${OVPN_CONVERT_VERSION}"
			-o "${CMAKE_SOURCE_DIR}/po/messages.pot"
			${SOURCES}
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
		DEPENDS ${gettext_source_files}
	)
	ADD_CUSTOM_TARGET(update-pot DEPENDS "po/messages.pot")
ENDIF()

SET(po_files)
FOREACH(language ${translated_languages})
	LIST(APPEND po_files "${CMAKE_CURRENT_BINARY_DIR}/${language}.po")
	ADD_CUSTOM_COMMAND(OUTPUT "${language}.po"
		COMMAND ${GETTEXT_MSGMERGE_EXECUTABLE}
			--update ${language}.po messages.pot
		DEPENDS "messages.pot"
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
ENDFOREACH(language)
ADD_CUSTOM_TARGET(update-po ALL DEPENDS ${po_files})

SET(mo_files)
FOREACH(language ${translated_languages})
	LIST(APPEND mo_files "${CMAKE_CURRENT_BINARY_DIR}/${language}.mo")
	ADD_CUSTOM_COMMAND(OUTPUT "${language}.mo"
		COMMAND ${GETTEXT_MSGFMT_EXECUTABLE}
			--use-fuzzy
			-o "${CMAKE_CURRENT_BINARY_DIR}/${language}.mo"
			"${language}.po"
		DEPENDS "${language}.po"
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
	INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/${language}.mo"
		RENAME "${PROJECT_NAME}.mo"
		DESTINATION "${CMAKE_INSTALL_LOCALEDIR}/${language}/LC_MESSAGES/"
	)
ENDFOREACH(language)
ADD_CUSTOM_TARGET(update-mo ALL DEPENDS ${mo_files})
