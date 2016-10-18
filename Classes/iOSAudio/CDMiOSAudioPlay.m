//
//  CDMiOSAudioPlay.m
//  BullPoker
//
//  Created by 陈冬梅 on 16/8/31.
//
//

#import "CDMiOSAudioPlay.h"
#import "lame.h"
@implementation CDMiOSAudioPlay

extern  BOOL isRecording;


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

#pragma mark- 转码
- (void)audio_PCMtoMP3
{
    NSString *cafFilePath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/pokerAudio.caf"];
    
    NSString *mp3FilePath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/pokerAudio.mp3"];
    
    
    NSFileManager* fileManager=[NSFileManager defaultManager];
    if([fileManager removeItemAtPath:mp3FilePath error:nil])
    {
        NSLog(@"删除");
    }
    
    @try {
        int read, write;
        
        FILE *pcm = fopen([cafFilePath cStringUsingEncoding:1], "rb");  //source 被转换的音频文件位置
        if (pcm==nil) {
            NSLog(@"pcm为空");
            
            return;
        }
        fseek(pcm, 4*1024, SEEK_CUR);                                   //skip file header
        FILE *mp3 = fopen([mp3FilePath cStringUsingEncoding:1], "wb");  //output 输出生成的Mp3文件位置
        
        const int PCM_SIZE = 8192;
        const int MP3_SIZE = 8192;
        short int pcm_buffer[PCM_SIZE*2];
        unsigned char mp3_buffer[MP3_SIZE];
        
        lame_t lame = lame_init();
        lame_set_in_samplerate(lame, 8000.0);
        lame_set_VBR(lame, vbr_default);
        lame_init_params(lame);
        
        do {
            read = fread(pcm_buffer, 2*sizeof(short int), PCM_SIZE, pcm);
            if (read == 0)
                write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
            else
                write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
            
            fwrite(mp3_buffer, write, 1, mp3);
            
        } while (read != 0);
        
        lame_close(lame);
        fclose(mp3);
        fclose(pcm);
    }
    @catch (NSException *exception) {
        NSLog(@"%@",[exception description]);

    }
    @finally {
        NSURL*audioPathURL=[[NSURL alloc] initFileURLWithPath:mp3FilePath];
        NSData *audiodata=[NSData dataWithContentsOfURL:audioPathURL];
        binayData=[audiodata bytes];
        [self playAudio_BinayData];
    }
}
#pragma mark-播放本地文件
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

#pragma mark-播放二进制文件
-(void)playAudio_BinayData{
    isRecording = NO;
    [recorder stop];
    recorder = nil;
//    char * a = (char*)malloc(sizeof(Byte)*16);
    NSData *data = [NSData dataWithBytes: binayData   length:strlen(binayData)];
    NSString *mp3FilePath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents/playAudio.mp3"];
    NSURL*videoPathURL=[[NSURL alloc]initFileURLWithPath:mp3FilePath];
    [data writeToURL:videoPathURL options:NSAtomicWrite error:nil];
    NSError *playerError;
    player = [[AVAudioPlayer alloc] initWithContentsOfURL:videoPathURL error:&playerError];
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
@end
