#ifndef MAGTUBE_MACRO_H
#define MAGTUBE_MACRO_H

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

#define GENERATE_SWITCH(NAME) \
         case ## NAME: ## return [NAME]; break;

#endif //MAGTUBE_MACRO_H
