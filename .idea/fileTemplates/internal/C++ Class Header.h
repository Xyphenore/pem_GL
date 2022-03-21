#parse("C File Header.h")
#[[#ifndef]]# ${INCLUDE_GUARD}
#[[#define]]# ${INCLUDE_GUARD}

#[[#ifndef]]# __cplusplus
#[[#error]]# Un compilateur C++ est nécessaire.
#[[#endif]]#

#[[#if]]# __cplusplus < 201703L
#[[#error]]# GL_Engine a été développée pour C++17. Veuillez supprimer cette condition est testé le code à vos risques et périls.
#[[#endif]]#

${NAMESPACES_OPEN}

class ${NAME} {

};

${NAMESPACES_CLOSE}

#[[#endif]]# // ${INCLUDE_GUARD}
