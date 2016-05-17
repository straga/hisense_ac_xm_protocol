//
//  CByte.cpp
//  devices
//
//  Created by 肖芳亮 on 16/1/6.
//  Copyright © 2016年 xiaofangliang. All rights reserved.
//

#include "CByte.h"

CByte::CByte(char *data, int length)
{
    this->data = data;
    this->length = length;
}

CByte::CByte()
{
    
}

CByte::~CByte()
{
    this->data = NULL;
}

char* CByte::getData()
{
    return this->data;
}

int CByte::getLength()
{
    return this->length;
}