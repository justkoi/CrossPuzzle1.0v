package com.starry.crosspuzzle;

import java.text.SimpleDateFormat;

import twitter4j.Twitter;
import twitter4j.auth.AccessToken;
import twitter4j.auth.RequestToken;

public class BasicInfo {

	public static final String TWIT_API_KEY = "LrIG5bA8giM6spJUzajg";
	public static final String TWIT_CONSUMER_KEY = "LrIG5bA8giM6spJUzajg";
	public static final String TWIT_CONSUMER_SECRET = "qxKg43ctkZRYe0D2qmwrut7z6IkxpyixHDdL69I";
	public static final String TWIT_CALLBACK_URL = "http://www.gmae.hs.kr";

	public static final int REQ_CODE_TWIT_LOGIN = 1001;

	public static boolean TwitLogin = false;
	public static Twitter TwitInstance = null;
	public static AccessToken TwitAccessToken = null;
	public static RequestToken TwitRequestToken = null;

	public static String TWIT_KEY_TOKEN = "";
	public static String TWIT_KEY_TOKEN_SECRET = "";
	public static String TwitScreenName = "";

	public static SimpleDateFormat DateFormat = new SimpleDateFormat("yyyy년 MM월 dd일 HH시 mm분");

}
