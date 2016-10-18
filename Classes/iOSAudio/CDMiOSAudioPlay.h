//
//  CDMiOSAudioPlay.h
//  BullPoker
//
//  Created by 陈冬梅 on 16/8/31.
//
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
@interface CDMiOSAudioPlay : NSObject<AVAudioPlayerDelegate>
{
    NSURL *recordedFile;
    AVAudioPlayer *player;
    AVAudioRecorder *recorder;
    char *binayData;
    
}
/**
 *  播放录音
 */
-(void)playAudio;
/**
 *  开始录音
 */
-(void)AudioRecording;
/**
 *  转码
 */
- (void)audio_PCMtoMP3;

@end
