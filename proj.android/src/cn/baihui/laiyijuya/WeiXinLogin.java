package cn.baihui.laiyijuya;

import org.apache.http.Header;
import org.json.JSONException;
import org.json.JSONObject;

import com.loopj.android.http.AsyncHttpClient;
import com.loopj.android.http.AsyncHttpResponseHandler;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

public class WeiXinLogin {
	private Context context;

	public WeiXinLogin(Context context) {
		this.context = context;
	}

	public void getWeiXinInfo(String code) {
		Log.d("", "getWeiXinOpenId------------------------");

		String getWeiXinOpenIdUrl = "https://api.weixin.qq.com/sns/oauth2/access_token?" + "appid="
				+ Constant.WEIXIN_APP_ID + "&secret=" + Constant.WEIXIN_APP_SECRET + "&code=" + code
				+ "&grant_type=authorization_code";
		new AsyncHttpClient().get(getWeiXinOpenIdUrl, new AsyncHttpResponseHandler() {

			@Override
			public void onSuccess(int statusCode, Header[] headers, byte[] responseBody) {
				String result = new String(responseBody);
				Log.d("", "result----------getWeiXinOpenId------------" + result);

				try {
					JSONObject object = new JSONObject(result);
					String openId = object.getString("openid");
					String accessToken = object.getString("access_token");
					Log.d("", "WeiXinLogin,openId:" + openId + ", accessToken:" + accessToken);
					Toast.makeText(context, result, Toast.LENGTH_SHORT).show();
				} catch (JSONException e) {
					e.printStackTrace();
				}
			}

			@Override
			public void onFailure(int arg0, Header[] arg1, byte[] arg2, Throwable arg3) {
				Log.d("", "result---------------------failure------------");
			}
		});
	}
	
	public void getUID(final String openId, final String accessToken) {
		Log.d("", "getWeiXinOpenId------------------------");

		String getWeiXinUIDUrl = "https://api.weixin.qq.com/sns/userinfo?access_token="
				+ accessToken + "&openid=" + openId;
		new AsyncHttpClient().get(getWeiXinUIDUrl, new AsyncHttpResponseHandler() {

			@Override
			public void onSuccess(int statusCode, Header[] headers, byte[] responseBody) {
				String result = new String(responseBody);
				Log.d("", "result----------getWeiXinOpenId------------" + result);

				try {
					JSONObject jsonObject = new JSONObject(result);
					String nickname = jsonObject.getString("nickname");
                    String openid = jsonObject.getString("openid");
                    String sex = jsonObject.getString("sex");
                    String province = jsonObject.getString("province");	//省份
                    String country = jsonObject.getString("country");
                    String headimgurl = jsonObject.getString("headimgurl");//头像
                    String unionid = jsonObject.getString("unionid");
                    
                    Log.i("", "nickname = " + nickname);
                    Log.i("", "unionid = " + unionid);
				} catch (JSONException e) {
					e.printStackTrace();
				}
			}

			@Override
			public void onFailure(int arg0, Header[] arg1, byte[] arg2, Throwable arg3) {
				Log.d("", "result---------------------failure------------");
			}
		});
	}
}
