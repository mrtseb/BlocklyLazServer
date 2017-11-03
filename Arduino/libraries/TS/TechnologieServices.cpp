/*
*Library Technologie Services
* Copyright © 2016 by Technologie Services. All rights reserved
Version 1
<http://www.technologieservices.fr>
*/



#include "TechnologieServices.h"

#define LED 13

TechnologieServices::TechnologieServices(){
	pinMode(LED,OUTPUT);
	state = false;
}
