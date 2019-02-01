#ifndef _MESSAGEBOX_
#define _MESSAGEBOX_

#include "common.h"
#include "functions.h"

#include <string>

//this should only be called after vita2d_init(). 
//calls vita2d_end_drawing() when finished. 
//make sure to start drawing again. 
extern bool makeYesNoBox(std::string message, std::string message1, std::string message2);

#endif