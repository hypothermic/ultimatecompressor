#ifndef MAGTUBE_MACRO_H
#define MAGTUBE_MACRO_H

#define GENERATE_STRING(NAME) #NAME,
#define GENERATE_ENUM(NAME) NAME,

#define GENERATE_FUNC_ENUM(NAME)  \
         uc_arc_ ## NAME,

#define GENERATE_FUNC(NAME) \
        guchar* uc_arc_ ## NAME (guchar* input);

#define GENERATE_SWITCH(NAME) \
         case ## NAME: ## return [NAME]; break;

#endif //MAGTUBE_MACRO_H
