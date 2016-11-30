package cn.baihui.laiyijuya.wxapi;

import cn.baihui.laiyijuya.Constant;
import cn.baihui.laiyijuya.WeiXinLogin;

import org.cocos2dx.cpp.AppActivity;

import com.tencent.mm.sdk.constants.ConstantsAPI;
import com.tencent.mm.sdk.modelbase.BaseReq;
import com.tencent.mm.sdk.modelbase.BaseResp;
import com.tencent.mm.sdk.modelmsg.SendAuth;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

public class WXEntryActivity extends Activity implements IWXAPIEventHandler{
	private static IWXAPI wxapi;
	private static AppActivity instance;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		//注册到微信
		wxapi = WXAPIFactory.createWXAPI(this, Constant.WEIXIN_APP_ID, true);
		wxapi.handleIntent(getIntent(), this);
	
		Log.v("WeiChatLogin","WXEntryActivity  onCreate ---------");
	}

	// 微信发送请求到第三方应用时，会回调到该方法
	@Override
	public void onReq(BaseReq req) {
		// TODO Auto-generated method stub
		finish();
		Log.v("WeiChatLogin", "onReq++++++++++++");
	}

	// 第三方应用发送到微信的请求处理后的响应结果，会回调到该方法
	@Override
	public void onResp(BaseResp resp) {
		// TODO Auto-generated method stub
		Log.v("WeiChatLogin", "onResp-------------");
		String result = "";
		switch (resp.errCode) {
		case BaseResp.ErrCode.ERR_OK:
			if (resp.getType() == ConstantsAPI.COMMAND_SENDAUTH)//登陆回调
			{
				Log.v("", "this is WXLogin callBack .... ");
                String code = ((SendAuth.Resp) resp).code; // 这里的code就是接入指南里要拿到的code
                new WeiXinLogin(this).getWeiXinInfo(code);
                
                Toast.makeText(this, "onResp------------- " + code, 6000).show();
              //这里写获取到code之后的事件
			} else if (resp.getType() == ConstantsAPI.COMMAND_SENDMESSAGE_TO_WX)//分享回调
			{
				Log.v("", "this is share callBack .... ");
			}
			finish();//必须要有，用于点击返回游戏的时候不会留在微信
			break;
			
		case BaseResp.ErrCode.ERR_USER_CANCEL:
			Log.v("WeiChatLogin", "login----ERR_USER_CANCEL-");
            break;
            
		case BaseResp.ErrCode.ERR_AUTH_DENIED:
            Log.v("WeiChatLogin", "login----ERR_AUTH_DENIED-");
            break;   
            
		default:
			Log.v("WeiChatLogin", "login--unknown---");
			break;
		}
	}
	
	@Override
	protected void onNewIntent(Intent intent) {
		// TODO Auto-generated method stub
		super.onNewIntent(intent);
		setIntent(intent);
		wxapi.handleIntent(intent, this);
		finish();
	}

}
