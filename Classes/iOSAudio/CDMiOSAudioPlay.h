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
    
}
-(void)playAudio;
-(void)AudioRecording;


@end
