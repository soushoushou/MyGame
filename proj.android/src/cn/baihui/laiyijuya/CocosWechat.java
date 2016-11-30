package cn.baihui.laiyijuya;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.tencent.mm.sdk.modelmsg.SendAuth;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

import android.os.Bundle;
import android.util.Log;

public class CocosWechat extends Cocos2dxActivity{
	
	private static IWXAPI wxapi;
	private static CocosWechat instance;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		Log.v("WeiChatLogin","WXEntryActivity  Register success ---------");
	}
	
	//登录微信
	public static void  loginWeixin(){
		Log.v("WeiChatLogin", "login-------------");
		
		wxapi = WXAPIFactory.createWXAPI(CocosWechat.getContext(), Constant.WEIXIN_APP_ID, true);
		
		wxapi.registerApp(Constant.WEIXIN_APP_ID);
		SendAuth.Req req = new SendAuth.Req();
		req.scope = "snsapi_userinfo";
		req.state = "wechat_sdk_demo";
		wxapi.sendReq(req);
		
		
	}
}
