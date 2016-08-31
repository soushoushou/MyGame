//
//  CDMiOSAudioPlay.m
//  BullPoker
//
//  Created by 陈冬梅 on 16/8/31.
//
//

#import "CDMiOSAudioPlay.h"

@implementation CDMiOSAudioPlay

extern  BOOL isRecording;

-(void)playAudio
{
    isRecording = NO;
    [recorder stop];
    recorder = nil;
    NSError *playerError;
    player = [[AVAudioPlayer alloc] initWithContentsOfURL:recordedFile error:&playerError];
    if (player == nil)
    {
        NSLog(@"创建player: %@失败!", [playerError description]);
    }
    else{
        player.delegate = self;
         NSLog(@"开始录音播放");
        [player play];
    }
}

-(void)AudioRecording
{
    NSString *path = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/pokerAudio.caf"];
    NSFileManager* fileManager=[NSFileManager defaultManager];
    if([fileManager removeItemAtPath:path error:nil])
    {
        NSLog(@"删除原录音");
    }
    recordedFile=[[NSURL alloc]initFileURLWithPath:path];
    AVAudioSession *session = [AVAudioSession sharedInstance];
    NSError *sessionError;
    [session setCategory:AVAudioSessionCategoryPlayAndRecord error:&sessionError];
    
    if(session == nil)
        NSLog(@"创建session: %@失败!", [sessionError description]);
    else
        [session setActive:YES error:nil];
    
    if(!isRecording)
    {
        isRecording = YES;
        NSLog(@"正在录音");
        recorder = [[AVAudioRecorder alloc] initWithURL:recordedFile settings:[self getVoiceRecordSetting] error:nil];
        [recorder prepareToRecord];
        [recorder record];
        player = nil;
    }
}

-(NSMutableDictionary*)getVoiceRecordSetting
{
    //录音设置
    NSMutableDictionary *settings = [[NSMutableDictionary alloc] init];
    //录音格式 无法使用
    [settings setValue :[NSNumber numberWithInt:kAudioFormatLinearPCM] forKey: AVFormatIDKey];
    //采样率
    [settings setValue :[NSNumber numberWithFloat:8000.0] forKey: AVSampleRateKey];//44100.0
    //通道数
    [settings setValue :[NSNumber numberWithInt:2] forKey: AVNumberOfChannelsKey];
    //线性采样位数
    [settings setValue :[NSNumber numberWithInt:16] forKey: AVLinearPCMBitDepthKey];
    //音频质量,采样质量
    [settings setValue:[NSNumber numberWithInt:AVAudioQualityMin] forKey:AVEncoderAudioQualityKey];
    
    return settings;
}


@end
