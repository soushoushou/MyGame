//
//  CDMRecordObject.h
//  BullPoker
//
//  Created by 陈冬梅 on 16/9/1.
//
//

#ifndef CDMRecordObject_h
#define CDMRecordObject_h

#include <iostream>


USING_NS_CC;

class CDMRecordObject{
public:
    CDMRecordObject();
    ~CDMRecordObject();
    /**
     *  开始录音
     */
     void StartRecord();
    /**
     *  开始播放
     */
     void StartPlay();
    /**
     *  转码为MP3
     */
    void convertToMp3();
};

#endif