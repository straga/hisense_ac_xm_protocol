//
//  CByte.hpp
//  devices
//
//  Created by 肖芳亮 on 16/1/6.
//  Copyright © 2016年 xiaofangliang. All rights reserved.
//

#ifndef CByte_h
#define CByte_h

#include <stdio.h>

class CByte
{
    
private:
    
    char *data;     //字节数据
    
    int length;     //字节数据的长度
    
public:
    
    CByte(char *data, int length);
    
    CByte();
    
    ~CByte();
    
    char *getData();
    
    int getLength();
};

#endif /* CByte_h */
