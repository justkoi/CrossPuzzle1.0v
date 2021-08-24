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


import java.util.Date;

import twitter4j.Status;
import twitter4j.Twitter;
import twitter4j.TwitterException;
import twitter4j.TwitterFactory;
import twitter4j.auth.RequestToken;
import twitter4j.conf.Configuration;
import twitter4j.conf.ConfigurationBuilder;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ImageButton;
import android.widget.Toast;

public class crosspuzzle extends Activity{
	
	public static final String TAG = "SampleTwitAppActivity";


	private static boolean bCheckPopup = false;
	// Button writeBtn;
	// EditText writeInput;
	
	protected void onCreate(Bundle savedInstanceState){
		setTheme(android.R.style.Theme_NoTitleBar_Fullscreen);
		super.onCreate(savedInstanceState);
		
		ImageButton connectBtn;
		ImageButton connectBtn2;
		
		
		setContentView(R.layout.main);

        connectBtn = (ImageButton) findViewById(R.id.imageButton1);
        connectBtn.setOnClickListener(new OnClickListener() {
        	public void onClick(View v) {
        		connect();
        	}
        });


        connectBtn2 = (ImageButton) findViewById(R.id.imageButton2);
        connectBtn2.setOnClickListener(new OnClickListener() {
        	public void onClick(View v) {
        		start();
        	}
        });


		
//		 facebook.authorize(this, new DialogListener() {
//	            @Override
//	            public void onComplete(Bundle values) {
//	            	
//	            }
//
//	            @Override
//	            public void onFacebookError(FacebookError error) {}
//
//	            @Override
//	            public void onError(DialogError e) {}
//
//	            @Override
//	            public void onCancel() {}
//	        });
		
		
//		// start Facebook Login
//        Session.openActiveSession(this, true, new Session.StatusCallback() {
//
//        @Override
//          // callback when session changes state
//          public void call(Session session, SessionState state, Exception exception) {
//            if (session.isOpened()) {
//
//              // make request to the /me API
//              Request.executeMeRequestAsync(session, new Request.GraphUserCallback() {
//
//            	 @Override
//                // callback after Graph API response with user object
//                public void onCompleted(GraphUser user, Response response) {
//                  
//                    //TextView welcome = (TextView) findViewById(R.id.tv);
//                    //welcome.setText("Hello " + user.getName() + "!");
//                	Intent intent = new Intent(crosspuzzle.this, game.class);
//                	crosspuzzle.this.startActivity(intent);
//                	
//                  
//                }
//              });
//            }
//          }
//        });
		
	}


//	@Override
//	public void onActivityResult(int requestCode, int resultCode, Intent data) {
//		  super.onActivityResult(requestCode, resultCode, data);
//		  Session.getActiveSession().onActivityResult(this, requestCode, resultCode, data);
//		  Intent intent = new Intent(crosspuzzle.this, game.class);
//      	  crosspuzzle.this.startActivity(intent);
//      	  finish();
//		}
//	
	
	private void updateStatus(String statusText) {
    	try {
    		Status status = BasicInfo.TwitInstance.updateStatus(statusText);
    		Date curDate = status.getCreatedAt();

    		Toast.makeText(getApplicationContext(), "글을 업데이트했습니다 : " + BasicInfo.DateFormat.format(curDate), 1000).show();


    	} catch(Exception ex) {
    		ex.printStackTrace();
    	}

    }
	private void start() {
		
		  Intent intent = new Intent(crosspuzzle.this, game.class);
	      crosspuzzle.this.startActivity(intent);
	      finish();
	      
	      Toast.makeText(getBaseContext(), "Guest님 안녕하세요! 환영합니다!", Toast.LENGTH_LONG).show();
			
	}

    private void connect() {
		Log.d(TAG, "connect() called.");

		if (BasicInfo.TwitLogin) {
			Log.d(TAG, "twitter already logged in.");
			Toast.makeText(getBaseContext(), "twitter already logged in.", Toast.LENGTH_LONG).show();

			try {
				ConfigurationBuilder builder = new ConfigurationBuilder();

				
				builder.setOAuthAccessToken(BasicInfo.TWIT_KEY_TOKEN);
				builder.setOAuthAccessTokenSecret(BasicInfo.TWIT_KEY_TOKEN_SECRET);
				builder.setOAuthConsumerKey(BasicInfo.TWIT_CONSUMER_KEY);
				builder.setOAuthConsumerSecret(BasicInfo.TWIT_CONSUMER_SECRET);

				Configuration config = builder.build();
				TwitterFactory tFactory = new TwitterFactory(config);
				BasicInfo.TwitInstance = tFactory.getInstance();

				Toast.makeText(getBaseContext(), "twitter connected.", Toast.LENGTH_LONG).show();

	    	} catch (Exception ex) {
				ex.printStackTrace();
			}


		} else {

	    	try {
				ConfigurationBuilder builder = new ConfigurationBuilder();
				builder.setDebugEnabled(true);
				builder.setOAuthConsumerKey(BasicInfo.TWIT_CONSUMER_KEY);
				builder.setOAuthConsumerSecret(BasicInfo.TWIT_CONSUMER_SECRET);

				TwitterFactory factory = new TwitterFactory(builder.build());
				Twitter mTwit = factory.getInstance();
				RequestToken mRequestToken = mTwit.getOAuthRequestToken();
				String outToken = mRequestToken.getToken();
				String outTokenSecret = mRequestToken.getTokenSecret();

				Log.d(TAG, "Request Token : " + outToken + ", " + outTokenSecret);
				Log.d(TAG, "AuthorizationURL : " + mRequestToken.getAuthorizationURL());

				BasicInfo.TwitInstance = mTwit;
				BasicInfo.TwitRequestToken = mRequestToken;

				Intent intent = new Intent(this, twitt_login.class);
				intent.putExtra("authUrl", mRequestToken.getAuthorizationURL());
				startActivityForResult(intent, BasicInfo.REQ_CODE_TWIT_LOGIN);

	    	} catch (Exception ex) {
				ex.printStackTrace();
			}

		}

    }
    @Override
	  public void onBackPressed(){
		  //super.onBackPressed();
	  }
	 @Override
	 public boolean dispatchKeyEvent(KeyEvent event) {
	  if(event.getKeyCode()==KeyEvent.KEYCODE_BACK) {
		
		  if(bCheckPopup == false)
		  {
			  new AlertDialog.Builder(this)
			  .setTitle("게임 종료")
		      .setMessage("종료하시겠습니까?")
		      .setCancelable(false)
		      .setPositiveButton("예", new DialogInterface.OnClickListener() {
		    	  @Override
		      public void onClick(DialogInterface dialog, int which) {    
		    	  System.exit(0);
		    	  bCheckPopup = false;
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
   @Override
     public void onActivityResult(int requestCode, int resultCode, Intent data) {
         super.onActivityResult(requestCode, resultCode, data);

         if(resultCode == RESULT_OK) 
		    {
        	 long t = System.currentTimeMillis(); 
        	 	try {
					Status status = BasicInfo.TwitInstance.updateStatus("[CrossPuzzle] 게임에 로그인했습니다. (" + String.valueOf(t).toString() + ")");
					
				} catch (TwitterException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
        	 	Toast.makeText(getBaseContext(), BasicInfo.TwitScreenName + "님 안녕하세요! 환영합니다!", Toast.LENGTH_LONG).show();
			
		    }
 		
         Intent intent = new Intent(crosspuzzle.this, game.class);
         crosspuzzle.this.startActivity(intent);
         finish();
     }


  
}
