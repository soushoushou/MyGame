package com.video.android;

import java.io.IOException;

import android.graphics.Path;
import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.os.Environment;
import android.util.Log;

public class Audio {
	private static final String LOG_TAG = "AudioRecordTest"; 
	
	//语音操作对象  
    private static MediaPlayer mPlayer = null;  
	private static MediaRecorder mRecorder = null;  
	private static String path = Environment.getExternalStorageDirectory().getAbsolutePath() + "/ione.pcm";
	
	public static void recordAudio(){
		
		mRecorder = new MediaRecorder();  
		//设置音源为Micphone 
        mRecorder.setAudioSource(MediaRecorder.AudioSource.MIC); 
        //设置封装格式 
        mRecorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);  
        mRecorder.setOutputFile(path);  
        //设置编码格式
        mRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);  
        try {  
            mRecorder.prepare();  
        } catch (IOException e) {  
            Log.e(LOG_TAG, "prepare() failed");  
        }  
        mRecorder.start();
        Log.e(LOG_TAG, "start record！");
         
	}
	
	public static void startPlay(){
		mRecorder.stop();  
        mRecorder.release();  
        mRecorder = null;
        mPlayer = new MediaPlayer();  
        try{  
            mPlayer.setDataSource(path);  
            mPlayer.prepare();  
            mPlayer.start();  
        }catch(IOException e){  
            Log.e(LOG_TAG,"播放失败");  
        } 
        Log.e(LOG_TAG,"播放成功");  
	}
}
