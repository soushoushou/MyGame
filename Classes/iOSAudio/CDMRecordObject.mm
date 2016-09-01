//
//  CDMRecordObject.cpp
//  BullPoker
//
//  Created by 陈冬梅 on 16/9/1.
//
//

#include "CDMRecordObject.h"
#include "CDMiOSAudioPlay.h"

CDMiOSAudioPlay *m_audioPlay;

CDMRecordObject::CDMRecordObject(){
    m_audioPlay=[[CDMiOSAudioPlay alloc]init];
}

CDMRecordObject::~CDMRecordObject(){
    m_audioPlay=nil;
}

void CDMRecordObject::StartRecord(){
    [m_audioPlay AudioRecording];
}

void CDMRecordObject::StartPlay(){
    [m_audioPlay playAudio];
}