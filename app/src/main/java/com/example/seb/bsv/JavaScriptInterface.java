package com.example.seb.bsv;

import android.util.Log;
import android.webkit.JavascriptInterface;

import com.integreight.onesheeld.sdk.OneSheeldDevice;

public class JavaScriptInterface
{
    private OneSheeldDevice arduino;

    public JavaScriptInterface(OneSheeldDevice arduino)
    {
        this.arduino = arduino;
    }

    @JavascriptInterface
    public void sendMessage(final String message)
    {
        new Thread(new Runnable()
        {
            public void run()
            {
                Log.i(this.getClass().getName(), "Message send : " + message.concat("0"));
                byte[] data = message.concat("0").getBytes();
                arduino.sendSerialData(data);
            }
        }).start();
    }
}
