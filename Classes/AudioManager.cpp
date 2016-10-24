//
//  AudioManager.cpp
//  BullPoker
//
//  Created by 陈冬梅 on 2016/10/23.
//
//

#include "AudioManager.h"
#include "NetworkManger.h"
static AudioManager* m_pInstance = NULL;

AudioManager* AudioManager::getInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new AudioManager;
    }
    return m_pInstance;
}

void AudioManager::fileConvertedToBinary_Send(const char *filePath){
    FILE *fp; char *str; long flength;
    fp = fopen(filePath, "rb");
    if (!fp)
    {
        log("!!FILE open ERROR \n");
        return;
    }
    
    fseek(fp, 0, SEEK_END);
    flength = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    str = (char*)malloc(flength * sizeof(char));
    assert(str != NULL);
    
    fread(str, flength, 1, fp);
    printf("%s\n", str);
    fclose(fp);
//    S_VoiceChatReq vcr(str, flength * sizeof(char));
//    NetworkManger::getInstance()->SendRequest_VoiceChat(vcr);
    data=str;
    length=flength;
    log("send audio file");
    free(str);
}

void AudioManager::binaryConvertedToFile_Rev(const char *filePath,const char* binaryData,long length){
    ofstream out(filePath,ios::binary);
    out.write(binaryData,length);
    out.close();
}






























