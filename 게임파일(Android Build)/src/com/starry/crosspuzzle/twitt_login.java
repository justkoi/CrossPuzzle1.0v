/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.starry.crosspuzzle;

import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.auth.AccessToken;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.EditText;
import android.widget.Toast;

public class twitt_login extends Activity{
	
	 Intent mIntent;

	private static boolean bCheckPopup = false;
	protected void onCreate(Bundle savedInstanceState){
		setTheme(android.R.style.Theme_NoTitleBar_Fullscreen);
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.twit_login);
		EditText et = (EditText)findViewById(R.id.editText1);
		et.setFocusable(false);
		et.setFocusableInTouchMode(false);
		WebView webview = (WebView) findViewById(R.id.webView);
		webview.getSettings().setJavaScriptEnabled(true);
		webview.addJavascriptInterface(new JavaScriptInterface(), "PINCODE");
		
		webview.setWebViewClient(new WebViewClient() {
			public void onPageFinished(WebView view, String url) {
				super.onPageFinished(view, url);


				EditText et = (EditText)findViewById(R.id.editText1);
				et.setFocusable(true);
				et.setFocusableInTouchMode(true);
				
				if (url != null && url.equals("http://mobile.twitter.com/")) {
					finish();
				} else if (url != null && url.startsWith(BasicInfo.TWIT_CALLBACK_URL)) {
					String[] params = url.split("\\?")[1].split("&");
					String oauthToken = "";
					String oauthVerifier = "";

					try {
						if (params[0].startsWith("oauth_token")) {
							oauthToken = params[0].split("=")[1];
						} else if (params[1].startsWith("oauth_token")) {
							oauthToken = params[1].split("=")[1];
						}

						if (params[0].startsWith("oauth_verifier")) {
							oauthVerifier = params[0].split("=")[1];
						} else if (params[1].startsWith("oauth_verifier")) {
							oauthVerifier = params[1].split("=")[1];
						}

						Intent resultIntent = new Intent();
						resultIntent.putExtra("oauthToken", oauthToken);
						resultIntent.putExtra("oauthVerifier", oauthVerifier);

						setResult(RESULT_OK, resultIntent);
						finish();
					} catch (Exception e)
					{
						e.printStackTrace();
					}
				}
				//view.loadUrl("javascript:window.PINCODE.getPinCode(document.getElementById('oauth_pin').innerHTML);");
			
				//finish();
			}
		});


		Intent passedIntent = getIntent();
		String authUrl = passedIntent.getStringExtra("authUrl");
		webview.loadUrl(authUrl);
		
	}
	
	@Override
	 public boolean dispatchKeyEvent(KeyEvent event) {
	  if(event.getKeyCode()==KeyEvent.KEYCODE_BACK) {
		
		  if(bCheckPopup == false)
		  {
			  new AlertDialog.Builder(this)
			  .setTitle("로그인 취소")
		      .setMessage("트위터 로그인을 취소하시겠습니까?")
		      .setCancelable(false)
		      .setPositiveButton("예", new DialogInterface.OnClickListener() {
		    	  @Override
		      public void onClick(DialogInterface dialog, int which) {    
		    	  finish();
		    	  bCheckPopup = false;
		    	  Toast.makeText(getBaseContext(), "Guest님 안녕하세요! 환영합니다!", Toast.LENGTH_LONG).show();
		       }
		      })
		      .setNegativeButton("아니요", new DialogInterface.OnClickListener() {
		    	  @Override
		       public void onClick(DialogInterface dialog, int which) {
		        dialog.cancel();
		        bCheckPopup = false;
		       }
		      })
		      .show();
			  bCheckPopup = true;
		  }
	     
	   return true;
	  }
	  else {
	   return super.dispatchKeyEvent(event);
	  }
	 }
	public void Button1(View v){
	
		Twitter mTwit = BasicInfo.TwitInstance;
		
		EditText et = (EditText)findViewById(R.id.editText1);
		String pin = et.getText().toString();
		AccessToken accessToken = null;
		
		try {
			accessToken = mTwit.getOAuthAccessToken(BasicInfo.TwitRequestToken,pin);
		} catch (TwitterException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		mTwit.setOAuthAccessToken(accessToken);
		
		try {
			BasicInfo.TwitLogin = true;
			BasicInfo.TWIT_KEY_TOKEN = accessToken.getToken();
			BasicInfo.TWIT_KEY_TOKEN_SECRET = accessToken.getTokenSecret();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			setResult(0, mIntent);
			finish();
			
			Toast.makeText(getBaseContext(), "인증실패! Guest계정으로 로그인 합니다! 환영합니다!", Toast.LENGTH_LONG).show();
		}
		
//
		BasicInfo.TwitAccessToken = accessToken;
//
		try {
			BasicInfo.TwitScreenName = mTwit.getScreenName();
		} catch (IllegalStateException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (TwitterException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		setResult(RESULT_OK, mIntent);
		finish();
	}

	  class JavaScriptInterface
	  {
	    public void getPinCode(String pin)
	    {
	      if (pin.length() > 0)
	      {
	        mIntent.putExtra("pin_code", pin);
	        setResult(RESULT_OK, mIntent);
	        finish();
	      }
	      else
	      {
	        Log.v("GG", "get pin failed...");
	      }
	    }
	  }
	  
	  @Override
	  public void onBackPressed(){
		  //super.onBackPressed();
	  }
	
}
