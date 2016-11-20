package com.android.audio;

import java.io.IOException;

import android.media.MediaPlayer;
import android.os.Environment;
import android.util.Log;

public class MP3Recorder {
	private static final String LOG_TAG = "MP3RecorderTest"; 
	
	final static MP3RecorderUtil recorder = new MP3RecorderUtil();
	
	//语音操作对象  
    private static MediaPlayer mPlayer = null;  
    private static String path = "";
	private static String playPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/AudioRecorder/voice.mp3";
    
	public static String recordAudio(){
		try {
			path = recorder.startRecording();
		} catch (IOException e) {
			Log.e(LOG_TAG, "start record failed！");
			e.printStackTrace();
		}
		Log.e(LOG_TAG, "start record success！");
		return path;
	}
	
	public static String stopAudio(){
		try {
			recorder.stopRecording();
		} catch (IOException e) {
			Log.e(LOG_TAG, "stop record failed!");
			e.printStackTrace();
		}
		Log.e(LOG_TAG, "stop record success!");
//		// 如果要关闭可以
//		util.close();
//		util = null;
		return path;
	}
	
	public static void playAudio(String voicePath){
		mPlayer = new MediaPlayer();  
        try{
        	mPlayer.reset();
            mPlayer.setDataSource(voicePath);
            mPlayer.prepare();  
            mPlayer.start();  
        }catch(IOException e){  
            Log.e(LOG_TAG,"播放失败");  
        } 
        Log.e(LOG_TAG,"播放成功");
	}
	
	public static String getAudioPath(){
		return playPath;
	}
}
