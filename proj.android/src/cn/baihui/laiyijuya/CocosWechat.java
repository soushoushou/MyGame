package cn.baihui.laiyijuya;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.tencent.mm.sdk.modelmsg.SendAuth;
import com.tencent.mm.sdk.modelmsg.SendMessageToWX;
import com.tencent.mm.sdk.modelmsg.WXMediaMessage;
import com.tencent.mm.sdk.modelmsg.WXWebpageObject;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

public class CocosWechat extends Cocos2dxActivity{
	
	private static IWXAPI wxapi;
	//private static CocosWechat instance = (CocosWechat) CocosWechat.getContext();
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		Log.v("WeiChatLogin","WXEntryActivity  Register success ---------");
	}
	
	//注册到微信
	public static void regToWeixin(){
		Log.v("WeiChat", "register------begin-------");
		wxapi = WXAPIFactory.createWXAPI(CocosWechat.getContext(), Constant.WEIXIN_APP_ID, true);	
		wxapi.registerApp(Constant.WEIXIN_APP_ID);
		Log.v("WeiChat", "register------end-------");
	}
	
	//登录微信
	public static void  loginWeixin(){
		Log.v("WeiChatLogin", "login-------------");
		
		regToWeixin();
		
		SendAuth.Req req = new SendAuth.Req();
		req.scope = "snsapi_userinfo";
		req.state = "wechat_sdk_demo";
		wxapi.sendReq(req);
		
	}
	
	//发送给好友或者群聊
	public static void sendMsgToFriend(){
		Log.v("WeiChat", "sendMsgToFriend------begin-------");
		
		regToWeixin();
		
		if(wxapi.openWXApp()){
			
			WXWebpageObject webpage = new WXWebpageObject();
			webpage.webpageUrl = "http://www.baidu.com";
			WXMediaMessage msg = new WXMediaMessage(webpage);
			msg.title = "来一局游戏分享";
			msg.description = "来自来一局牛牛游戏分享测试";

			Bitmap thumb = BitmapFactory.decodeResource(CocosWechat.getContext().getResources(), R.drawable.icon); // 解析图标，就是分享到微信的那个title图标
			msg.thumbData = WeiXinShare.bmpToByteArray(thumb, true);

			SendMessageToWX.Req req = new SendMessageToWX.Req();
			req.transaction = WeiXinShare.buildTransaction("webpage");
			req.message = msg;
			req.scene = SendMessageToWX.Req.WXSceneSession;
			wxapi.sendReq(req);
			
		}else {
			Toast.makeText(CocosWechat.getContext(), "未安装微信", Toast.LENGTH_SHORT).show();
		}
	}
	
}
